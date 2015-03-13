using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using WeifenLuo.WinFormsUI.Docking;

namespace Common.Docking
{
	/// <summary>
	/// Док-панель
	/// </summary>
	public sealed class SafeDockPanel : DockPanel, IStorable
	{
		/// <summary>Событие, возникающее при смене сообщения.</summary>
		public event MessageChangedEventHandler MessageChanged;

		/// <summary>Словарь фабрик доков</summary>
		private readonly Dictionary<string, CreateDock> _creator = new Dictionary<string, CreateDock>();
		/// <summary>Словарь xml-секций доков</summary>
		private readonly Dictionary<string, XmlElement> _xmlDocks = new Dictionary<string, XmlElement>();
		/// <summary>Разделитель между типом панели и заголовком для PersistString</summary>
		private readonly XmlDocument _xmlDoc = new XmlDocument();
		/// <summary>Флаг очистки докпанели</summary>
		internal bool _clearing;

		#region Конструктор
		public SafeDockPanel()
		{
			this.Dock = DockStyle.Fill;
			this.DocumentStyle = DocumentStyle.DockingWindow;
			this.ShowDocumentIcon = true;
		} 
		#endregion
		#region Dispose
		protected override void Dispose(bool disposing)
		{
			_clearing = true;
			base.Dispose(disposing);
		} 
		#endregion

		#region Регистрация делегата создания дока заданного типа
		/// <summary>Регистрация делегата создания дока заданного типа.</summary>
		public CreateDock this[Type type]
		{
			get { return (type != null) ? this[type.Name] : null; }
			set
			{
				if (type != null)
				{
					var isFind = false;
					var basetype = type.BaseType;
					while (basetype != typeof(object))
					{
						if (basetype == typeof(SafeDockContent))
						{
							isFind = true;
							break;
						}
						basetype = basetype.BaseType;
					}
					Debug.Assert(isFind, string.Format("Тип, регистрируемый в док-панели, должен наследовать SafeDockContent! Ош {0}", type.Name));
					this[type.Name] = value;
				}
			}
		}
		/// <summary>Регистрация делегата создания дока заданного названия типа.</summary>
		public CreateDock this[string typeNameDock]
		{
			get
			{
				CreateDock createDock;
				return _creator.TryGetValue(typeNameDock, out createDock) ? createDock : null;
			}
			set { _creator[typeNameDock] = value; }
		} 
		#endregion

		#region Clear

		public void Clear()
		{
			_clearing = true;
			this.CloseAll();
			_clearing = false;
		} 
		private void CloseAll()
		{
			this.SuspendLayout(true);
			this.CloseAllContents();
			this.ResumeLayout(true, true);
		}
		private void CloseAllContents()
		{
			if (this.DocumentStyle == DocumentStyle.SystemMdi)
			{
				//foreach (Form form in MdiChildren)
				//  form.Close();
			}
			else
			{
				for (var index = this.Contents.Count - 1; index >= 0; index--)
				{
					var content = this.Contents[index];
					content.DockHandler.Close();
				}
			}
		}
		
		#endregion

		#region SaveDocksToString/LoadDocksFromString
		/// <summary>
		/// Сохранение состояния контролов в виде xml-строки.
		/// </summary>
		public string SaveDocksToString()
		{
			//Сохранение доков в словаре
			this.SaveDocks();

			//Сохранение словаря
			var xmlParent = _xmlDoc.CreateElement("Docks");
			foreach (var kv in _xmlDocks)
			{
				xmlParent.AppendChild(kv.Value);
			}
			return xmlParent.InnerXml;
		}
		/// <summary>
		/// Сохраненеи всех открытых доков в словаре.
		/// </summary>
		private void SaveDocks()
		{
			_xmlDocks.Clear();
			for (var i = 0; i < this.Contents.Count; i++)
			{
				var dock = this.Contents[i] as SafeDockContent;
				if (dock == null) continue;

				var xmlParent = _xmlDoc.CreateElement(string.Format("Dock{0}", i));
				_xmlDocks[dock.PersistString] = xmlParent;

				//Сохраняем свойства дока
				this.SaveDock(dock, xmlParent);
			}
		}
		/// <summary>
		/// Загрузка состояния контролов из xml-строки.
		/// </summary>
		private void LoadDocksFromString(string controlsInnerXmlString)
		{
			//Восстановление словаря xml-доков
			_xmlDocks.Clear();
			var xmlControls = IOxml.FromString(controlsInnerXmlString);
			if (xmlControls != null)
			{
				foreach (var xmlControl in xmlControls.ChildNodes)
				{
					var xmlParent = xmlControl as XmlElement;
					if (xmlParent != null)
					{
						var persist = IOxml.ReadString(xmlParent, "persist");
						if (!string.IsNullOrEmpty(persist))
						{
							_xmlDocks[persist] = xmlParent;
						}
					}
				}
			}
		}
		#endregion
		
