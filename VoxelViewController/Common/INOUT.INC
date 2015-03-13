//////////////////////////////////////////////////////////////////////////////
//                    процедуры ввода-вывода информации                     //
//////////////////////////////////////////////////////////////////////////////
#ifndef INPUT_OUTPUT_INFO_TYPE_INC
#define INPUT_OUTPUT_INFO_TYPE_INC
// подключаемые файлы
#include "service.inc"
#include <string.h>
#include "basedata.inc"

//================== основные структуры ввода-вывода ==================

//---------------------- двоичный ввод-вывод ------------------------

class BinReadType
{// устройство  для двоичного ввода
    BinReadType(BinReadType &); // заглушка
    void operator = (BinReadType &); // заглушка
    public:
    PRIZNAK_SERVICE_DLL BinReadType();
    PRIZNAK_SERVICE_DLL virtual ~BinReadType(); // inout.cpp
    virtual void read(void * x,size_t n) = 0;// ввод
    PRIZNAK_SERVICE_DLL BinReadType & operator >> (char *& S);
    PRIZNAK_SERVICE_DLL BinReadType & operator >> (char & x);
    BinReadType & operator >> (unsigned char & x){return (*this)>>(char &)x;}
    BinReadType & operator >> (signed char & x){return (*this)>>(char &)x;}
    PRIZNAK_SERVICE_DLL BinReadType & operator >> (short & x);
    BinReadType & operator >> (unsigned short & x){return (*this)>>(short &)x;}
    PRIZNAK_SERVICE_DLL BinReadType & operator >> (int & x);
    BinReadType & operator >> (unsigned int & x){return (*this)>>(int &)x;}
    PRIZNAK_SERVICE_DLL BinReadType & operator >> (long & x);
    BinReadType & operator >> (unsigned long & x){return (*this)>>(long &)x;}
    PRIZNAK_SERVICE_DLL BinReadType & operator >> (float & x);
    PRIZNAK_SERVICE_DLL BinReadType & operator >> (double & x);
    PRIZNAK_SERVICE_DLL BinReadType & operator >> (long double & x);
};// BinReadType

class BinReadPosType : public BinReadType
{// устройство для двоичного ввода с позиционированием
    public:
    virtual long pos() = 0; // возвращает текущую позицию
    virtual void pos(long) = 0;// устанавливает текущую позицию
    PRIZNAK_SERVICE_DLL BinReadPosType();
    PRIZNAK_SERVICE_DLL ~BinReadPosType();
};// BinReadPosType

class BinWriteType
{// устройство для двоичного вывода
    BinWriteType(BinWriteType &);     // заглушка
    void operator = (BinWriteType &); // заглушка
    public:
    PRIZNAK_SERVICE_DLL BinWriteType();
    PRIZNAK_SERVICE_DLL virtual ~BinWriteType();// inout.cpp
    virtual  void write(const void * x,size_t n) = 0;// вывод
    PRIZNAK_SERVICE_DLL BinWriteType & operator << (const char * S);
    PRIZNAK_SERVICE_DLL BinWriteType & operator << (const char x);
    BinWriteType & operator << (const unsigned char x){return (*this)<<(char)x;}
    BinWriteType & operator << (const signed char x){return (*this)<<(char)x;}
    PRIZNAK_SERVICE_DLL BinWriteType & operator << (const short x);
    BinWriteType & operator << (const unsigned short x){return (*this)<<(short)x;}
    PRIZNAK_SERVICE_DLL BinWriteType & operator << (const int x);
    BinWriteType & operator << (const unsigned int x){return (*this)<<(int)x;}
    PRIZNAK_SERVICE_DLL BinWriteType & operator << (const long x);
    BinWriteType & operator << (const unsigned long x){return (*this)<<(long)x;}
    PRIZNAK_SERVICE_DLL BinWriteType & operator << (const float & x);
    PRIZNAK_SERVICE_DLL BinWriteType & operator << (const double & x);
    PRIZNAK_SERVICE_DLL BinWriteType & operator << (const long double & x);
    PRIZNAK_SERVICE_DLL BinWriteType & copy(BinReadType & in,size_t n);
};// BinWriteType

class BinWritePosType : public BinWriteType
{// устройство для двоичного вывода с позиционированием
    public:
    virtual long pos() = 0; // возвращает текущую позицию
    virtual void pos(long) = 0;// устанавливает текущую позицию
    PRIZNAK_SERVICE_DLL BinWritePosType();
    PRIZNAK_SERVICE_DLL ~BinWritePosType();
};// BinWritePosType

