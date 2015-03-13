#ifndef TVECT3_PROCCESS
#define TVECT3_PROCCESS

class TVect3{
  protected :
    double r[3];
    friend class TMatr3;
  public :
    TVect3(){};
    TVect3(const double & ax, const double & ay, const double & az){r[0]=ax; r[1]=ay; r[2]=az;}
    double x() const {return r[0];}
    double y() const {return r[1];}
    double z() const {return r[2];}
    void x(const double & a) {r[0]=a;}
    void y(const double & a) {r[1]=a;}
    void z(const double & a) {r[2]=a;}
    double operator * (const TVect3 & ) const;
    TVect3 operator + (const TVect3 & ) const;
    TVect3 operator - (const TVect3 & ) const;
    TVect3 operator * (const double & ) const;
    TVect3 operator / (const double & ) const;
    TVect3 operator + (const double & ) const;
    TVect3 operator - (const double & ) const;
    void   operator = (const TVect3 & );
    void   operator = (const double & );
    void   operator += (const TVect3 & );
    void   operator -= (const TVect3 & );
    void   operator *= (const double & );
    void   operator /= (const double & );
    TVect3 operator - () const;
    TVect3 operator + () const;
    double operator () (const int) const;       // взятие индекса x-0, y-1, z-2
    TVect3 operator %  (const TVect3 &) const;  // векторное произведение
    double operator ^ (const TVect3 & ) const;  // угол между векторами
    double norm() const;                        // норма
    TVect3 operator || (const TVect3 &) const;  // определения проекции вектора вдоль заданного
           operator double * () { return r; }
           operator const double * () const { return r; }
    void   resolute(const TVect3 &, TVect3 &, TVect3 &) const; // разложение вектора на сонаправленный заданному и перпендикулярный
    friend TVect3 operator * ( const double & , const TVect3 & );  // double * TVect3
    friend TVect3 operator * (const TVect3 &, const TMatr3 &);     // умножение вектора на матрицу
    friend TVect3 operator / (const TVect3 & , const TMatr3 & );   // решение системы уравнений
};

class TMatr3{
    protected :
      double A[3][3];
    public :
      TMatr3(){};
      TMatr3(const TVect3 &, const TVect3 &, const TVect3 &);
      TMatr3(const double &,const double &,const double &,
             const double &,const double &,const double &,
             const double &,const double &,const double &);
      double operator () (const int, const int) const;
      void operator () (const TVect3 & , const TVect3 & , const TVect3 & ); // формирование матрицы как комбинации скалярных векторов из тройки
      void operator () (const TVect3 *); // формирование матрицы как комбинации скалярных векторов из тройки
      void   operator = (const TMatr3 & );// присваивание матрицы
      double minor(const int , const int) const; // взятие минора
      double det() const;                        // определитель матрицы
      TVect3 row(const int ) const;              // взятие строки
      TVect3 column(const int ) const;           // взятие колонки
      void   operator = (const double &);        // инициализация матрицы числом
      TMatr3 operator * (const TMatr3 &) const;  // умножение матриц
      TVect3 operator * (const TVect3 &) const;  // умножение матрицы на вектор (правое)
      TMatr3 operator * (const double &) const;  // умножение матрицы на число (правое)
      TMatr3 operator / (const double &) const;  // деление на число
      TMatr3 operator + (const TMatr3 &) const;  // сложение матриц
      TMatr3 operator - (const TMatr3 &) const;  // вычитание матриц
      TMatr3 operator - () const;
      TMatr3 operator ~ () const;                // транспонирование матрицы
      void   operator /=(const double &);        // обращение матрицы с умножением на число
      void   operator += (const TMatr3 &);       //
      void   operator -= (const TMatr3 &);       //
           operator double * () { return A[0]; }
           operator const double * () const { return A[0]; }
      friend TVect3 operator * (const TVect3 & , const TMatr3 & ); // умножение вектора на матрицу
      friend TMatr3 operator * (const double & , const TMatr3 & ); // умножение числа на вектор
      friend TMatr3 operator / (const double & , const TMatr3 & ); // нахождение обратной матрицы умноженной на число
      friend TVect3 operator / (const TVect3 & , const TMatr3 & ); // решение системы уравнений
};

double norm(const TVect3 & );

TVect3 operator * ( const double & , const TVect3 & );  // double * TVect3

TVect3 operator * (const TVect3 &, const TMatr3 &);

TMatr3 operator * ( const double & , const TMatr3 & );  // TVect3 * TMatr3

#endif
