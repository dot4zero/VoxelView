using System;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Collections.Generic;

namespace Common
{
	/// <summary>
	/// Метод создания экземпляра объекта, поддерживающего интерфейс IStorable.
	/// </summary>
	/// <returns></returns>
	public delegate IStorable StorableObjectCreator();

	static public class IOxml
	{
		#region Culture
		private static readonly CultureInfo s_culture = CultureInfo.InvariantCulture;
		//private static IFormatProvider format = CultureInfo.InvariantCulture;

		static public CultureInfo Culture
		{
			get { return s_culture; }
		}
		#endregion

		#region CreateSection
		/// <summary>
		/// Метод: возвращает созданную секцию с заданным именем в заданном родительском разделе
		/// </summary>
		/// <param name="xmlParent"></param>
		/// <param name="nameChild"></param>
		/// <returns></returns>
		static public XmlElement CreateSection(XmlElement xmlParent, string nameChild)
		{
			XmlElement result = xmlParent.OwnerDocument.CreateElement(nameChild);
			xmlParent.AppendChild(result);
			return result;
		}
		#endregion
		#region DeleteSection
		/// <summary>
		/// Метод: удаляет секцию с заданным именем в заданном родительском разделе
		/// </summary>
		/// <param name="xmlParent"></param>
		/// <param name="nameChild"></param>
		static public void DeleteSection(XmlElement xmlParent, string nameChild)
		{
			XmlElement node = IOxml.GetSection(xmlParent, nameChild);
			if (node != null)
			{
				xmlParent.RemoveChild(node);
			}
		}
		#endregion
		#region GetSection
		/// <summary>
		/// Метод: возвращает первую попавшуюся секцию с заданным именем в заданном родительском разделе
		/// </summary>
		/// <param name="xmlParent"></param>
		/// <param name="nameChild"></param>
		/// <returns></returns>
		//static public XmlElement GetSection(XmlElement xmlParent, string nameChild)
		//{
		//  XmlNodeList nodes = xmlParent.GetElementsByTagName(nameChild);
		//  return (nodes.Count > 0) ? (XmlElement)nodes[0] : null;
		//}

		static public XmlElement GetSection(XmlNode xmlParent, string nameChild)
		{
			if (xmlParent != null)
			{
				XmlNode childNode = xmlParent.FirstChild;

				while (childNode != null)
				{
					if (childNode.Name == nameChild)
						return childNode as XmlElement;
					childNode = childNode.NextSibling;
				}
			}
			return null;
		}
		#endregion

		#region CreateUniqueSection
		/// <summary>
		/// Метод: возвращает созданную секцию с заданным именем в заданном родительском разделе
		/// </summary>
		/// <param name="xmlParent"></param>
		/// <param name="nameChild"></param>
		/// <returns></returns>
		static public XmlElement CreateUniqueSection(XmlElement xmlParent, string nameChild)
		{
			RemoveAllSections(xmlParent, nameChild);
			return CreateSection(xmlParent, nameChild);
		}
		#endregion
		#region RemoveAllSections
		/// <summary>
		/// Метод: удаляет все секции с заданным именем в заданном родительском разделе
		/// </summary>
		/// <param name="xmlParent"></param>
		/// <param name="nameChild"></param>
		static public void RemoveAllSections(XmlElement xmlParent, string nameChild)
		{
			if (xmlParent != null)
			{
				XmlNode childNode = xmlParent.FirstChild;
				while (childNode != null)
				{
					XmlNode next = childNode.NextSibling;
					if (childNode.Name == nameChild)
					{
						xmlParent.RemoveChild(childNode);
					}
					childNode = next;
				}
			}
		}
		#endregion

		#region Копирование/Клонирование секций
		static readonly XmlDocument _tmpXmlDoc = new XmlDocument();
		public static XmlElement CreateTempSection(string nameSection)
		{
			return _tmpXmlDoc.CreateElement(nameSection);
		}

