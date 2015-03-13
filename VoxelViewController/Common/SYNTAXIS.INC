//////////////////////////////////////////////////////////////////////////////
//                  процедуры синтаксического разбора                       //
//////////////////////////////////////////////////////////////////////////////
#ifndef IN_OUT_TEXT_TYPE_INC
#define IN_OUT_TEXT_TYPE_INC
// подключаемые файлы
#include "service.inc"
#include "inout.inc"

//=================== Множество символов ================================
class SetOfChar // квазипаскаль ( только для 8-битовых char'ов)
{// множество символов
    unsigned char A[32];
    public:
    void operator += (unsigned char c){A[c>>3] |= (unsigned char)(1 << (c&7));}
    void operator -= (unsigned char c){A[c>>3] &= (unsigned char)(~(1 << (c&7)));}
    int operator == (unsigned char c)const{return (A[c>>3]&(1 << (c&7)))!=0;}
    int operator != (unsigned char c)const{return (A[c>>3]&(1 << (c&7)))==0;}
    PRIZNAK_SERVICE_DLL SetOfChar();
    PRIZNAK_SERVICE_DLL SetOfChar(unsigned char c);
    PRIZNAK_SERVICE_DLL SetOfChar(const char *);
    PRIZNAK_SERVICE_DLL void operator = (unsigned char c);
    PRIZNAK_SERVICE_DLL void operator = (const char *);
    PRIZNAK_SERVICE_DLL void operator += (const char *);
    PRIZNAK_SERVICE_DLL void operator -= (const char *);
    PRIZNAK_SERVICE_DLL void operator += (const SetOfChar &);
    PRIZNAK_SERVICE_DLL void operator -= (const SetOfChar &);
};// SetOfChar

//===================== Текстовый ввод ================================
class ReadTextType; // ввод текста (абстрактный класс)
class PosTextBuffType
{// сохранение позиции для класса ReadTextType
    friend class ReadTextType;
    long NomPos;      // текущий номер позиции
    int NomString;    // текущий номер строки
    int NomPosString; // текущий номер позиции от начала строки
    public:
    PRIZNAK_SERVICE_DLL void operator = (const ReadTextType &);// определить позицию
    PosTextBuffType(){}
    PosTextBuffType(const ReadTextType & text){ *this = text;}
};// PosTextBuffType

class ReadTextType // ввод текста (абстрактный класс)
{
    ReadTextType(const ReadTextType &);     // заглушка
    void operator = (const ReadTextType &); // заглушка

    friend class PosTextBuffType;
    friend class ReadText2Type;
    char read(PosTextBuffType &); // чтение со сдвигом позиции и определением ея
    virtual char read()=0; // чтение со сдвигом позиции '\0' - конец ввода
    virtual long pos()const=0; // возвращает текущую позицию
    virtual void pos(const long)=0;// устанавливает текущую позицию
    int NomString; // текущий номер строки
    int NomPos; // текущий номер позиции от начала строки
    virtual void nom_str(int);// установить текущий номер строки
    virtual void nom_pos(int); // установить текущий номер позиции от начала строки
    // переменные определяющие синтаксис (служебные символы)
    const char * const * koment; // таблица коментариев в формате :
                                 // нач.ком.1, кон.ком.1,...,0 ( заканчивается 0 !!! )
                                 // 0 - нет коментариев
                                 // по умолчанию "/*","*/","//","\n",0
    const char * zero_char;// таблица пропускаемых символов
                     // по умолчанию "\t\n "
    public:
    PRIZNAK_SERVICE_DLL virtual const char * const * set_kom(const char * const *);// установить таблицу коментариев (возврат - предыдущая)
    PRIZNAK_SERVICE_DLL virtual const char * set_zero(const char * );// установить пропускаемых символов (возврат - предыдущая)
    // основные функции
    PRIZNAK_SERVICE_DLL char chr();// чтение символа из буфера (если '\0', то конец буфера)
               // !!! перед чтением пропускаются служебные символы
    operator char (){ return chr(); }
    PRIZNAK_SERVICE_DLL char operator ++ (); // сдвиг буфера на одну позицию
    // считывать в <TextOutType> пока входит в <SetOfChar>
    // возврат: первый несовпадающий символ
    PRIZNAK_SERVICE_DLL char read_EQ(TextOutType &,const SetOfChar &);
    // считывать в <TextOutType> пока не входит в <SetOfChar>
    // возврат: первый совпадающий символ
    PRIZNAK_SERVICE_DLL char read_NE(TextOutType &,const SetOfChar &);
    // чтение от текущей позиции до заданной (если текущая меньше, то не считываются)
    // при выходе устанавливается заданная позиция
    PRIZNAK_SERVICE_DLL void read_do(TextOutType &,const PosTextBuffType &);
    // сервисные функции
    PRIZNAK_SERVICE_DLL int find(const char * string);// ищет строку string
                                  // если найдена - возврат 0
                                  //      позиция после строки
                                  // если не найдена - возврат не 0
                                  //      позиция в конце
    PRIZNAK_SERVICE_DLL int find(TextOutType &,const char * string);// то-же что и предыдущая, но
                                            // со считыванием на TextOutType
                                            // ( string не считывается )
    PRIZNAK_SERVICE_DLL int check_wait(const char c,TextOutType & err);// проверка на символ
                                               // если это он,
                                               // то возврат 0 и считывание
                                               // иначе сообщение в err
    PRIZNAK_SERVICE_DLL int check_wait(const char c);// тоже что и предыдущая, но без сообщения
    PRIZNAK_SERVICE_DLL virtual void print_sost(TextOutType &);// печать текущего состояния
    PRIZNAK_SERVICE_DLL void operator = (const PosTextBuffType &);// установить позицию
    PRIZNAK_SERVICE_DLL ReadTextType();
    virtual ~ReadTextType(){}
    PRIZNAK_SERVICE_DLL int nom_str()const{ return NomString; }// текущий номер строки
    PRIZNAK_SERVICE_DLL int nom_pos()const{ return NomPos;} // текущий номер позиции от начала строки
};// ReadTextType

