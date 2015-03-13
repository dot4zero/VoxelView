#pragma once

#include <string>

#define get_Handle(str) (str.m_string != nullptr ? str.m_string : System::String::Empty)
#define get_ThisHandle() (m_string != nullptr ? m_string : System::String::Empty)
#define verify_Handle() if (m_string == nullptr) m_string = System::String::Empty

public value class RefString
{
	System::String^ m_string;

public:
	typedef wchar_t char_type;
	typedef int     size_type;

	RefString(System::String^ string)
	{
		m_string = string != nullptr ? string : System::String::Empty;
	}

	RefString(const std::wstring& string)
	{
		using namespace System::Runtime::InteropServices;
		m_string = Marshal::PtrToStringUni(System::IntPtr((void*)string.c_str()));
	}

	RefString(const wchar_t* string)
	{
		using namespace System::Runtime::InteropServices;
		m_string = Marshal::PtrToStringUni(System::IntPtr((void*)string));
	}

	RefString(wchar_t c)
	{
		const wchar_t string[] = { c, 0 };
		using namespace System::Runtime::InteropServices;
		m_string = Marshal::PtrToStringUni(System::IntPtr((void*)string));
	}

	RefString(const std::string& string)
	{
		using namespace System::Runtime::InteropServices;
		m_string = Marshal::PtrToStringAnsi(System::IntPtr((void*)string.c_str()));
	}

	RefString(const char* string)
	{
		using namespace System::Runtime::InteropServices;
		m_string = Marshal::PtrToStringAnsi(System::IntPtr((void*)string));
	}

	RefString(char c)
	{
		const char string[] = { c, 0 };
		using namespace System::Runtime::InteropServices;
		m_string = Marshal::PtrToStringAnsi(System::IntPtr((void*)string));
	}

	RefString (int value)
	{
		m_string = System::Convert::ToString(value);
	}

	RefString (long value)
	{
		m_string = System::Convert::ToString(value);
	}

	RefString (float value)
	{
		m_string = value.ToString("E");
	}

	RefString (double value)
	{
		m_string = value.ToString("E");
	}

	///

	System::String^ operator -> ()
	{
		return get_ThisHandle();
	}

	static operator System::String^ (RefString string)
	{
		return string.m_string;
	}

	static operator RefString (System::String^ string)
	{
		return RefString(string);
	}

	///
	
	static operator std::string (RefString string)
	{
		using namespace System::Runtime::InteropServices;
		if (System::String::IsNullOrEmpty(string.m_string)) return std::string();
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(get_Handle(string))).ToPointer();
		std::string ret = chars;
		Marshal::FreeHGlobal(System::IntPtr((void*)chars));
		return ret;
	}

	static operator RefString (std::string string)
	{
		return RefString(string);
	}

	static operator RefString (const char* string)
	{
		return RefString(string);
	}

	static operator RefString (int value)
	{
		return RefString(System::Convert::ToString(value));
	}

	static operator RefString (long value)
	{
		return RefString(System::Convert::ToString(value));
	}

	static operator RefString (float value)
	{
		return RefString(value.ToString("E"));
	}

	static operator RefString (double value)
	{
		return RefString(value.ToString("E"));
	}

	///

	static operator std::wstring (RefString string)
	{
		using namespace System::Runtime::InteropServices;
		if (System::String::IsNullOrEmpty(string.m_string)) return std::wstring();
		const wchar_t* chars = (const wchar_t*)(Marshal::StringToHGlobalUni(get_Handle(string))).ToPointer();
		std::wstring ret = chars;
		Marshal::FreeHGlobal(System::IntPtr((void*)chars));
		return ret;
	}

	static operator RefString (std::wstring string)
	{
		return RefString(string);
	}

	static operator RefString (const wchar_t* string)
	{
		return RefString(string);
	}

	///

	static RefString operator + (RefString lhs, RefString rhs)
	{
		return RefString(get_Handle(lhs) + get_Handle(rhs));
	}

	///

	static bool operator == (RefString lhs, RefString rhs)
	{
		return get_Handle(lhs) == get_Handle(rhs);
	}

	static bool operator != (RefString lhs, RefString rhs)
	{
		return get_Handle(lhs) != get_Handle(rhs);
	}

	///

	const char* c_str()
	{
		if (empty()) return "";	
		using namespace System::Runtime::InteropServices;
		return (const char*)(Marshal::StringToHGlobalAnsi(m_string).ToPointer());
	}

	char* str()
	{
		if (empty()) return nullptr;
		using namespace System::Runtime::InteropServices;
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(m_string).ToPointer());
		char* ret = new char[m_string->Length+1];
		memcpy(ret, chars, m_string->Length);
		ret[m_string->Length] = '\0';
		Marshal::FreeHGlobal(System::IntPtr((void*)chars));
		return ret;
	}

	size_type size()
	{
		return m_string != nullptr ? m_string->Length : 0;
	}

	size_type length()
	{
		return m_string != nullptr ? m_string->Length : 0;
	}

	bool empty()
	{
		return System::String::IsNullOrEmpty(m_string);
	}

	void clear()
	{
		m_string = System::String::Empty;
	}

	void erase()
	{
		m_string = System::String::Empty;
	}

	void erase(size_type pos)
	{
		m_string = get_ThisHandle()->Remove(pos);
	}
	
	void erase(size_type pos, size_type n)
	{
		m_string = get_ThisHandle()->Remove(pos, n);
	}

	void replace(size_type pos, size_type n, RefString str)
	{
		verify_Handle();
		m_string = m_string->Remove(pos, n);
		m_string = m_string->Insert(pos, str);
	}

	RefString% operator += (RefString str)
	{
		verify_Handle();
		m_string = m_string + str.m_string;
		return *this;
	}

	///

	size_type find (RefString str)
	{
		return m_string != nullptr ? m_string->IndexOf(get_Handle(str)) : -1;
	}
	
	size_type find (RefString str, size_type pos)
	{
		return get_ThisHandle()->IndexOf(get_Handle(str), pos);
	}

	size_type find (char_type c)
	{
		return m_string != nullptr ? m_string->IndexOf(c) : -1;
	}

	size_type find (char_type c, size_type pos)
	{
		return get_ThisHandle()->IndexOf(c, pos);
	}

	///

	size_type rfind(RefString str)
	{
		return m_string != nullptr ? m_string->LastIndexOf(get_Handle(str)) : -1;
	}
	
	size_type rfind(RefString str, size_type pos)
	{
		return get_ThisHandle()->LastIndexOf(get_Handle(str), pos);
	}
	
	size_type rfind(char_type c)
	{
		return m_string != nullptr ? m_string->LastIndexOf(c) : -1;
	}

	size_type rfind(char_type c, size_type pos)
	{
		return get_ThisHandle()->LastIndexOf(c, pos);
	}

	///

	RefString substr(size_type pos)
	{
		return RefString(get_ThisHandle()->Substring(pos));
	}

	RefString substr(size_type pos, size_type n)
	{
		return RefString(get_ThisHandle()->Substring(pos, n));
	}

	///

	int compare(RefString str)
	{
		return System::String::Compare(get_ThisHandle(), get_Handle(str));
	}

	int compare(size_type p0, size_type n0, RefString str)
	{
		return System::String::Compare(get_ThisHandle(), p0, get_Handle(str), 0, n0);
	}

	int compare(size_type p0, size_type n0, RefString str, size_type p1)
	{
		return System::String::Compare(get_ThisHandle(), p0, get_Handle(str), p1, n0);
	}

	///

	//
  // Below you can find non standard features (std::string does not have them)
  //

	int compareNoCase(RefString str)
	{
		return System::String::Compare(get_ThisHandle(), get_Handle(str), true);
	}

	int compareNoCase(size_type p0, size_type n0, RefString str)
	{
		return System::String::Compare(get_ThisHandle(), p0, get_Handle(str), 0, n0, true);
	}

	int compareNoCase(size_type p0, size_type n0, RefString str, size_type p1)
	{
		return System::String::Compare(get_ThisHandle(), p0, get_Handle(str), p1, n0, true);
	}

	///

	RefString toLower()
	{
		return RefString(get_ThisHandle()->ToLower());
	}

	RefString toUpper()
	{
		return RefString(get_ThisHandle()->ToUpper());
	}

	///

	int toInt32()
	{
		try	{	return System::Convert::ToInt32(get_ThisHandle()); } catch(...) { return 0; }
	}

	unsigned int toUInt32()
	{
		try	{	return System::Convert::ToUInt32(get_ThisHandle()); } catch(...) { return 0; }
	}

	__int64 toInt64()
	{
		try	{	return System::Convert::ToInt64(get_ThisHandle()); } catch(...) { return 0; }
	}

	float toFloat()
	{
		try	{	return System::Convert::ToSingle(get_ThisHandle()); } catch(...) { return 0; }
	}

	double toDouble()
	{
		try	{	return System::Convert::ToDouble(get_ThisHandle()); } catch(...) { return 0; }
	}

	///

	RefString toString(int value)
	{
		return RefString(System::Convert::ToString(value));
	}

	RefString toString(unsigned int value)
	{
		return RefString(System::Convert::ToString(value));
	}

	RefString toString(__int64 value)
	{
		return RefString(System::Convert::ToString(value));
	}

	RefString toString(float value)
	{
		return RefString(System::Convert::ToString(value));
	}

	RefString toString(double value)
	{
		return RefString(System::Convert::ToString(value));
	}
};

#undef get_Handle
#undef get_ThisHandle
#undef verify_Handle