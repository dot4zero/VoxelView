//               �������� ���� �������� ������
#ifndef BASE_DATA_TYPE_INC
#define BASE_DATA_TYPE_INC
// ������������ �����
#include "service.inc"
#include <stdio.h>

//======================== ������ � �������� ===========================
// ���������� � ������ offs ����
inline void * Add_Byte_PTR(void * ptr,int offs){ return ((char *)ptr)+offs;}
inline const void * Add_Byte_PTR(const void * ptr,int offs){ return ((char *)ptr)+offs;}

//=================== ��������� ������ ================================
class TextOutType; // ������������
class ErrorType
{
    public:
    typedef void (*exit_type)();// ������� ���������� ������
    typedef void (*write_type)(const char *);// ������� ������ ��������� �� �������
    private:
    static exit_type func_exit;// ������� ���������� ������
    static write_type func_write;// ������� ������ ��������� �� �������
    public:
    // ��������������� �������, ������� : ���������� �������� (0 - �� �������������)
    PRIZNAK_SERVICE_DLL static exit_type SetExit(exit_type e = 0);
    PRIZNAK_SERVICE_DLL static write_type SetWrite(write_type e = 0);
    PRIZNAK_SERVICE_DLL static void act(const char * s);
    PRIZNAK_SERVICE_DLL static TextOutType & Out; // ��� ������ ��������� �� �������
    PRIZNAK_SERVICE_DLL static void Write(const char * s);
    PRIZNAK_SERVICE_DLL static void Exit();
};// ErrorType

//-------------------- �������� ����� -----------------------------
class DiskFileType // �������� ����
{
    void operator = (DiskFileType &); // ��������
    void error_obr(int);// ��������� ������ � ����������
    enum {extrn_file,lock_file} tip;// ��� ����� (������� ��� ������������ ������)
    char * NameFile;
    protected:
    FILE * uFILE; // ��������� �� ����
    protected:
    PRIZNAK_SERVICE_DLL virtual void error(const char *);// ��������� ������ � ����������
    public:
    enum open_type  // ���� �������� �����
    {
      TxtRead      = 0, // ��������� ������
      TxtWrite_new = 1, // ��������� ������
      TxtWrite     = 2, // ��������� ��������
      BinInOut     = 3, // �������� ����-����� � ��������� ����
      BinInOut_new = 4, // �������� ����-����� � �������������
      BinIn        = 5, // �������� ����
      BinOut       = 6, // �������� ����� � ��������� ����
      BinOut_new   = 7  // �������� ����� � �������������
    };
    const char * name()const{ return NameFile; }
    PRIZNAK_SERVICE_DLL DiskFileType(DiskFileType &);
    PRIZNAK_SERVICE_DLL DiskFileType(const char *,const open_type);// ��������
    PRIZNAK_SERVICE_DLL virtual ~DiskFileType();
    // �������
    PRIZNAK_SERVICE_DLL long FilePos()const;// ��������� ������� �����
    PRIZNAK_SERVICE_DLL void FilePos(const long pos);// ��������� ������� �����
    PRIZNAK_SERVICE_DLL void BinWrite(const void *,size_t);// �������� ������ (BinInOut, BinInOut_new)
    PRIZNAK_SERVICE_DLL void BinRead(void *,size_t); // �������� ������ (BinInOut, BinInOut_new)
    PRIZNAK_SERVICE_DLL void TextWrite(const char *);// ��������� ������ (TxtWrite, TxtWrite_new)
    PRIZNAK_SERVICE_DLL void FormatTextWrite(const char * format,...);// ��������������� ��������� ������ (TxtWrite, TxtWrite_new)
    PRIZNAK_SERVICE_DLL char TextRead();
    PRIZNAK_SERVICE_DLL int TextRead(char * s,int N); // ������ � ������ �� ������� '\n'
    // �����������
    PRIZNAK_SERVICE_DLL void bufoff(); // ��������� �����������
    PRIZNAK_SERVICE_DLL void bufset(unsigned size); // ������ ������ ������
    PRIZNAK_SERVICE_DLL void flush();
    PRIZNAK_SERVICE_DLL static void flush_all();
    // ������
    PRIZNAK_SERVICE_DLL long size()const; // ������ �����
    PRIZNAK_SERVICE_DLL int end()const; // �������� �� ����� �����
    //   <  0 - ���� � ������ Name �� ����������
    //   >= 0 - ������ �����
    PRIZNAK_SERVICE_DLL static long CheckFile(const char * NameFile);
};// DiskFileType