class ReadText2Type : public ReadTextType
{// ввод текста из 2-х устройств
    ReadTextType & text1;// устройство 1 (конечное)
    ReadTextType & text2;// устройство 2
    char const * const name1; // имя устройства 1
    char const * const name2; // имя устройства 1
    char prizn2; // признак текущего 2-го устройства
    long size1;// размер 1-го устройства
    int  KolString1;// число строк 1-го устройства
    char read(); // чтение со сдвигом позиции '\0' - конец ввода
    void pos(const long);// устанавливает текущую позицию
    long pos()const; // возвращает текущую позицию
    void nom_str(int);// установить текущий номер строки
    void nom_pos(int); // установить текущий номер позиции от начала строки
    public:
    PRIZNAK_SERVICE_DLL const char * const * set_kom(const char * const *);// установить таблицу коментариев (возврат - предыдущая)
    PRIZNAK_SERVICE_DLL const char * set_zero(const char *);// установить пропускаемых символов (возврат - предыдущая)
    PRIZNAK_SERVICE_DLL void print_sost(TextOutType &);// печать текущего состояния
    PRIZNAK_SERVICE_DLL ReadText2Type(const char * n1,ReadTextType & t1,const char * n2,ReadTextType & t2);
    PRIZNAK_SERVICE_DLL ~ReadText2Type();
    void operator = (const PosTextBuffType & pos){ ((ReadTextType &) *this) = pos;}// установить позицию
};// ReadText2Type

class ReadTextString : public ReadTextType
{// ввод текста из строки
    const char * const Begin;
    const char * Tek;
    char read(); // чтение со сдвигом позиции '\0' - конец ввода
    void pos(const long);// устанавливает текущую позицию
    public:
    PRIZNAK_SERVICE_DLL long pos()const; // возвращает текущую позицию
    PRIZNAK_SERVICE_DLL ReadTextString(const char *);
    PRIZNAK_SERVICE_DLL ~ReadTextString();
    void operator = (const PosTextBuffType & pos){ ((ReadTextType &) *this) = pos;}// установить позицию
};// ReadTextString

class ReadTextFile : public ReadTextType, public DiskFileType
{// ввод текста из файла
    char read(); // чтение со сдвигом позиции '\0' - конец ввода
    long pos()const; // возвращает текущую позицию
    void pos(const long);// устанавливает текущую позицию
    public:
    PRIZNAK_SERVICE_DLL void print_sost(TextOutType &);// печать текущего состояния
    PRIZNAK_SERVICE_DLL ReadTextFile(const char * NameFile);
    PRIZNAK_SERVICE_DLL ReadTextFile(DiskFileType &);
    PRIZNAK_SERVICE_DLL ~ReadTextFile();
    void operator = (const PosTextBuffType & pos){ ((ReadTextType &) *this) = pos;}// установить позицию
};// ReadTextFile

//===================== Тип для ввода-вывода имен =========================
class NameType
{// имя (изменится не может)
    NameType(NameType &);         // заглушка
    void operator = (NameType &); // заглушка

    const char * const Name;
    public:
    // Общеупотребительные наборы символов
    PRIZNAK_SERVICE_DLL static const char KirAlfString[];  // кирилица
    PRIZNAK_SERVICE_DLL static const char LatAlfString[];  // латинский алфавит
    PRIZNAK_SERVICE_DLL static const char ArZiferString[]; // арабские цифры
    PRIZNAK_SERVICE_DLL static const SetOfChar KirAlf;  // кирилица
    PRIZNAK_SERVICE_DLL static const SetOfChar LatAlf;  // латинский алфавит
    PRIZNAK_SERVICE_DLL static const SetOfChar ArZifer; // арабские цифры
    PRIZNAK_SERVICE_DLL static const SetOfChar BeginName;// начало имени (KirAlf+LatAlf+'_')
    PRIZNAK_SERVICE_DLL static const SetOfChar NextName;// продолжение имени (BeginName+ArZifer)
    // инициализация
    PRIZNAK_SERVICE_DLL NameType();
    PRIZNAK_SERVICE_DLL NameType(const char * );
    PRIZNAK_SERVICE_DLL ~NameType();
    // ----------- Процедуры сравнения --------
    // Проверка на совпадение имени и начала буфера ввода <ReadTextType>
    //  Name - в формате имени
    //  считывает если совпало
    //  возврат 0 - совпало, 1 - не совпало
    PRIZNAK_SERVICE_DLL int cmp(ReadTextType &)const;
    PRIZNAK_SERVICE_DLL int cmp(ReadTextType &,const SetOfChar &)const;
    PRIZNAK_SERVICE_DLL int cmp_name(ReadTextType &)const;// также как cmp(,NextName);
    // а так-же
    PRIZNAK_SERVICE_DLL static int cmp(const char *,ReadTextType &);
    PRIZNAK_SERVICE_DLL static int cmp(const char *,ReadTextType &,const SetOfChar &);
    PRIZNAK_SERVICE_DLL static int cmp_name(const char *,ReadTextType &);//также как cmp(,,NextName);
    // вспомогательные операторы
    PRIZNAK_SERVICE_DLL operator const char * ()const; // приведение к строке
    int yes()const{ return Name != 0; } // имя есть
    int no()const{ return Name == 0; }  // имени нет
};// NameType

//===================== Ввод объекта ===========================
class VariablBaseCopyType;// тип для копирования всех действий внешннего объекта (предописание)
class SpisokVariablBaseType;// список вводимых данных (предописание)
class VariablBaseType;