struct BinInOutType : public BinReadPosType, public BinWritePosType
{// устройство  для двоичного ввода-вывода
    PRIZNAK_SERVICE_DLL BinInOutType();
    PRIZNAK_SERVICE_DLL ~BinInOutType();
};// BinInOutType

//-------------------------- текстовый вывод --------------------------

class TextOutType
{// устройство для текстового вывода
    TextOutType(TextOutType &);  // заглушка
    void operator = (TextOutType &);  // заглушка
    // private - функции для вывода целых чисел
    TextOutType & write_int(long x,const char sgn);// стандартный вывод целых чисел
    PRIZNAK_SERVICE_DLL TextOutType & write_2(unsigned long x,int size); // вывод целых чисел с основанием 2
    PRIZNAK_SERVICE_DLL TextOutType & write_16(unsigned long x,int size);// вывод целых чисел с основанием 16
    // виртуальная функция вывода строки
    virtual void write_string(const char *)=0;
    public:
    PRIZNAK_SERVICE_DLL static signed char real_tip; // тип вывода действительных чисел по умолчанию 0
                                 // < 0 - формат f
                                 // = 0 - формат G  (установлен по умолчанию)
                                 // > 0 - формат E
    PRIZNAK_SERVICE_DLL static signed char real_prec;// точность вывода действительных чисел по умолчанию -1
                                 // (число цифр после запятой)
                                 // < 0 - системное
    PRIZNAK_SERVICE_DLL static signed char real_sgn;// вывод знака + при выводе действительных чисел по умолчанию 0
                                // 0 - не выводить, > 0 - выводить знак, < 0 - выводить пробел
    static TextOutType & NIL(){ TextOutType * o = 0; return *o; } // нулевое устройство (ничего не делает)
    static TextOutType & Out; // стандартное устройство вывода
    static TextOutType & Err; // стандартное устройство вывода ошибок
    PRIZNAK_SERVICE_DLL TextOutType();
    PRIZNAK_SERVICE_DLL virtual ~TextOutType();
    // Основные функции
    PRIZNAK_SERVICE_DLL TextOutType & write(const char *);// вывод строки
    PRIZNAK_SERVICE_DLL TextOutType & write(const char); // вывод символа
    PRIZNAK_SERVICE_DLL TextOutType & write(const char chain,int n); // вывод цепочки символов
    // целые числа
    PRIZNAK_SERVICE_DLL TextOutType & write(const short int);
    PRIZNAK_SERVICE_DLL TextOutType & write(const unsigned short int);
    PRIZNAK_SERVICE_DLL TextOutType & write(const int);
    PRIZNAK_SERVICE_DLL TextOutType & write(const unsigned int);
    PRIZNAK_SERVICE_DLL TextOutType & write(const long int);
    PRIZNAK_SERVICE_DLL TextOutType & write(const unsigned long int);
    TextOutType & write_2(const char x){ return write_2(x,sizeof(x)); }
    TextOutType & write_2(const signed char x){ return write_2(x,sizeof(x)); }
    TextOutType & write_2(const unsigned char x){ return write_2(x,sizeof(x)); }
    TextOutType & write_2(const short x){ return write_2(x,sizeof(x)); }
    TextOutType & write_2(const unsigned short x){ return write_2(x,sizeof(x)); }
    TextOutType & write_2(const int x){ return write_2(x,sizeof(x)); }
    TextOutType & write_2(const unsigned int x){ return write_2(x,sizeof(x)); }
    TextOutType & write_2(const long x){ return write_2(x,sizeof(x)); }
    TextOutType & write_2(const unsigned long x){ return write_2(x,sizeof(x)); }
    TextOutType & write_16(const char x){ return write_16(x,sizeof(x)); }
    TextOutType & write_16(const signed char x){ return write_16(x,sizeof(x)); }
    TextOutType & write_16(const unsigned char x){ return write_16(x,sizeof(x)); }
    TextOutType & write_16(const short x){ return write_16(x,sizeof(x)); }
    TextOutType & write_16(const unsigned short x){ return write_16(x,sizeof(x)); }
    TextOutType & write_16(const int x){ return write_16(x,sizeof(x)); }
    TextOutType & write_16(const unsigned int x){ return write_16(x,sizeof(x)); }
    TextOutType & write_16(const long x){ return write_16(x,sizeof(x)); }
    TextOutType & write_16(const unsigned long x){ return write_16(x,sizeof(x)); }
    // действительные числа
    PRIZNAK_SERVICE_DLL TextOutType & write(const float &);
    PRIZNAK_SERVICE_DLL TextOutType & write(const double &);
    PRIZNAK_SERVICE_DLL TextOutType & write(const long double &);
    PRIZNAK_SERVICE_DLL TextOutType & write(const float &,signed char prec,signed char tip,signed char sgn = 0);
    PRIZNAK_SERVICE_DLL TextOutType & write(const double &,signed char prec,signed char tip,signed char sgn = 0);
    PRIZNAK_SERVICE_DLL TextOutType & write(const long double &,signed char prec,signed char tip,signed char sgn = 0);
    // Оператор << (для удобства)
    TextOutType & operator << (const char * S){return write(S);}
    TextOutType & operator << (const char x){return write(x);}
    TextOutType & operator << (const short x){return write(x);}
    TextOutType & operator << (const unsigned short x){return write(x);}
    TextOutType & operator << (const int x){return write(x);}
    TextOutType & operator << (const unsigned int x){return write(x);}
    TextOutType & operator << (const long x){return write(x);}
    TextOutType & operator << (const unsigned long x){return write(x);}
    TextOutType & operator << (const float & x){return write(x);}
    TextOutType & operator << (const double & x){return write(x);}
    TextOutType & operator << (const long double & x){return write(x);}
};// TextOutType

