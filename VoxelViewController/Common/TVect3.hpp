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
    double operator () (const int) const;       // ������ ������� x-0, y-1, z-2
    TVect3 operator %  (const TVect3 &) const;  // ��������� ������������
    double operator ^ (const TVect3 & ) const;  // ���� ����� ���������
    double norm() const;                        // �����
    TVect3 operator || (const TVect3 &) const;  // ����������� �������� ������� ����� ���������
           operator double * () { return r; }
           operator const double * () const { return r; }
    void   resolute(const TVect3 &, TVect3 &, TVect3 &) const; // ���������� ������� �� �������������� ��������� � ����������������
    friend TVect3 operator * ( const double & , const TVect3 & );  // double * TVect3
    friend TVect3 operator * (const TVect3 &, const TMatr3 &);     // ��������� ������� �� �������
    friend TVect3 operator / (const TVect3 & , const TMatr3 & );   // ������� ������� ���������
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
      void operator () (const TVect3 & , const TVect3 & , const TVect3 & ); // ������������ ������� ��� ���������� ��������� �������� �� ������
      void operator () (const TVect3 *); // ������������ ������� ��� ���������� ��������� �������� �� ������
      void   operator = (const TMatr3 & );// ������������ �������
      double minor(const int , const int) const; // ������ ������
      double det() const;                        // ������������ �������
      TVect3 row(const int ) const;              // ������ ������
      TVect3 column(const int ) const;           // ������ �������
      void   operator = (const double &);        // ������������� ������� ������
      TMatr3 operator * (const TMatr3 &) const;  // ��������� ������
      TVect3 operator * (const TVect3 &) const;  // ��������� ������� �� ������ (������)
      TMatr3 operator * (const double &) const;  // ��������� ������� �� ����� (������)
      TMatr3 operator / (const double &) const;  // ������� �� �����
      TMatr3 operator + (const TMatr3 &) const;  // �������� ������
      TMatr3 operator - (const TMatr3 &) const;  // ��������� ������
      TMatr3 operator - () const;
      TMatr3 operator ~ () const;                // ���������������� �������
      void   operator /=(const double &);        // ��������� ������� � ���������� �� �����
      void   operator += (const TMatr3 &);       //
      void   operator -= (const TMatr3 &);       //
           operator double * () { return A[0]; }
           operator const double * () const { return A[0]; }
      friend TVect3 operator * (const TVect3 & , const TMatr3 & ); // ��������� ������� �� �������
      friend TMatr3 operator * (const double & , const TMatr3 & ); // ��������� ����� �� ������
      friend TMatr3 operator / (const double & , const TMatr3 & ); // ���������� �������� ������� ���������� �� �����
      friend TVect3 operator / (const TVect3 & , const TMatr3 & ); // ������� ������� ���������
};

double norm(const TVect3 & );

TVect3 operator * ( const double & , const TVect3 & );  // double * TVect3

TVect3 operator * (const TVect3 &, const TMatr3 &);

TMatr3 operator * ( const double & , const TMatr3 & );  // TVect3 * TMatr3

#endif