class NameReadType
{// класс для ввода имени
 //  вводит имя из устройства ввода и инициализирует указатель
 //  соответствующим значением из списка
 // имя - либо простое имя, либо имя с индексом
    void operator = (NameReadType &); // заглушка
    struct WorkType
    {
      int tip;   // тип (возврвщаемое значение)
      int index; // индекс
      unsigned char prizn_index; // признак наличия индекса (если не 0, то имя = name[index])
      char * name;
    } * spisok;
    int size;
    void add(const char * name,int index,int tip,unsigned char prizn_index);
    public:
    PRIZNAK_SERVICE_DLL void add(const char * name,int tip); // добавить имя и тип
    PRIZNAK_SERVICE_DLL void add(const char * name,int index,int tip); // добавить имя c индексом и тип
    PRIZNAK_SERVICE_DLL void add(const NameReadType & n,int shift); // добавить список со сдвигом в индексе shift
    // добавить элемент списка со сдвигом в индексе shift
    // возврат: число прочитанных элементов (0 - значит была ошибка)
    // элемент списка ::= имя | имя[индекс] | имя[набор индексов]
    PRIZNAK_SERVICE_DLL int add1(ReadTextType &,TextOutType &,VariablBaseType *,int shift = 0);
    // добавить список со сдвигом в индексе shift
    PRIZNAK_SERVICE_DLL int add(ReadTextType &,TextOutType &,VariablBaseType *,char end,int shift = 0);
    PRIZNAK_SERVICE_DLL int MaxIndex()const; // максимальное значение типа ( если список пуст, то -1)
    PRIZNAK_SERVICE_DLL int operator ()(ReadTextType &,VariablBaseType * base = 0)const;// ввод (-1 если не введено )
    PRIZNAK_SERVICE_DLL int operator ()(const char * name)const;// поиск (-1 если не определено )
    PRIZNAK_SERVICE_DLL void clear();
    PRIZNAK_SERVICE_DLL int print(TextOutType & out,int i)const;
    PRIZNAK_SERVICE_DLL ~NameReadType();
    PRIZNAK_SERVICE_DLL NameReadType();
    PRIZNAK_SERVICE_DLL NameReadType(const NameReadType &);
    // каждому имени (строке) из массива строк сопоставляется тип
    // начиная с begin
    // пустые строки игнорируются при вводе
    PRIZNAK_SERVICE_DLL NameReadType(char const * const * s,unsigned int begin = 0);
};// NameReadType

//=======================================================================
class VariablBaseType
{// Базовый тип для связывания переменной с правилами синтаксического разбора.
 //  синтаксис по умолчанию ::= (<имя>) (=) (метасимвол ввода)
    friend class VariablBaseCopyType;
    VariablBaseType(VariablBaseType &); // заглушка
    void operator = (VariablBaseType &);// заглушка

    public:
    VariablBaseType * Base;// ссылка на предыдущий уровень вложености
                           // для обратной связи
    protected:
    NameType Name;         // имя объекта
    NameType symv_razd;    // символ-разделитель ( присваивания )

    // Определение себя как базовой для данной переменной
    PRIZNAK_SERVICE_DLL virtual void define_base(VariablBaseType *);
    public:
    const int Min; // минимальное число изменений - по умолчанию 0
    const int Max; // максимальное число изменений - по умолчанию -1 (бесконечность)
    int KolIzm; // число изменений (успешных вызовов функции read)
    // Процедуры работы с глобальными конструкциями
    // (файл varglob.cpp)
    typedef int (* ProcReadGlob)(ReadTextType &,TextOutType &,VariablBaseType *);
    private:
    struct SetGlobType{const char * NameProc; ProcReadGlob Proc;};
    struct ReadGlobType{ReadTextType * text;TextOutType * err;VariablBaseType * base;};
    static int GlobProc(void *,int);
    public:
    //занести процедуру в список глобальных данных
    PRIZNAK_SERVICE_DLL static void SetGlobProc(const char * NameProc,ProcReadGlob);
    //ввод глобальных данных
    PRIZNAK_SERVICE_DLL static int ReadGlobProc(ReadTextType &,TextOutType &,VariablBaseType *);

    // Процедуры ввода объекта из буфера ввода <ReadTextType>
    //   возврат:
    //   0 - успешный ввод
    //   1 - в буфере не тот объект ( лучше посмотреть другие )
    //   2 - тот объект но задан неправильно ( коментарии в <TextOutType> )
    // (файл varread.cpp)
    PRIZNAK_SERVICE_DLL virtual int read_name(ReadTextType &,TextOutType &);//  ввод имени
    PRIZNAK_SERVICE_DLL virtual int read_obj(ReadTextType &,TextOutType &);// ввод значения объекта
    PRIZNAK_SERVICE_DLL virtual int read(ReadTextType &,TextOutType &); // ввода объекта
    PRIZNAK_SERVICE_DLL int read_full(ReadTextType &,TextOutType &); // полный ввода объекта (с проверкой)

    // Идентификация объекта из буфера ввода <ReadTextType>
    //   возврат:
    //   0     - иденфицирован
    //   1     - не иденфицирован
    //   иначе - ошибка
    // (файл varread.cpp)
    PRIZNAK_SERVICE_DLL virtual int type_obj(const void *& tip,void *& V,ReadTextType &,TextOutType &);// идентификация объекта
    // Поиск объекта идентифицированного началом буфера ввода <ReadTextType>
    // возврат как у type_obj
    // (файл varread.cpp)
    PRIZNAK_SERVICE_DLL virtual int find(const void *& tip,void *& V,ReadTextType &,TextOutType &);

