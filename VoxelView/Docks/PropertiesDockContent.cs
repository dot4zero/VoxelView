using System;
using Common.Docking;

namespace VoxelView
{
	public partial class PropertiesDockContent : SafeDockContent
	{
		private VoxelViewDockContent VoxelViewDockContent
		{
			get { return FormMain.ActiveViewDockContent; }
		}

		private VoxelViewController VoxelViewController
		{
			get { return (VoxelViewDockContent != null) ? VoxelViewDockContent.VoxelViewController : null; }
		}

		public PropertiesDockContent()
		{
			InitializeComponent();
		}

		public void UpdateData()
		{
			if (VoxelViewController == null)
			{
				this.Enabled = false;
				return;
			}

			this.Enabled = true;

			checkBoxPercent.CheckedChanged -= checkBoxPercent_CheckedChanged;
			checkBoxIsolines.CheckedChanged -= checkBoxIsolines_CheckedChanged;
			numericUpDownLevels.ValueChanged -= numericUpDownLevels_ValueChanged;
			trackBarDepth.ValueChanged -= trackBarDepth_ValueChanged;
			numericUpDownDepth.ValueChanged -= numericUpDownDepth_ValueChanged;
			trackBarAlphaBox.ValueChanged -= trackBarAlphaBox_ValueChanged;
			trackBarAlphaRes.ValueChanged -= trackBarAlphaRes_ValueChanged;

			try
			{
				radioButton1.Enabled = VoxelViewController.SizeY > 1 && VoxelViewController.SizeZ > 1;
				radioButton2.Enabled = VoxelViewController.SizeX > 1 && VoxelViewController.SizeZ > 1;
				radioButton3.Enabled = VoxelViewController.SizeX > 1 && VoxelViewController.SizeY > 1;

				if (VoxelViewController.Axis == 0)
				{
					trackBarDepth.SetRange(0, (int)VoxelViewController.SizeX - 1);
					radioButton1.Checked = true;
				}
				else if (VoxelViewController.Axis == 1)
				{
					trackBarDepth.SetRange(0, (int)VoxelViewController.SizeY - 1);
					radioButton2.Checked = true;
				}
				else if (VoxelViewController.Axis == 2)
				{
					trackBarDepth.SetRange(0, (int)VoxelViewController.SizeZ - 1);
					radioButton3.Checked = true;
				}
				else
				{
					throw new NotSupportedException("Не определено значение Axis!");
				}

				if (trackBarDepth.Maximum > 1)
				{
					trackBarDepth.Enabled = true;
					numericUpDownDepth.Enabled = true;
				}
				else
				{
					trackBarDepth.Enabled = false;
					numericUpDownDepth.Enabled = false;
				}

				checkBoxPercent.Checked = VoxelViewController.Percent;
				checkBoxIsolines.Checked = VoxelViewController.Isolines;
				numericUpDownLevels.Value = VoxelViewController.Levels;
				numericUpDownDepth.Minimum = trackBarDepth.Minimum;
				numericUpDownDepth.Maximum = trackBarDepth.Maximum;
				trackBarDepth.Value = (int)VoxelViewController.Depth;
				numericUpDownDepth.Value = trackBarDepth.Value;
				trackBarAlphaBox.Value = (int)(VoxelViewDockContent.AlphaBox * 100);
				trackBarAlphaRes.Value = (int)(VoxelViewDockContent.AlphaRes * 100);

				labelSizeX.Text = String.Format("{0} x {1}mm", VoxelViewController.SizeX, VoxelViewController.BoxSizeX * 10);
				labelSizeY.Text = String.Format("{0} x {1}mm", VoxelViewController.SizeY, VoxelViewController.BoxSizeY * 10);
				labelSizeZ.Text = String.Format("{0} x {1}mm", VoxelViewController.SizeZ, VoxelViewController.BoxSizeZ * 10);

				UpdateLabelDepth();
			}
			finally
			{
				checkBoxPercent.CheckedChanged += checkBoxPercent_CheckedChanged;
				checkBoxIsolines.CheckedChanged += checkBoxIsolines_CheckedChanged;
				numericUpDownLevels.ValueChanged += numericUpDownLevels_ValueChanged;
				trackBarDepth.ValueChanged += trackBarDepth_ValueChanged;
				numericUpDownDepth.ValueChanged += numericUpDownDepth_ValueChanged;
				trackBarAlphaBox.ValueChanged += trackBarAlphaBox_ValueChanged;
				trackBarAlphaRes.ValueChanged += trackBarAlphaRes_ValueChanged;
			}

			if (VoxelViewController.HasResult)
			{
				groupBoxResults.Enabled = true;
				trackBarAlphaRes.Enabled = true;
				numericUpDownAlphaRes.Enabled = true;
			}
			else
			{
				groupBoxResults.Enabled = false;
				trackBarAlphaRes.Enabled = false;
				numericUpDownAlphaRes.Enabled = false;
			}
		}

		private void checkBoxIsolines_CheckedChanged(object sender, EventArgs e)
		{
			VoxelViewController.Isolines = checkBoxIsolines.Checked;
			VoxelViewDockContent.ImageVoxelResValid = false;
			VoxelViewDockContent.UpdateImage();
		}

