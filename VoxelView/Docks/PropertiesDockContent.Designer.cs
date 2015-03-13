namespace VoxelView
{
	partial class PropertiesDockContent
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
			this.label1 = new System.Windows.Forms.Label();
			this.numericUpDownDepth = new System.Windows.Forms.NumericUpDown();
			this.trackBarDepth = new System.Windows.Forms.TrackBar();
			this.radioButton3 = new System.Windows.Forms.RadioButton();
			this.radioButton2 = new System.Windows.Forms.RadioButton();
			this.radioButton1 = new System.Windows.Forms.RadioButton();
			this.numericUpDownAlphaBox = new System.Windows.Forms.NumericUpDown();
			this.trackBarAlphaBox = new System.Windows.Forms.TrackBar();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.groupBoxTransparance = new System.Windows.Forms.GroupBox();
			this.trackBarAlphaRes = new System.Windows.Forms.TrackBar();
			this.label2 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.numericUpDownAlphaRes = new System.Windows.Forms.NumericUpDown();
			this.groupBoxBounds = new System.Windows.Forms.GroupBox();
			this.labelDepth = new System.Windows.Forms.Label();
			this.labelSizeZ = new System.Windows.Forms.Label();
			this.labelSizeY = new System.Windows.Forms.Label();
			this.labelSizeX = new System.Windows.Forms.Label();
			this.groupBoxResults = new System.Windows.Forms.GroupBox();
			this.checkBoxPercent = new System.Windows.Forms.CheckBox();
			this.numericUpDownLevels = new System.Windows.Forms.NumericUpDown();
			this.checkBoxIsolines = new System.Windows.Forms.CheckBox();
			this.label6 = new System.Windows.Forms.Label();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownDepth)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarDepth)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownAlphaBox)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarAlphaBox)).BeginInit();
			this.groupBoxTransparance.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBarAlphaRes)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownAlphaRes)).BeginInit();
			this.groupBoxBounds.SuspendLayout();
			this.groupBoxResults.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownLevels)).BeginInit();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(10, 101);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(73, 13);
			this.label1.TabIndex = 15;
			this.label1.Text = "Координата:";
			// 
			// numericUpDownDepth
			// 
			this.numericUpDownDepth.Location = new System.Drawing.Point(88, 99);
			this.numericUpDownDepth.Name = "numericUpDownDepth";
			this.numericUpDownDepth.Size = new System.Drawing.Size(45, 21);
			this.numericUpDownDepth.TabIndex = 2;
			this.numericUpDownDepth.TabStop = false;
			this.numericUpDownDepth.ValueChanged += new System.EventHandler(this.numericUpDownDepth_ValueChanged);
			// 
			// trackBarDepth
			// 
			this.trackBarDepth.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.trackBarDepth.Location = new System.Drawing.Point(6, 126);
			this.trackBarDepth.Maximum = 0;
			this.trackBarDepth.Name = "trackBarDepth";
			this.trackBarDepth.Size = new System.Drawing.Size(283, 45);
			this.trackBarDepth.TabIndex = 12;
			this.trackBarDepth.TabStop = false;
			this.trackBarDepth.ValueChanged += new System.EventHandler(this.trackBarDepth_ValueChanged);
			// 
			// radioButton3
			// 
			this.radioButton3.AutoSize = true;
			this.radioButton3.Location = new System.Drawing.Point(12, 72);
			this.radioButton3.Name = "radioButton3";
			this.radioButton3.Size = new System.Drawing.Size(57, 17);
			this.radioButton3.TabIndex = 11;
			this.radioButton3.Text = "Ось Z:";
			this.radioButton3.UseVisualStyleBackColor = true;
			this.radioButton3.Click += new System.EventHandler(this.radioButton3_Click);
			// 
			// radioButton2
			// 
			this.radioButton2.AutoSize = true;
			this.radioButton2.Location = new System.Drawing.Point(12, 49);
			this.radioButton2.Name = "radioButton2";
			this.radioButton2.Size = new System.Drawing.Size(57, 17);
			this.radioButton2.TabIndex = 10;
			this.radioButton2.Text = "Ось Y:";
			this.radioButton2.UseVisualStyleBackColor = true;
			this.radioButton2.Click += new System.EventHandler(this.radioButton2_Click);
			// 
			// radioButton1
			// 
			this.radioButton1.AutoSize = true;
			this.radioButton1.Checked = true;
			this.radioButton1.Location = new System.Drawing.Point(12, 26);
			this.radioButton1.Name = "radioButton1";
			this.radioButton1.Size = new System.Drawing.Size(57, 17);
			this.radioButton1.TabIndex = 9;
			this.radioButton1.TabStop = true;
			this.radioButton1.Text = "Ось X:";
			this.radioButton1.UseVisualStyleBackColor = true;
			this.radioButton1.Click += new System.EventHandler(this.radioButton1_Click);
			// 
			// numericUpDownAlphaBox
			// 
			this.numericUpDownAlphaBox.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
			this.numericUpDownAlphaBox.Location = new System.Drawing.Point(88, 20);
			this.numericUpDownAlphaBox.Name = "numericUpDownAlphaBox";
			this.numericUpDownAlphaBox.Size = new System.Drawing.Size(45, 21);
			this.numericUpDownAlphaBox.TabIndex = 3;
			this.numericUpDownAlphaBox.TabStop = false;
			this.numericUpDownAlphaBox.ValueChanged += new System.EventHandler(this.numericUpDownAlphaBox_ValueChanged);
			// 
			// trackBarAlphaBox
			// 
			this.trackBarAlphaBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.trackBarAlphaBox.LargeChange = 10;
			this.trackBarAlphaBox.Location = new System.Drawing.Point(6, 52);
			this.trackBarAlphaBox.Maximum = 100;
			this.trackBarAlphaBox.Name = "trackBarAlphaBox";
			this.trackBarAlphaBox.Size = new System.Drawing.Size(283, 45);
			this.trackBarAlphaBox.SmallChange = 10;
			this.trackBarAlphaBox.TabIndex = 16;
			this.trackBarAlphaBox.TabStop = false;
			this.trackBarAlphaBox.TickFrequency = 10;
			this.trackBarAlphaBox.ValueChanged += new System.EventHandler(this.trackBarAlphaBox_ValueChanged);
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(139, 23);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(18, 13);
			this.label3.TabIndex = 19;
			this.label3.Text = "%";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(10, 23);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(75, 13);
			this.label4.TabIndex = 20;
			this.label4.Text = "Воксельбокс:";
			// 
			// groupBoxTransparance
			// 
			this.groupBoxTransparance.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.groupBoxTransparance.Controls.Add(this.trackBarAlphaRes);
			this.groupBoxTransparance.Controls.Add(this.label2);
			this.groupBoxTransparance.Controls.Add(this.label5);
			this.groupBoxTransparance.Controls.Add(this.numericUpDownAlphaRes);
			this.groupBoxTransparance.Controls.Add(this.trackBarAlphaBox);
			this.groupBoxTransparance.Controls.Add(this.label3);
			this.groupBoxTransparance.Controls.Add(this.label4);
			this.groupBoxTransparance.Controls.Add(this.numericUpDownAlphaBox);
			this.groupBoxTransparance.Location = new System.Drawing.Point(3, 293);
			this.groupBoxTransparance.Name = "groupBoxTransparance";
			this.groupBoxTransparance.Size = new System.Drawing.Size(295, 178);
			this.groupBoxTransparance.TabIndex = 21;
			this.groupBoxTransparance.TabStop = false;
			this.groupBoxTransparance.Text = "Прозрачность";
			// 
			// trackBarAlphaRes
			// 
			this.trackBarAlphaRes.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.trackBarAlphaRes.LargeChange = 10;
			this.trackBarAlphaRes.Location = new System.Drawing.Point(6, 126);
			this.trackBarAlphaRes.Maximum = 100;
			this.trackBarAlphaRes.Name = "trackBarAlphaRes";
			this.trackBarAlphaRes.Size = new System.Drawing.Size(283, 45);
			this.trackBarAlphaRes.SmallChange = 10;
			this.trackBarAlphaRes.TabIndex = 21;
			this.trackBarAlphaRes.TabStop = false;
			this.trackBarAlphaRes.TickFrequency = 10;
			this.trackBarAlphaRes.ValueChanged += new System.EventHandler(this.trackBarAlphaRes_ValueChanged);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(139, 101);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(18, 13);
			this.label2.TabIndex = 23;
			this.label2.Text = "%";
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(10, 101);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(72, 13);
			this.label5.TabIndex = 24;
			this.label5.Text = "Результаты:";
			// 
			// numericUpDownAlphaRes
			// 
			this.numericUpDownAlphaRes.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
			this.numericUpDownAlphaRes.Location = new System.Drawing.Point(88, 99);
			this.numericUpDownAlphaRes.Name = "numericUpDownAlphaRes";
			this.numericUpDownAlphaRes.Size = new System.Drawing.Size(45, 21);
			this.numericUpDownAlphaRes.TabIndex = 4;
			this.numericUpDownAlphaRes.TabStop = false;
			this.numericUpDownAlphaRes.ValueChanged += new System.EventHandler(this.numericUpDownAlphaRes_ValueChanged);
			// 
			// groupBoxBounds
			// 
			this.groupBoxBounds.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.groupBoxBounds.Controls.Add(this.labelDepth);
			this.groupBoxBounds.Controls.Add(this.labelSizeZ);
			this.groupBoxBounds.Controls.Add(this.labelSizeY);
			this.groupBoxBounds.Controls.Add(this.labelSizeX);
			this.groupBoxBounds.Controls.Add(this.label1);
			this.groupBoxBounds.Controls.Add(this.numericUpDownDepth);
			this.groupBoxBounds.Controls.Add(this.radioButton1);
			this.groupBoxBounds.Controls.Add(this.radioButton2);
			this.groupBoxBounds.Controls.Add(this.trackBarDepth);
			this.groupBoxBounds.Controls.Add(this.radioButton3);
			this.groupBoxBounds.Location = new System.Drawing.Point(3, 110);
			this.groupBoxBounds.Name = "groupBoxBounds";
			this.groupBoxBounds.Size = new System.Drawing.Size(295, 177);
			this.groupBoxBounds.TabIndex = 22;
			this.groupBoxBounds.TabStop = false;
			this.groupBoxBounds.Text = "Размеры";
			// 
			// labelDepth
			// 
			this.labelDepth.AutoSize = true;
			this.labelDepth.Location = new System.Drawing.Point(139, 101);
			this.labelDepth.Name = "labelDepth";
			this.labelDepth.Size = new System.Drawing.Size(29, 13);
			this.labelDepth.TabIndex = 19;
			this.labelDepth.Text = "0mm";
			// 
			// labelSizeZ
			// 
			this.labelSizeZ.AutoSize = true;
			this.labelSizeZ.Location = new System.Drawing.Point(71, 74);
			this.labelSizeZ.Name = "labelSizeZ";
			this.labelSizeZ.Size = new System.Drawing.Size(13, 13);
			this.labelSizeZ.TabIndex = 18;
			this.labelSizeZ.Text = "0";
			// 
			// labelSizeY
			// 
			this.labelSizeY.AutoSize = true;
			this.labelSizeY.Location = new System.Drawing.Point(71, 51);
			this.labelSizeY.Name = "labelSizeY";
			this.labelSizeY.Size = new System.Drawing.Size(13, 13);
			this.labelSizeY.TabIndex = 17;
			this.labelSizeY.Text = "0";
			// 
			// labelSizeX
			// 
			this.labelSizeX.AutoSize = true;
			this.labelSizeX.Location = new System.Drawing.Point(71, 28);
			this.labelSizeX.Name = "labelSizeX";
			this.labelSizeX.Size = new System.Drawing.Size(13, 13);
			this.labelSizeX.TabIndex = 16;
			this.labelSizeX.Text = "0";
			// 
			// groupBoxResults
			// 
			this.groupBoxResults.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.groupBoxResults.Controls.Add(this.checkBoxPercent);
			this.groupBoxResults.Controls.Add(this.numericUpDownLevels);
			this.groupBoxResults.Controls.Add(this.checkBoxIsolines);
			this.groupBoxResults.Controls.Add(this.label6);
			this.groupBoxResults.Location = new System.Drawing.Point(3, 3);
			this.groupBoxResults.Name = "groupBoxResults";
			this.groupBoxResults.Size = new System.Drawing.Size(295, 101);
			this.groupBoxResults.TabIndex = 27;
			this.groupBoxResults.TabStop = false;
			this.groupBoxResults.Text = "Результаты";
			// 
			// checkBoxPercent
			// 
			this.checkBoxPercent.AutoSize = true;
			this.checkBoxPercent.Location = new System.Drawing.Point(12, 73);
			this.checkBoxPercent.Name = "checkBoxPercent";
			this.checkBoxPercent.Size = new System.Drawing.Size(100, 17);
			this.checkBoxPercent.TabIndex = 25;
			this.checkBoxPercent.TabStop = false;
			this.checkBoxPercent.Text = "Выводить в %";
			this.checkBoxPercent.UseVisualStyleBackColor = true;
			this.checkBoxPercent.CheckedChanged += new System.EventHandler(this.checkBoxPercent_CheckedChanged);
			// 
			// numericUpDownLevels
			// 
			this.numericUpDownLevels.Location = new System.Drawing.Point(94, 43);
			this.numericUpDownLevels.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
			this.numericUpDownLevels.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
			this.numericUpDownLevels.Name = "numericUpDownLevels";
			this.numericUpDownLevels.Size = new System.Drawing.Size(45, 21);
			this.numericUpDownLevels.TabIndex = 1;
			this.numericUpDownLevels.TabStop = false;
			this.numericUpDownLevels.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
			this.numericUpDownLevels.ValueChanged += new System.EventHandler(this.numericUpDownLevels_ValueChanged);
			// 
			// checkBoxIsolines
			// 
			this.checkBoxIsolines.AutoSize = true;
			this.checkBoxIsolines.Location = new System.Drawing.Point(12, 20);
			this.checkBoxIsolines.Name = "checkBoxIsolines";
			this.checkBoxIsolines.Size = new System.Drawing.Size(74, 17);
			this.checkBoxIsolines.TabIndex = 0;
			this.checkBoxIsolines.TabStop = false;
			this.checkBoxIsolines.Text = "Изолинии";
			this.checkBoxIsolines.UseVisualStyleBackColor = true;
			this.checkBoxIsolines.CheckedChanged += new System.EventHandler(this.checkBoxIsolines_CheckedChanged);
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(9, 45);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(79, 13);
			this.label6.TabIndex = 24;
			this.label6.Text = "Кол. уровней:";
			// 
			// PropertiesDockContent
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(285, 458);
			this.CloseButton = false;
			this.CloseButtonVisible = false;
			this.Controls.Add(this.groupBoxResults);
			this.Controls.Add(this.groupBoxTransparance);
			this.Controls.Add(this.groupBoxBounds);
			this.DockAreas = ((WeifenLuo.WinFormsUI.Docking.DockAreas)(((((WeifenLuo.WinFormsUI.Docking.DockAreas.Float | WeifenLuo.WinFormsUI.Docking.DockAreas.DockLeft)
						| WeifenLuo.WinFormsUI.Docking.DockAreas.DockRight)
						| WeifenLuo.WinFormsUI.Docking.DockAreas.DockTop)
						| WeifenLuo.WinFormsUI.Docking.DockAreas.DockBottom)));
			this.Enabled = false;
			this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.Name = "PropertiesDockContent";
			this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.DockRight;
			this.TabText = "";
			this.Text = "Свойства";
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownDepth)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarDepth)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownAlphaBox)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarAlphaBox)).EndInit();
			this.groupBoxTransparance.ResumeLayout(false);
			this.groupBoxTransparance.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBarAlphaRes)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownAlphaRes)).EndInit();
			this.groupBoxBounds.ResumeLayout(false);
			this.groupBoxBounds.PerformLayout();
			this.groupBoxResults.ResumeLayout(false);
			this.groupBoxResults.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownLevels)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.NumericUpDown numericUpDownDepth;
		private System.Windows.Forms.TrackBar trackBarDepth;
		private System.Windows.Forms.RadioButton radioButton3;
		private System.Windows.Forms.RadioButton radioButton2;
		private System.Windows.Forms.RadioButton radioButton1;
		private System.Windows.Forms.NumericUpDown numericUpDownAlphaBox;
		private System.Windows.Forms.TrackBar trackBarAlphaBox;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.GroupBox groupBoxTransparance;
		private System.Windows.Forms.TrackBar trackBarAlphaRes;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.NumericUpDown numericUpDownAlphaRes;
		private System.Windows.Forms.GroupBox groupBoxBounds;
		private System.Windows.Forms.Label labelSizeX;
		private System.Windows.Forms.Label labelSizeZ;
		private System.Windows.Forms.Label labelSizeY;
		private System.Windows.Forms.GroupBox groupBoxResults;
		private System.Windows.Forms.NumericUpDown numericUpDownLevels;
		private System.Windows.Forms.CheckBox checkBoxIsolines;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label labelDepth;
		private System.Windows.Forms.CheckBox checkBoxPercent;
	}
}
