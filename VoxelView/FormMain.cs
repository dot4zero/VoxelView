using System;
using System.Drawing;
using System.Windows.Forms;
using Common;
using System.IO;
using System.Xml;

namespace VoxelView
{
	public delegate void EmptyEventHandler();

	public partial class FormMain : Form
	{
		private static readonly ApplicationContext _applicationContext = new ApplicationContext();

		private static FormMain ActiveMainForm
		{
			get { return (FormMain)_applicationContext.MainForm; }
		}

		public static VoxelViewDockContent ActiveViewDockContent
		{
			get { return ActiveMainForm.dockPanel.GetActiveDock<VoxelViewDockContent>(); }
		}

		public static PropertiesDockContent PropertiesDockContent
		{
			get { return ActiveMainForm.dockPanel.GetActiveDock<PropertiesDockContent>(); }
		}

		public static DiagramsDockContent DiagramsDockContent
		{
			get { return ActiveMainForm.dockPanel.GetDock<DiagramsDockContent>(); }
		}

		public static MaterialsDockContent MaterialsDockContent
		{
			get { return ActiveMainForm.dockPanel.GetDock<MaterialsDockContent>(); }
		}

		public FormMain()
		{
			InitializeComponent();

			dockPanel[typeof(PropertiesDockContent)] = args => new PropertiesDockContent();
			dockPanel[typeof(MaterialsDockContent)] = args => new MaterialsDockContent();
			dockPanel[typeof(VoxelViewDockContent)] = args => new VoxelViewDockContent();
			dockPanel[typeof(DiagramsDockContent)] = args => new DiagramsDockContent();
		}

		public static void SetStatus(string text)
		{
			ActiveMainForm.statusLabelInfo.Text = text;
		}

		public static void SetProgress(int progress)
		{
			ActiveMainForm.progreesBar.Value = progress;
		}

		public static void EnableProgress()
		{
			ActiveMainForm.statusLabelInfo.Visible = false;
			ActiveMainForm.statusLabelWait.Visible = true;
			ActiveMainForm.progreesBar.Value = 0;
			ActiveMainForm.progreesBar.Visible = true;
		}

		public static void DisableProgress()
		{
			ActiveMainForm.progreesBar.Visible = false;
			ActiveMainForm.statusLabelWait.Visible = false;
			ActiveMainForm.statusLabelInfo.Visible = true;
		}