		private void numericUpDownLevels_ValueChanged(object sender, EventArgs e)
		{
			VoxelViewController.Levels = (uint)numericUpDownLevels.Value;
			VoxelViewDockContent.ImageVoxelResValid = false;
			VoxelViewDockContent.UpdateImage();
		}

		private void trackBarDepth_ValueChanged(object sender, EventArgs e)
		{
			numericUpDownDepth.Value = trackBarDepth.Value;
		}

		private void numericUpDownDepth_ValueChanged(object sender, EventArgs e)
		{
			trackBarDepth.ValueChanged -= trackBarDepth_ValueChanged;
			trackBarDepth.Value = (int)numericUpDownDepth.Value;
			trackBarDepth.ValueChanged += trackBarDepth_ValueChanged;

			VoxelViewController.Depth = (uint)trackBarDepth.Value;
			UpdateLabelDepth();
			VoxelViewDockContent.ImageVoxelBoxValid = false;
			VoxelViewDockContent.ImageVoxelResValid = false;
			VoxelViewDockContent.UpdateImage();
		}

		private void UpdateLabelDepth()
		{
			switch (VoxelViewController.Axis)
			{
				case 0:
					labelDepth.Text = String.Format("({0}mm)", VoxelViewController.Depth * VoxelViewController.BoxSizeX * 10);
					break;
				case 1:
					labelDepth.Text = String.Format("({0}mm)", VoxelViewController.Depth * VoxelViewController.BoxSizeY * 10);
					break;
				case 2:
					labelDepth.Text = String.Format("({0}mm)", VoxelViewController.Depth * VoxelViewController.BoxSizeZ * 10);
					break;
				default:
					throw new NotSupportedException("VoxelViewController.Axis=" + VoxelViewController.Axis);
			}
		}

		private void radioButton1_Click(object sender, EventArgs e)
		{
			if (VoxelViewController != null &&
				VoxelViewController.SizeY > 1 &&
				VoxelViewController.SizeZ > 1)
			{
				VoxelViewController.Axis = 0;
				VoxelViewDockContent.SetPanelBounds();
				VoxelViewDockContent.ImageVoxelBoxValid = false;
				VoxelViewDockContent.ImageVoxelResValid = false;
				VoxelViewDockContent.UpdateImage();
				UpdateData();
			}
		}

		private void radioButton2_Click(object sender, EventArgs e)
		{
			if (VoxelViewController != null &&
				VoxelViewController.SizeX > 1 &&
				VoxelViewController.SizeZ > 1)
			{
				VoxelViewController.Axis = 1;
				VoxelViewDockContent.SetPanelBounds();
				VoxelViewDockContent.ImageVoxelBoxValid = false;
				VoxelViewDockContent.ImageVoxelResValid = false;
				VoxelViewDockContent.UpdateImage();
				UpdateData();
			}
		}

		private void radioButton3_Click(object sender, EventArgs e)
		{
			if (VoxelViewController != null &&
				VoxelViewController.SizeX > 1 &&
				VoxelViewController.SizeY > 1)
			{
				VoxelViewController.Axis = 2;
				VoxelViewDockContent.SetPanelBounds();
				VoxelViewDockContent.ImageVoxelBoxValid = false;
				VoxelViewDockContent.ImageVoxelResValid = false;
				VoxelViewDockContent.UpdateImage();
				UpdateData();
			}
		}

		private void trackBarAlphaBox_ValueChanged(object sender, EventArgs e)
		{
			numericUpDownAlphaBox.Value = trackBarAlphaBox.Value;
		}

		private void numericUpDownAlphaBox_ValueChanged(object sender, EventArgs e)
		{
			trackBarAlphaBox.ValueChanged -= trackBarAlphaBox_ValueChanged;
			trackBarAlphaBox.Value = (int)numericUpDownAlphaBox.Value;
			trackBarAlphaBox.ValueChanged += trackBarAlphaBox_ValueChanged;

			VoxelViewDockContent.AlphaBox = ((float)numericUpDownAlphaBox.Value) / 100.0f;
			VoxelViewDockContent.RefreshImage();
		}

		private void trackBarAlphaRes_ValueChanged(object sender, EventArgs e)
		{
			numericUpDownAlphaRes.Value = trackBarAlphaRes.Value;
		}

		private void numericUpDownAlphaRes_ValueChanged(object sender, EventArgs e)
		{
			trackBarAlphaRes.ValueChanged -= trackBarAlphaRes_ValueChanged;
			trackBarAlphaRes.Value = (int)numericUpDownAlphaRes.Value;
			trackBarAlphaRes.ValueChanged += trackBarAlphaRes_ValueChanged;

			VoxelViewDockContent.AlphaRes = ((float)numericUpDownAlphaRes.Value) / 100.0f;
			VoxelViewDockContent.RefreshImage();
		}

		private void checkBoxPercent_CheckedChanged(object sender, EventArgs e)
		{
			VoxelViewController.Percent = checkBoxPercent.Checked;
			VoxelViewDockContent.Refresh();
			if (FormMain.DiagramsDockContent != null)
				FormMain.DiagramsDockContent.UpdateData();
		}
	}
}
