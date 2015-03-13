using System;
using System.Windows.Forms;

namespace VoxelView
{
	static class Program
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			var mainForm = new FormMain();
			FormMain.LoadConfig(mainForm);
			FormMain.LoadColorMap();
			Application.Run(mainForm);
		}
	}
}