//=======================  ���� =============================
class D_Stack_Base_Type
{// ������� ��� ��� �����
    D_Stack_Base_Type(D_Stack_Base_Type &);// ��������
    void operator = (D_Stack_Base_Type &);// ��������
    // ���������� ������
    struct SpisokBaseType // ������� ������
    {
      SpisokBaseType * next;// ��������� �� ��������� �������
      char * data; // ��������� �� ������������ ������ (char - 1���� !!!)
    } * Spisok;
    char * tek; // ��������� �� ��������� ���������� ������� (���� ���� �� ����)
    const unsigned int SizeLine; // ������ ��������� ������� (� ���������)
    const unsigned int SizeLineByte; // ������ ��������� ������� (� ������) == SizeLine*sizeof_data
    const unsigned int sizeof_data;//������ ������ ������������ � ����
    // ���������� �������
    void * (*new_data)(int);// ��������� ������ ��� ������ ������
    void (*delete_data)(void * );// ����������� ������ ����� new_data
    protected:
    PRIZNAK_SERVICE_DLL void * push();// ��������� � ����
    PRIZNAK_SERVICE_DLL void * pop();// ������� �� �����
    public:
    // ��������
    PRIZNAK_SERVICE_DLL D_Stack_Base_Type(const unsigned int data,const unsigned int size,
                      void * (*e_new_data)(int),void (*e_delete_data)(void * ));
    PRIZNAK_SERVICE_DLL ~D_Stack_Base_Type();
//--------------- user'���� �������� ------------------------
    void clear(); // ������� �����
    int pust()const{return (Spisok==0)||((Spisok->next == 0)&&(Spisok->data == tek));}// ������ ���� ����
    int size()const;// ������ �����
};// D_Stack_Base_Type

//----------------  ������������ ���� -----------------------
template <class type> class D_Stack : public D_Stack_Base_Type
{//  ������������ ����
 //  ��� type ������ ����� ����������� ��� ����������
    static void * s_new_data(int i){return new type[i];}// ��������� ������ ��� ������ ������
    static void s_delete_data(void * x){delete[] (type *)x;}// ����������� ������ ����� new_data
    public:
    // �����������
    D_Stack():D_Stack_Base_Type(sizeof(type),1,s_new_data,s_delete_data){}
    D_Stack(const int size):D_Stack_Base_Type(sizeof(type),size,s_new_data,s_delete_data){}
    ~D_Stack(){}
    void operator <= (const type & t)
    {// ��������� � ����
      *((type *)push()) = t;
    }
    int pop(type & t)
    {// ������� �� �����
      type * prom = (type *)D_Stack_Base_Type::pop();
      if(prom == 0) return 1;
      t = *prom;
      return 0;
    }// <=
};// D_Stack
template<class type> inline int operator <= (type & t,D_Stack<type> & Stack){ return Stack.pop(t); }

//============================  ������ ==============================

