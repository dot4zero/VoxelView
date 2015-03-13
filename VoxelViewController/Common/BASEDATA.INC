//               Основные типы структур данных
#ifndef BASE_DATA_TYPE_INC
#define BASE_DATA_TYPE_INC
// подключаемые файлы
#include "service.inc"
#include <stdio.h>

//======================== Работа с адресами ===========================
// добавление к адресу offs байт
inline void * Add_Byte_PTR(void * ptr,int offs){ return ((char *)ptr)+offs;}
inline const void * Add_Byte_PTR(const void * ptr,int offs){ return ((char *)ptr)+offs;}

//=================== Обработка ошибок ================================
class TextOutType; // предописание
class ErrorType
{
    public:
    typedef void (*exit_type)();// функция аварийного выхода
    typedef void (*write_type)(const char *);// функция выдачи сообщений об ошибках
    private:
    static exit_type func_exit;// функция аварийного выхода
    static write_type func_write;// функция выдачи сообщений об ошибках
    public:
    // переопределение функций, возврат : предыдущее значение (0 - не устанавливать)
    PRIZNAK_SERVICE_DLL static exit_type SetExit(exit_type e = 0);
    PRIZNAK_SERVICE_DLL static write_type SetWrite(write_type e = 0);
    PRIZNAK_SERVICE_DLL static void act(const char * s);
    PRIZNAK_SERVICE_DLL static TextOutType & Out; // для выдачи сообщений об ошибках
    PRIZNAK_SERVICE_DLL static void Write(const char * s);
    PRIZNAK_SERVICE_DLL static void Exit();
};// ErrorType

//-------------------- дисковые файлы -----------------------------
class DiskFileType // дисковый файл
{
    void operator = (DiskFileType &); // заглушка
    void error_obr(int);// обработка ошибки с сообщением
    enum {extrn_file,lock_file} tip;// тип файла (внешний или определенный внутри)
    char * NameFile;
    protected:
    FILE * uFILE; // указатель на файл
    protected:
    PRIZNAK_SERVICE_DLL virtual void error(const char *);// обработка ошибки с сообщением
    public:
    enum open_type  // типы открытия файла
    {
      TxtRead      = 0, // текстовое чтение
      TxtWrite_new = 1, // текстовая запись
      TxtWrite     = 2, // текстовая дозапись
      BinInOut     = 3, // двоичный ввод-вывод в имеющийся файл
      BinInOut_new = 4, // двоичный ввод-вывод с переоткрытием
      BinIn        = 5, // двоичный ввод
      BinOut       = 6, // двоичный вывод в имеющийся файл
      BinOut_new   = 7  // двоичный вывод с переоткрытием
    };
    const char * name()const{ return NameFile; }
    PRIZNAK_SERVICE_DLL DiskFileType(DiskFileType &);
    PRIZNAK_SERVICE_DLL DiskFileType(const char *,const open_type);// открытие
    PRIZNAK_SERVICE_DLL virtual ~DiskFileType();
    // функции
    PRIZNAK_SERVICE_DLL long FilePos()const;// получение позиции файла
    PRIZNAK_SERVICE_DLL void FilePos(const long pos);// установка позиции файла
    PRIZNAK_SERVICE_DLL void BinWrite(const void *,size_t);// двоичная запись (BinInOut, BinInOut_new)
    PRIZNAK_SERVICE_DLL void BinRead(void *,size_t); // двоичное чтение (BinInOut, BinInOut_new)
    PRIZNAK_SERVICE_DLL void TextWrite(const char *);// текстовая запись (TxtWrite, TxtWrite_new)
    PRIZNAK_SERVICE_DLL void FormatTextWrite(const char * format,...);// форматированная текстовая запись (TxtWrite, TxtWrite_new)
    PRIZNAK_SERVICE_DLL char TextRead();
    PRIZNAK_SERVICE_DLL int TextRead(char * s,int N); // чтение в строку до символа '\n'
    // буферизация
    PRIZNAK_SERVICE_DLL void bufoff(); // отключить буферизацию
    PRIZNAK_SERVICE_DLL void bufset(unsigned size); // задать размер буфера
    PRIZNAK_SERVICE_DLL void flush();
    PRIZNAK_SERVICE_DLL static void flush_all();
    // сервис
    PRIZNAK_SERVICE_DLL long size()const; // размер файла
    PRIZNAK_SERVICE_DLL int end()const; // проверка на конец файла
    //   <  0 - файл с именем Name не существует
    //   >= 0 - размер файла
    PRIZNAK_SERVICE_DLL static long CheckFile(const char * NameFile);
};// DiskFileType

