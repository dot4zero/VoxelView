namespace Common.Docking
{
	/// <summary>
	/// Делегат создания дока
	/// </summary>
	/// <param name="args">аргументы</param>
	/// <returns></returns>
	public delegate SafeDockContent CreateDock(string args);

	/// <summary>
	/// Делегат вывода сообщения
	/// </summary>
	/// <param name="msg">сообщение</param>
	public delegate void MessageChangedEventHandler(string msg);
}