class D_Spisok_Simple_Base_Type
{// ������� ����� ��� ������������� ������ �������� ����
 // (�.�. ����, ������������ ����������� �� memcpy)
 // ������� �������� ��������� : ����������, �������� ��������, ��������� ������
    D_Spisok_Simple_Base_Type(D_Spisok_Simple_Base_Type&); // ��������
    void operator = (D_Spisok_Simple_Base_Type&); // ��������
    public:
    struct ObrType
    {// ������������ ��� ��� ���������
     // �������� x ������� func - ��������� �� ������� ������� ������
      virtual int func(void * x) = 0;
      virtual ~ObrType(){}
    };// ObrType
    //------------------ ���� ������� ------------------
    protected:
    int pSize;
    void * pTable;
    // ������ ������
    public:
    int size()const{ return pSize; }
    //------------------ ���������� � ������ ------------------
    // ���������:
    //   Table     - ��������� �� ������� (������ ������)
    //   size_tabl - ����� ������� � ��������� (������������� �� 1)
    //   size_data - ������ ������ (� ������)
    //   new_data  - ��������� ������ ��� ������ ������
    //   del_data  - ����������� ������ ����� new_data
    // ���������� � ����� ������
    // �������: ������ ���������� ��������
    public:
    PRIZNAK_SERVICE_DLL static int add(void *& Table,int & size_tabl,int size_data,void * data,void * (*new_data)(int),void (*del_data)(void * ));
    protected:
    PRIZNAK_SERVICE_DLL int add(int size_data,void * data,void * (*new_data)(int),void (*del_data)(void * ));
    // ���������� � ������, � ������������ � ���������� ������� ���������� cmp:
    //   cmp - ��������� � ���������� ������, ������� ������� func:
    //        > 0 <=> ������� ������ >
    //        = 0 <=> ������� ������ =
    //        < 0 <=> ������� ������ <
    // ����������� ����� ����� ����� ���������, ��� �������� �������� func > 0,
    // ��� � �����, ���� �� �� ������.
    // ���� ��� ���� ����������� ������� � ������ 0 ��������� func - �� ���������� �� ����������,
    // �������: ������ ���������� ��������
    public:
    PRIZNAK_SERVICE_DLL static int add(void *& Table,int & size_tabl,int size_data,void * data,void * (*new_data)(int),void (*del_data)(void * ),D_Spisok_Simple_Base_Type::ObrType & cmp);
    protected:
    PRIZNAK_SERVICE_DLL int add(int size_data,void * data,void * (*new_data)(int),void (*del_data)(void * ),D_Spisok_Simple_Base_Type::ObrType & cmp);
    //------------------ �������� �������� ------------------
    // �������� ���������� ��������
    public:
    PRIZNAK_SERVICE_DLL static void del(void *& Table,int & size_tabl,int size_data,void * (*new_data)(int),void (*del_data)(void * ));
    protected:
    PRIZNAK_SERVICE_DLL void del(int size_data,void * (*new_data)(int),void (*del_data)(void * ));
    // �������� �������� �� �������
    // ��������� (����� ��������� ����):
    //   index - ������ ���������� �������� (�� 0)
    public:
    PRIZNAK_SERVICE_DLL static void del(void *& Table,int & size_tabl,int size_data,void * (*new_data)(int),void (*del_data)(void * ),int index);
    protected:
    PRIZNAK_SERVICE_DLL void del(int size_data,void * (*new_data)(int),void (*del_data)(void * ),int index);
    // �������� �������� ����� ���������
    // ��������� (����� ��������� ����):
    //   kol - ����� ��������� ���������
    public:
    PRIZNAK_SERVICE_DLL static void del(void *& Table,int & size_tabl,int size_data,void * (*new_data)(int),void (*del_data)(void * ),int index,int kol);
    protected:
    PRIZNAK_SERVICE_DLL void del(int size_data,void * (*new_data)(int),void (*del_data)(void * ),int index,int kol);
    //------------------ ����������� ��������� ------------------
    // ��������� (����� ��������� ��� ������� add):
    //   dev - ���������� ��������� ������ ��������
    // ��������� ��� ���� �������� ������� dev.func = 0
    private:
    PRIZNAK_SERVICE_DLL static int obr(void * Table,int size_tabl,int size_data,D_Spisok_Simple_Base_Type::ObrType & dev,int dir);
    // ��������� � ������
    public:
    PRIZNAK_SERVICE_DLL static int obr_beg(void * Table,int size_tabl,int size_data,D_Spisok_Simple_Base_Type::ObrType & dev);
    protected:
    PRIZNAK_SERVICE_DLL int obr_beg(int size_data,D_Spisok_Simple_Base_Type::ObrType & dev)const;
    // ��������� � �����
    public:
    PRIZNAK_SERVICE_DLL static int obr_end(void * Table,int size_tabl,int size_data,D_Spisok_Simple_Base_Type::ObrType & dev);
    protected:
    PRIZNAK_SERVICE_DLL int obr_end(int size_data,D_Spisok_Simple_Base_Type::ObrType & dev)const;
    //------------------ ����� ������� ------------------
    public:
    PRIZNAK_SERVICE_DLL D_Spisok_Simple_Base_Type();
    PRIZNAK_SERVICE_DLL ~D_Spisok_Simple_Base_Type(); // �� ������� ������
};// D_Spisok_Simple_Base_Type