//=======================  Стек =============================
class D_Stack_Base_Type
{// базовый тип для стека
    D_Stack_Base_Type(D_Stack_Base_Type &);// заглушка
    void operator = (D_Stack_Base_Type &);// заглушка
    // внутренние данные
    struct SpisokBaseType // элемент списка
    {
      SpisokBaseType * next;// указатель на следующий элемент
      char * data; // указатель на записываемые данные (char - 1байт !!!)
    } * Spisok;
    char * tek; // указатель на последний занесенный элемент (если СТЕК не пуст)
    const unsigned int SizeLine; // размер линейного участка (в элементах)
    const unsigned int SizeLineByte; // размер линейного участка (в байтах) == SizeLine*sizeof_data
    const unsigned int sizeof_data;//размер данных записываемых в стек
    // внутренние функции
    void * (*new_data)(int);// выделение памяти под массив данных
    void (*delete_data)(void * );// уничтожение памяти после new_data
    protected:
    PRIZNAK_SERVICE_DLL void * push();// занесение в стек
    PRIZNAK_SERVICE_DLL void * pop();// выборка из стека
    public:
    // создание
    PRIZNAK_SERVICE_DLL D_Stack_Base_Type(const unsigned int data,const unsigned int size,
                      void * (*e_new_data)(int),void (*e_delete_data)(void * ));
    PRIZNAK_SERVICE_DLL ~D_Stack_Base_Type();
//--------------- user'ские операции ------------------------
    void clear(); // очистка стека
    int pust()const{return (Spisok==0)||((Spisok->next == 0)&&(Spisok->data == tek));}// истина если пуст
    int size()const;// размер стека
};// D_Stack_Base_Type

//----------------  динамический стек -----------------------
template <class type> class D_Stack : public D_Stack_Base_Type
{//  динамический стек
 //  тип type должен иметь конструктор без параметров
    static void * s_new_data(int i){return new type[i];}// выделение памяти под массив данных
    static void s_delete_data(void * x){delete[] (type *)x;}// уничтожение памяти после new_data
    public:
    // конструктор
    D_Stack():D_Stack_Base_Type(sizeof(type),1,s_new_data,s_delete_data){}
    D_Stack(const int size):D_Stack_Base_Type(sizeof(type),size,s_new_data,s_delete_data){}
    ~D_Stack(){}
    void operator <= (const type & t)
    {// занесение в стек
      *((type *)push()) = t;
    }
    int pop(type & t)
    {// выборка из стека
      type * prom = (type *)D_Stack_Base_Type::pop();
      if(prom == 0) return 1;
      t = *prom;
      return 0;
    }// <=
};// D_Stack
template<class type> inline int operator <= (type & t,D_Stack<type> & Stack){ return Stack.pop(t); }

//============================  Список ==============================