		/// <summary>
		/// Метод: создает клон XmlElement не в новом XmlDocument
		/// </summary>
		public static XmlElement CloneSection(XmlElement xmlSection)
		{
			return CloneSection(_tmpXmlDoc, xmlSection);
		}
		/// <summary>
		/// Метод: создает клон xmlItem в документе xmlDoc
		/// </summary>
		/// <param name="xmlDoc"></param>
		/// <param name="xmlItem"></param>
		/// <returns></returns>
		public static XmlElement CloneSection(XmlDocument xmlDoc, XmlElement xmlSection)
		{
			XmlElement xml = xmlDoc.CreateElement(xmlSection.Name);
			xml.InnerXml = xmlSection.InnerXml;
			foreach (XmlAttribute attribute in xmlSection.Attributes)
			{
				xml.SetAttribute(attribute.Name, attribute.Value);
			}
			return xml;
		}
		public static XmlElement CopySection(XmlElement xmlSrcSection, XmlElement xmlDstParentSection)
		{
			XmlElement xml = CloneSection(xmlDstParentSection.OwnerDocument, xmlSrcSection);
			xmlDstParentSection.AppendChild(xml);
			return xml;
		}

		#endregion

		/// <summary>
		/// Создание xml-элемента из его строкового представления.
		/// </summary>
		/// <param name="innerXml"></param>
		/// <returns></returns>
		public static XmlElement FromString(string innerXml)
		{
			XmlDocument xmlDoc = new XmlDocument();
			XmlElement result = xmlDoc.CreateElement("Tmp");
			result.InnerXml = (innerXml) ?? string.Empty;
			return result;
		}

		#region RemoveSectionIfEmpty
		/// <summary>
		/// Метод: удаляет секцию в заданном родительском разделе, если она пустая
		/// </summary>
		/// <param name="xmlParent"></param>
		/// <param name="xmlChild"></param>
		static public void RemoveSectionIfEmpty(XmlElement xmlParent, XmlElement xmlChild)
		{
			if (xmlChild.Attributes.Count == 0 && xmlChild.ChildNodes.Count == 0)
			{
				xmlParent.RemoveChild(xmlChild);
			}
		}
		#endregion
		#region GetValueAttribute
		static public string GetValueAttribute(XmlElement xmlElement, string nameAttribute)
		{
			XmlAttribute a = xmlElement.Attributes[nameAttribute];
			return (a != null) ? a.Value : null;
		}
		#endregion
		#region WriteDocToFile
		/// <summary>
		/// Запись Xml-документа в файл
		/// </summary>
		/// <param name="xmlDoc"></param>
		/// <param name="xmlFile"></param>
		static public void WriteDocToFile(XmlDocument xmlDoc, string xmlFile)
		{
			XmlWriterSettings settings = new XmlWriterSettings();
			settings.CheckCharacters = false;
			settings.Indent = true;
			settings.CloseOutput = true;
			//settings.NewLineOnAttributes = true;
			using (XmlWriter xmlWriter = XmlWriter.Create(xmlFile, settings))
			{
				xmlDoc.Save(xmlWriter);
			}
		}
		#endregion

		#region Read, Write double?
		/// <summary>
		/// Чтение значения заданного атрибута
		/// </summary>
		/// <param name="xmlElement"></param>
		/// <param name="nameAttribute"></param>
		/// <returns></returns>
		static public double? ReadDoubleNull(XmlElement xmlElement, string nameAttribute)
		{
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);

			double? result = null;

			if (value != null)
			{
				double val;
				double.TryParse(value, NumberStyles.Any, s_culture, out val);
				result = val;
			}

			return result;
		}

		/// <summary>
		/// Запись значения заданного атрибута
		/// </summary>
		/// <param name="xmlElement">xml-элемент</param>
		/// <param name="nameAttribute">название атрибута</param>
		/// <param name="value">значение</param>
		static public void Write(XmlElement xmlElement, string nameAttribute, double? value)
		{
			if (value != null)
			{
				IOxml.Write(xmlElement, nameAttribute, value.Value);
			}
		}

		#endregion