class TextOutPlusType : public TextOutType
{// преобразование текстового вывода с выводом N резервных символов
 // в начале каждой строки (по умочанию - пробелы)
    TextOutPlusType(TextOutPlusType &); // заглушка
    void operator = (TextOutPlusType &); // заглушка
    TextOutType & out;
    const int N; // число дополнительно-выводимых символов
    const char sym; // сам символ
    enum { yes, no } sost;
    void write_string(const char *s);// textout.cpp
    public:
    PRIZNAK_SERVICE_DLL ~TextOutPlusType();
    PRIZNAK_SERVICE_DLL TextOutPlusType(TextOutType &,const char * s,char sym = ' ');// textout.cpp
    // Сначала выводится строка (и N = strlen(s))
    PRIZNAK_SERVICE_DLL TextOutPlusType(TextOutType &,int N,char sym = ' ');// textout.cpp
    // так-же как и при s = N*sym
};// TextOutPlusType

class TransTextBinOutType : public TextOutType
{// преобразование из текстового вывода в двоичный
    TransTextBinOutType(TransTextBinOutType &); // заглушка
    void operator = (TransTextBinOutType &); // заглушка
    BinWriteType & out;
    public:
    PRIZNAK_SERVICE_DLL void write_string(const char *s);// textout.cpp
    PRIZNAK_SERVICE_DLL TransTextBinOutType(BinWriteType & O);// textout.cpp
    PRIZNAK_SERVICE_DLL ~TransTextBinOutType();
};// TransTextBinOutType

class TableOutType
{// Таблицы для вывода
    public:
    PRIZNAK_SERVICE_DLL virtual int prizn_eq(int i);// признак выравнивания i-того элемента
                                // (0 - центровка, < 0 - слева, > 0 - справа
                                //   по умолчанию 0
                                //   имена всегда центрируются
    virtual int dim_X() = 0; // размер по 'X'
    virtual int dim_Y() = 0; // размер по 'Y'
    virtual void WriteName(TextOutType & out,int i)=0; // вывод имени i-того элемента
    virtual void WriteTerm(TextOutType & out,int i,int j)=0; // вывод (i,j)-того элемента
    // !!! индексация от 1
    // элементы расположены :
    // (1,1)  (1,2) ... (1,dim_X())
    // ...........................
    // (dim_Y(),1) ... (dim_Y(),dim_X())
    unsigned char kol_left; // число пробелов слева  (по умолчанию 1)
    unsigned char kol_right;// число пробелов справа (по умолчанию 1)
    PRIZNAK_SERVICE_DLL TableOutType();
    PRIZNAK_SERVICE_DLL virtual ~TableOutType();
    PRIZNAK_SERVICE_DLL void print_table(TextOutType &);// печать таблицы
};// TableOutType