class D_Spisok_Simple_Base_Type
{// базовый класс для динамического списка простого типа
 // (т.е. типа, допускающего копирование по memcpy)
 // описаны основные алгоритмы : добавления, удаления элемента, обработки списка
    D_Spisok_Simple_Base_Type(D_Spisok_Simple_Base_Type&); // заглушка
    void operator = (D_Spisok_Simple_Base_Type&); // заглушка
    public:
    struct ObrType
    {// интерфейсный тип для обработки
     // параметр x функции func - указатель на текущий элемент списка
      virtual int func(void * x) = 0;
      virtual ~ObrType(){}
    };// ObrType
    //------------------ поля объекта ------------------
    protected:
    int pSize;
    void * pTable;
    // размер списка
    public:
    int size()const{ return pSize; }
    //------------------ добавление в список ------------------
    // параметры:
    //   Table     - указатель на таблицу (массив данных)
    //   size_tabl - длина таблицы в элементах (увеличивается на 1)
    //   size_data - размер данных (в байтах)
    //   new_data  - выделение памяти под массив данных
    //   del_data  - уничтожение памяти после new_data
    // добавление в конец списка
    // возврат: индекс занесённого элемента
    public:
    PRIZNAK_SERVICE_DLL static int add(void *& Table,int & size_tabl,int size_data,void * data,void * (*new_data)(int),void (*del_data)(void * ));
    protected:
    PRIZNAK_SERVICE_DLL int add(int size_data,void * data,void * (*new_data)(int),void (*del_data)(void * ));
    // добавление в список, в соответствие с отношением порядка задаваемым cmp:
    //   cmp - сравнение с элементами списка, возврат функции func:
    //        > 0 <=> элемент списка >
    //        = 0 <=> элемент списка =
    //        < 0 <=> элемент списка <
    // добавляется перед самым левым элементом, для которого значение func > 0,
    // или в конец, если он не найден.
    // если при этом встречается элемент с равным 0 значением func - то добавление не происходит,
    // возврат: индекс занесённого элемента
    public:
    PRIZNAK_SERVICE_DLL static int add(void *& Table,int & size_tabl,int size_data,void * data,void * (*new_data)(int),void (*del_data)(void * ),D_Spisok_Simple_Base_Type::ObrType & cmp);
    protected:
    PRIZNAK_SERVICE_DLL int add(int size_data,void * data,void * (*new_data)(int),void (*del_data)(void * ),D_Spisok_Simple_Base_Type::ObrType & cmp);
    //------------------ удаление элемента ------------------
    // удаление последнего элемента
    public:
    PRIZNAK_SERVICE_DLL static void del(void *& Table,int & size_tabl,int size_data,void * (*new_data)(int),void (*del_data)(void * ));
    protected:
    PRIZNAK_SERVICE_DLL void del(int size_data,void * (*new_data)(int),void (*del_data)(void * ));
    // удаление элемента по индексу
    // параметры (кроме описанных выше):
    //   index - индекс удаляемого элемента (от 0)
    public:
    PRIZNAK_SERVICE_DLL static void del(void *& Table,int & size_tabl,int size_data,void * (*new_data)(int),void (*del_data)(void * ),int index);
    protected:
    PRIZNAK_SERVICE_DLL void del(int size_data,void * (*new_data)(int),void (*del_data)(void * ),int index);
    // удаление заданого числа элементов
    // параметры (кроме описанных выше):
    //   kol - число удаляемых элементов
    public:
    PRIZNAK_SERVICE_DLL static void del(void *& Table,int & size_tabl,int size_data,void * (*new_data)(int),void (*del_data)(void * ),int index,int kol);
    protected:
    PRIZNAK_SERVICE_DLL void del(int size_data,void * (*new_data)(int),void (*del_data)(void * ),int index,int kol);
    //------------------ циклическая обработка ------------------
    // параметры (кроме описанных для функций add):
    //   dev - устройство обработки одного элемента
    // обработка идёт пока значение функции dev.func = 0
    private:
    PRIZNAK_SERVICE_DLL static int obr(void * Table,int size_tabl,int size_data,D_Spisok_Simple_Base_Type::ObrType & dev,int dir);
    // обработка с начала
    public:
    PRIZNAK_SERVICE_DLL static int obr_beg(void * Table,int size_tabl,int size_data,D_Spisok_Simple_Base_Type::ObrType & dev);
    protected:
    PRIZNAK_SERVICE_DLL int obr_beg(int size_data,D_Spisok_Simple_Base_Type::ObrType & dev)const;
    // обработка с конца
    public:
    PRIZNAK_SERVICE_DLL static int obr_end(void * Table,int size_tabl,int size_data,D_Spisok_Simple_Base_Type::ObrType & dev);
    protected:
    PRIZNAK_SERVICE_DLL int obr_end(int size_data,D_Spisok_Simple_Base_Type::ObrType & dev)const;
    //------------------ общие функции ------------------
    public:
    PRIZNAK_SERVICE_DLL D_Spisok_Simple_Base_Type();
    PRIZNAK_SERVICE_DLL ~D_Spisok_Simple_Base_Type(); // не очищает список
};// D_Spisok_Simple_Base_Type