		#region SaveToString/LoadFromString
		/// <summary>
		/// Сохранение конфигурации dockPanel'и в виде строки
		/// </summary>
		private string SaveToString()
		{
			using (var stream = new MemoryStream())
			{
				this.SaveAsXml(stream, Encoding.UTF8, true);
				using (var sr = new StreamReader(stream))
				{
					stream.Position = 0;
					var result = sr.ReadToEnd();
					//Уберем вот это:
					//<!-- DockPanel configuration file. Author: Weifen Luo, all rights reserved. -->
					//<!-- !!! AUTOMATICALLY GENERATED FILE. DO NOT MODIFY !!! -->
					result = result.Remove(0, result.IndexOf("<DockPanel"));
					return result;
				}
			}
		}
		/// <summary>
		/// Загрузка конфигурации dockPanel'и из строки
		/// </summary>
		/// <param name="s"></param>
		private void LoadFromString(string s)
		{
			using (var stream = new MemoryStream(s.Length))
			{
				using (var sw = new StreamWriter(stream))
				{
					sw.Write(s);
					sw.Flush();
					stream.Position = 0;
					try
					{
						this.SuspendLayout(true);

						var contents = new IDockContent[this.Contents.Count];
						this.Contents.CopyTo(contents, 0);

						//Если у докпанели есть доки, то очистить докпанель
						foreach (var dc in contents)
						{
							dc.DockHandler.DockPanel = null;
						}

						this.LoadFromXml(stream, OnDeserializeDockContent);

						//Если у докпанели были доки, то возвращаем их
						foreach (var dc in contents)
						{
							dc.DockHandler.DockPanel = this;
						}

						this.ResumeLayout(true, true);
					}
					catch (Exception err)
					{
						MessageBox.Show(
							string.Format(CultureInfo.CurrentCulture, "Ош десериализации dock-панели: {0}", err.Message),
							Application.ProductName);
					}
				}
			}
		}
		private IDockContent OnDeserializeDockContent(string persistString)
		{
			string typeName;
			string args;
			SafeDockContent.PersistStringSplit(persistString, out typeName, out args);

			//Сначала проверяем есть ли уже такой док?
			var result = this.GetDock(typeName, args);
			if (result != null)
			{
				//Такой док уже есть => второго не создаем
				return null;
			}

			//Нет такого => создаем
			result = this.CreateDock(typeName, args);
			if (result != null)
			{
				this.FireMessageChanged(string.Format(CultureInfo.CurrentCulture, "Создание вида: {0}", result.TabText));
			}
			return result;
		} 
		#endregion

		#region CreateDock
		private SafeDockContent CreateDock(string typeName, string args)
		{
			if (string.IsNullOrEmpty(typeName)) return null;

			var createDock = this[typeName];
			if (createDock == null) return null;

			var dock = createDock(args);
			if (dock == null) return null;
			dock.Args = args;

			XmlElement xmlParent;
			if (_xmlDocks.TryGetValue(dock.PersistString, out xmlParent))
			{
				this.LoadDock(dock, xmlParent);
			}

			return dock;
		}
		
		#endregion

		#region SaveDock/LoadDock
		internal void SaveDock(SafeDockContent dock)
		{
			//При очистке докпанели доки не сохраняются!
			if (_clearing) return;

			XmlElement xmlParent;
			if (!_xmlDocks.TryGetValue(dock.PersistString, out xmlParent))
			{
				xmlParent = _xmlDoc.CreateElement(string.Format("Dock{0}", this.Contents.Count));
				_xmlDocks[dock.PersistString] = xmlParent;
			}

			//Сохраняем свойства дока
			this.SaveDock(dock, xmlParent);
		} 