		#region Read,Write double
		/// <summary>
		/// Чтение значения заданного атрибута
		/// </summary>
		/// <param name="xmlElement"></param>
		/// <param name="nameAttribute"></param>
		/// <returns></returns>
		static public double ReadDouble(XmlElement xmlElement, string nameAttribute)
		{
			return ReadDouble(xmlElement, nameAttribute, 0.0);
		}
		/// <summary>
		/// Чтение значения заданного атрибута, если его нет, то берется значение по умолчанию
		/// </summary>
		/// <param name="xmlElement"></param>
		/// <param name="nameAttribute"></param>
		/// <param name="defaultValue"></param>
		/// <returns></returns>
		static public double ReadDouble(XmlElement xmlElement, string nameAttribute, double defaultValue)
		{
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			double result = defaultValue;
			if (value != null)
			{
				double.TryParse(value, NumberStyles.Any, s_culture, out result);
			}
			return result;
		}
		/// <summary>
		/// Запись значения заданного атрибута
		/// </summary>
		/// <param name="xmlElement">xml-элемент</param>
		/// <param name="nameAttribute">название атрибута</param>
		/// <param name="value"></param>
		static public void Write(XmlElement xmlElement, string nameAttribute, double value)
		{
			xmlElement.SetAttribute(nameAttribute, value.ToString("G", s_culture));
		}
		/// <summary>
		/// Запись значения заданного атрибута в случае, если оно не равно значению по умолчанию
		/// </summary>
		/// <param name="xmlElement">xml-элемент</param>
		/// <param name="nameAttribute">название атрибута</param>
		/// <param name="value">значение атрибута</param>
		/// <param name="defaultValue">значение по умолчанию</param>
		static public void Write(XmlElement xmlElement, string nameAttribute, double value, double defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}

		static public void Write(XmlElement xmlElement, string nameAttribute, double value, object defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}

		#endregion
		#region Read,Write float

		static public float ReadFloat(XmlElement xmlElement, string nameAttribute)
		{
			return ReadFloat(xmlElement, nameAttribute, 0.0f);
		}
		static public float ReadFloat(XmlElement xmlElement, string nameAttribute, float defaultValue)
		{
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			return (value != null) ? float.Parse(value, (IFormatProvider)s_culture) : defaultValue;
		}

		static public void Write(XmlElement xmlElement, string nameAttribute, float value)
		{
			xmlElement.SetAttribute(nameAttribute, value.ToString("F", s_culture));
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, float value, float defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, float value, object defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}

		#endregion
		#region Read,Write int

		static public int ReadInt(XmlElement xmlElement, string nameAttribute)
		{
			return ReadInt(xmlElement, nameAttribute, 0);
		}
		static public int ReadInt(XmlElement xmlElement, string nameAttribute, int defaultValue)
		{
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			return (value != null) ? int.Parse(value, s_culture) : defaultValue;
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, int value)
		{
			xmlElement.SetAttribute(nameAttribute, value.ToString(s_culture));
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, int value, int defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, int value, object defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}

		#endregion
		#region Read,Write string

		static public string ReadString(XmlNode xmlNode, string nameAttribute)
		{
			return ReadString(xmlNode as XmlElement, nameAttribute);
		}