class D_Spisok_Base_Ptr : public D_Spisok_Simple_Base_Type
{// базовый тип для списка указателей
    // функции работы с динамической памятью
    static void * new_void_ptr(int);
    static void delete_void_ptr(void *);
    public:
    void * const * table()const{ return (void * const *)pTable; }
    void * table(int i)const{ return ((void **)pTable)[i]; }
    //------------------ добавление в список ------------------
    // добавить в конец списка
    PRIZNAK_SERVICE_DLL static int add(void **& Table,int & size,void * el);
    PRIZNAK_SERVICE_DLL int add(void * el);
    int operator += (void * el){ return add(el); }
    // добавить в список в соответствие с порядком задаваемым cmp (обработка сначала)
    PRIZNAK_SERVICE_DLL static int add(void **& Table,int & size,void * el,D_Spisok_Simple_Base_Type::ObrType &);
    PRIZNAK_SERVICE_DLL int add(void * el,D_Spisok_Simple_Base_Type::ObrType &);
    //------------------ удаление элемента ------------------
    // удаление последнего элемента
    PRIZNAK_SERVICE_DLL static void del(void **& Table,int & size_tabl);
    PRIZNAK_SERVICE_DLL void del();
    // удаление элемента по индексу
    //   index - индекс удаляемого элемента (от 0)
    PRIZNAK_SERVICE_DLL static void del(void **& Table,int & size_tabl,int index);
    PRIZNAK_SERVICE_DLL void del(int index);
    // удаление заданого числа элементов
    //   kol - число удаляемых элементов
    PRIZNAK_SERVICE_DLL static void del(void **& Table,int & size_tabl,int index,int kol);
    PRIZNAK_SERVICE_DLL void del(int index,int kol);
    //------------------ циклическая обработка ------------------
    typedef void (*FuncObrType)(void *); // функция обработки
    private:
    // функция циклической обработки
    typedef int (*FuncCycleType)(void * Table,int size_tabl,int size_data,D_Spisok_Simple_Base_Type::ObrType & dev);
    static void obr(void ** Table,int size,D_Spisok_Base_Ptr::FuncObrType,D_Spisok_Base_Ptr::FuncCycleType);
    public:
    // обработка всего списка с начала
    PRIZNAK_SERVICE_DLL static void obr_beg(void ** Table,int size,D_Spisok_Base_Ptr::FuncObrType);
    PRIZNAK_SERVICE_DLL void obr_beg(D_Spisok_Base_Ptr::FuncObrType)const;
    // обработка всего списка с конца
    PRIZNAK_SERVICE_DLL static void obr_end(void ** Table,int size,D_Spisok_Base_Ptr::FuncObrType);
    PRIZNAK_SERVICE_DLL void obr_end(D_Spisok_Base_Ptr::FuncObrType)const;
    //------------------ общие функции ------------------
    PRIZNAK_SERVICE_DLL void clear();
    PRIZNAK_SERVICE_DLL ~D_Spisok_Base_Ptr();
};// D_Spisok_Base_Ptr


