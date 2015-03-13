using System.Xml;

namespace Common
{
	/// <summary>
	/// Непортящийся ( способный сохраняться )
	/// </summary>
	public interface IStorable
	{
		/// <summary>
		/// Вовращение имени своей секции
		/// </summary>
		/// <returns></returns>
		string GetNameSection();
		/// <summary>
		/// Сохранение в родительском xml-элементе
		/// </summary>
		/// <param name="xmlParent"></param>
		void SaveXml(XmlElement xmlParent);
		/// <summary>
		/// Восстановление из родительского xml-элемента
		/// </summary>
		/// <param name="xmlParent"></param>
		void LoadXml(XmlElement xmlParent);
	}
}