class D_Spisok_Base_Ptr : public D_Spisok_Simple_Base_Type
{// ������� ��� ��� ������ ����������
    // ������� ������ � ������������ �������
    static void * new_void_ptr(int);
    static void delete_void_ptr(void *);
    public:
    void * const * table()const{ return (void * const *)pTable; }
    void * table(int i)const{ return ((void **)pTable)[i]; }
    //------------------ ���������� � ������ ------------------
    // �������� � ����� ������
    PRIZNAK_SERVICE_DLL static int add(void **& Table,int & size,void * el);
    PRIZNAK_SERVICE_DLL int add(void * el);
    int operator += (void * el){ return add(el); }
    // �������� � ������ � ������������ � �������� ���������� cmp (��������� �������)
    PRIZNAK_SERVICE_DLL static int add(void **& Table,int & size,void * el,D_Spisok_Simple_Base_Type::ObrType &);
    PRIZNAK_SERVICE_DLL int add(void * el,D_Spisok_Simple_Base_Type::ObrType &);
    //------------------ �������� �������� ------------------
    // �������� ���������� ��������
    PRIZNAK_SERVICE_DLL static void del(void **& Table,int & size_tabl);
    PRIZNAK_SERVICE_DLL void del();
    // �������� �������� �� �������
    //   index - ������ ���������� �������� (�� 0)
    PRIZNAK_SERVICE_DLL static void del(void **& Table,int & size_tabl,int index);
    PRIZNAK_SERVICE_DLL void del(int index);
    // �������� �������� ����� ���������
    //   kol - ����� ��������� ���������
    PRIZNAK_SERVICE_DLL static void del(void **& Table,int & size_tabl,int index,int kol);
    PRIZNAK_SERVICE_DLL void del(int index,int kol);
    //------------------ ����������� ��������� ------------------
    typedef void (*FuncObrType)(void *); // ������� ���������
    private:
    // ������� ����������� ���������
    typedef int (*FuncCycleType)(void * Table,int size_tabl,int size_data,D_Spisok_Simple_Base_Type::ObrType & dev);
    static void obr(void ** Table,int size,D_Spisok_Base_Ptr::FuncObrType,D_Spisok_Base_Ptr::FuncCycleType);
    public:
    // ��������� ����� ������ � ������
    PRIZNAK_SERVICE_DLL static void obr_beg(void ** Table,int size,D_Spisok_Base_Ptr::FuncObrType);
    PRIZNAK_SERVICE_DLL void obr_beg(D_Spisok_Base_Ptr::FuncObrType)const;
    // ��������� ����� ������ � �����
    PRIZNAK_SERVICE_DLL static void obr_end(void ** Table,int size,D_Spisok_Base_Ptr::FuncObrType);
    PRIZNAK_SERVICE_DLL void obr_end(D_Spisok_Base_Ptr::FuncObrType)const;
    //------------------ ����� ������� ------------------
    PRIZNAK_SERVICE_DLL void clear();
    PRIZNAK_SERVICE_DLL ~D_Spisok_Base_Ptr();
};// D_Spisok_Base_Ptr


class D_Spisok_Int_Type : public D_Spisok_Simple_Base_Type
{// ��� ��� ������ ��������
    // ������� ������ � ������������ �������
    static void * new_void_ptr(int);
    static void delete_void_ptr(void *);
    public:
    int * table()const{ return (int *)pTable; }
    int & operator[] (int i)const{ return ((int *)pTable)[i]; }
    //------------------ ���������� � ������ ------------------
    // �������� � ����� ������
    PRIZNAK_SERVICE_DLL static int add(int *& Table,int & size,int el);
    PRIZNAK_SERVICE_DLL int add(int el);
    int operator += (int el){ return add(el); }
    // �������� � ������ � ������������ � �������� ���������� cmp (��������� �������)
    typedef int (*CmpType)(int x,int y);
    // ������� ���������, �������:
    //        > 0 <=> x > y
    //        = 0 <=> x = y
    //        < 0 <=> x < y
    // x - ������� ������� �������, y - ������������ ��������
    PRIZNAK_SERVICE_DLL static int add(int *& Table,int & size,int el,D_Spisok_Int_Type::CmpType);
    PRIZNAK_SERVICE_DLL int add(int el,D_Spisok_Int_Type::CmpType);
    //------------------ �������� �������� ------------------
    // �������� ���������� ��������
    PRIZNAK_SERVICE_DLL static void del(int *& Table,int & size_tabl);
    PRIZNAK_SERVICE_DLL void del();
    // �������� �������� �� �������
    //   index - ������ ���������� �������� (�� 0)
    PRIZNAK_SERVICE_DLL static void del(int *& Table,int & size_tabl,int index);
    PRIZNAK_SERVICE_DLL void del(int index);
    // �������� �������� ����� ���������
    //   kol - ����� ��������� ���������
    PRIZNAK_SERVICE_DLL static void del(int *& Table,int & size_tabl,int index,int kol);
    PRIZNAK_SERVICE_DLL void del(int index,int kol);
    //------------------ ����� ������� ------------------
    PRIZNAK_SERVICE_DLL void clear();
    PRIZNAK_SERVICE_DLL int find(int k)const;// ����� ����������� ������� �������� �� ��������� k (���� ���, �� -1)
    PRIZNAK_SERVICE_DLL int findr(int k)const;// ����� ����������� ������� �������� �� ��������� k (���� ���, �� -1)
    PRIZNAK_SERVICE_DLL D_Spisok_Int_Type();
    PRIZNAK_SERVICE_DLL ~D_Spisok_Int_Type();
};// D_Spisok_Int_Type