class D_Spisok_Int_Type : public D_Spisok_Simple_Base_Type
{// тип для списка индексов
    // функции работы с динамической памятью
    static void * new_void_ptr(int);
    static void delete_void_ptr(void *);
    public:
    int * table()const{ return (int *)pTable; }
    int & operator[] (int i)const{ return ((int *)pTable)[i]; }
    //------------------ добавление в список ------------------
    // добавить в конец списка
    PRIZNAK_SERVICE_DLL static int add(int *& Table,int & size,int el);
    PRIZNAK_SERVICE_DLL int add(int el);
    int operator += (int el){ return add(el); }
    // добавить в список в соответствие с порядком задаваемым cmp (обработка сначала)
    typedef int (*CmpType)(int x,int y);
    // функция сравнения, возврат:
    //        > 0 <=> x > y
    //        = 0 <=> x = y
    //        < 0 <=> x < y
    // x - текущий элемент таблицы, y - сравниваемое значение
    PRIZNAK_SERVICE_DLL static int add(int *& Table,int & size,int el,D_Spisok_Int_Type::CmpType);
    PRIZNAK_SERVICE_DLL int add(int el,D_Spisok_Int_Type::CmpType);
    //------------------ удаление элемента ------------------
    // удаление последнего элемента
    PRIZNAK_SERVICE_DLL static void del(int *& Table,int & size_tabl);
    PRIZNAK_SERVICE_DLL void del();
    // удаление элемента по индексу
    //   index - индекс удаляемого элемента (от 0)
    PRIZNAK_SERVICE_DLL static void del(int *& Table,int & size_tabl,int index);
    PRIZNAK_SERVICE_DLL void del(int index);
    // удаление заданого числа элементов
    //   kol - число удаляемых элементов
    PRIZNAK_SERVICE_DLL static void del(int *& Table,int & size_tabl,int index,int kol);
    PRIZNAK_SERVICE_DLL void del(int index,int kol);
    //------------------ общие функции ------------------
    PRIZNAK_SERVICE_DLL void clear();
    PRIZNAK_SERVICE_DLL int find(int k)const;// поиск наименьшего индекса элемента со значением k (если нет, то -1)
    PRIZNAK_SERVICE_DLL int findr(int k)const;// поиск наибольшего индекса элемента со значением k (если нет, то -1)
    PRIZNAK_SERVICE_DLL D_Spisok_Int_Type();
    PRIZNAK_SERVICE_DLL ~D_Spisok_Int_Type();
};// D_Spisok_Int_Type


template <class type> class D_SpisokPtr : public D_Spisok_Base_Ptr
{// не упорядоченый динамический список указателей
    void add(); // заглушка
    //void del(); // заглушка
    public:
    ~D_SpisokPtr(){}
    static void add(type **& t,int & size,type * x){ D_Spisok_Base_Ptr::add((void **&)t,size,x); }
    void operator += (type * x){ D_Spisok_Base_Ptr::add(x); }
    type * operator [](int i)const{ return ((type **)pTable)[i]; }
    type * table(int i)const{ return ((type **)pTable)[i]; }
    type * const * table()const{ return (type * const *)pTable; }
};// D_SpisokPtr

template <class type> class D_SpisokSimpleType : public D_Spisok_Simple_Base_Type
{// не упорядоченый динамический список
    public:
    static void * new_data(int n){ return new type[n]; }
    static void delete_data(void * x){ delete[] (type *)x; }
    ~D_SpisokSimpleType(){ delete_data(pTable); }
    void clear(){ delete_data(pTable); pTable = 0; pSize = 0; }
    static void add(type *& t,int & size,const type & x)
    {
      D_Spisok_Simple_Base_Type::add((void *&)t,size,sizeof(type),(void*)&x,new_data,delete_data);
    }// add
    void operator += (const type & x){ D_Spisok_Simple_Base_Type::add(sizeof(type),(void*)&x,new_data,delete_data); }
    void del(){ D_Spisok_Simple_Base_Type::del(sizeof(type),new_data,delete_data);}
    void del(int i){ D_Spisok_Simple_Base_Type::del(sizeof(type),new_data,delete_data,i);}
    void del(int i,int kol){ D_Spisok_Simple_Base_Type::del(sizeof(type),new_data,delete_data,i,kol);}
    static void del(type *& t,int & size)
    {
      D_Spisok_Simple_Base_Type::del((void *&)t,size,sizeof(type),new_data,delete_data);
    }// del
    static void del(type *& t,int & size,int i)
    {
      D_Spisok_Simple_Base_Type::del((void *&)t,size,sizeof(type),new_data,delete_data,i);
    }// del
    static void del(type *& t,int & size,int i,int kol)
    {
      D_Spisok_Simple_Base_Type::del((void *&)t,size,sizeof(type),new_data,delete_data,i,kol);
    }// del
    type & operator[](int i)const{ return ((type *)pTable)[i]; }
    type & table(int i)const{ return ((type *)pTable)[i]; }
    type * table()const{ return (type *)pTable; }
};// D_SpisokSimpleType