		private void miOpenFileVxb_Click(object sender, EventArgs e)
		{
			using (var dlg = new OpenFileDialog())
			{
				dlg.RestoreDirectory = true;
				dlg.Filter = "Файлы геометрии (*.vxb)|*.vxb|Все файлы (*.*)|*.*";

				if (dlg.ShowDialog() == DialogResult.OK)
				{
					this.UseWaitCursor = true;
					Application.DoEvents();

					var fileName = Path.GetFileName(dlg.FileName);
					var voxelViewControl = dockPanel.ShowDock<VoxelViewDockContent>(dlg.FileName);
					voxelViewControl.TabText = fileName;

					try
					{
						voxelViewControl.InitVoxelBox(dlg.FileName);
						dockPanel.ShowDock<PropertiesDockContent>().UpdateData();
						if (MaterialsDockContent != null)
							MaterialsDockContent.UpdateData();
					}
					catch (Exception ex)
					{
						MessageBox.Show(ex.Message, Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
						voxelViewControl.Close();
					}
					finally
					{
						this.UseWaitCursor = false;
					}
				}
			}
		}

		private void miOpenFileBin_Click(object sender, EventArgs e)
		{
			using (var dlg = new OpenFileDialog())
			{
				dlg.RestoreDirectory = true;
				dlg.Filter = "Файлы результатов (*.bin)|*.bin|Все файлы (*.*)|*.*";

				if (dlg.ShowDialog() == DialogResult.OK)
				{
					this.UseWaitCursor = true;
					Application.DoEvents();

					var voxelViewControl = dockPanel.GetActiveDock<VoxelViewDockContent>();
					voxelViewControl.TabText = voxelViewControl.TabText.Split(':')[0].Trim() +
						" : " + Path.GetFileName(Path.GetFileName(dlg.FileName));

					try
					{
						voxelViewControl.InitVoxelRes(dlg.FileName);
						dockPanel.ShowDock<PropertiesDockContent>().UpdateData();
						if (DiagramsDockContent != null)
							DiagramsDockContent.UpdateData();

					}
					catch (Exception ex)
					{
						MessageBox.Show(ex.Message, Application.ProductName, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
					}
					finally
					{
						this.UseWaitCursor = false;
					}
				}
			}
		}

		#region miFile_DropDownOpened
		private void miFile_DropDownOpened(object sender, EventArgs e)
		{
			miOpenFileBin.Enabled = ActiveViewDockContent != null;
			miExport.Enabled = ActiveViewDockContent != null && ActiveViewDockContent.VoxelViewController.HasResult;
		}
		#endregion

		#region miOptions_DropDownOpened
		private void miOptions_DropDownOpened(object sender, EventArgs e)
		{
			miMaterials.Checked = MaterialsDockContent != null;
			miDiagrams.Checked = DiagramsDockContent != null;
		}
		#endregion

		#region miFileExit_Click
		private void miFileExit_Click(object sender, EventArgs e)
		{
			Close();
		}
		#endregion

		#region OnFormClosing
		protected override void OnFormClosing(FormClosingEventArgs e)
		{
			if (e.CloseReason == CloseReason.UserClosing)
			{
				foreach (var dock in dockPanel.Docks<VoxelViewDockContent>())
					dock.Close();

				SaveConfig();
				SaveColorMap();
			}

			base.OnFormClosing(e);
		}
		#endregion

		#region LoadConfig
		internal static void LoadConfig(FormMain mainForm)
		{
			_applicationContext.MainForm = mainForm;

			//var myDocuments = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
			//var dirname = Path.Combine(myDocuments, "VoxelView");
			//if (!Directory.Exists(dirname))
			//    Directory.CreateDirectory(dirname);
			//var cfgFile = Path.Combine(dirname, "VoxelView.cfg");

			var cfgFile = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "VoxelView.cfg");

			if (File.Exists(cfgFile))
			{
				try
				{
					var xmlDoc = new XmlDocument();
					xmlDoc.Load(cfgFile);
					var xmlRoot = xmlDoc.DocumentElement;
					if (xmlRoot != null && xmlRoot.Name == "Configuration")
						mainForm.LoadConfig(xmlRoot);
				}
				catch
				{
					File.Delete(cfgFile);
				}
			}
		}
		#endregion

		#region LoadConfig(XmlElement xmlParent)
		private void LoadConfig(XmlElement xmlParent)
		{
			var xmlMainForm = IOxml.GetSection(xmlParent, "MainForm");
			if (xmlMainForm != null)
			{
				//Геометрия формы
				LoadGeometryForm(xmlMainForm);

				//Dock-панель
				dockPanel.LoadXml(xmlMainForm);
			}
		}
		#endregion

		#region LoadGeometryForm
		private void LoadGeometryForm(XmlNode xmlParent)
		{
			var xmlMain = IOxml.GetSection(xmlParent, "Main");
			if (xmlMain != null)
			{
				WindowState = IOxml.ReadEnum<FormWindowState>(xmlMain, "WindowState");
				var bounds = IOxml.ReadRectangle(xmlMain, "Bounds");
				if (bounds != Rectangle.Empty)
					SetBounds(bounds.X, bounds.Y, bounds.Width, bounds.Height);
			}
		}
		#endregion

		#region SaveConfig
		internal static void SaveConfig()
		{
			//var myDocuments = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
			//var dirname = Path.Combine(myDocuments, "VoxelView");
			//if (!Directory.Exists(dirname))
			//    Directory.CreateDirectory(dirname);
			//var cfgFile = Path.Combine(dirname, "VoxelView.cfg");

			var cfgFile = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "VoxelView.cfg");

			var xmlDoc = new XmlDocument();
			var xmlRoot = xmlDoc.CreateElement("Configuration");
			xmlDoc.AppendChild(xmlRoot);

			// Сохранить геометрию главной формы
			var form = (FormMain)_applicationContext.MainForm;
			if (form != null)
				form.SaveConfig(xmlRoot);

			IOxml.WriteDocToFile(xmlDoc, cfgFile);
		}
		#endregion

