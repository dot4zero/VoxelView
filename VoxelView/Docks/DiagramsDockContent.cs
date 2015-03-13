using System;
using System.Drawing;
using System.Windows.Forms;
using Common.Docking;
using Steema.TeeChart.Styles;
using System.IO;

namespace VoxelView
{
	public partial class DiagramsDockContent : SafeDockContent
	{
		private readonly FastLine _fastlineX;
		private readonly FastLine _fastlineY;

		private VoxelViewDockContent VoxelViewDockContent
		{
			get { return FormMain.ActiveViewDockContent; }
		}

		private VoxelViewController VoxelViewController
		{
			get { return (VoxelViewDockContent != null) ? VoxelViewDockContent.VoxelViewController : null; }
		}

		public DiagramsDockContent()
		{
			InitializeComponent();

			_fastlineX = new FastLine(tChart.Chart) { ShowInLegend = false };
			_fastlineY = new FastLine(tChart.Chart) { ShowInLegend = false };

			_fastlineX.LinePen.Color = Color.Red;
			_fastlineY.LinePen.Color = Color.Blue;
		}

		public void UpdateData()
		{
			_fastlineX.Clear();
			_fastlineY.Clear();

			if (VoxelViewController == null || !VoxelViewController.HasResult)
			{
				_fastlineX.ShowInLegend = false;
				_fastlineY.ShowInLegend = false;
				this.Enabled = false;
				return;
			}

			this.Enabled = true;

			_fastlineX.ShowInLegend = true;
			_fastlineY.ShowInLegend = true;
			tChart.Axes.Left.Title.Visible = VoxelViewController.Percent;

			VoxelViewDockContent.UpdateCrossCenter();
			var crossCenter = VoxelViewController.CrossCenter;

			var sizeX = (VoxelViewController.Axis == 0)
				? (int)VoxelViewController.SizeY
				: (int)VoxelViewController.SizeX;

			var sizeY = (VoxelViewController.Axis == 0)
				? (int)VoxelViewController.SizeZ
				: (int)VoxelViewController.SizeY;

			var boxSizeX = (VoxelViewController.Axis == 0)
				? VoxelViewController.BoxSizeY
				: VoxelViewController.BoxSizeX;

			var boxSizeY = (VoxelViewController.Axis == 0)
				? VoxelViewController.BoxSizeZ
				: VoxelViewController.BoxSizeY;

			_fastlineX.Title = String.Format(VoxelViewController.Axis == 2 ? "Y = {0:f2}mm" : "Z = {0:f2}mm", crossCenter.Y * boxSizeY * 10);
			_fastlineY.Title = String.Format(VoxelViewController.Axis == 0 ? "Y = {0:f2}mm" : "X = {0:f2}mm", crossCenter.X * boxSizeX * 10);
			_fastlineX.BeginUpdate();

			if (VoxelViewController.Percent)
			{
				for (var x = 0; x < sizeX; x++)
					_fastlineX.Add(x * boxSizeX * 10, VoxelViewController.GetNormValue(new Point(x, crossCenter.Y)) * 100);

				_fastlineX.Add(sizeX * boxSizeX * 10, VoxelViewController.GetNormValue(new Point(sizeX - 1, crossCenter.Y)) * 100);
			}
			else
			{
				for (var x = 0; x < sizeX; x++)
					_fastlineX.Add(x * boxSizeX * 10, VoxelViewController.GetValue(new Point(x, crossCenter.Y)) / VoxelViewController.Hist);

				_fastlineX.Add(sizeX * boxSizeX * 10, VoxelViewController.GetValue(new Point(sizeX - 1, crossCenter.Y)) / VoxelViewController.Hist);
			}

			_fastlineX.EndUpdate();

			_fastlineY.BeginUpdate();

			if (VoxelViewController.Percent)
			{
				for (var y = 0; y < sizeY; y++)
					_fastlineY.Add(y * boxSizeY * 10, VoxelViewController.GetNormValue(new Point(crossCenter.X, y)) * 100);

				_fastlineY.Add(sizeY * boxSizeY * 10, VoxelViewController.GetNormValue(new Point(crossCenter.X, sizeY - 1)) * 100);
			}
			else
			{
				for (var y = 0; y < sizeY; y++)
					_fastlineY.Add(y * boxSizeY * 10, VoxelViewController.GetValue(new Point(crossCenter.X, y)) / VoxelViewController.Hist);

				_fastlineY.Add(sizeY * boxSizeY * 10, VoxelViewController.GetValue(new Point(crossCenter.X, sizeY - 1)) / VoxelViewController.Hist);
			}

			_fastlineX.EndUpdate();
		}

		private void miSaveBmp_Click(object sender, EventArgs e)
		{
			using (var dlg = new SaveFileDialog())
			{
				dlg.FileName = Path.ChangeExtension(VoxelViewDockContent.ResFileName, "bmp");
				dlg.Filter = "Файлы изображений (*.bmp)|*.bmp|Все файлы (*.*)|*.*";

				if (dlg.ShowDialog() == DialogResult.OK)
				{
					var image = new Bitmap(this.Width, this.Height);
					DrawToBitmap(image, this.Bounds);
					image.MakeTransparent(this.BackColor);
					image.Save(dlg.FileName);
				}
			}
		}
	}
}