//============  создание архивов динамических объектов  ================

struct PRIZNAK_SERVICE_DLL MassivArchiveType
{// архив массивов : один каждого типа на всю программу
 //                  save - сравнивает массив и если нет такого то сохраняет в памяти,
 //                         иначе удаляет его и присвает значение найденного
 //                  del - удаляет массив из памяти
    // для int
    static const int * save(int * x,int size);// сохранение
    static void del(const int * x,int size);// удаление
    // для float
    static const float * save(float * x,int size);// сохранение
    static void del(const float * x,int size);// удаление
    // для double
    static const double * save(double * x,int size);// сохранение
    static void del(const double * x,int size);// удаление
    // для long double
    static const long double * save(long double * x,int size);// сохранение
    static void del(const long double * x,int size);// удаление
};// MassivArchiveType

class ArchiveDinamicDataBaseType
{
    D_Spisok_Base_Ptr SpisData; // список данных
  //----- функции для работы с данными -----
    // удаление данных
    void (*del_data)(void *);
    // сравнение данных (data) с идентификатором (id)
    //   при эквивалентности возврат 1 (истина)
    //   иначе                       0 (ложь)
    int (*cmp_data)(const void * data,const void * id);
    public:
  //----- функции самого объекта -----
    // добавить ещё один элемент данных
    void new_data(void * data){ SpisData += data; }
    void operator += (void * data){ new_data(data); }
    // поиск элемента данных эквивалентному идентификатору (id)
    // при неудаче возврат 0
    PRIZNAK_SERVICE_DLL void * find(const void * id);
    const D_Spisok_Base_Ptr & spisok()const{ return SpisData; }
    // очистка
    PRIZNAK_SERVICE_DLL void clear();
    // создание-уничтожение
    PRIZNAK_SERVICE_DLL ArchiveDinamicDataBaseType(void (*del)(void *),int (*cmp)(const void * data,const void * id));
    PRIZNAK_SERVICE_DLL ~ArchiveDinamicDataBaseType();
};// ArchiveDinamicDataBaseType

class SuperArchiveType : public ArchiveDinamicDataBaseType
{// архив архивов
    static void del(void *);
    static int cmp(const void * data,const void * id);
    public:
    PRIZNAK_SERVICE_DLL SuperArchiveType();
    PRIZNAK_SERVICE_DLL void operator += (ArchiveDinamicDataBaseType &);
};// SuperArchiveType

template <class data_type,class id_type>
class ArchiveDinamicDataType : public ArchiveDinamicDataBaseType
{// должен быть определён  int operator == (const data_type &,const id_type &);
    static void del(void * data)
    {// удаление данных
      delete (data_type *)data;
    }// del_data
    static int cmp(const void * data,const void * id)
    {// сравнение данных (data) с идентификатором (id)
     //   при эквивалентности возврат 1 (истина)
     //   иначе                       0 (ложь)
      return (*(data_type *)data) == (*(id_type *)id);
    }// cmp_data
    public:
    void new_data(data_type * data)
    {// добавить ещё один элемент данных
      ArchiveDinamicDataBaseType::new_data(data);
    }// new_data
    void operator += (data_type * data){ new_data(data); }
    data_type * find(const id_type & id)
    {// поиск элемента данных эквивалентному идентификатору (id)
     // при неудаче возврат 0
      return (data_type *)ArchiveDinamicDataBaseType::find(&id);
    }
    int size()const{ return spisok().size(); }
    data_type * const * table()const{ return (data_type * const *)spisok().table(); }
    ArchiveDinamicDataType():ArchiveDinamicDataBaseType(del,cmp){}
};// ArchiveDinamicDataType

