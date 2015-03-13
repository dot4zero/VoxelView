namespace VoxelView
{
	partial class VoxelViewDockContent
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
			if (disposing)
			{
				if (components != null)
					components.Dispose();

				if (_voxelViewController != null)
				{
					_voxelViewController.DecRefCount();
					_voxelViewController = null;
				}

				if (_timer != null)
					_timer.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.labelTitle = new System.Windows.Forms.Label();
			this.panelView = new VoxelView.PanelViewControl();
			this.panelColorBar = new VoxelView.PanelViewControl();
			this.contextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.miSaveBmp = new System.Windows.Forms.ToolStripMenuItem();
			this.contextMenu.SuspendLayout();
			this.SuspendLayout();
			// 
			// labelTitle
			// 
			this.labelTitle.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.labelTitle.Location = new System.Drawing.Point(30, 0);
			this.labelTitle.Name = "labelTitle";
			this.labelTitle.Size = new System.Drawing.Size(620, 27);
			this.labelTitle.TabIndex = 12;
			this.labelTitle.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// panelView
			// 
			this.panelView.Anchor = System.Windows.Forms.AnchorStyles.None;
			this.panelView.Location = new System.Drawing.Point(30, 30);
			this.panelView.Name = "panelView";
			this.panelView.Size = new System.Drawing.Size(620, 562);
			this.panelView.TabIndex = 0;
			this.panelView.TabStop = true;
			this.panelView.Paint += new System.Windows.Forms.PaintEventHandler(this.panelView_Paint);
			this.panelView.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panelView_MouseMove);
			this.panelView.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panelView_MouseDown);
			this.panelView.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panelView_MouseUp);
			// 
			// panelColorBar
			// 
			this.panelColorBar.Anchor = System.Windows.Forms.AnchorStyles.Right;
			this.panelColorBar.Location = new System.Drawing.Point(660, 30);
			this.panelColorBar.Name = "panelColorBar";
			this.panelColorBar.Size = new System.Drawing.Size(100, 562);
			this.panelColorBar.TabIndex = 0;
			this.panelColorBar.Paint += new System.Windows.Forms.PaintEventHandler(this.panelColorBar_Paint);
			// 
			// contextMenu
			// 
			this.contextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miSaveBmp});
			this.contextMenu.Name = "contextMenu";
			this.contextMenu.Size = new System.Drawing.Size(204, 26);
			// 
			// miSaveBmp
			// 
			this.miSaveBmp.Name = "miSaveBmp";
			this.miSaveBmp.Size = new System.Drawing.Size(203, 22);
			this.miSaveBmp.Text = "Сохранить в bmp-файл";
			this.miSaveBmp.Click += new System.EventHandler(this.miSaveBmp_Click);
			// 
			// VoxelViewDockContent
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(774, 622);
			this.ContextMenuStrip = this.contextMenu;
			this.Controls.Add(this.labelTitle);
			this.Controls.Add(this.panelView);
			this.Controls.Add(this.panelColorBar);
			this.DockAreas = WeifenLuo.WinFormsUI.Docking.DockAreas.Document;
			this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.Name = "VoxelViewDockContent";
			this.Paint += new System.Windows.Forms.PaintEventHandler(this.VoxelViewControl_Paint);
			this.contextMenu.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private PanelViewControl panelView;
		private PanelViewControl panelColorBar;
		private System.Windows.Forms.Label labelTitle;
		private System.Windows.Forms.ContextMenuStrip contextMenu;
		private System.Windows.Forms.ToolStripMenuItem miSaveBmp;
	}
}