//-------------------------- текстовый ввод --------------------------
class TextInType
{// устройство для текстового ввода
    TextInType(TextInType &); // заглушка
    void operator = (TextInType &); // заглушка
    char c_pos; // если не равно 0, то это последний считаный символ
    public:
    const char * end_string; // символы-разделители строк (по умолчанию "\n")
    PRIZNAK_SERVICE_DLL TextInType();
    PRIZNAK_SERVICE_DLL virtual ~TextInType();
    // Основные функции
    PRIZNAK_SERVICE_DLL char read_str(char *,int n = -1);// функция ввода строки
                                     // n - максимальное число считываемых символов
                                     // ( в S должено быть еще 1 место, для символа '\0' )
                                     // n < 0 => длинна не контролируется !!!
                                     // возврат : '\0' если следующий символ - разделитель
                                     //           иначе этот символ
    private:
    virtual char read_char()=0;// виртуальная функция ввода символа
    virtual long double read_real() = 0;// виртуальная функция ввода реального числа
    PRIZNAK_SERVICE_DLL virtual long read_integer();// виртуальная функция ввода целого числа
                                // базовая - преобразование из действительного
    // операции для ввода
    public:
    TextInType & operator >> (char * S){ read_str(S); return *this; }
    TextInType & operator >> (char & x){ x = read_char(); return *this; }
    // целые числа
    TextInType & operator >> (signed char & x){ x = (signed char)read_integer(); return *this; }
    TextInType & operator >> (unsigned char & x){ x = (unsigned char)read_integer(); return *this; }
    TextInType & operator >> (short & x){ x = (short)read_integer(); return *this; }
    TextInType & operator >> (unsigned short & x){ x = (unsigned short)read_integer(); return *this; }
    TextInType & operator >> (int & x){ x = (int)read_integer(); return *this; }
    TextInType & operator >> (unsigned int & x){ x = (unsigned int)read_integer(); return *this; }
    TextInType & operator >> (long & x){ x = read_integer(); return *this; }
    TextInType & operator >> (unsigned long & x){ x = (unsigned long)read_integer(); return *this; }
    // реальные числа
    TextInType & operator >> (float & x){ x = read_real(); return *this; }
    TextInType & operator >> (double & x){ x = read_real(); return *this; }
    TextInType & operator >> (long double & x){ x = read_real(); return *this; }
    PRIZNAK_SERVICE_DLL virtual int end()const; // проверка на исчерпывание устройства
};// TextInType

class TextInSyntaxisType : public TextInType
{// расшифровка действительных чисел функциями из подбиблиотеки SYNTAXIS
    long double read_real();// функция ввода реального числа
    PRIZNAK_SERVICE_DLL virtual void error(const char * s);
    public:
    PRIZNAK_SERVICE_DLL TextInSyntaxisType();
    PRIZNAK_SERVICE_DLL ~TextInSyntaxisType();
};// TextInSyntaxisType
//======================= Конкретные типы ============================

//---------------------- двоичный ввод-вывод ------------------------
class LzssCodeType : public BinWriteType
{// LZSS - кодирование
    public:
    enum
    {
      N = 0x1000,   // size of ring buffer
      F = 18,       // upper limit for match_length
      THRESHOLD = 2,// encode string into position and length if match_length is greater than this
      NIL = N       // index for root of binary search trees
    };
    private:
    unsigned char text_buf[N+F-1];    // ring buffer of size N,
                   // with extra F-1 bytes to facilitate string comparison
    int match_position, match_length;// of longest match.  These are set by the InsertNode() procedure.
    int lson[N+1], rson[N+257], dad[N+1];// left & right children & parents -- These constitute binary search trees.
    int  len, r, s, last_match_length, code_buf_ptr;
	unsigned char  code_buf[17], mask;
    int index;
    int step;
    BinWriteType & out;
    void InsertNode(int r);
    void DeleteNode(int p);  // deletes node p from tree
    void func1();
    void func2();
    void write1(unsigned char c);
    public:
    PRIZNAK_SERVICE_DLL virtual  void write(const void * x,size_t n);// вывод
    PRIZNAK_SERVICE_DLL LzssCodeType(BinWriteType & out);
    PRIZNAK_SERVICE_DLL ~LzssCodeType();
};// LzssCodeType

