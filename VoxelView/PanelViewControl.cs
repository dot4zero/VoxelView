using System.Windows.Forms;

namespace VoxelView
{
	public partial class PanelViewControl : Panel
	{
		public PanelViewControl()
		{
			InitializeComponent();

			SetStyle(ControlStyles.AllPaintingInWmPaint |
					 ControlStyles.OptimizedDoubleBuffer |
					 ControlStyles.ResizeRedraw,
					 true);
		}
	}
}