template <class data_type,class id_type>
class LibrDinamicDataType : public ArchiveDinamicDataType<data_type,id_type>
{// библиотека динамических данных
 // должен быть определён  data_type(const id_type &);
    public:
    data_type & create(const id_type & id)
    {// создание указателя на объект
      data_type * data = find(id);
      if(data == 0)
      {
         data = new data_type(id);
         new_data(data);
      }
      return *data;
    }// create
};// LibrDinamicDataType


//============  размножение указателей на объект со счётчиком ссылок ================
struct CounterObjectBasePtr
{// базовый класс для слежения за размножением ссылки на обект
 // не допустимо копирование функциями типа memcpy
    typedef void (*delproc)(void *);// процедура удаления объекта
    protected:
    void * Obj; // указатель на объект
    // ofs - смещение счётчика (типа int) в объекте (в конструкторе счётчик должен занулятся)
    // например: ofs = offsetof(ObjType,count)
    PRIZNAK_SERVICE_DLL void inc(void * O,int ofs);    // запомнить ссылку (для конструктора)
    PRIZNAK_SERVICE_DLL void dec(delproc dp,int ofs); // удалить ссылку   (для деструктора)
    PRIZNAK_SERVICE_DLL void copy(void * O,delproc dp,int ofs); // копировать ссылку (для оператора = )
    void copy(const CounterObjectBasePtr & O,delproc dp,int ofs){copy(O.Obj,dp,ofs); } // копировать ссылку (для оператора = )
    // для работы со списками, возврат - новый размер
    PRIZNAK_SERVICE_DLL static int add_spis(CounterObjectBasePtr *& table,int size,const CounterObjectBasePtr & O,int ofs);// добавить в конец
    PRIZNAK_SERVICE_DLL static int del_spis(CounterObjectBasePtr *& table,int size,delproc dp,int ofs,int i);// удалить i-тый элемент списка
    PRIZNAK_SERVICE_DLL static void del_spis_end(CounterObjectBasePtr * table,int size,delproc dp,int ofs);// удалить из конца списока
    PRIZNAK_SERVICE_DLL static void del_spis(CounterObjectBasePtr * table,int size,delproc dp,int ofs);// удалить весь список
    public:
    operator int()const{ return Obj != 0; } // если сущесвует, то истинно
};// CounterObjectBasePtr

template <class type,int ofs> class CounterObjectPtr : public CounterObjectBasePtr
{// шаблон для слежения: type - тип объекта,
 // ofs - смещение счётчика (типа int) в объекте (в конструкторе счётчик должен занулятся)
 // например: ofs = offsetof(ObjType,count)
    static void dp(void * t){ delete (type*)t; }
    public:
    const type * operator ->()const{ return (const type*)Obj; } // взять элемент константного объекта
    type * operator ->(){ return (type*)Obj; }                  // взять элемент объекта
    CounterObjectPtr & operator = (const CounterObjectPtr & O){ copy(O,dp,ofs); return *this; }
    CounterObjectPtr(type * O){ inc(O,ofs); }
    CounterObjectPtr(const CounterObjectPtr & O){ inc(O.Obj,ofs); }
    ~CounterObjectPtr(){ dec(dp,ofs); }
    // для работы со списками, возврат - новый размер
    static int add_spis(CounterObjectPtr *& table,int size,const CounterObjectPtr & O){ return CounterObjectBasePtr::add_spis((CounterObjectBasePtr*&)table,size,O,ofs); }// добавить в конец
    static int del_spis(CounterObjectPtr *& table,int size,int i){ return CounterObjectBasePtr::del_spis((CounterObjectBasePtr*&)table,size,dp,ofs,i); }// удалить i-тый элемент списка
    static void del_spis(CounterObjectPtr * table,int size){ CounterObjectBasePtr::del_spis(table,size,dp,ofs); }// удалить весь список
};// CounterObjectPtr

#endif