		internal void SaveDock(SafeDockContent dock, XmlElement xmlParent)
		{
			//Сохраняем свойства дока
			IOxml.Write(xmlParent, "persist", dock.PersistString);
			IOxml.WriteEnum(xmlParent, "state", dock.VisibleState);
			if (dock.FloatPane != null && dock.FloatPane.FloatWindow != null)
			{
				IOxml.Write(xmlParent, "bounds", dock.FloatPane.FloatWindow.Bounds);
			}
			//TODO: сохранить др. свойства дока

			//Сохраняем содержимое дока
			dock.SaveXml(xmlParent);
		}
		internal void LoadDock(SafeDockContent dock, XmlElement xmlParent)
		{
			//Восстанавливаем содержимое дока
			dock.LoadXml(xmlParent);

			var state = IOxml.ReadEnum(xmlParent, "state", dock.ShowHint);
			if (dock.IsDockStateValid(state))
			{
				dock.ShowHint = state;
			}
			dock._floatPaneBounds = IOxml.ReadRectangle(xmlParent, "bounds");
		}
		#endregion

		#region Итератор по докам заданного типа, включая наследников - Docks
		/// <summary>
		/// Итератор по докам заданного типа, включая наследников.
		/// </summary>
		/// <typeparam name="T">Любой интефейс или тип-наследник SafeDockContent</typeparam>
		/// <returns></returns>
		public IEnumerable<T> Docks<T>() //where T : SafeDockContent
		{
			var contents = new IDockContent[this.Contents.Count];
			this.Contents.CopyTo(contents, 0);

			foreach (var dock in contents)
			{
				if (dock is T)
				{
					yield return (T)dock;
				}
			}
		}
		#endregion

		#region GetDock...
		/// <summary>
		/// Возвращает док строго по заданному имени типа и аргументам.
		/// </summary>
		/// <param name="typeName"></param>
		/// <param name="args"></param>
		/// <returns></returns>
		public SafeDockContent GetDock(string typeName, string args)
		{
			var contents = new IDockContent[this.Contents.Count];
			this.Contents.CopyTo(contents, 0);

			foreach (var dc in contents)
			{
				var dock = dc as SafeDockContent;
				if (dock != null && dock.IsMy(typeName, args))
				{
					return dock;
				}
			}
			return null;
		}
		/// <summary>
		/// Возвращает док строго по заданному имени типа.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="args"></param>
		/// <returns></returns>
		public T GetDock<T>() where T : SafeDockContent
		{
			return this.GetDock<T>(string.Empty);
		}
		/// <summary>
		/// Возвращает док строго по заданному имени типа и аргументам.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="args"></param>
		/// <returns></returns>
		public T GetDock<T>(string args) where T : SafeDockContent
		{
			var contents = new IDockContent[this.Contents.Count];
			this.Contents.CopyTo(contents, 0);

			foreach (var dc in contents)
			{
				var dock = dc as SafeDockContent;
				if (dock != null && dock.IsMy(typeof(T).Name, args))
				{
					return (T)dock;
				}
			}
			return null;
		}
		#endregion