    // Проверка ввода
    // (файл varread.cpp)
    PRIZNAK_SERVICE_DLL virtual int read_check(TextOutType &); // проверка ввода
    // Печать
    // (файл varread.cpp)
    PRIZNAK_SERVICE_DLL virtual int print(TextOutType &);      // полный вывод объекта
    PRIZNAK_SERVICE_DLL virtual int print_name(TextOutType &); // вывод имени
    PRIZNAK_SERVICE_DLL virtual int print_obj(TextOutType &);  // вывод объекта
    PRIZNAK_SERVICE_DLL int print_full_name(TextOutType &); // вывод полного имени
    PRIZNAK_SERVICE_DLL void print_full_info(TextOutType &); // печать полной информации о вводе

    // Инициализация
    // (файл varread.cpp)
    PRIZNAK_SERVICE_DLL VariablBaseType();
    PRIZNAK_SERVICE_DLL VariablBaseType(int min_izm,int max_izm1);
    PRIZNAK_SERVICE_DLL VariablBaseType(const char * ExtName);
    PRIZNAK_SERVICE_DLL VariablBaseType(const char * ExtName,int min_izm,int max_izm);
    PRIZNAK_SERVICE_DLL VariablBaseType(const char * ExtName,const char * ext_symv);
    PRIZNAK_SERVICE_DLL VariablBaseType(const char * ExtName,const char * ext_symv,int min_izm,int max_izm);
    PRIZNAK_SERVICE_DLL virtual ~VariablBaseType();

    // Вспомогательные операции
    PRIZNAK_SERVICE_DLL void operator <= (VariablBaseType * v);// сделать v базовой для себя
    PRIZNAK_SERVICE_DLL void operator += (VariablBaseType * v);// сделать себя базовой для v
    void operator += (VariablBaseType & v){ *this += &v; }
    PRIZNAK_SERVICE_DLL virtual const SpisokVariablBaseType * SetSpisok()const;// указатель на список (сложную структуру), умолчание 0

};// VariablBaseType


//=======================================================================
class VariablBaseCopyType : public VariablBaseType
{// тип для копирования всех действий внешннего объекта
 // копируются все виртуальные функции
 // !!! объект должен быть размещен в динамической памяти
 //     ( в деструкторе эта память освобождается )
    VariablBaseType * obj; // объект
    VariablBaseType * obj_del; // объект для удаления
    VariablBaseType * coxBase; // сохранение базового
    unsigned char priz_find; // признак поиска
    public:
    PRIZNAK_SERVICE_DLL virtual int read_name(ReadTextType &,TextOutType &);//  ввод имени
    PRIZNAK_SERVICE_DLL virtual int read_obj(ReadTextType &,TextOutType &);// ввод объекта
    PRIZNAK_SERVICE_DLL virtual int read(ReadTextType &,TextOutType &); // полный ввода объекта
    PRIZNAK_SERVICE_DLL virtual int type_obj(const void *& tip,void *& V,ReadTextType &,TextOutType &);// идентификация объекта
    PRIZNAK_SERVICE_DLL virtual int find(const void *& tip,void *& V,ReadTextType &,TextOutType &);
    PRIZNAK_SERVICE_DLL virtual int read_check(TextOutType &); // проверка ввода
    PRIZNAK_SERVICE_DLL virtual int print(TextOutType &);      // полный вывод объекта
    PRIZNAK_SERVICE_DLL virtual int print_name(TextOutType &); // вывод имени
    PRIZNAK_SERVICE_DLL virtual int print_obj(TextOutType &);  // вывод объекта
    PRIZNAK_SERVICE_DLL virtual const SpisokVariablBaseType * SetSpisok()const;// указатель на список (сложную структуру), умолчание 0
    // (файл varcopy.cpp)
    PRIZNAK_SERVICE_DLL VariablBaseCopyType(VariablBaseType * obj,VariablBaseType * obj_del = 0);
    PRIZNAK_SERVICE_DLL ~VariablBaseCopyType();
};// VariablBaseCopyType

//=======================================================================
class SpisokVariablBaseType : public D_Spisok_Base_Ptr
{// список вводимых данных
 // !!! для все объекты должны быть распределены в динамической памяти
 // ( т.к. деструктор пытается удалить их от туда )
  static void delete_var(void *);
  public:
    // Процедуры циклической обработки списков
    // (файл varcycle.cpp)

    //    тип int (ReadTextType &,TextOutType &);
    //    подразумеваются процедуры чтения
    typedef int (VariablBaseType::*ProcRead)(ReadTextType &,TextOutType &);
    //    алгоритм :  просматривает весь список пока код возврата = 1
    //                вызывая соответствующую процедуру и возвращает
    //                последний код возврата
    PRIZNAK_SERVICE_DLL int read(ProcRead,ReadTextType &,TextOutType &);
    //    тип int (void *&,ReadTextType &);
    //    подразумеваются процедуры поиска
    typedef int (VariablBaseType::*ProcFind)(const void *& tip,void *& V,ReadTextType &,TextOutType &);
    //    алгоритм :  просматривает весь список пока код возврата = 1
    //                вызывая соответствующую процедуру и возвращает
    //                последний код возврата
    PRIZNAK_SERVICE_DLL int find(ProcFind,const void *& tip,void *& V,ReadTextType &,TextOutType &);

    //    тип int (TextOutType &);
    //    подразумеваются процедуры печати (или read_check)
    typedef int (VariablBaseType::*ProcPrint)(TextOutType &);
    //    алгоритм :  просматривает весь список
    //                вызывая соответствующую процедуру и возвращает
    //                максимальный код возврата
    PRIZNAK_SERVICE_DLL int print(ProcPrint,TextOutType &);

    //    и еще
    void operator += (VariablBaseType * v){ add(v); }
    VariablBaseType * const * table()const{ return (VariablBaseType * const *)D_Spisok_Base_Ptr::table(); }
    VariablBaseType * operator [](int i)const{ return (VariablBaseType *)D_Spisok_Base_Ptr::table(i); }
    PRIZNAK_SERVICE_DLL SpisokVariablBaseType();
    PRIZNAK_SERVICE_DLL ~SpisokVariablBaseType();
};// SpisokVariablBaseType

