using System;
using System.Drawing;
using Common.Docking;

namespace VoxelView
{
	public partial class MaterialsDockContent : SafeDockContent
	{
		private VoxelViewDockContent VoxelViewDockContent
		{
			get { return FormMain.ActiveViewDockContent; }
		}

		private VoxelViewController VoxelViewController
		{
			get { return (VoxelViewDockContent != null) ? VoxelViewDockContent.VoxelViewController : null; }
		}

		public int Material
		{
			set
			{
				if (value > 0)
				{
					comboBoxMaterials.SelectedIndexChanged -= comboBoxMaterials_SelectedIndexChanged;
					numericUpDownColor.ValueChanged -= numericUpDownColor_ValueChanged;
					trackBarColor.ValueChanged -= trackBarColor_ValueChanged;

					try
					{
						comboBoxMaterials.Text = value.ToString();
						var color = VoxelViewController.GetColorValue(value);
						numericUpDownColor.Value = color;
						trackBarColor.Value = color;
						panelColor.BackColor = Color.FromArgb(color, color, color);
					}
					finally
					{
						comboBoxMaterials.SelectedIndexChanged += comboBoxMaterials_SelectedIndexChanged;
						numericUpDownColor.ValueChanged += numericUpDownColor_ValueChanged;
						trackBarColor.ValueChanged += trackBarColor_ValueChanged;
					}
				}
			}
		}

		public MaterialsDockContent()
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

			comboBoxMaterials.Items.Clear();
			var materials = VoxelViewController.GetMaterials();
			foreach (var material in materials)
				comboBoxMaterials.Items.Add(material);
			if (comboBoxMaterials.Items.Count > 0)
				comboBoxMaterials.SelectedIndex = 0;
		}

		private void trackBarColor_ValueChanged(object sender, EventArgs e)
		{
			numericUpDownColor.Value = trackBarColor.Value;
		}

		private void numericUpDownColor_ValueChanged(object sender, EventArgs e)
		{
			trackBarColor.ValueChanged -= trackBarColor_ValueChanged;
			trackBarColor.Value = (int)numericUpDownColor.Value;
			trackBarColor.ValueChanged += trackBarColor_ValueChanged;

			var color = (int)numericUpDownColor.Value;
			panelColor.BackColor = Color.FromArgb(color, color, color);

			VoxelViewController.SetColorValue((int)comboBoxMaterials.Items[comboBoxMaterials.SelectedIndex], color);
			VoxelViewDockContent.ImageVoxelBoxValid = false;
			VoxelViewDockContent.UpdateImage();
		}

		private void comboBoxMaterials_SelectedIndexChanged(object sender, EventArgs e)
		{
			Material = (int)comboBoxMaterials.Items[comboBoxMaterials.SelectedIndex];
		}
	}
}
