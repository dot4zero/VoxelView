using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.Threading;
using Common.Docking;

namespace VoxelView
{
	public partial class VoxelViewDockContent : SafeDockContent
	{
		private VoxelViewController _voxelViewController;
		private Image _imageVoxelBox;
		private Image _imageVoxelRes;
		private float _alphaBox = 1.0f;
		private float _alphaRes = 0.6f;
		private string _resFileName;

		public bool ImageVoxelBoxValid;
		public bool ImageVoxelResValid;

		public VoxelViewController VoxelViewController
		{
			get { return _voxelViewController; }
		}

		public float AlphaBox
		{
			get { return _alphaBox; }
			set { _alphaBox = value; }
		}

		public float AlphaRes
		{
			get { return _alphaRes; }
			set { _alphaRes = value; }
		}

		public int Progress
		{
			get { return (int)_voxelViewController.Progress; }
		}

		public string ResFileName
		{
			get { return _resFileName; }
		}

		public VoxelViewDockContent()
		{
			InitializeComponent();

			_timer = new System.Threading.Timer(TimerCallback);
		}

		public void UpdateCrossCenter()
		{
			if (_voxelViewController != null)
				_voxelViewController.UpdateCrossCenter(panelView.Size);
		}

		public void InitVoxelBox(string fileName)
		{
			if (_voxelViewController != null)
			{
				_imageVoxelRes = null;
				_voxelViewController.Dispose();
			}

			_voxelViewController = new VoxelViewController();
			_voxelViewController.InitVoxelBox(fileName);
			SetPanelBounds();
			UpdateImage();
		}

		public void InitVoxelRes(string fileName)
		{
			_voxelViewController.InitVoxelRes(fileName);
			_resFileName = Path.GetFileNameWithoutExtension(fileName);
			labelTitle.Text =
				"Номер результата: " + _voxelViewController.ResultID +
				" Тип частицы: " + _voxelViewController.ParticleID +
				" Число частиц: " + _voxelViewController.Hist;
			SetPanelBounds();
			UpdateImage();
		}

		protected override void OnResize(EventArgs e)
		{
			if (_voxelViewController != null)
				SetPanelBounds();
			base.OnResize(e);
		}

		public void SetPanelBounds()
		{
			var destRect = new Rectangle(20, 20, Bounds.Width - 160, Bounds.Height - 40);
			var voxelSize = _voxelViewController.Size;
			var voxelRatio = (float)voxelSize.Width / (float)voxelSize.Height;

			if ((float)(destRect.Width - 60) / (float)(destRect.Height - 40) > voxelRatio)
			{
				panelView.Height = destRect.Height;
				panelView.Width = (int)((float)(panelView.Height - 40) * voxelRatio) + 60;
			}
			else
			{
				panelView.Width = destRect.Width;
				panelView.Height = (int)((float)(panelView.Width - 60) / voxelRatio) + 40;
			}

			panelView.Left = 20 + (destRect.Width - panelView.Width) / 2;
			panelView.Top = 20 + (destRect.Height - panelView.Height) / 2;

			panelColorBar.Top = panelView.Top;
			panelColorBar.Height = panelView.Height;

			labelTitle.Left = panelView.Left;
			labelTitle.Width = panelView.Width;
			labelTitle.Top = 10;
			labelTitle.Height = panelView.Top;
		}

		private void miSaveBmp_Click(object sender, EventArgs e)
		{
			using (var dlg = new SaveFileDialog())
			{
				dlg.FileName = Path.ChangeExtension(_resFileName, "bmp");
				dlg.Filter = "Файлы изображений (*.bmp)|*.bmp|Все файлы (*.*)|*.*";

				if (dlg.ShowDialog() == DialogResult.OK)
				{
					var image = new Bitmap(this.Width, this.Height);
					var g = Graphics.FromImage(image);
					DrawImage(g, panelView.Bounds);
					DrawTitle(g);
					DrawLabels(g);
					DrawColorBar(g, panelColorBar.Bounds);
					image.Save(dlg.FileName);
				}
			}
		}

		private void panelView_Paint(object sender, PaintEventArgs e)
		{
			DrawImage(e.Graphics, new Rectangle(0, 0, panelView.Width, panelView.Height));

			if (_voxelViewController != null)
				_voxelViewController.DrawCross(e.Graphics, panelView.Size);
		}