//=======================================================================
class SpisokReadType : public VariablBaseType
{// список вводимых данных
 // !!! для все объекты должны быть распределены в динамической памяти
 // ( т.к. деструктор пытается удалить их от туда )
    // переопределяемые виртуальные функции
    private:
    int read_op(ReadTextType &,TextOutType &);// ввод 1 оператора
    int read_spisok(ReadTextType &,TextOutType &);// ввод списка
    char const * const end_read; // конец ввода
    PRIZNAK_SERVICE_DLL void define_base(VariablBaseType *);
    public:
    char end_op; // конец оператора (по умолчанию ;)
    PRIZNAK_SERVICE_DLL virtual int read_obj(ReadTextType &,TextOutType &); // ввод объекта
    PRIZNAK_SERVICE_DLL virtual int print_obj(TextOutType &); // контрольная распечатка
    PRIZNAK_SERVICE_DLL virtual int find(const void *& tip,void *& V,ReadTextType &,TextOutType &);// поиск по обратной связи
    SpisokVariablBaseType SpisokData;  // список данных
    PRIZNAK_SERVICE_DLL virtual int read_check(TextOutType &); // проверка ввода
    PRIZNAK_SERVICE_DLL const SpisokVariablBaseType * SetSpisok()const;// указатель на список (сложную структуру)
    PRIZNAK_SERVICE_DLL void copy(const SpisokVariablBaseType & SD);
    void copy(const SpisokReadType & Sp){ copy(Sp.SpisokData); }
    PRIZNAK_SERVICE_DLL SpisokReadType(const char *,const char * end = 0);// именованый список (0 - без имени)
    PRIZNAK_SERVICE_DLL SpisokReadType(const char *,int min,int max,const char * end = 0);// именованый список (0 - без имени)
    PRIZNAK_SERVICE_DLL ~SpisokReadType();
};// SpisokReadType

//=======================================================================
class ReadTablStructBaseType : public VariablBaseType, public TableOutType
{// базовый класс для ввода таблицы структур ( readtabl.cpp )
    PRIZNAK_SERVICE_DLL int dim_X();
    PRIZNAK_SERVICE_DLL int dim_Y();
    PRIZNAK_SERVICE_DLL void WriteName(TextOutType & out,int i);
    PRIZNAK_SERVICE_DLL void WriteTerm(TextOutType & out,int i,int j);
    public:
    virtual void * new_struct(VariablBaseType &) = 0;// создание новой структуры
    SpisokVariablBaseType SpisokData;
    void **& AdrTabl; // адрес таблицы
    int & dim;       // размер таблицы (в элементах)
    // переопределяемые виртуальные функции класса VariablBaseType
    PRIZNAK_SERVICE_DLL virtual int read_obj(ReadTextType &,TextOutType &);// ввод
    PRIZNAK_SERVICE_DLL virtual int type_obj(const void *& tip,void *& V,ReadTextType &,TextOutType &);// идентификация объекта
    PRIZNAK_SERVICE_DLL virtual int print_obj(TextOutType &);// печать
    // Инициализация
    PRIZNAK_SERVICE_DLL ReadTablStructBaseType(const char * NameTabl,void **& A,int & D);
    PRIZNAK_SERVICE_DLL ~ReadTablStructBaseType();
};// ReadTablStructBaseType

template<class Type_Tabl>
class ReadTablStructType : public ReadTablStructBaseType
{// структура Type_Tabl должна иметь конструктор
 //   Type_Tabl(VariablBaseType &)
    void * new_struct(VariablBaseType & SP){ return new Type_Tabl(SP); }
    public:
    ReadTablStructType(const char * name,Type_Tabl **& V,int & dim)
        :ReadTablStructBaseType(name,(void **&)V,dim){}
};// ReadTablStructType

template<class Type_Tabl>
inline VariablBaseType * OprTablStruct(const char * Name,Type_Tabl **& Tabl,int & dim)
// связать массив структур
// структура Type_Tabl должна иметь конструктор Type_Tabl(VariablBaseType &)
{
    return new ReadTablStructType<Type_Tabl>(Name,Tabl,dim);
}// OprTablStruct

//--------------------- ввод списка объектов ---------------------------
class ReadSpisokStructPtrBaseType : public VariablBaseType
{// базовый класс для ввода списка указателей на структуры ( rspisstr.cpp )
    protected:
    void **& AdrTabl; // адрес таблицы
    int & dim;       // размер таблицы (в элементах)
    virtual void * read_struct(ReadTextType & text,TextOutType & err) = 0;// ввод структуры
    PRIZNAK_SERVICE_DLL virtual int read_obj(ReadTextType & text,TextOutType & err);
    public:
    PRIZNAK_SERVICE_DLL ReadSpisokStructPtrBaseType(const char * name,void **& A,int & D);
    PRIZNAK_SERVICE_DLL ~ReadSpisokStructPtrBaseType();
};// ReadSpisokStructPtrBaseType

class ReadSpisokObjBaseType : public ReadSpisokStructPtrBaseType
{// базовый класс для ввода списка объектов ( rspisobj.cpp )
    virtual void * new_obj(VariablBaseType *&) = 0;// создание нового объекта
    PRIZNAK_SERVICE_DLL void * read_struct(ReadTextType & text,TextOutType & err);// ввод структуры
    SpisokVariablBaseType SpisokData;  // список данных
    PRIZNAK_SERVICE_DLL virtual int print(TextOutType & err);
    public:
    PRIZNAK_SERVICE_DLL ReadSpisokObjBaseType(const char * name,void **& A,int & D);
    PRIZNAK_SERVICE_DLL ~ReadSpisokObjBaseType();
};// ReadSpisokObjBaseType

