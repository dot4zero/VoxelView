namespace VoxelView
{
	partial class MaterialsDockContent
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

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.trackBarColor = new System.Windows.Forms.TrackBar();
			this.numericUpDownColor = new System.Windows.Forms.NumericUpDown();
			this.label7 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.comboBoxMaterials = new System.Windows.Forms.ComboBox();
			this.panelColor = new VoxelView.PanelViewControl();
			((System.ComponentModel.ISupportInitialize)(this.trackBarColor)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownColor)).BeginInit();
			this.SuspendLayout();
			// 
			// trackBarColor
			// 
			this.trackBarColor.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.trackBarColor.BackColor = System.Drawing.SystemColors.Control;
			this.trackBarColor.LargeChange = 15;
			this.trackBarColor.Location = new System.Drawing.Point(6, 61);
			this.trackBarColor.Maximum = 255;
			this.trackBarColor.Name = "trackBarColor";
			this.trackBarColor.Size = new System.Drawing.Size(306, 45);
			this.trackBarColor.TabIndex = 0;
			this.trackBarColor.TabStop = false;
			this.trackBarColor.TickFrequency = 15;
			this.trackBarColor.ValueChanged += new System.EventHandler(this.trackBarColor_ValueChanged);
			// 
			// numericUpDownColor
			// 
			this.numericUpDownColor.Location = new System.Drawing.Point(204, 19);
			this.numericUpDownColor.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
			this.numericUpDownColor.Name = "numericUpDownColor";
			this.numericUpDownColor.Size = new System.Drawing.Size(45, 21);
			this.numericUpDownColor.TabIndex = 9;
			this.numericUpDownColor.TabStop = false;
			this.numericUpDownColor.ValueChanged += new System.EventHandler(this.numericUpDownColor_ValueChanged);
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(161, 23);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(37, 13);
			this.label7.TabIndex = 0;
			this.label7.Text = "Цвет:";
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Location = new System.Drawing.Point(15, 23);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(61, 13);
			this.label8.TabIndex = 0;
			this.label8.Text = "Материал:";
			// 
			// comboBoxMaterials
			// 
			this.comboBoxMaterials.FormattingEnabled = true;
			this.comboBoxMaterials.Location = new System.Drawing.Point(82, 19);
			this.comboBoxMaterials.Name = "comboBoxMaterials";
			this.comboBoxMaterials.Size = new System.Drawing.Size(53, 21);
			this.comboBoxMaterials.TabIndex = 1;
			this.comboBoxMaterials.SelectedIndexChanged += new System.EventHandler(this.comboBoxMaterials_SelectedIndexChanged);
			// 
			// panelColor
			// 
			this.panelColor.BackColor = System.Drawing.Color.Black;
			this.panelColor.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.panelColor.Location = new System.Drawing.Point(260, 13);
			this.panelColor.Name = "panelColor";
			this.panelColor.Size = new System.Drawing.Size(32, 32);
			this.panelColor.TabIndex = 0;
			// 
			// MaterialsDockContent
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(316, 111);
			this.Controls.Add(this.comboBoxMaterials);
			this.Controls.Add(this.panelColor);
			this.Controls.Add(this.trackBarColor);
			this.Controls.Add(this.numericUpDownColor);
			this.Controls.Add(this.label8);
			this.Controls.Add(this.label7);
			this.DockAreas = ((WeifenLuo.WinFormsUI.Docking.DockAreas)(((((WeifenLuo.WinFormsUI.Docking.DockAreas.Float | WeifenLuo.WinFormsUI.Docking.DockAreas.DockLeft)
						| WeifenLuo.WinFormsUI.Docking.DockAreas.DockRight)
						| WeifenLuo.WinFormsUI.Docking.DockAreas.DockTop)
						| WeifenLuo.WinFormsUI.Docking.DockAreas.DockBottom)));
			this.Enabled = false;
			this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.MaximizeBox = false;
			this.Name = "MaterialsDockContent";
			this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.Float;
			this.ShowInTaskbar = false;
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.Text = "Редактор материалов";
			((System.ComponentModel.ISupportInitialize)(this.trackBarColor)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownColor)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private PanelViewControl panelColor;
		private System.Windows.Forms.TrackBar trackBarColor;
		private System.Windows.Forms.NumericUpDown numericUpDownColor;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.ComboBox comboBoxMaterials;
	}
}
