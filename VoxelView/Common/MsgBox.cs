using System.Windows.Forms;
using System;
using System.Net.Sockets;
using System.Runtime.Remoting;

namespace Common
{
	/// <summary>
	/// Вызов стандартных сообщений
	/// </summary>
	public static class MsgBox
	{
		/// <summary>
		/// Вывод сообщения об ошибке.
		/// </summary>
		/// <param name="message">Текст сообщения</param>
		public static void ShowError(string message)
		{
			Show(message, null, MessageBoxButtons.OK, MessageBoxIcon.Error);
		}

		public static void ShowError(Exception ex)
		{
			Show(string.Empty, ex, MessageBoxButtons.OK, MessageBoxIcon.Error);
		}

		public static void ShowError(string message, Exception ex)
		{
			Show(message, ex, MessageBoxButtons.OK, MessageBoxIcon.Error);
		}

		public static void ShowExclamation(string message)
		{
			Show(message, null, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
		}

		public static void ShowExclamation(Exception ex)
		{
			Show(string.Empty, ex, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
		}

		public static void ShowExclamation(string message, Exception ex)
		{
			Show(message, ex, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
		}

		public static void ShowInfo(string message)
		{
			Show(message, null, MessageBoxButtons.OK, MessageBoxIcon.Information);
		}

		private static void Show(string message, Exception ex, MessageBoxButtons buttons, MessageBoxIcon icon)
		{
			if (ex != null)
			{
				while (ex.InnerException != null)
					ex = ex.InnerException;

				var exMessage = (ex is ApplicationException || ex is SocketException || ex is RemotingException)
					? ex.Message.Trim()
					: FormatException(ex);

				message = !String.IsNullOrEmpty(message)
					? (ex is ApplicationException || ex is SocketException || ex is RemotingException)
						? String.Format("{0} - {1}", message, exMessage)
						: String.Format("{0}\n{1}", message, exMessage)
					: exMessage;
			}

			MessageBox.Show(message, Application.ProductName, buttons, icon);
		}

		private static string FormatException(Exception ex)
		{
			return String.Format("{0}: {1}\n{2}", ex.GetType(), ex.Message.Trim(), ex.StackTrace.Trim());
		}
	}
}