template<class Type_Tabl>
class ReadSpisokObjType : public ReadSpisokObjBaseType
{// структура Type_Tabl должна иметь конструктор
 //   Type_Tabl(VariablBaseType *&)
    void * new_obj(VariablBaseType *& SP){ return new Type_Tabl(SP);}
    public:
    ReadSpisokObjType(const char * name,Type_Tabl **& A,int & D)
        :ReadSpisokObjBaseType(name,(void **&)A,D){}
};// ReadSpisokObjType

template<class Type_Tabl>
inline VariablBaseType * OprSpisokObj(const char * Name,Type_Tabl **& A,int & D)
// связать список объектов
// структура Type_Tabl должна иметь конструктор Type_Tabl(VariablBaseType *&)
{
    return new ReadSpisokObjType<Type_Tabl>(Name,A,D);
}// OprSpisokObj


//--------------------- ввод массива объектов ---------------------------
class ReadMassivPtrBaseType : public VariablBaseType
{// базовый класс для ввода списка указателей на структуры ( rspisstr.cpp )
    protected:
    void **& AdrTabl;// адрес таблицы
    int & dim;       // размер таблицы (в элементах)
    const char razd; // разделитель
    virtual void * read_element(ReadTextType & text,TextOutType & err) = 0;// ввод структуры
    PRIZNAK_SERVICE_DLL virtual int read_obj(ReadTextType & text,TextOutType & err);
    public:
    PRIZNAK_SERVICE_DLL ReadMassivPtrBaseType(const char * name,void **& A,int & D,char r,int min,int max);
    PRIZNAK_SERVICE_DLL ~ReadMassivPtrBaseType();
};// ReadMassivPtrBaseType

class ReadMassivObjBaseType : public ReadMassivPtrBaseType
{// базовый класс для ввода списка объектов ( rspisobj.cpp )
    virtual void * new_obj(VariablBaseType *&) = 0;// создание нового объекта
    PRIZNAK_SERVICE_DLL void * read_element(ReadTextType & text,TextOutType & err);// ввод структуры
    SpisokVariablBaseType SpisokData;  // список данных
    PRIZNAK_SERVICE_DLL virtual int print(TextOutType & err);
    public:
    PRIZNAK_SERVICE_DLL ReadMassivObjBaseType(const char * name,void **& A,int & D,char r,int min,int max);
    PRIZNAK_SERVICE_DLL ~ReadMassivObjBaseType();
};// ReadMassivObjBaseType


template<class Type_Tabl>
class ReadMassivObjType : public ReadMassivObjBaseType
{// структура Type_Tabl должна иметь конструктор
 //   Type_Tabl(VariablBaseType *&)
    void * new_obj(VariablBaseType *& SP){ return new Type_Tabl(SP);}
    public:
    ReadMassivObjType(const char * name,Type_Tabl **& A,int & D,char r,int min,int max)
        :ReadMassivObjBaseType(name,(void **&)A,D,r,min,max){}
};// ReadMassivObjType

template<class Type_Tabl>
inline VariablBaseType * OprMassivObj(const char * Name,Type_Tabl **& A,int & D,char r,int min,int max)
// связать список объектов
// структура Type_Tabl должна иметь конструктор Type_Tabl(VariablBaseType *&)
{
    return new ReadMassivObjType<Type_Tabl>(Name,A,D,r,min,max);
}// OprMassivObj


//--------------------------- Ввод множеств ---------------------------
//    синтаксис:
//         <имя> =  множество
//         множество ::= { <имя_1>,..,<имя_n> } | { <имя_1>,..,<имя_n> } / { <имя_1>,..,<имя_n> }
//         (имя_i - имя элемента или подмножества)

class ReadSetType : public VariablBaseType
{// для ввода множества
    int shab_zap; // шаблон занесения
    int shab_ret; // шаблон возврата
    SpisokVariablBaseType SpisEl; // список элементов
    public:
    // переопределяемые виртуальные функции класса VariablBaseType
    PRIZNAK_SERVICE_DLL virtual int read_obj(ReadTextType & text,TextOutType & err);
    PRIZNAK_SERVICE_DLL virtual int print_obj(TextOutType & out);
    // инициализация
    //   после ввода: Prizn == 0 - несодержится  Prizn != 0 - содержится
    PRIZNAK_SERVICE_DLL void add(const char * NameEl,int & Prizn);// добавить элемент NameEl
    // добавить подмножество NameSubset
    //  Prizn - массив указателей на признаки (может быть локальным)
    //  size  - его размер
    PRIZNAK_SERVICE_DLL void add(const char * NameSubset,int ** Prizn,int size);
    PRIZNAK_SERVICE_DLL ReadSetType(const char * Name,int min = 0,int max = -1);
};// ReadSetType

//------------------------- для ввода строк --------------------------
class WriteStringBaseType : public VariablBaseType
{// базовый класс для обеспечения ввода символьных строк
    PRIZNAK_SERVICE_DLL static char typ; // тип
    protected:
    PRIZNAK_SERVICE_DLL virtual int type_obj(const void *& tip,void *& V,ReadTextType &,TextOutType &);// возврат - указатель на себя
    PRIZNAK_SERVICE_DLL virtual int print(TextOutType &);
    PRIZNAK_SERVICE_DLL virtual int print_obj(TextOutType &);
    public:
    virtual void get_str(TextOutType &)const = 0;// значение строки
    static const void * tip(){ return &typ; } // значение типа
    PRIZNAK_SERVICE_DLL WriteStringBaseType(const char * name,int min,int max,const char * razd = "=");
};// WriteStringBaseType


//-- Ввод строки (если ошибка возвращает 0, иначе адрес строки в д-памяти)--
// синтаксис :  МВ1 + МВ2 + ... ;
//       где :  МВi ::= '...' | "..." |  [число] | <имя строки>
PRIZNAK_SERVICE_DLL char * ReadString(ReadTextType & text,VariablBaseType * base=0);
PRIZNAK_SERVICE_DLL char * ReadString(ReadTextType & text,TextOutType & err,VariablBaseType * base=0);