		#region ShowDock...
		public void ShowDocument(Control control)
		{
			if (control == null) return;

			var dock = control.Parent as SafeDockContent;
			if (dock == null)
			{
				dock = new SafeDockContent
				{
					DockAreas = DockingAreas.Document,
					ShowHint = DockingState.Document
				};
			}
			control.Parent = dock;
			control.Dock = DockStyle.Fill;
			dock.Show(this);
		}
		/// <summary>
		/// Показывает заданный док.
		/// </summary>
		/// <param name="dock"></param>
		public void ShowDock(SafeDockContent dock)
		{
			if (dock != null)
				dock.Show(this);
		}
		/// <summary>
		/// Находит док по заданному имени типа и аргументам и показывает
		/// (если нет такого, то создает).
		/// </summary>
		/// <param name="typeName"></param>
		/// <param name="args"></param>
		/// <returns></returns>
		public SafeDockContent ShowDock(string typeName, string args)
		{
			var dock = this.GetDock(typeName, args) ?? this.CreateDock(typeName, args);
			if (dock != null)
			{
				dock.Args = args;
				dock.Show(this);
			}
			return dock;
		}
		/// <summary>
		/// Находит док по заданной persistString и показывает
		/// (если нет такого, то создает).
		/// </summary>
		/// <param name="persistString"></param>
		/// <returns></returns>
		public SafeDockContent ShowDock(string persistString)
		{
			string typeName;
			string args;
			SafeDockContent.PersistStringSplit(persistString, out typeName, out args);
			var dock = this.GetDock(typeName, args) ?? this.CreateDock(typeName, args);
			if (dock != null)
			{
				dock.Args = args;
				dock.Show(this);
			}
			return dock;
		}
		/// <summary>
		/// Находит и показывает док заданного типа с пустыми аргументами
		/// (если нет такого, то создает).
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		public T ShowDock<T>() where T : SafeDockContent
		{
			return this.ShowDock<T>(string.Empty);
		}
		/// <summary>
		/// Находит и показывает док заданного типа с заданными аргументами
		/// (если нет такого, то создает).
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="args"></param>
		/// <returns></returns>
		public T ShowDock<T>(string args) where T : SafeDockContent
		{
			var dock = this.GetDock<T>(args) ?? this.CreateDock(typeof(T).Name, args);
			if (dock != null)
			{
				dock.Args = args;
				dock.Show(this);
			}
			return (T)dock;
		} 
		#endregion
	
		#region CloseDock
		/// <summary>
		/// Закрывает док.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="args"></param>
		public void CloseDock<T>(string args) where T : SafeDockContent
		{
			var dock = this.GetDock<T>(args);
			if (dock != null)
				dock.Close();
		}
		public void CloseDock(string typeName, string args)
		{
			var dock = this.GetDock(typeName, args);
			if (dock != null)
				dock.Close();
		}
		#endregion

		#region GetActiveDock
		/// <summary>
		/// Возвращает активный док из семейства доков заданного типа.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		public T GetActiveDock<T>() where T : SafeDockContent
		{
			T result = null;
			foreach (var dock in this.Docks<T>())
			{
				result = dock;
				if (dock.IsActivated)
				{
					break;
				}
			}
			return result;
		} 
		#endregion

		#region FireMessageChanged
		private void FireMessageChanged(string msg)
		{
			var handler = MessageChanged;
			if (handler != null)
			{
				handler(msg);
			}
		}
		#endregion

		#region IStorable Members

		private const string SectionDocks = "Docks";
		private const string SectionDockPanel = "DockPanelInnerXml";

		public string GetNameSection()
		{
			return "SafeDockPanel";
		}

		public void SaveXml(XmlElement xmlParent)
		{
			var xmlSmartDockPanel = IOxml.CreateSection(xmlParent, this.GetNameSection());

			//1. Сохранение доков в словаре, а затем словаря в секции родителя
			var xmlControls = IOxml.CreateSection(xmlSmartDockPanel, SectionDocks);
			xmlControls.InnerXml = this.SaveDocksToString();

			//2. Сохранение докпанели
			var xmlDockPanel = IOxml.CreateSection(xmlSmartDockPanel, SectionDockPanel);
			xmlDockPanel.InnerXml = this.SaveToString();
		}

		public void LoadXml(XmlElement xmlParent)
		{
			var xmlSmartDockPanel = IOxml.GetSection(xmlParent, this.GetNameSection());
			if (xmlSmartDockPanel != null)
			{
				//1. Восстановление словаря xml-доков
				var xmlControls = IOxml.GetSection(xmlSmartDockPanel, SectionDocks);
				if (xmlControls != null)
				{
					this.LoadDocksFromString(xmlControls.InnerXml);
				}

				//2. Восстановление докпанели и доков (в делегате OnDeserializeDockContent)
				var xmlDockPanel = IOxml.GetSection(xmlSmartDockPanel, SectionDockPanel);
				if (xmlDockPanel != null)
				{
					this.LoadFromString(xmlDockPanel.InnerXml);
				}
			}
		}
		#endregion

		/// <summary>Обновить содержимое всех открытых и видимых доков.</summary>
		public void UpdateContents()
		{
			foreach (var dock in this.Docks<SafeDockContent>())
			{
				dock.UpdateContent();
			}
		}
	}
}