class LzssDecodeType : public BinReadType
{// LZSS - раскодирование
    enum
    {
      N = LzssCodeType::N,                // size of ring buffer
      F = LzssCodeType::F,                // upper limit for match_length
      THRESHOLD = LzssCodeType::THRESHOLD,// encode string into position and length if match_length is greater than this
    };
    unsigned char text_buf[N+F-1];    // ring buffer of size N,
                   // with extra F-1 bytes to facilitate string comparison
    int r;
    unsigned int  flags;
    int  index[2];
    BinReadType & in;
    unsigned char ret(unsigned char c);
    unsigned char ret();
    unsigned char read1();
    public:
    PRIZNAK_SERVICE_DLL virtual void read(void * x,size_t n);// ввод
    PRIZNAK_SERVICE_DLL LzssDecodeType(BinReadType & in);
    PRIZNAK_SERVICE_DLL ~LzssDecodeType();
};// LzssDecodeType

class InBinFileType: public BinReadPosType, public DiskFileType
{// чтение из двоичного файла
    public:
    PRIZNAK_SERVICE_DLL void read( void *,size_t);
    PRIZNAK_SERVICE_DLL long pos();        // возвращает текущую позицию
    PRIZNAK_SERVICE_DLL void pos(long n);  // устанавливает текущую позицию
    PRIZNAK_SERVICE_DLL InBinFileType(DiskFileType & D);
    PRIZNAK_SERVICE_DLL InBinFileType(const char * NameFile);
    PRIZNAK_SERVICE_DLL ~InBinFileType();
};// InBinFileType

//-----------------------------------------------------------------------
class OutBinFileType: public BinWritePosType, public DiskFileType
{// запись в двоичный файл
    protected:
    PRIZNAK_SERVICE_DLL OutBinFileType(const char * NameFile,open_type);
    public:
    PRIZNAK_SERVICE_DLL void write(const void *,size_t);
    PRIZNAK_SERVICE_DLL long pos();              // возвращает текущую позицию
    PRIZNAK_SERVICE_DLL void pos(long n);  // устанавливает текущую позицию
    PRIZNAK_SERVICE_DLL OutBinFileType(DiskFileType & D);
    PRIZNAK_SERVICE_DLL OutBinFileType(const char * NameFile);
    PRIZNAK_SERVICE_DLL ~OutBinFileType();
};// OutBinFileType

//-----------------------------------------------------------------------
class OutBinNewFileType: public OutBinFileType
{// запись в двоичный файл создаваемый заново
    public:
    PRIZNAK_SERVICE_DLL OutBinNewFileType(DiskFileType & D);
    PRIZNAK_SERVICE_DLL OutBinNewFileType(const char * NameFile);
    PRIZNAK_SERVICE_DLL ~OutBinNewFileType();
};// OutBinNewFileType

//-----------------------------------------------------------------------
class InOutBinFileType: public BinInOutType, public DiskFileType
{// ввод-вывод в двоичный файл
    protected:
    PRIZNAK_SERVICE_DLL InOutBinFileType(const char * NameFile,open_type);
    public:
    PRIZNAK_SERVICE_DLL void write(const void *,size_t);
    PRIZNAK_SERVICE_DLL void read(void *,size_t);
    PRIZNAK_SERVICE_DLL long pos();              // возвращает текущую позицию
    PRIZNAK_SERVICE_DLL void pos(long n);  // устанавливает текущую позицию
    PRIZNAK_SERVICE_DLL InOutBinFileType(DiskFileType & D);
    PRIZNAK_SERVICE_DLL InOutBinFileType(const char * NameFile);
    PRIZNAK_SERVICE_DLL ~InOutBinFileType();
};// InOutBinFileType

//-----------------------------------------------------------------------
class InOutBinNewFileType: public InOutBinFileType
{// ввод-вывод в двоичный файл создаваемый заново
    public:
    PRIZNAK_SERVICE_DLL InOutBinNewFileType(DiskFileType & D);
    PRIZNAK_SERVICE_DLL InOutBinNewFileType(const char * NameFile);
    PRIZNAK_SERVICE_DLL ~InOutBinNewFileType();
};// InOutBinNewFileType

//-------------------------- текстовый вывод --------------------------
//-----------------------------------------------------------------------
class CountTextOutType : public TextOutType // подсчет выводимых символов
{
    unsigned int N;
    void write_string(const char * s);// textout.cpp
    public:
    PRIZNAK_SERVICE_DLL CountTextOutType();
    PRIZNAK_SERVICE_DLL ~CountTextOutType();
    operator unsigned int ()const{ return N;}
};// CountTextOutType

//-----------------------------------------------------------------------