		private void DrawImage(Graphics g, Rectangle bounds)
		{
			if (_imageVoxelBox != null)
			{
				var colorMatrix = new ColorMatrix(
					new[]
						{
							new[] {1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
							new[] {0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
							new[] {0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
							new[] {0.0f, 0.0f, 0.0f, _alphaBox, 0.0f},
							new[] {0.0f, 0.0f, 0.0f, 0.0f, 1.0f}
						});

				var imageAttributes = new ImageAttributes();
				imageAttributes.SetColorMatrix(
					colorMatrix,
					ColorMatrixFlag.Default,
					ColorAdjustType.Bitmap);

				g.DrawImage(_imageVoxelBox,
					new Rectangle(bounds.Left + 40, bounds.Top + 20, panelView.Width - 60, panelView.Height - 40),
					_voxelViewController.Bounds.Left - 0.5f,
					_voxelViewController.Bounds.Top - 0.5f,
					_voxelViewController.Bounds.Width,
					_voxelViewController.Bounds.Height,
					GraphicsUnit.Pixel,
					imageAttributes);
			}

			if (_imageVoxelRes != null)
			{
				var colorMatrix = new ColorMatrix(
					new[]
						{
							new[] {1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
							new[] {0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
							new[] {0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
							new[] {0.0f, 0.0f, 0.0f, _alphaRes, 0.0f},
							new[] {0.0f, 0.0f, 0.0f, 0.0f, 1.0f}
						});

				var imageAttributes = new ImageAttributes();
				imageAttributes.SetColorMatrix(
					colorMatrix,
					ColorMatrixFlag.Default,
					ColorAdjustType.Bitmap);

				g.DrawImage(_imageVoxelRes,
					new Rectangle(bounds.Left + 40, bounds.Top + 20, panelView.Width - 60, panelView.Height - 40),
					_voxelViewController.Bounds.Left - 0.5f,
					_voxelViewController.Bounds.Top - 0.5f,
					_voxelViewController.Bounds.Width,
					_voxelViewController.Bounds.Height,
					GraphicsUnit.Pixel,
					imageAttributes);
			}

			if (_voxelViewController != null && _voxelViewController.RefCount > 0)
				_voxelViewController.DrawGrid(g, Font, bounds);
		}

		private void panelColorBar_Paint(object sender, PaintEventArgs e)
		{
			DrawColorBar(e.Graphics, new Rectangle(0, 0, panelColorBar.Width, panelColorBar.Height));
		}

		private void DrawColorBar(Graphics g, Rectangle bounds)
		{
			if (_voxelViewController != null && _voxelViewController.HasResult)
				_voxelViewController.DrawColorBar(g, Font, bounds);
		}

		private void VoxelViewControl_Paint(object sender, PaintEventArgs e)
		{
			DrawLabels(e.Graphics);
		}

		private void DrawLabels(Graphics g)
		{
			if (_voxelViewController != null && _voxelViewController.RefCount > 0)
			{
				var labelX = (_voxelViewController.Axis == 0) ? "Y, mm" : "X, mm";
				var labelY = (_voxelViewController.Axis == 2) ? "Y, mm" : "Z, mm";
				var sizeX = g.MeasureString(labelX, Font);
				var sizeY = g.MeasureString(labelY, Font);
				g.DrawString(labelX, Font, Brushes.Black, new PointF(panelView.Right - 20 - sizeX.Width / 2, panelView.Bottom));
				g.DrawString(labelY, Font, Brushes.Black, new PointF(panelView.Left - sizeY.Width, panelView.Top + 20 - sizeY.Height / 2));
			}
		}

		private void DrawTitle(Graphics g)
		{
			if (_voxelViewController != null && _voxelViewController.RefCount > 0)
			{
				var stringFormat = new StringFormat { Alignment = StringAlignment.Center, LineAlignment = StringAlignment.Center };
				g.DrawString(labelTitle.Text, labelTitle.Font, Brushes.Black,
					new RectangleF(labelTitle.Left, labelTitle.Top, labelTitle.Width, labelTitle.Height), stringFormat);
			}
		}

		private bool _busy;
		private bool _delayded;
		private readonly System.Threading.Timer _timer;

		public void RefreshImage()
		{
			if (_busy)
			{
				_delayded = true;
			}
			else
			{
				_busy = true;
				(new EmptyEventHandler(AsyncRefreshImage)).BeginInvoke(RefreshImageCallback, null);
			}
		}

		private void AsyncRefreshImage()
		{
			if (_delayded)
			{
				_delayded = false;
				AsyncRefreshImage();
			}
		}

		public void RefreshImageCallback(IAsyncResult ar)
		{
			if (this.InvokeRequired)
			{
				this.Invoke(new AsyncCallback(RefreshImageCallback), ar);
			}
			else
			{
				Refresh();
				_busy = false;
			}
		}

		public void UpdateImage()
		{
			if (_busy)
			{
				if (!_delayded)
				{
					_voxelViewController.Cancel = true;
					_delayded = true;
				}
			}
			else
			{
				this.UseWaitCursor = true;
				_busy = true;
				_timer.Change(0, 100);
				FormMain.EnableProgress();
				(new EmptyEventHandler(AsyncUpdateImage)).BeginInvoke(UpdateImageCallback, null);
			}
		}

		private void AsyncUpdateImage()
		{
			if (!ImageVoxelBoxValid)
			{
				var imageVoxelBox = _voxelViewController.CreateImageVoxelBox();
				if (imageVoxelBox != null)
				{
					_imageVoxelBox = imageVoxelBox;
					ImageVoxelBoxValid = true;
				}
			}

			if (!ImageVoxelResValid && _voxelViewController.HasResult && ImageVoxelBoxValid)
			{
				var imageVoxelRes = _voxelViewController.CreateImageVoxelRes();
				if (imageVoxelRes != null)
				{
					_imageVoxelRes = imageVoxelRes;
					ImageVoxelResValid = true;
				}
				else
				{
					ImageVoxelBoxValid = false;
				}
			}

			if (_delayded)
			{
				_delayded = false;
				AsyncUpdateImage();
			}
		}

		public void UpdateImageCallback(IAsyncResult ar)
		{
			_timer.Change(Timeout.Infinite, Timeout.Infinite);

			if (this.InvokeRequired)
			{
				this.Invoke(new AsyncCallback(UpdateImageCallback), ar);
			}
			else
			{
				Refresh();
				FormMain.DisableProgress();
				if (FormMain.DiagramsDockContent != null)
					FormMain.DiagramsDockContent.UpdateData();
				this.UseWaitCursor = false;
				_busy = false;
			}
		}

		private void TimerCallback(object state)
		{
			if (this.InvokeRequired)
			{
				this.Invoke(new TimerCallback(TimerCallback), state);
			}
			else
			{
				FormMain.SetProgress((int)_voxelViewController.Progress);
			}
		}

		private Point PointToAbs(Point location, bool center)
		{
			return (_voxelViewController != null) ? _voxelViewController.PointToAbs(location, panelView.Size, center) : Point.Empty;
		}

		private Point AbsToPoint(Point point)
		{
			return (_voxelViewController != null) ? _voxelViewController.AbsToPoint(point, panelView.Size) : Point.Empty;
		}

		private void DockVoxelRect(ref Rectangle voxelRect, Size voxelSize)
		{
			if (voxelRect.Right > voxelSize.Width)
				voxelRect.X = voxelSize.Width - voxelRect.Width;

			if (voxelRect.Bottom > voxelSize.Height)
				voxelRect.Y = voxelSize.Height - voxelRect.Height;

			if (voxelRect.X < 0)
				voxelRect.X = 0;

			if (voxelRect.Y < 0)
				voxelRect.Y = 0;

			if (voxelRect.Width > voxelSize.Width)
				voxelRect.Width = voxelSize.Width;

			if (voxelRect.Height > voxelSize.Height)
				voxelRect.Height = voxelSize.Height;
		}

		protected override void OnMouseWheel(MouseEventArgs e)
		{
			if (e.Location.X > panelView.Left + 40 && e.Location.X < panelView.Right - 20 &&
				e.Location.Y > panelView.Top + 20 && e.Location.Y < panelView.Bottom - 20)
			{
				var voxelRect = _voxelViewController.Bounds;
				var voxelSize = _voxelViewController.Size;
				var deltaX = voxelRect.Width / 10;
				var deltaY = voxelRect.Height / 10;
				if (deltaX == 0) deltaX = 1;
				if (deltaY == 0) deltaY = 1;

				var p1 = PointToAbs(new Point(e.Location.X - panelView.Left, e.Location.Y - panelView.Top), true);

				if (e.Delta > 0 && voxelRect.Width > voxelSize.Width / 20 && voxelRect.Height > voxelSize.Height / 20)
				{
					voxelRect.Width -= deltaX;
					voxelRect.Height -= deltaY;
				}
				else if (e.Delta < 0 && (voxelRect.X > 0 || voxelRect.Y > 0 || voxelRect.Width < voxelSize.Width || voxelRect.Height < voxelSize.Height))
				{
					voxelRect.Width += deltaX;
					voxelRect.Height += deltaY;
				}

				_voxelViewController.Bounds = voxelRect;

				var p2 = PointToAbs(new Point(e.Location.X - panelView.Left, e.Location.Y - panelView.Top), true);
				voxelRect.X -= p2.X - p1.X;
				voxelRect.Y -= p2.Y - p1.Y;
				_voxelViewController.Bounds = voxelRect;

				DockVoxelRect(ref voxelRect, voxelSize);
				_voxelViewController.Bounds = voxelRect;

				UpdateStatusBar(p2);
				panelView.Refresh();
			}
		}

		private bool _isMoving;
		private bool _isMoving2;
		private Point _startPoint;
		private Rectangle _startBounds;

		private bool HitCrossCenter(Point p)
		{
			var crossCenter = AbsToPoint(_voxelViewController.CrossCenter);
			return Math.Sqrt(Math.Pow((double)(p.X - crossCenter.X), 2.0) + Math.Pow((double)(p.Y - crossCenter.Y), 2.0)) < 15;
		}

		private void panelView_MouseDown(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
			{
				if (!_isMoving && !_isMoving2)
				{
					if (HitCrossCenter(e.Location))
						_isMoving2 = true;
					else
						_isMoving = true;

					_startPoint = e.Location;
					_startBounds = _voxelViewController.Bounds;
				}

				if (FormMain.MaterialsDockContent != null)
					FormMain.MaterialsDockContent.Material = _voxelViewController.GetMaterial(PointToAbs(e.Location, false));
			}
		}

		private void panelView_MouseMove(object sender, MouseEventArgs e)
		{
			if (_voxelViewController == null)
				return;

			var voxelRect = _voxelViewController.Bounds;
			var voxelSize = _voxelViewController.Size;

			if (_isMoving)
			{
				var deltaX = (int)((float)voxelRect.Width / (float)(panelView.Bounds.Width - 40) * (float)(_startPoint.X - e.Location.X));
				var deltaY = (int)((((float)voxelRect.Height) / ((float)(panelView.Bounds.Height - 40))) * ((float)(_startPoint.Y - e.Location.Y)));
				voxelRect.X = _startBounds.X + deltaX;
				voxelRect.Y = _startBounds.Y + deltaY;
				DockVoxelRect(ref voxelRect, voxelSize);
				_voxelViewController.Bounds = voxelRect;
				panelView.Refresh();
			}
			else if (_isMoving2)
			{
				var point = PointToAbs(e.Location, true);
				_voxelViewController.CrossCenter = point;
				if (FormMain.DiagramsDockContent != null)
					FormMain.DiagramsDockContent.UpdateData();
				panelView.Refresh();
			}

			if (e.Location.X > 40 && e.Location.X < panelView.Width - 20 &&
				e.Location.Y > 20 && e.Location.Y < panelView.Height - 20)
			{
				UpdateStatusBar(PointToAbs(e.Location, false));
			}

			Cursor = HitCrossCenter(e.Location) ? Cursors.SizeAll : DefaultCursor;

			panelView.Focus();
		}

		private void panelView_MouseUp(object sender, MouseEventArgs e)
		{
			_isMoving = false;
			_isMoving2 = false;
		}

		private void UpdateStatusBar(Point point)
		{
			var labelX = (_voxelViewController.Axis == 0) ? "Y" : "X";
			var labelY = (_voxelViewController.Axis == 2) ? "Y" : "Z";

			var absX = (_voxelViewController.Axis == 0)
				? point.X * _voxelViewController.BoxSizeY
				: point.X * _voxelViewController.BoxSizeX;

			var absY = (_voxelViewController.Axis == 2)
				? point.Y * _voxelViewController.BoxSizeX
				: point.Y * _voxelViewController.BoxSizeZ;

			var status = String.Format("Координаты: {0}={1} ({2}mm), {3}={4} ({5}mm). Материал: {6}",
				labelX, point.X, absX * 10, labelY, point.Y, absY * 10, _voxelViewController.GetMaterial(point));

			if (VoxelViewController.HasResult)
				status += String.Format(". Результат: {0:f2}", _voxelViewController.GetValue(point) / _voxelViewController.Hist);

			FormMain.SetStatus(status);
		}

		public void Export(int format)
		{
			int size;
			float boxSize;
			string fileName;
			string line1;
			string line2;
			string line3;

			switch (_voxelViewController.Axis)
			{
				case 0:
					size = (int)_voxelViewController.SizeX;
					boxSize = _voxelViewController.BoxSizeX;
					fileName = String.Format("{0}x__y{1}z{2}.txt", ResFileName,
					                         _voxelViewController.CrossCenter.X,
					                         _voxelViewController.CrossCenter.Y);
					line1 = String.Format("\"{0}, f(x), y={1}mm, z={2}mm\"", ResFileName,
					                      _voxelViewController.CrossCenter.X * _voxelViewController.BoxSizeY * 10,
					                      _voxelViewController.CrossCenter.Y * _voxelViewController.BoxSizeZ * 10);
					line2 = "\"x, mm";
					break;
				case 1:
					size = (int)_voxelViewController.SizeY;
					boxSize = _voxelViewController.BoxSizeY;
					fileName = String.Format("{0}x{1}y__z{2}.txt", ResFileName,
					                         _voxelViewController.CrossCenter.X,
					                         _voxelViewController.CrossCenter.Y);
					line1 = String.Format("\"{0}, x={1}mm, f(y), z={2}mm\"", ResFileName,
					                      _voxelViewController.CrossCenter.X * _voxelViewController.BoxSizeX * 10,
					                      _voxelViewController.CrossCenter.Y * _voxelViewController.BoxSizeZ * 10);
					line2 = "\"y, mm";
					break;
				case 2:
					size = (int)_voxelViewController.SizeZ;
					boxSize = _voxelViewController.BoxSizeZ;
					fileName = String.Format("{0}x{1}y{2}z__.txt", ResFileName,
					                         _voxelViewController.CrossCenter.X,
					                         _voxelViewController.CrossCenter.Y);
					line1 = String.Format("\"{0}, x={1}mm, y={2}mm, f(z)\"", ResFileName,
					                      _voxelViewController.CrossCenter.X * _voxelViewController.BoxSizeX * 10,
					                      _voxelViewController.CrossCenter.Y * _voxelViewController.BoxSizeY * 10);
					line2 = "\"z, mm";
					break;
				default:
					throw new NotSupportedException("_voxelViewController.Axis=" + _voxelViewController.Axis);
			}

			switch (_voxelViewController.ResultID)
			{
				case 1:
					line3 = "dose, MeV/g\"";
					break;
				case 2:
					line3 = "length span, cm\"";
					break;
				case 3:
					line3 = "time span, cm/c\"";
					break;
				case 4:
					line3 = "eq.dose, arb.units\"";
					break;
				default:
					throw new NotSupportedException("_voxelViewController.ResultID=" + _voxelViewController.ResultID);
			}

			using (var dlg = new SaveFileDialog())
			{
				if (format == 2)
					fileName = fileName.Replace(".txt", "#.txt");
				dlg.FileName = fileName;
				dlg.RestoreDirectory = true;
				dlg.Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";

				if (dlg.ShowDialog() == DialogResult.OK)
				{
					using (var writer = new StreamWriter(dlg.FileName))
					{
						writer.WriteLine(line1);
						writer.WriteLine(line2);
						writer.WriteLine(line3);
						for (var i = 0; i < size; i++)
						{
							var str = String.Format("{0:F}\t{1:F}", i * boxSize * 10,
								_voxelViewController.GetValue(i) / _voxelViewController.Hist);
							if (format == 2)
								str = String.Format("{0:D}\t{1}", i, str);
							writer.WriteLine(str);
						}
					}
				}
			}
		}
	}
}
