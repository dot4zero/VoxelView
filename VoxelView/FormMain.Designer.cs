namespace VoxelView
{
	partial class FormMain
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			WeifenLuo.WinFormsUI.Docking.DockPanelSkin dockPanelSkin1 = new WeifenLuo.WinFormsUI.Docking.DockPanelSkin();
			WeifenLuo.WinFormsUI.Docking.AutoHideStripSkin autoHideStripSkin1 = new WeifenLuo.WinFormsUI.Docking.AutoHideStripSkin();
			WeifenLuo.WinFormsUI.Docking.DockPanelGradient dockPanelGradient1 = new WeifenLuo.WinFormsUI.Docking.DockPanelGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient1 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.DockPaneStripSkin dockPaneStripSkin1 = new WeifenLuo.WinFormsUI.Docking.DockPaneStripSkin();
			WeifenLuo.WinFormsUI.Docking.DockPaneStripGradient dockPaneStripGradient1 = new WeifenLuo.WinFormsUI.Docking.DockPaneStripGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient2 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.DockPanelGradient dockPanelGradient2 = new WeifenLuo.WinFormsUI.Docking.DockPanelGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient3 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.DockPaneStripToolWindowGradient dockPaneStripToolWindowGradient1 = new WeifenLuo.WinFormsUI.Docking.DockPaneStripToolWindowGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient4 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient5 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.DockPanelGradient dockPanelGradient3 = new WeifenLuo.WinFormsUI.Docking.DockPanelGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient6 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient7 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.miFile = new System.Windows.Forms.ToolStripMenuItem();
			this.miOpenFileVxb = new System.Windows.Forms.ToolStripMenuItem();
			this.miOpenFileBin = new System.Windows.Forms.ToolStripMenuItem();
			this.miExport = new System.Windows.Forms.ToolStripMenuItem();
			this.tsExport1 = new System.Windows.Forms.ToolStripMenuItem();
			this.tsExport2 = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.miFileExit = new System.Windows.Forms.ToolStripMenuItem();
			this.miOptions = new System.Windows.Forms.ToolStripMenuItem();
			this.miMaterials = new System.Windows.Forms.ToolStripMenuItem();
			this.miDiagrams = new System.Windows.Forms.ToolStripMenuItem();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.statusLabelInfo = new System.Windows.Forms.ToolStripStatusLabel();
			this.statusLabelWait = new System.Windows.Forms.ToolStripStatusLabel();
			this.progreesBar = new System.Windows.Forms.ToolStripProgressBar();
			this.dockPanel = new Common.Docking.SafeDockPanel();
			this.menuStrip1.SuspendLayout();
			this.statusStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miFile,
            this.miOptions});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
			this.menuStrip1.Size = new System.Drawing.Size(942, 24);
			this.menuStrip1.TabIndex = 1;
			this.menuStrip1.Text = "menuStrip";
			// 
			// miFile
			// 
			this.miFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miOpenFileVxb,
            this.miOpenFileBin,
            this.miExport,
            this.toolStripSeparator2,
            this.miFileExit});
			this.miFile.Name = "miFile";
			this.miFile.Size = new System.Drawing.Size(48, 20);
			this.miFile.Text = "Файл";
			this.miFile.DropDownOpened += new System.EventHandler(this.miFile_DropDownOpened);
			// 
			// miOpenFileVxb
			// 
			this.miOpenFileVxb.Name = "miOpenFileVxb";
			this.miOpenFileVxb.Size = new System.Drawing.Size(176, 22);
			this.miOpenFileVxb.Text = "Открыть vxb-файл";
			this.miOpenFileVxb.Click += new System.EventHandler(this.miOpenFileVxb_Click);
			// 
			// miOpenFileBin
			// 
			this.miOpenFileBin.Name = "miOpenFileBin";
			this.miOpenFileBin.Size = new System.Drawing.Size(176, 22);
			this.miOpenFileBin.Text = "Открыть bin-файл";
			this.miOpenFileBin.Click += new System.EventHandler(this.miOpenFileBin_Click);
			// 
			// miExport
			// 
			this.miExport.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsExport1,
            this.tsExport2});
			this.miExport.Enabled = false;
			this.miExport.Name = "miExport";
			this.miExport.Size = new System.Drawing.Size(176, 22);
			this.miExport.Text = "Экспорт";
			// 
			// tsExport1
			// 
			this.tsExport1.Name = "tsExport1";
			this.tsExport1.Size = new System.Drawing.Size(126, 22);
			this.tsExport1.Text = "Формат 1";
			this.tsExport1.Click += new System.EventHandler(this.tsExport1_Click);
			// 
			// tsExport2
			// 
			this.tsExport2.Name = "tsExport2";
			this.tsExport2.Size = new System.Drawing.Size(126, 22);
			this.tsExport2.Text = "Формат 2";
			this.tsExport2.Click += new System.EventHandler(this.tsExport2_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(173, 6);
			// 
			// miFileExit
			// 
			this.miFileExit.Name = "miFileExit";
			this.miFileExit.Size = new System.Drawing.Size(176, 22);
			this.miFileExit.Text = "Выход";
			this.miFileExit.Click += new System.EventHandler(this.miFileExit_Click);
			// 
			// miOptions
			// 
			this.miOptions.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miMaterials,
            this.miDiagrams});
			this.miOptions.Name = "miOptions";
			this.miOptions.Size = new System.Drawing.Size(59, 20);
			this.miOptions.Text = "Сервис";
			this.miOptions.DropDownOpened += new System.EventHandler(this.miOptions_DropDownOpened);
			// 
			// miMaterials
			// 
			this.miMaterials.CheckOnClick = true;
			this.miMaterials.Name = "miMaterials";
			this.miMaterials.Size = new System.Drawing.Size(193, 22);
			this.miMaterials.Text = "Редактор материалов";
			this.miMaterials.CheckedChanged += new System.EventHandler(this.miMaterials_CheckedChanged);
			// 
			// miDiagrams
			// 
			this.miDiagrams.CheckOnClick = true;
			this.miDiagrams.Name = "miDiagrams";
			this.miDiagrams.Size = new System.Drawing.Size(193, 22);
			this.miDiagrams.Text = "Диаграммы сечений";
			this.miDiagrams.CheckedChanged += new System.EventHandler(this.miDiagrams_CheckedChanged);
			// 
			// statusStrip1
			// 
			this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusLabelInfo,
            this.statusLabelWait,
            this.progreesBar});
			this.statusStrip1.Location = new System.Drawing.Point(0, 613);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(942, 22);
			this.statusStrip1.TabIndex = 7;
			// 
			// statusLabelInfo
			// 
			this.statusLabelInfo.Name = "statusLabelInfo";
			this.statusLabelInfo.Size = new System.Drawing.Size(927, 17);
			this.statusLabelInfo.Spring = true;
			this.statusLabelInfo.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// statusLabelWait
			// 
			this.statusLabelWait.Name = "statusLabelWait";
			this.statusLabelWait.Size = new System.Drawing.Size(157, 17);
			this.statusLabelWait.Text = "Построение изображения: ";
			this.statusLabelWait.Visible = false;
			// 
			// progreesBar
			// 
			this.progreesBar.Name = "progreesBar";
			this.progreesBar.Size = new System.Drawing.Size(100, 16);
			this.progreesBar.Step = 1;
			this.progreesBar.Visible = false;
			// 
			// dockPanel
			// 
			this.dockPanel.ActiveAutoHideContent = null;
			this.dockPanel.AutoSize = true;
			this.dockPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.dockPanel.DockBackColor = System.Drawing.SystemColors.Control;
			this.dockPanel.DocumentStyle = WeifenLuo.WinFormsUI.Docking.DocumentStyle.DockingWindow;
			this.dockPanel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.dockPanel.Location = new System.Drawing.Point(0, 24);
			this.dockPanel.Name = "dockPanel";
			this.dockPanel.ShowDocumentIcon = true;
			this.dockPanel.Size = new System.Drawing.Size(942, 589);
			dockPanelGradient1.EndColor = System.Drawing.SystemColors.ControlLight;
			dockPanelGradient1.StartColor = System.Drawing.SystemColors.ControlLight;
			autoHideStripSkin1.DockStripGradient = dockPanelGradient1;
			tabGradient1.EndColor = System.Drawing.SystemColors.Control;
			tabGradient1.StartColor = System.Drawing.SystemColors.Control;
			tabGradient1.TextColor = System.Drawing.SystemColors.ControlDarkDark;
			autoHideStripSkin1.TabGradient = tabGradient1;
			autoHideStripSkin1.TextFont = new System.Drawing.Font("Segoe UI", 9F);
			dockPanelSkin1.AutoHideStripSkin = autoHideStripSkin1;
			tabGradient2.EndColor = System.Drawing.SystemColors.ControlLightLight;
			tabGradient2.StartColor = System.Drawing.SystemColors.ControlLightLight;
			tabGradient2.TextColor = System.Drawing.SystemColors.ControlText;
			dockPaneStripGradient1.ActiveTabGradient = tabGradient2;
			dockPanelGradient2.EndColor = System.Drawing.SystemColors.Control;
			dockPanelGradient2.StartColor = System.Drawing.SystemColors.Control;
			dockPaneStripGradient1.DockStripGradient = dockPanelGradient2;
			tabGradient3.EndColor = System.Drawing.SystemColors.ControlLight;
			tabGradient3.StartColor = System.Drawing.SystemColors.ControlLight;
			tabGradient3.TextColor = System.Drawing.SystemColors.ControlText;
			dockPaneStripGradient1.InactiveTabGradient = tabGradient3;
			dockPaneStripSkin1.DocumentGradient = dockPaneStripGradient1;
			dockPaneStripSkin1.TextFont = new System.Drawing.Font("Segoe UI", 9F);
			tabGradient4.EndColor = System.Drawing.SystemColors.ActiveCaption;
			tabGradient4.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
			tabGradient4.StartColor = System.Drawing.SystemColors.GradientActiveCaption;
			tabGradient4.TextColor = System.Drawing.SystemColors.ActiveCaptionText;
			dockPaneStripToolWindowGradient1.ActiveCaptionGradient = tabGradient4;
			tabGradient5.EndColor = System.Drawing.SystemColors.Control;
			tabGradient5.StartColor = System.Drawing.SystemColors.Control;
			tabGradient5.TextColor = System.Drawing.SystemColors.ControlText;
			dockPaneStripToolWindowGradient1.ActiveTabGradient = tabGradient5;
			dockPanelGradient3.EndColor = System.Drawing.SystemColors.ControlLight;
			dockPanelGradient3.StartColor = System.Drawing.SystemColors.ControlLight;
			dockPaneStripToolWindowGradient1.DockStripGradient = dockPanelGradient3;
			tabGradient6.EndColor = System.Drawing.SystemColors.InactiveCaption;
			tabGradient6.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
			tabGradient6.StartColor = System.Drawing.SystemColors.GradientInactiveCaption;
			tabGradient6.TextColor = System.Drawing.SystemColors.InactiveCaptionText;
			dockPaneStripToolWindowGradient1.InactiveCaptionGradient = tabGradient6;
			tabGradient7.EndColor = System.Drawing.Color.Transparent;
			tabGradient7.StartColor = System.Drawing.Color.Transparent;
			tabGradient7.TextColor = System.Drawing.SystemColors.ControlDarkDark;
			dockPaneStripToolWindowGradient1.InactiveTabGradient = tabGradient7;
			dockPaneStripSkin1.ToolWindowGradient = dockPaneStripToolWindowGradient1;
			dockPanelSkin1.DockPaneStripSkin = dockPaneStripSkin1;
			this.dockPanel.Skin = dockPanelSkin1;
			this.dockPanel.TabIndex = 4;
			this.dockPanel.ActiveDocumentChanged += new System.EventHandler(this.dockPanel_ActiveDocumentChanged);
			// 
			// FormMain
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(942, 635);
			this.Controls.Add(this.dockPanel);
			this.Controls.Add(this.statusStrip1);
			this.Controls.Add(this.menuStrip1);
			this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.IsMdiContainer = true;
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "FormMain";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "VoxelViewer";
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.statusStrip1.ResumeLayout(false);
			this.statusStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem miFile;
		private System.Windows.Forms.ToolStripMenuItem miOpenFileVxb;
		private System.Windows.Forms.ToolStripMenuItem miOpenFileBin;
		private Common.Docking.SafeDockPanel dockPanel;
		private System.Windows.Forms.StatusStrip statusStrip1;
		public System.Windows.Forms.ToolStripStatusLabel statusLabelInfo;
		private System.Windows.Forms.ToolStripMenuItem miFileExit;
		private System.Windows.Forms.ToolStripProgressBar progreesBar;
		private System.Windows.Forms.ToolStripStatusLabel statusLabelWait;
		private System.Windows.Forms.ToolStripMenuItem miOptions;
		private System.Windows.Forms.ToolStripMenuItem miMaterials;
		private System.Windows.Forms.ToolStripMenuItem miDiagrams;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripMenuItem miExport;
		private System.Windows.Forms.ToolStripMenuItem tsExport1;
		private System.Windows.Forms.ToolStripMenuItem tsExport2;
	}
}