class S_StringOut_Base : public TextOutType
{// базовый класс для S_StringOut
    S_StringOut_Base(S_StringOut_Base &); // заглушка
    void operator = (S_StringOut_Base &); // заглушка
    char * const base;
    int tek;
    protected:
    PRIZNAK_SERVICE_DLL void write_string(const char * s);
    public:
    PRIZNAK_SERVICE_DLL void clear();
    size_t size()const{ return strlen(base); }
    PRIZNAK_SERVICE_DLL S_StringOut_Base(char * base_e,const int max);
    PRIZNAK_SERVICE_DLL ~S_StringOut_Base();
};// S_StringOut_Base

template<const int size_str> class S_StringOut : public S_StringOut_Base
{ // вывод в статическую строку
    char string[size_str+1];
    public:
    S_StringOut():S_StringOut_Base(string,size_str){}
    ~S_StringOut(){}
    operator const char * ()const{ return string; }
};// S_StringOut

//-----------------------------------------------------------------------
class D_StringOut:public TextOutType
{// вывод в динамическую строку
    D_StringOut(D_StringOut &); // заглушка
    void operator = (D_StringOut &); // заглушка
    char * string;
    void write_string(const char *);
    public:
    PRIZNAK_SERVICE_DLL D_StringOut();
    PRIZNAK_SERVICE_DLL ~D_StringOut();
    PRIZNAK_SERVICE_DLL static void add(char *& str,const char * s);// добавить в динамическую строку str строку s
    operator const char * ()const{ return string; }
    char * out(){ char * s = string; string = 0; return s;}// сброс значения
    PRIZNAK_SERVICE_DLL void clear();
    size_t size()const{ return strlen(string); }
};

//-----------------------------------------------------------------------
class OutTextFileType : public TextOutType, public DiskFileType
{// вывод в текстовый файл
    void write_string(const char *);
    protected:
    PRIZNAK_SERVICE_DLL OutTextFileType(const char * NameFile,open_type);
    public:
    PRIZNAK_SERVICE_DLL OutTextFileType(DiskFileType & D);
    PRIZNAK_SERVICE_DLL OutTextFileType(const char * NameFile);
    PRIZNAK_SERVICE_DLL ~OutTextFileType();
};// OutTextFileType

class OutTextNewFileType : public OutTextFileType
{// вывод в текстовый файл создаваемый заново
    public:
    PRIZNAK_SERVICE_DLL OutTextNewFileType(DiskFileType & D);
    PRIZNAK_SERVICE_DLL OutTextNewFileType(const char * NameFile);
    PRIZNAK_SERVICE_DLL ~OutTextNewFileType();
};// OutTextNewFileType

//-----------------------------------------------------------------------
class SpisokTextOutType : public TextOutType // вывод в список устройств
{
    D_Spisok_Base_Ptr Sp;
    void write_string(const char * S);
    public:
    PRIZNAK_SERVICE_DLL SpisokTextOutType();
    PRIZNAK_SERVICE_DLL ~SpisokTextOutType();
    void operator += (TextOutType * T){ Sp += T; }
    void operator += (TextOutType & T){ Sp += &T; }
};// SpisokTextOutType

//-------------------------- текстовый ввод --------------------------
class InTextStandType : public TextInSyntaxisType
{// ввод со стандартного устройства
    char read_char(){ return (char)getc(stdin); }
};// InTextStandType

class InTextFileType : public TextInSyntaxisType, public DiskFileType
{// ввод из текстового файла
    char read_char();
    public:
    PRIZNAK_SERVICE_DLL InTextFileType(DiskFileType & D);
    PRIZNAK_SERVICE_DLL InTextFileType(const char * NameFile);
    PRIZNAK_SERVICE_DLL ~InTextFileType();
    PRIZNAK_SERVICE_DLL int end()const; // проверка на конец файла
};// InTextFileType

class InTextStringType : public TextInSyntaxisType
{// ввод из массива строк
    char const * const * buff; // буфер строк
    unsigned int size_buff; // его размер
    char const * tek; // текущее значение
    char read_char();
    public:
    PRIZNAK_SERVICE_DLL int end()const;
    PRIZNAK_SERVICE_DLL InTextStringType(char const * s); // 1 строка
    PRIZNAK_SERVICE_DLL InTextStringType(char const * const * b,unsigned int size); // массив строк
    PRIZNAK_SERVICE_DLL ~InTextStringType();
};// InTextStringType
#endif