		static public string ReadString(XmlElement xmlElement, string nameAttribute)
		{
			return ReadString(xmlElement, nameAttribute, "");
		}
		static public string ReadString(XmlElement xmlElement, string nameAttribute, string defaultValue)
		{
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			return value ?? defaultValue;
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, string value)
		{
			xmlElement.SetAttribute(nameAttribute, value);
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, string value, string defaultValue)
		{
			if (!object.Equals(value, defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, string value, object defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}

		#endregion
		#region Read,Write bool

		static public bool ReadBool(XmlElement xmlElement, string nameAttribute)
		{
			return ReadBool(xmlElement, nameAttribute, false);
		}
		static public bool ReadBool(XmlElement xmlElement, string nameAttribute, bool defaultValue)
		{
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			return (value != null) ? bool.Parse(value) : defaultValue;
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, bool value)
		{
			xmlElement.SetAttribute(nameAttribute, value.ToString());
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, bool value, bool defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, bool value, object defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}

		#endregion
		#region Read,Write Color

		static public Color ReadColor(XmlElement xmlElement, string nameAttribute)
		{
			return ReadColor(xmlElement, nameAttribute, Color.Black);
		}
		static public Color ReadColor(XmlElement xmlElement, string nameAttribute, Color defaultValue)
		{
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			if (value == "?")
			{
				return Color.Empty;
			}
			else
			{
				return (value != null) ? Color.FromArgb(int.Parse(value, s_culture)) : defaultValue;
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, Color value)
		{
			if (value.IsEmpty)
			{
				IOxml.Write(xmlElement, nameAttribute, "?");
			}
			else
			{
				IOxml.Write(xmlElement, nameAttribute, value.ToArgb());
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, Color value, Color defaultValue)
		{
			if (value.ToArgb() != defaultValue.ToArgb())
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, Color value, object defaultValue)
		{
			if (defaultValue != null)
			{
				IOxml.Write(xmlElement, nameAttribute, value, (Color)defaultValue);
			}
			else
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}

		#endregion

		#region Read, Write TimeSpan
		static public TimeSpan ReadTimeSpan(XmlElement xmlElement, string nameAttribute)
		{
			return ReadTimeSpan(xmlElement, nameAttribute, TimeSpan.Zero);
		}
		static public TimeSpan ReadTimeSpan(XmlElement xmlElement, string nameAttribute, TimeSpan defaultValue)
		{
			TimeSpan result;
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			return (TimeSpan.TryParse(value, out result)) ? result : defaultValue;
		}

		static public void Write(XmlElement xmlElement, string nameAttribute, TimeSpan value)
		{
			xmlElement.SetAttribute(nameAttribute, value.ToString());
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, TimeSpan value, TimeSpan defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}

		#endregion

		#region Read,Write Guid?
		static public Guid? ReadGuidNullable(XmlElement xmlElement, string nameAttribute)
		{
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			return (value != null) ? new Guid?(new Guid(value)) : null;
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, Guid? value)
		{
			if (value != null)
				xmlElement.SetAttribute(nameAttribute, value.Value.ToString());
		}
		#endregion

		#region Read,Write DateTime

		static public DateTime ReadDateTime(XmlElement xmlElement, string nameAttribute)
		{
			return ReadDateTime(xmlElement, nameAttribute, DateTime.Now);
		}
		static public DateTime ReadDateTime(XmlElement xmlElement, string nameAttribute, DateTime defaultValue)
		{
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			return (value != null) ? DateTime.Parse(value, s_culture) : defaultValue;
		}
		static public DateTime[] ReadDateTimes(XmlElement xmlElement, string nameAttribute)
		{
			string s = IOxml.ReadString(xmlElement, nameAttribute);
			if (!string.IsNullOrEmpty(s))
			{
				string[] ids = s.Split(new char[] { ';' });
				DateTime[] list = new DateTime[ids.Length];
				for (int i = 0; i < ids.Length; i++)
				{
					DateTime result;
					DateTime.TryParse(ids[i], (IFormatProvider)s_culture, DateTimeStyles.None, out result);
					list[i] = result;
				}
				return list;
			}
			else
			{
				return new DateTime[0];
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, DateTime value)
		{
			xmlElement.SetAttribute(nameAttribute, value.ToString(s_culture));
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, DateTime value, DateTime defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, DateTime value, object defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value);
			}
		}

		#endregion
		#region Read,Write Point3D

		//static public Geometry.Point3D ReadPoint3D(XmlElement xmlElement, string nameAttribute)
		//{
		//    return ReadPoint3D(xmlElement, nameAttribute, Geometry.Point3D.Empty);
		//}
		//static public Geometry.Point3D ReadPoint3D(XmlElement xmlElement, string nameAttribute, Geometry.Point3D defaultValue)
		//{
		//    string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
		//    return (value != null) ? Geometry.Point3D.Parse(value, s_culture) : defaultValue;
		//}
		//static public void Write(XmlElement xmlElement, string nameAttribute, Geometry.Point3D value)
		//{
		//    xmlElement.SetAttribute(nameAttribute, value.ToString(s_culture));
		//}

		#endregion
		#region Read,Write Rectangle

		static public Rectangle ReadRectangle(XmlElement xmlElement, string nameAttribute)
		{
			return ReadRectangle(xmlElement, nameAttribute, Rectangle.Empty);
		}

		static public Rectangle ReadRectangle(XmlElement xmlElement, string nameAttribute, Rectangle defaultValue)
		{
			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			return (value != null) ?
				(Rectangle)new RectangleConverter().ConvertFromString(value) : defaultValue;
		}

		static public void Write(XmlElement xmlElement, string nameAttribute, Rectangle value)
		{
			xmlElement.SetAttribute(nameAttribute, new RectangleConverter().ConvertToString(value));
		}

		#endregion
		#region ReadObject,WriteObject : двоичная сериализация -> строка -> xml

		static public object ReadObject(XmlElement xmlElement)
		{
			BinaryFormatter f = new BinaryFormatter();
			byte[] buff = Convert.FromBase64String(xmlElement.InnerText);
			object o = null;
			using (MemoryStream s = new MemoryStream(buff))
			{
				o = f.Deserialize(s);
			}
			return o;
		}
		static public void WriteObject(XmlElement xmlElement, object o)
		{
			BinaryFormatter f = new BinaryFormatter();
			f.AssemblyFormat = System.Runtime.Serialization.Formatters.FormatterAssemblyStyle.Simple;
			f.TypeFormat = System.Runtime.Serialization.Formatters.FormatterTypeStyle.TypesWhenNeeded;
			byte[] buff;
			using (MemoryStream s = new MemoryStream())
			{
				f.Serialize(s, o);
				buff = s.GetBuffer();
			}
			xmlElement.InnerText = Convert.ToBase64String(buff);
		}
		#endregion
		#region ReadObjectAs,WriteObjectAs object : запись значения заданного типа (опасен для Nullable-типов)

		static public object ReadObjectAs(XmlElement xmlElement, string nameAttribute, Type type)
		{
			string s = IOxml.ReadString(xmlElement, nameAttribute);
			if ((s == "?") && !type.Equals(typeof(string)))
			{
				return null;
			}

			if (type != null)
			{
				if (type.IsEnum) { return IOxml.ReadEnum(xmlElement, nameAttribute, type); }
				else if (type.Equals(typeof(bool))) { return IOxml.ReadBool(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(double))) { return IOxml.ReadDouble(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(double?))) { return IOxml.ReadDouble(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(float))) { return IOxml.ReadFloat(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(float?))) { return IOxml.ReadFloat(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(int))) { return IOxml.ReadInt(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(int?))) { return IOxml.ReadInt(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(string))) { return IOxml.ReadString(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(Color))) { return IOxml.ReadColor(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(DateTime))) { return IOxml.ReadDateTime(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(DateTime?))) { return IOxml.ReadDateTime(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(TimeSpan))) { return IOxml.ReadTimeSpan(xmlElement, nameAttribute); }
				else if (type.Equals(typeof(object))) { return null; }
				else
					throw new ArgumentException(
						string.Format(s_culture, "ReadObjectAs: Неподдерживаемый тип {0}", type.FullName));
			}
			return null;
		}
		static public void WriteObjectAs(XmlElement xmlElement, string nameAttribute, object o, Type type)
		{
			if (o == null)
			{
				IOxml.Write(xmlElement, nameAttribute, "?");
			}
			else if (type != null)
			{
				if (type.IsEnum) { IOxml.WriteEnum(xmlElement, nameAttribute, o); }
				else if (type.Equals(typeof(bool))) { IOxml.Write(xmlElement, nameAttribute, (bool)o); }
				else if (type.Equals(typeof(double))) { IOxml.Write(xmlElement, nameAttribute, (double)o); }
				else if (type.Equals(typeof(double?))) { IOxml.Write(xmlElement, nameAttribute, (double)o); }
				else if (type.Equals(typeof(float))) { IOxml.Write(xmlElement, nameAttribute, (float)o); }
				else if (type.Equals(typeof(float?))) { IOxml.Write(xmlElement, nameAttribute, (float)o); }
				else if (type.Equals(typeof(int))) { IOxml.Write(xmlElement, nameAttribute, (int)o); }
				else if (type.Equals(typeof(int?))) { IOxml.Write(xmlElement, nameAttribute, (int)o); }
				else if (type.Equals(typeof(string))) { IOxml.Write(xmlElement, nameAttribute, (string)o); }
				else if (type.Equals(typeof(Color))) { IOxml.Write(xmlElement, nameAttribute, (Color)o); }
				else if (type.Equals(typeof(DateTime))) { IOxml.Write(xmlElement, nameAttribute, (DateTime)o); }
				else if (type.Equals(typeof(DateTime?))) { IOxml.Write(xmlElement, nameAttribute, (DateTime)o); }
				else if (type.Equals(typeof(object))) { IOxml.Write(xmlElement, nameAttribute, "?"); }
				else if (type.Equals(typeof(TimeSpan))) { IOxml.Write(xmlElement, nameAttribute, (TimeSpan)o); }
				else
					throw new ArgumentException(
						string.Format(s_culture, "WriteObjectAs: Неподдерживаемый тип {0}", type.FullName));
			}
		}
		#endregion
		#region Read,Write enum

		static public TEnum ReadEnum<TEnum>(XmlElement xmlElement, string nameAttribute)
		{
			return ReadEnum<TEnum>(xmlElement, nameAttribute, (TEnum)Enum.ToObject(typeof(TEnum), 0));
		}

		static public TEnum ReadEnum<TEnum>(XmlElement xmlElement, string nameAttribute, TEnum defaultValue)
		{
			Type t = typeof(TEnum);
			if (!t.IsEnum)
			{
				throw new ArgumentException(string.Format(s_culture, "{0}- не Enum", t));
			}

			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			try
			{
				return (value != null) ? (TEnum)Enum.Parse(typeof(TEnum), value) : defaultValue;
			}
			catch
			{
				return defaultValue;
			}
		}

		static public void WriteEnum<TEnum>(XmlElement xmlElement, string nameAttribute, TEnum value)
		{
			IOxml.Write(xmlElement, nameAttribute, value.ToString());
		}

		static public void WriteEnum<TEnum>(XmlElement xmlElement, string nameAttribute, TEnum value, TEnum defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value.ToString());
			}
		}

		static public object ReadEnum(XmlElement xmlElement, string nameAttribute, Type type)
		{
			if (!type.IsEnum)
			{
				throw new ArgumentException(string.Format(s_culture, "{0}- не Enum", type));
			}

			string value = IOxml.GetValueAttribute(xmlElement, nameAttribute);
			return (value != null) ? Enum.Parse(type, value) : Enum.GetValues(type).GetValue(0);
		}

		static public void WriteEnum(XmlElement xmlElement, string nameAttribute, object value)
		{
			IOxml.Write(xmlElement, nameAttribute, value.ToString());
		}

		static public void WriteEnum(XmlElement xmlElement, string nameAttribute, object value, object defaultValue)
		{
			if (!value.Equals(defaultValue))
			{
				IOxml.Write(xmlElement, nameAttribute, value.ToString());
			}
		}

		#endregion
		#region Read,Write int[]

		//static public IList<T> ReadList<T>(XmlElement xmlElement, string nameAttribute)
		//{
		//  IList<T> list = new List<T>();
		//  string s = IOxml.ReadString(xmlElement, nameAttribute);
		//  if (!string.IsNullOrEmpty(s))
		//  {
		//    string[] ids = s.Split(new char[] { ',' });
		//    for (int i = 0; i < ids.Length; i++)
		//    {
		//      T id = T.Parse(ids[i]);
		//      list.Add(id);
		//    }
		//  }
		//  return list;
		//}
		//static public void WriteList<T>(XmlElement xmlElement, string nameAttribute, IList<T> list)
		//{
		//  if (list != null && list.Count != 0)
		//  {
		//    StringBuilder sb = new StringBuilder();
		//    foreach (T item in list)
		//    {
		//      sb.Append(item);
		//      sb.Append(",");
		//    }
		//    sb.Remove(sb.Length - 1, 1);
		//    IOxml.Write(xmlElement, nameAttribute, sb.ToString());
		//  }
		//}
		static public int[] ReadInts(XmlElement xmlElement, string nameAttribute)
		{
			string s = IOxml.ReadString(xmlElement, nameAttribute);
			if (!string.IsNullOrEmpty(s))
			{
				string[] ids = s.Split(new char[] { ',', ';' });
				int[] list = new int[ids.Length];
				for (int i = 0; i < ids.Length; i++)
				{
					list[i] = int.Parse(ids[i], s_culture);
				}
				return list;
			}
			else
			{
				return new int[0];
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, int[] list)
		{
			if (list != null && list.Length != 0)
			{
				StringBuilder sb = new StringBuilder();
				foreach (int item in list)
				{
					sb.Append(item);
					sb.Append(',');
				}
				sb.Remove(sb.Length - 1, 1);
				IOxml.Write(xmlElement, nameAttribute, sb.ToString());
			}
		}

		#endregion
		#region Read,Write double[]

		static public double[] ReadDoubles(XmlElement xmlElement, string nameAttribute)
		{
			string s = IOxml.ReadString(xmlElement, nameAttribute);
			if (!string.IsNullOrEmpty(s))
			{
				string[] ids = s.Split(new char[] { ';' });
				double[] list = new double[ids.Length];
				for (int i = 0; i < ids.Length; i++)
				{
					//list[i] = double.Parse(ids[i]);

					double result;
					double.TryParse(ids[i], NumberStyles.Any, s_culture, out result);
					list[i] = result;
				}
				return list;
			}
			else
			{
				return new double[0];
			}
		}
		static public double?[] ReadNullableDoubles(XmlElement xmlElement, string nameAttribute)
		{
			string s = IOxml.ReadString(xmlElement, nameAttribute);
			if (!string.IsNullOrEmpty(s))
			{
				string[] ids = s.Split(new char[] { ';' });
				double?[] list = new double?[ids.Length];
				for (int i = 0; i < ids.Length; i++)
				{
					double result;
					if (double.TryParse(ids[i], NumberStyles.Any, s_culture, out result))
					{
						list[i] = result;
					}
					else
					{
						list[i] = null;
					}
				}
				return list;
			}
			else
			{
				return new double?[0];
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, double[] list)
		{
			if (list != null && list.Length != 0)
			{
				StringBuilder sb = new StringBuilder();
				foreach (double item in list)
				{
					sb.AppendFormat(s_culture, "{0}", item);
					sb.Append(';');
				}
				sb.Remove(sb.Length - 1, 1);
				IOxml.Write(xmlElement, nameAttribute, sb.ToString());
			}
		}

		#endregion
		#region Read,Write float[]

		static public float[] ReadFloats(XmlElement xmlElement, string nameAttribute, float[] defaultValue)
		{
			var result = IOxml.ReadFloats(xmlElement, nameAttribute);
			if (result.Length == 0)
			{
				result = defaultValue;
			}
			return result;
		}

		static public float[] ReadFloats(XmlElement xmlElement, string nameAttribute)
		{
			string s = IOxml.ReadString(xmlElement, nameAttribute);
			if (!string.IsNullOrEmpty(s))
			{
				var ids = s.Split(new char[] { ';' });
				var list = new float[ids.Length];
				for (int i = 0; i < ids.Length; i++)
				{
					float result;
					float.TryParse(ids[i], NumberStyles.Any, s_culture, out result);
					list[i] = result;
				}
				return list;
			}

			return new float[0];
		}
		//static public double?[] ReadNullableDoubles(XmlElement xmlElement, string nameAttribute)
		//{
		//  string s = IOxml.ReadString(xmlElement, nameAttribute);
		//  if (!string.IsNullOrEmpty(s))
		//  {
		//    string[] ids = s.Split(new char[] { ';' });
		//    double?[] list = new double?[ids.Length];
		//    for (int i = 0; i < ids.Length; i++)
		//    {
		//      double result;
		//      if (double.TryParse(ids[i], NumberStyles.Any, s_culture, out result))
		//      {
		//        list[i] = result;
		//      }
		//      else
		//      {
		//        list[i] = null;
		//      }
		//    }
		//    return list;
		//  }
		//  else
		//  {
		//    return new double?[0];
		//  }
		//}
		static public void Write(XmlElement xmlElement, string nameAttribute, float[] list)
		{
			if (list != null && list.Length != 0)
			{
				var sb = new StringBuilder();
				foreach (var item in list)
				{
					sb.AppendFormat(s_culture, "{0}", item);
					sb.Append(';');
				}
				sb.Remove(sb.Length - 1, 1);
				IOxml.Write(xmlElement, nameAttribute, sb.ToString());
			}
		}

		#endregion

		#region Read,Write IList<T>

		static public object ReadList(XmlElement xmlElement, string nameAttribute, Type type)
		{
			if (type == typeof(int))
				return ReadInts(xmlElement, nameAttribute);
			else if (type == typeof(double))
				return ReadDoubles(xmlElement, nameAttribute);
			else if (type == typeof(double?))
				return ReadNullableDoubles(xmlElement, nameAttribute);
			else if (type == typeof(DateTime))
				return ReadDateTimes(xmlElement, nameAttribute);
			else if (type == typeof(string))
				return ReadStrings(xmlElement, nameAttribute, ';');
			else
				return null;
		}

		static public void Write<T>(XmlElement xmlElement, string nameAttribute, IList<T> list, int firstIdx)
		{
			IOxml.Write<T>(xmlElement, nameAttribute, list, firstIdx, list.Count - 1);
		}

		static public void Write<T>(XmlElement xmlElement, string nameAttribute, IList<T> list, int firstIdx, int endIdx)
		{
			if (list != null && firstIdx >= 0 && endIdx < list.Count && firstIdx <= endIdx)
			{
				StringBuilder sb = new StringBuilder();
				for (int i = firstIdx; i <= endIdx; i++)
				{
					sb.AppendFormat(s_culture, "{0}", list[i]);
					sb.Append(';');
				}

				if (sb.Length > 0)
				{
					sb.Remove(sb.Length - 1, 1);
				}
				IOxml.Write(xmlElement, nameAttribute, sb.ToString());
			}
		}

		#endregion

		/// <summary>
		/// Читает список объектов типа IStorable из указанного элемента Xml-документа.
		/// </summary>
		/// <param name="xmlElement"></param>
		/// <param name="storableObjectCreator">Метод создания IStorable-объектов.</param>
		static public void Read(XmlElement xmlElement, StorableObjectCreator storableObjectCreator)
		{
			foreach (XmlNode currentXmlNode in xmlElement.ChildNodes)
			{
				IStorable storableObject = storableObjectCreator();
				storableObject.LoadXml(currentXmlNode as XmlElement);
			}
		}
		/// <summary>
		/// Записывает список сохраняемых объектов в указанный элемент Xml-документа.
		/// </summary>
		/// <param name="xmlElement"></param>
		/// <param name="list">Список сохраняемых объектов.</param>
		static public void Write(XmlElement xmlElement, IList<IStorable> list)
		{
			for (int i = 0; i < list.Count; i++)
			{
				IStorable storableObj = list[i];
				string currentSectionName = storableObj.GetNameSection();
				currentSectionName = string.Format(
					s_culture,
					"{0}{1}",
					string.IsNullOrEmpty(currentSectionName) ? "I" : currentSectionName,
					i);
				XmlElement currentXmlElement = IOxml.CreateSection(xmlElement, currentSectionName);
				storableObj.SaveXml(currentXmlElement);
			}
		}

		#region Read,Write string[]

		static public string[] ReadStrings(XmlElement xmlElement, string nameAttribute, char separator)
		{
			string s = IOxml.ReadString(xmlElement, nameAttribute);
			if (!string.IsNullOrEmpty(s))
			{
				string[] list = s.Split(new char[] { separator });
				return list;
			}
			else
			{
				return new string[0];
			}
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, string[] list, char separator)
		{
			if (list != null && list.Length != 0)
			{
				StringBuilder sb = new StringBuilder();
				foreach (string item in list)
				{
					sb.Append(item);
					sb.Append(separator);
				}
				sb.Remove(sb.Length - 1, 1);
				IOxml.Write(xmlElement, nameAttribute, sb.ToString());
			}
		}
		static public string[] ReadStrings(XmlElement xmlElement, string nameAttribute)
		{
			return ReadStrings(xmlElement, nameAttribute, ',');
		}
		static public void Write(XmlElement xmlElement, string nameAttribute, string[] list)
		{
			Write(xmlElement, nameAttribute, list, ',');
		}

		#endregion

		#region Проверка имени (схемы или задачи) на допустимость (с выводом сообщения)

		public static bool CheckFileName(string name, bool enableMessageBox)
		{
			if (name.IndexOfAny(new char[] { '\\', '/', ':', '*', '"', '<', '>', '|', '$' }) > -1)
			{
				if (enableMessageBox)
					MessageBox.Show("Имя не должно содержать символы : \\ / * ? \" < > | $",
							"Проверка имени на допустимость",
							MessageBoxButtons.OK,
							MessageBoxIcon.Exclamation);
				return false;
			}
			// Имя действительно
			return true;
		}
		#endregion
	}
}
