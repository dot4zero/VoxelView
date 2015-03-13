using System.Drawing;
using System.Xml;
using WeifenLuo.WinFormsUI.Docking;
using System;

namespace Common.Docking
{
	/// <summary>Док</summary>
	public partial class SafeDockContent : DockContent, IStorable
	{
		#region static
		/// <summary>
		/// Содание PersistString по имени типа дока и аргументам.
		/// </summary>
		/// <param name="typeName"></param>
		/// <param name="args"></param>
		/// <returns></returns>
		public static string PersistStringCreate(string typeName, string args)
		{
			return string.Format("{0}{1}{2}", typeName, Separator, args);
		}
		/// <summary>
		/// Разбиение PersistString на имя типа дока и аргументы.
		/// </summary>
		/// <param name="persistString"></param>
		/// <param name="typeName"></param>
		/// <param name="args"></param>
		public static void PersistStringSplit(string persistString, out string typeName, out string args)
		{
			var arr = persistString.Split(Separator);
			typeName = (arr.Length > 0) ? arr[0] : string.Empty;
			args = (arr.Length > 1) ? arr[1] : string.Empty;
		} 
		#endregion

		#region Конструктор
		public SafeDockContent()
		{
			InitializeComponent();
			this.DockAreas = DockingAreas.Anywhere;
			this.ShowHint = DockingState.Document;
			this.Args = string.Empty;
		}
		#endregion

		#region Свойства

		#region PersistString
		/// <summary>Кодовая строка (тип дока и аргументы)</summary>
		public string PersistString
		{
			get { return this.GetPersistString(); }
		}

		/// <summary>Разделитель между типом панели и заголовком для PersistString</summary>
		private const char Separator = '/';

		protected override string GetPersistString()
		{
			return PersistStringCreate(this.TypeName, this.Args);
		}
		#endregion

		/// <summary>Док-панель</summary>
		public new SafeDockPanel DockPanel
		{
			get { return (SafeDockPanel)base.DockPanel; }
		}
		/// <summary>Значок дока</summary>
		public Image Image
		{
			set { this.SetImage(value); }
		}
		/// <summary>Тип дока</summary>
		public string TypeName
		{
			get { return this.GetType().Name; }
		}
		/// <summary>Аргументы</summary>
		public string Args { get; set; }

		public bool IsMy(string typeName, string args)
		{
			return this.TypeName == typeName && this.Args == args;
		}
		#endregion

		#region ToggleVisible
		/// <summary>Переключатель видимости: если не видим, то становится видимым, и наоборот.</summary>
		public void ToggleVisible(SafeDockPanel dockPanel)
		{
			if (this.IsHidden || !this.Visible)
			{
				if (this.Width == 0 || this.Height == 0)
				{
					this.Size = this.DefaultSize;
				}
				this.Show(dockPanel);
			}
			else
			{
				this.Hide();
			}
		} 
		#endregion

		#region OnFormClosing
		protected override void OnFormClosing(System.Windows.Forms.FormClosingEventArgs e)
		{
			if (this.DockPanel != null)
			{
				this.DockPanel.SaveDock(this);
			}
			base.OnFormClosing(e);
		} 
		#endregion

		#region SetImage
		/// <summary>
		/// Установка картинки на табе дока
		/// </summary>
		/// <param name="image"></param>
		[System.Security.Permissions.PermissionSet(System.Security.Permissions.SecurityAction.Demand, Name = "FullTrust")]
		private void SetImage(Image image)
		{
			if (image == null) return;

			using (var b = image.Clone() as Bitmap)
			{
				//IntPtr hIcon = b.GetHicon();
				//using (Icon newIcon = Icon.FromHandle(hIcon))
				//{
				//  this.Icon = newIcon;
				//}
				if (b != null) 
					this.Icon = Icon.FromHandle(b.GetHicon());
			}
		}

		#endregion

		#region IStorable Members

		public virtual string GetNameSection()
		{
			return this.GetType().Name;
		}

		public virtual void SaveXml(XmlElement xmlParent)
		{
		}

		public virtual void LoadXml(XmlElement xmlParent)
		{
		}

		#endregion

		#region Обновление содержимого дока

		/// <summary>Возвращает true, если док видим и его можно обновлять.</summary>
		///<remarks>Поддержка отложенного обновления.</remarks>
		public virtual bool IsCanUpdate
		{
			get { return this.GetVisible(); }
		}

		/// <summary>Обновление содержимого дока (с поддержкой отложенного обновления).</summary>
		///<remarks>Поддержка отложенного обновления:
		///Если доку требуется отложенное обновление (т.е. обновлять только тогда,
		///когда он видим и не обновлять, если он не видим),
		///тогда перекройте метод UpdateContentAlways().</remarks>
		public void UpdateContent()
		{
			if (this.IsCanUpdate)
			{
				this.UpdateContentAlways();
			}
		}
		/// <summary>Обновление содержимого дока (без поддержки отложенного обновления).</summary>
		///<remarks>Обновляется всегда (и когда видим, и когда не видим).</remarks>
		protected virtual void UpdateContentAlways()
		{
		}

		[Obsolete("НЕ ПОЛЬЗУЙТЕСЬ")]
		public new void Update()
		{
			//
		}
	

		protected override void OnVisibleChanged(System.EventArgs e)
		{
			base.OnVisibleChanged(e);
			if (this.IsDestroyed) return;

			//Поддержка отложенного обновления
			this.UpdateContent();
		}

		internal Rectangle _floatPaneBounds = Rectangle.Empty;
		protected override void OnDockStateChanged(System.EventArgs e)
		{
			base.OnDockStateChanged(e);
			if (this.IsDestroyed) return;

			if (this.FloatPane != null && this.FloatPane.FloatWindow != null && _floatPaneBounds != Rectangle.Empty)
			{
				this.FloatPane.FloatWindow.Bounds = _floatPaneBounds;
			}

			//Поддержка отложенного обновления
			this.UpdateContent();
		}

		private bool _collapsing = false;
		protected override void OnResize(System.EventArgs e)
		{
			base.OnResize(e);
			if (this.IsDestroyed) return;
			
			//Надо отсечь простой ресайз - не обновляться!
			//Обновляться только на разворачивание после полного сворачивания формы.
			//Док свернули?
			if (this.ClientSize.Width == 0 || this.ClientSize.Height == 0)
			{
				//да => ставим флаг, что было свертывание
				_collapsing = true;
				return;
			}
			//Если было свертывание, то сейчас надо обновиться
			if (_collapsing)
			{
				//Поддержка отложенного обновления
				this.UpdateContent();
				_collapsing = false;
			}
		}
		private bool GetVisible()
		{
			if (this.IsDestroyed) return false;
			if (this.ClientRectangle.Width == 0 || this.ClientRectangle.Height == 0) return false;

			return (this.VisibleState == DockState.Hidden || this.VisibleState == DockState.Unknown)
				? false
				: this.Visible;
		}
		private bool IsDestroyed
		{
			get
			{
				return this.Disposing || this.IsDisposed || this.DockPanel == null || this.DockPanel._clearing;
			}
		}
		#endregion
	}
}
