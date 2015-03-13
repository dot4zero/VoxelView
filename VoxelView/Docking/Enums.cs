using WeifenLuo.WinFormsUI.Docking;

namespace Common.Docking
{
	//SLN 15.03.2012: Эти классы позволяют
	//не расставлять в контролах using WeifenLuo.WinFormsUI.Docking;
	//(только в References надо ставить ссылку на проект WinFormsUI)

	/// <summary>Возможные парковки.</summary>
	public static class DockingAreas
	{
		/// <summary>Document</summary>
		public const DockAreas Document = DockAreas.Document;
		
		/// <summary>Float+Top+Bottom+Left+Right</summary>
		public const DockAreas Tools =
			DockAreas.Float |
			DockAreas.DockTop | DockAreas.DockBottom |
			DockAreas.DockLeft | DockAreas.DockRight;
		
		/// <summary>Top+Bottom+Left+Right</summary>
		public const DockAreas ToolsWithoutFloat =
			DockAreas.DockTop | DockAreas.DockBottom |
			DockAreas.DockLeft | DockAreas.DockRight;

		/// <summary>Везде, где угодно: Document+Float+Top+Bottom+Left+Right</summary>
		public const DockAreas Anywhere =
			DockAreas.Document | DockAreas.Float |
			DockAreas.DockTop | DockAreas.DockBottom |
			DockAreas.DockLeft | DockAreas.DockRight;
	}

	/// <summary>Первоначальная парковка.</summary>
	public static class DockingState
	{
		/// <summary>DockState.Document</summary>
		public const DockState Document = DockState.Document;
		/// <summary>DockState.Float</summary>
		public const DockState Float = DockState.Float;
		
		/// <summary>DockState.DockTop</summary>
		public const DockState Top = DockState.DockTop;
		/// <summary>DockState.DockLeft</summary>
		public const DockState Left = DockState.DockLeft;
		/// <summary>DockState.DockBottom</summary>
		public const DockState Bottom = DockState.DockBottom;
		/// <summary>DockState.DockRight</summary>
		public const DockState Right = DockState.DockRight;

		/// <summary>DockState.DockTopAutoHide</summary>
		public const DockState TopAutoHide = DockState.DockTopAutoHide;
		/// <summary>DockState.DockLeftAutoHide</summary>
		public const DockState LeftAutoHide = DockState.DockLeftAutoHide;
		/// <summary>DockState.DockBottomAutoHide</summary>
		public const DockState BottomAutoHide = DockState.DockBottomAutoHide;
		/// <summary>DockState.DockRightAutoHide</summary>
		public const DockState RightAutoHide = DockState.DockRightAutoHide;
	}

	/// <summary>Стиль докпанели.</summary>
	public static class DockingStyle
	{
		/// <summary>DocumentStyle.DockingWindow</summary>
		public const DocumentStyle Window = DocumentStyle.DockingWindow;
		
		/// <summary>DocumentStyle.DockingSdi</summary>
		public const DocumentStyle Sdi = DocumentStyle.DockingSdi;
	}
}