template <class type> class D_SpisokPtr : public D_Spisok_Base_Ptr
{// �� ������������ ������������ ������ ����������
    void add(); // ��������
    //void del(); // ��������
    public:
    ~D_SpisokPtr(){}
    static void add(type **& t,int & size,type * x){ D_Spisok_Base_Ptr::add((void **&)t,size,x); }
    void operator += (type * x){ D_Spisok_Base_Ptr::add(x); }
    type * operator [](int i)const{ return ((type **)pTable)[i]; }
    type * table(int i)const{ return ((type **)pTable)[i]; }
    type * const * table()const{ return (type * const *)pTable; }
};// D_SpisokPtr

template <class type> class D_SpisokSimpleType : public D_Spisok_Simple_Base_Type
{// �� ������������ ������������ ������
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


//============  �������� ������� ������������ ��������  ================

struct PRIZNAK_SERVICE_DLL MassivArchiveType
{// ����� �������� : ���� ������� ���� �� ��� ���������
 //                  save - ���������� ������ � ���� ��� ������ �� ��������� � ������,
 //                         ����� ������� ��� � �������� �������� ����������
 //                  del - ������� ������ �� ������
    // ��� int
    static const int * save(int * x,int size);// ����������
    static void del(const int * x,int size);// ��������
    // ��� float
    static const float * save(float * x,int size);// ����������
    static void del(const float * x,int size);// ��������
    // ��� double
    static const double * save(double * x,int size);// ����������
    static void del(const double * x,int size);// ��������
    // ��� long double
    static const long double * save(long double * x,int size);// ����������
    static void del(const long double * x,int size);// ��������
};// MassivArchiveType

class ArchiveDinamicDataBaseType
{
    D_Spisok_Base_Ptr SpisData; // ������ ������
  //----- ������� ��� ������ � ������� -----
    // �������� ������
    void (*del_data)(void *);
    // ��������� ������ (data) � ��������������� (id)
    //   ��� ��������������� ������� 1 (������)
    //   �����                       0 (����)
    int (*cmp_data)(const void * data,const void * id);
    public:
  //----- ������� ������ ������� -----
    // �������� ��� ���� ������� ������
    void new_data(void * data){ SpisData += data; }
    void operator += (void * data){ new_data(data); }
    // ����� �������� ������ �������������� �������������� (id)
    // ��� ������� ������� 0
    PRIZNAK_SERVICE_DLL void * find(const void * id);
    const D_Spisok_Base_Ptr & spisok()const{ return SpisData; }
    // �������
    PRIZNAK_SERVICE_DLL void clear();
    // ��������-�����������
    PRIZNAK_SERVICE_DLL ArchiveDinamicDataBaseType(void (*del)(void *),int (*cmp)(const void * data,const void * id));
    PRIZNAK_SERVICE_DLL ~ArchiveDinamicDataBaseType();
};// ArchiveDinamicDataBaseType

class SuperArchiveType : public ArchiveDinamicDataBaseType
{// ����� �������
    static void del(void *);
    static int cmp(const void * data,const void * id);
    public:
    PRIZNAK_SERVICE_DLL SuperArchiveType();
    PRIZNAK_SERVICE_DLL void operator += (ArchiveDinamicDataBaseType &);
};// SuperArchiveType

template <class data_type,class id_type>
class ArchiveDinamicDataType : public ArchiveDinamicDataBaseType
{// ������ ���� ��������  int operator == (const data_type &,const id_type &);
    static void del(void * data)
    {// �������� ������
      delete (data_type *)data;
    }// del_data
    static int cmp(const void * data,const void * id)
    {// ��������� ������ (data) � ��������������� (id)
     //   ��� ��������������� ������� 1 (������)
     //   �����                       0 (����)
      return (*(data_type *)data) == (*(id_type *)id);
    }// cmp_data
    public:
    void new_data(data_type * data)
    {// �������� ��� ���� ������� ������
      ArchiveDinamicDataBaseType::new_data(data);
    }// new_data
    void operator += (data_type * data){ new_data(data); }
    data_type * find(const id_type & id)
    {// ����� �������� ������ �������������� �������������� (id)
     // ��� ������� ������� 0
      return (data_type *)ArchiveDinamicDataBaseType::find(&id);
    }
    int size()const{ return spisok().size(); }
    data_type * const * table()const{ return (data_type * const *)spisok().table(); }
    ArchiveDinamicDataType():ArchiveDinamicDataBaseType(del,cmp){}
};// ArchiveDinamicDataType

template <class data_type,class id_type>
class LibrDinamicDataType : public ArchiveDinamicDataType<data_type,id_type>
{// ���������� ������������ ������
 // ������ ���� ��������  data_type(const id_type &);
    public:
    data_type & create(const id_type & id)
    {// �������� ��������� �� ������
      data_type * data = find(id);
      if(data == 0)
      {
         data = new data_type(id);
         new_data(data);
      }
      return *data;
    }// create
};// LibrDinamicDataType


//============  ����������� ���������� �� ������ �� ��������� ������ ================
struct CounterObjectBasePtr
{// ������� ����� ��� �������� �� ������������ ������ �� �����
 // �� ��������� ����������� ��������� ���� memcpy
    typedef void (*delproc)(void *);// ��������� �������� �������
    protected:
    void * Obj; // ��������� �� ������
    // ofs - �������� �������� (���� int) � ������� (� ������������ ������� ������ ���������)
    // ��������: ofs = offsetof(ObjType,count)
    PRIZNAK_SERVICE_DLL void inc(void * O,int ofs);    // ��������� ������ (��� ������������)
    PRIZNAK_SERVICE_DLL void dec(delproc dp,int ofs); // ������� ������   (��� �����������)
    PRIZNAK_SERVICE_DLL void copy(void * O,delproc dp,int ofs); // ���������� ������ (��� ��������� = )
    void copy(const CounterObjectBasePtr & O,delproc dp,int ofs){copy(O.Obj,dp,ofs); } // ���������� ������ (��� ��������� = )
    // ��� ������ �� ��������, ������� - ����� ������
    PRIZNAK_SERVICE_DLL static int add_spis(CounterObjectBasePtr *& table,int size,const CounterObjectBasePtr & O,int ofs);// �������� � �����
    PRIZNAK_SERVICE_DLL static int del_spis(CounterObjectBasePtr *& table,int size,delproc dp,int ofs,int i);// ������� i-��� ������� ������
    PRIZNAK_SERVICE_DLL static void del_spis_end(CounterObjectBasePtr * table,int size,delproc dp,int ofs);// ������� �� ����� �������
    PRIZNAK_SERVICE_DLL static void del_spis(CounterObjectBasePtr * table,int size,delproc dp,int ofs);// ������� ���� ������
    public:
    operator int()const{ return Obj != 0; } // ���� ���������, �� �������
};// CounterObjectBasePtr

template <class type,int ofs> class CounterObjectPtr : public CounterObjectBasePtr
{// ������ ��� ��������: type - ��� �������,
 // ofs - �������� �������� (���� int) � ������� (� ������������ ������� ������ ���������)
 // ��������: ofs = offsetof(ObjType,count)
    static void dp(void * t){ delete (type*)t; }
    public:
    const type * operator ->()const{ return (const type*)Obj; } // ����� ������� ������������ �������
    type * operator ->(){ return (type*)Obj; }                  // ����� ������� �������
    CounterObjectPtr & operator = (const CounterObjectPtr & O){ copy(O,dp,ofs); return *this; }
    CounterObjectPtr(type * O){ inc(O,ofs); }
    CounterObjectPtr(const CounterObjectPtr & O){ inc(O.Obj,ofs); }
    ~CounterObjectPtr(){ dec(dp,ofs); }
    // ��� ������ �� ��������, ������� - ����� ������
    static int add_spis(CounterObjectPtr *& table,int size,const CounterObjectPtr & O){ return CounterObjectBasePtr::add_spis((CounterObjectBasePtr*&)table,size,O,ofs); }// �������� � �����
    static int del_spis(CounterObjectPtr *& table,int size,int i){ return CounterObjectBasePtr::del_spis((CounterObjectBasePtr*&)table,size,dp,ofs,i); }// ������� i-��� ������� ������
    static void del_spis(CounterObjectPtr * table,int size){ CounterObjectBasePtr::del_spis(table,size,dp,ofs); }// ������� ���� ������
};// CounterObjectPtr

#endif