// создание объекта типа символьной строки
//  name - имя, s - значение.
//  переменные name и s - копируются ( после их можно уничтожать )
PRIZNAK_SERVICE_DLL VariablBaseType * OprConstString(const char * name,const char * s);

//---------------------- связывание строки -----------------------------
//  Name - имя
//  S - строка ( адресная переменная )
//  max -  максимальное число изменений  (по умолчанию 1)
//  min -  минимальное число изменений  (по умолчанию 1)
PRIZNAK_SERVICE_DLL VariablBaseType * OprString(const char * Name,char * & S,int min,int max,const char * razd = "=");

//============================ Ввод чисел ==================================

//---------------- Определение скалярной константы -----------------------
PRIZNAK_SERVICE_DLL VariablBaseType * SetScalarConst(const char * name,const long double & x);

//--------------- чтение числа (если ошибка kod != 0) ----------------------
PRIZNAK_SERVICE_DLL long double ReadNumber(ReadTextType & text,int & kod);
PRIZNAK_SERVICE_DLL long double ReadNumber(ReadTextType & text,TextOutType & err,int & kod);
PRIZNAK_SERVICE_DLL long double ReadNumber(ReadTextType & text,int & kod,VariablBaseType * SR);
PRIZNAK_SERVICE_DLL long double ReadNumber(ReadTextType & text,TextOutType & err,int & kod,VariablBaseType * SR);

//------------------------- связывание числа -----------------------------
//  Name - имя
//  x   - число
//  min - минимальное число изменений
//  max - максимальное число изменений
//  fc  - функция проверки (возврат: истина если допустимо, ложь если недопустимо)
typedef int (*FuncCheckNumberType)(const long double &);// её тип
struct CheckNumberBaseType
{// проверка на допустимость числа
    virtual int check(const long double &)const = 0;// функция проверки (возврат: истина если допустимо, ложь если недопустимо)
    virtual ~CheckNumberBaseType(){}
};// CheckNumberBaseType
struct CheckNumberFuncType : public CheckNumberBaseType
{
    PRIZNAK_SERVICE_DLL static int b0(const long double &);// проверка на > 0
    PRIZNAK_SERVICE_DLL static int be0(const long double &);// проверка на >= 0
    PRIZNAK_SERVICE_DLL static int be1(const long double &);// проверка на >= 1
    FuncCheckNumberType FuncCheckNumber;
    PRIZNAK_SERVICE_DLL virtual int check(const long double &)const;// функция проверки (возврат: истина если допустимо, ложь если недопустимо)
    PRIZNAK_SERVICE_DLL CheckNumberFuncType(FuncCheckNumberType F);
};// CheckNumberFuncType
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,signed char & x,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,signed char & x,int min,int max,FuncCheckNumberType fc);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,signed char & x,int min,int max,const CheckNumberBaseType & c);
inline VariablBaseType * OprNumber(const char * Name,unsigned char & x,int min,int max){ return OprNumber(Name,(signed char&)x,min,max); }
inline VariablBaseType * OprNumber(const char * Name,unsigned char & x,int min,int max,FuncCheckNumberType fc){ return OprNumber(Name,(signed char&)x,min,max,fc); }
inline VariablBaseType * OprNumber(const char * Name,unsigned char & x,int min,int max,const CheckNumberBaseType & c){ return OprNumber(Name,(signed char&)x,min,max,c); }
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,short int & x,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,short int & x,int min,int max,FuncCheckNumberType fc);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,short int & x,int min,int max,const CheckNumberBaseType & c);
inline VariablBaseType * OprNumber(const char * Name,unsigned short int & x,int min,int max){ return OprNumber(Name,(short int&)x,min,max); }
inline VariablBaseType * OprNumber(const char * Name,unsigned short int & x,int min,int max,FuncCheckNumberType fc){ return OprNumber(Name,(short int&)x,min,max,fc); }
inline VariablBaseType * OprNumber(const char * Name,unsigned short int & x,int min,int max,const CheckNumberBaseType & c){ return OprNumber(Name,(short int&)x,min,max,c); }
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,int & x,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,int & x,int min,int max,FuncCheckNumberType fc);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,int & x,int min,int max,const CheckNumberBaseType & c);
inline VariablBaseType * OprNumber(const char * Name,unsigned int & x,int min,int max){ return OprNumber(Name,(int&)x,min,max); }
inline VariablBaseType * OprNumber(const char * Name,unsigned int & x,int min,int max,FuncCheckNumberType fc){ return OprNumber(Name,(int&)x,min,max,fc); }
inline VariablBaseType * OprNumber(const char * Name,unsigned int & x,int min,int max,const CheckNumberBaseType & c){ return OprNumber(Name,(int&)x,min,max,c); }
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,long int & x,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,long int & x,int min,int max,FuncCheckNumberType fc);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,long int & x,int min,int max,const CheckNumberBaseType & c);
inline VariablBaseType * OprNumber(const char * Name,unsigned long int & x,int min,int max){ return OprNumber(Name,(long int&)x,min,max); }
inline VariablBaseType * OprNumber(const char * Name,unsigned long int & x,int min,int max,FuncCheckNumberType fc){ return OprNumber(Name,(long int&)x,min,max,fc); }
inline VariablBaseType * OprNumber(const char * Name,unsigned long int & x,int min,int max,const CheckNumberBaseType & c){ return OprNumber(Name,(long int&)x,min,max,c); }
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,float & x,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,float & x,int min,int max,FuncCheckNumberType fc);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,float & x,int min,int max,const CheckNumberBaseType & c);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,double & x,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,double & x,int min,int max,FuncCheckNumberType fc);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,double & x,int min,int max,const CheckNumberBaseType & c);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,long double & x,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,long double & x,int min,int max,FuncCheckNumberType fc);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumber(const char * Name,long double & x,int min,int max,const CheckNumberBaseType & c);
//=========================== Ввод массива ===============================
//------------------- Определение массива констант -----------------------
// данные копируются !
PRIZNAK_SERVICE_DLL VariablBaseType * SetMassivConst(const char * name,const long double * x,int dim);