		#region SaveConfig(XmlElement xmlParent)
		private void SaveConfig(XmlElement xmlParent)
		{
			var xmlMainForm = IOxml.CreateSection(xmlParent, "MainForm");

			//Геометрия формы
			SaveGeometryForm(xmlMainForm);

			//Dock-панель
			dockPanel.SaveXml(xmlMainForm);
		}
		#endregion

		#region SaveGeometryForm
		private void SaveGeometryForm(XmlElement xmlParent)
		{
			var xmlMain = IOxml.CreateSection(xmlParent, "Main");
			IOxml.Write(xmlMain, "WindowState", WindowState.ToString());
			IOxml.Write(xmlMain, "Bounds", Bounds);
		}
		#endregion

		#region LoadColorMap
		internal static bool LoadColorMap()
		{
			//var myDocuments = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
			//var dirname = Path.Combine(myDocuments, "VoxelView");
			//if (!Directory.Exists(dirname))
			//    Directory.CreateDirectory(dirname);
			//var colorMapFileName = Path.Combine(dirname, _colorMapFileName);

			var colorMapFileName = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "ColorMap.xml");

			if (File.Exists(colorMapFileName))
			{
				try
				{
					var xmlDoc = new XmlDocument();
					xmlDoc.Load(colorMapFileName);
					var xmlRoot = xmlDoc.DocumentElement;
					if (xmlRoot != null)
					{
						foreach (XmlAttribute atr in xmlRoot.Attributes)
						{
							int material;
							int color;
							Int32.TryParse(atr.Name.TrimStart('m'), out material);
							Int32.TryParse(atr.Value, out color);
							VoxelViewController.SetColorValue(material, color);
						}
					}
				}
				catch (Exception e)
				{
					if (MessageBox.Show(String.Format("{0}\nПродолжить открытие приложения?", e.Message),
						"Ошибка чтения палитры цветов для материалов!", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation) == DialogResult.No)
					{
						return false;
					}

					File.Copy(colorMapFileName, colorMapFileName + ".bak");
				}
			}

			return true;
		}
		#endregion

		#region SaveColorMap
		internal static void SaveColorMap()
		{
			//var myDocuments = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
			//var dirname = Path.Combine(myDocuments, "VoxelView");
			//if (!Directory.Exists(dirname))
			//    Directory.CreateDirectory(dirname);
			//var colorMapFileName = Path.Combine(dirname, _colorMapFileName);

			var colorMapFileName = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "ColorMap.xml");

			var xmlDoc = new XmlDocument();
			var xmlRoot = xmlDoc.CreateElement("ColorMap");
			xmlDoc.AppendChild(xmlRoot);

			var colorMap = VoxelViewController.GetColorMap();
			foreach (var material in colorMap.Keys)
				IOxml.Write(xmlRoot, "m" + material.ToString(), colorMap[material].ToString());

			IOxml.WriteDocToFile(xmlDoc, colorMapFileName);
		}
		#endregion

		private void miMaterials_CheckedChanged(object sender, EventArgs e)
		{
			if (miMaterials.Checked)
			{
				dockPanel.ShowDock<MaterialsDockContent>().UpdateData();
			}
			else
			{
				MaterialsDockContent.Close();
			}
		}

		private void miDiagrams_CheckedChanged(object sender, EventArgs e)
		{
			if (miDiagrams.Checked)
			{
				dockPanel.ShowDock<DiagramsDockContent>().UpdateData();
			}
			else
			{
				DiagramsDockContent.Close();
			}
		}

		private void tsExport1_Click(object sender, EventArgs e)
		{
			var activeViewControl = ActiveViewDockContent;
			if (activeViewControl != null)
				activeViewControl.Export(1);
		}

		private void tsExport2_Click(object sender, EventArgs e)
		{
			var activeViewControl = ActiveViewDockContent;
			if (activeViewControl != null)
				activeViewControl.Export(2);
		}

		private void dockPanel_ActiveDocumentChanged(object sender, EventArgs e)
		{
			if (PropertiesDockContent != null)
				PropertiesDockContent.UpdateData();
			if (DiagramsDockContent != null)
				DiagramsDockContent.UpdateData();
			if (MaterialsDockContent != null)
				MaterialsDockContent.UpdateData();
		}
	}
}