//-------------------------- чтение массива ------------------------------
//   массив распределяется в динамической памяти (возврат 0 - ошибка чтения)
//   на выходе в параметре dim указывается размерность считаного массива
//   0 - значит скаляр (выделен 1 элемент)
PRIZNAK_SERVICE_DLL long double * ReadMassiv(unsigned int & dim,ReadTextType & text,VariablBaseType * SR = 0);
PRIZNAK_SERVICE_DLL long double * ReadMassiv(unsigned int & dim,ReadTextType & text,TextOutType & err,VariablBaseType * SR = 0);

//---------------------- связывание векторов ------------------------------
//  Name - имя
//  x - адрес
//  dim - размерность
//  min -  минимальное число изменений
//  max -  максимальное число изменений
//VariablBaseType * OprVector(const char * Name,int * x,int dim,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprVector(const char * Name,float * x,int dim,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprVector(const char * Name,double * x,int dim,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprVector(const char * Name,long double * x,int dim,int min,int max);

//-------------- связывание массива неопределенной длинны -----------------
//  Name - имя
//  x - адрес
//  dim - размерность
//  min -  минимальное число изменений
//  max -  максимальное число изменений
//VariablBaseType * OprNumPtr(const char * Name,int *& x,int & dim,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumPtr(const char * Name,float *& x,int & dim,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumPtr(const char * Name,double *& x,int & dim,int min,int max);
PRIZNAK_SERVICE_DLL VariablBaseType * OprNumPtr(const char * Name,long double *& x,int & dim,int min,int max);
//-----------------------------------------------------------------------

//======================== Ввод массива индексов ============================

//----------------------- чтение массива индексов ---------------------------
//  массив распределяется в динамической памяти (возврат 0 - ошибка чтения)
//  на выходе в параметре dim указывается размерность считаного массива
//  cmp - функция сравнения, возврат:
//        > 0 <=> x > y
//        = 0 <=> x = y
//        < 0 <=> x < y
//  x - текущий элемент таблицы, y - сравниваемое значение
//  индексы заносятся в соответствие с отношением порядка задаваемым cmp
//  если cmp = 0, то в порядке чтения
//      <элемемент> ::= <число>            : один индекс
//      <элемемент> ::= <число>..<число>[:<число>] : набор индексов в интервале между этими числами
//                                                   если задано :, то <число> - интервал
PRIZNAK_SERVICE_DLL int * ReadIndex(int & dim,ReadTextType & text,TextOutType & err,VariablBaseType * SR = 0,D_Spisok_Int_Type::CmpType cmp = 0);

//--------------------- связывание массива индексов ---------------------
//  Name - имя
//  x - адрес
//  dim - число введенных индексов
//  min -  минимальное число изменений
//  max -  максимальное число изменений
//  cmp - функция сравнения
//  s1  - открывающая скобка
//  s2  - закрывающая скобка
class ReadIndexType : public VariablBaseType
{// для ввода массива индексов
    protected:
    int *& index;
    int & kol_index;
    const char s1; // открывающая скобка
    const char s2; // закрывающая скобка
    D_Spisok_Int_Type::CmpType cmp;
    PRIZNAK_SERVICE_DLL int read_obj(ReadTextType & text,TextOutType & err);
    PRIZNAK_SERVICE_DLL int print_obj(TextOutType & out);
    public:
    // чтение 1 элемента массива индексов
    PRIZNAK_SERVICE_DLL static int read1(int & n1,int & n2,int & delta,ReadTextType & text,TextOutType & err,VariablBaseType * base = 0);
    PRIZNAK_SERVICE_DLL ReadIndexType(const char * name,int *& X,int & size,int min,int max,D_Spisok_Int_Type::CmpType cmp0 = 0);
    PRIZNAK_SERVICE_DLL ReadIndexType(const char * name,int *& X,int & size,char s10,char s20,int min,int max,D_Spisok_Int_Type::CmpType cmp0 = 0);
};// ReadIndexType


//================== функции создания временных объектов ====================
// для использования функции DefineProc с именем "ИМЯ" при вводе,
// необходимо определить ея как глобальную оператором:
//
//    VariablBaseType::SetGlobProc("ИМЯ",DefineProc);
//
// при этом синтаксис оператора создания временного объекта
// с именем имя_объекта следующий:
//
//  ИМЯ имя_объекта = <метасимвол ввода>
//
// примечание: имена объектов должны состоять из букв, цифр и символа
//             подчеркивания, при этом для объектов типа ЧИСЛО и ВЕКТОР
//             имена объектов не должны начинаться с цифры
//
// создание временного объекта типа СТРОКА
PRIZNAK_SERVICE_DLL int DefineString(ReadTextType & text,TextOutType & err,VariablBaseType * SR);
// создание объекта типа ЧИСЛО
PRIZNAK_SERVICE_DLL int DefineScalar(ReadTextType & text,TextOutType & err,VariablBaseType * SR);
// создание объекта типа ВЕКТОР
PRIZNAK_SERVICE_DLL int DefineVector(ReadTextType & text,TextOutType & err,VariablBaseType * SR);
// определение арифметической функции
// синтаксис : имя(x0,x1,..,xn) = <числовое выражение>
PRIZNAK_SERVICE_DLL int DefineFunction(ReadTextType & text,TextOutType & err,VariablBaseType * SR);

#endif
