#include "tvect3.hpp"
#include <math.h>

inline double sqr(const double & x) { return x*x;}
inline double sgnm(const int i){ return (i%2) ? -1 : 1; }
inline double norm(const TVect3 & a) {return sqrt(sqr(a.x())+sqr(a.y())+sqr(a.z())); }

TVect3 operator * ( const double & r, const TVect3 & u)  // double * Vect3
{
	return TVect3(u.x()*r,u.y()*r,u.z()*r);
}

TVect3 operator * (const TVect3 & b, const TMatr3 & A)
{
	return TVect3(b.r[0]*A.A[0][0]+b.r[1]*A.A[1][0]+b.r[2]*A.A[2][0],
		b.r[0]*A.A[0][1]+b.r[1]*A.A[1][1]+b.r[2]*A.A[2][1],
		b.r[0]*A.A[0][2]+b.r[1]*A.A[1][2]+b.r[2]*A.A[2][2]);
}

TMatr3 operator * ( const double & a, const TMatr3 & A)  // TVect3 * TMatr3
{
	return TMatr3(a*A.A[0][0],a*A.A[0][1],a*A.A[0][2],
		a*A.A[1][0],a*A.A[1][1],a*A.A[1][2],
		a*A.A[2][0],a*A.A[2][1],a*A.A[2][2]);
}

TMatr3 operator / (const double & a, const TMatr3 & A)
{
	double D=A.det();
	if(D==0) {
		return TMatr3(0,0,0,0,0,0,0,0,0);
	}
	double b=a/D;
	return TMatr3(b*A.minor(1,1),-b*A.minor(2,1),b*A.minor(3,1),
		-b*A.minor(1,2),b*A.minor(2,2),-b*A.minor(3,2),
		b*A.minor(1,3),-b*A.minor(2,3),b*A.minor(3,3));
}

TVect3 operator / (const TVect3 & b, const TMatr3 & A)
{
	TMatr3 B(A.minor(1,1),-A.minor(2,1),A.minor(3,1),
		-A.minor(1,2), A.minor(2,2),-A.minor(3,2),
		A.minor(1,3),-A.minor(2,3),A.minor(3,3));
	double D = A.A[0][0]*B.A[0][0]+A.A[0][1]*B.A[0][1]+A.A[0][2]*B.A[0][2];
	if(D==0) {
		return TVect3(0,0,0);
	}
	return TVect3((B.A[0][0]*b.r[0]+B.A[1][0]*b.r[1]+B.A[2][0]*b.r[2])/D,
		(B.A[0][1]*b.r[0]+B.A[1][1]*b.r[1]+B.A[2][1]*b.r[2])/D,
		(B.A[0][2]*b.r[0]+B.A[1][2]*b.r[1]+B.A[2][2]*b.r[2])/D);
}

//===================================================================================

TMatr3::TMatr3(const TVect3 & v0, const TVect3 & v1, const TVect3 & v2)
{
	A[0][0]= v0.r[0]; A[0][1]=v0.r[1]; A[0][2]=v0.r[2];
	A[1][0]= v1.r[0]; A[1][1]=v1.r[1]; A[1][2]=v1.r[2];
	A[2][0]= v2.r[2]; A[2][1]=v2.r[1]; A[2][2]=v2.r[2];
}

void   TMatr3::operator = (const double & a)
{
	this->A[0][0]=this->A[0][1]=this->A[0][2]=a;
	this->A[1][0]=this->A[1][1]=this->A[1][2]=a;
	this->A[2][0]=this->A[2][1]=this->A[2][2]=a;
}

double TMatr3::operator () (const int i, const int j) const
{
	if((i<1)||(i>3)||(j<1)||(j>3)) return 0;
	return A[i-1][j-1];
}

void TMatr3::operator () (const TVect3 & v0, const TVect3 & v1, const TVect3 & v2)
{
	this->A[0][0] = v0*v0; this->A[0][1]=this->A[1][0]=v0*v1; this->A[0][2]=this->A[2][0]=v0*v2;
	this->A[1][1] = v1*v1; this->A[1][2]=this->A[2][1]=v1*v2; this->A[2][2]=v2*v2;
}

void TMatr3::operator () (const TVect3 * v)
{
	(*this)(v[0],v[1],v[2]);
}

TMatr3::TMatr3(const double & a11,const double & a12,const double & a13,
			   const double & a21,const double & a22,const double & a23,
			   const double & a31,const double & a32,const double & a33)
{
	this->A[0][0]=a11; this->A[0][1]=a12; this->A[0][2]=a13;
	this->A[1][0]=a21; this->A[1][1]=a22; this->A[1][2]=a23;
	this->A[2][0]=a31; this->A[2][1]=a32; this->A[2][2]=a33;
}

void  TMatr3::operator = (const TMatr3 & A)
{
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++) this->A[i][j] = A.A[i][j];
}

double TMatr3::minor(const int i, const int j) const
{
	switch(i){
		case 1: switch(j){
		case 1: return this->A[1][1]*this->A[2][2] - this->A[2][1]*this->A[1][2];
		case 2: return this->A[0][1]*this->A[2][2] - this->A[2][1]*this->A[0][2];
		case 3: return this->A[0][1]*this->A[1][2] - this->A[1][1]*this->A[0][2];
				}
				break;
		case 2: switch(j){
		case 1: return this->A[1][0]*this->A[2][2] - this->A[2][0]*this->A[1][2];
		case 2: return this->A[0][0]*this->A[2][2] - this->A[2][0]*this->A[0][2];
		case 3: return this->A[0][0]*this->A[1][2] - this->A[1][0]*this->A[0][2];
				}
				break;
		case 3: switch(j){
		case 1: return this->A[1][0]*this->A[2][1] - this->A[2][0]*this->A[1][1];
		case 2: return this->A[0][0]*this->A[2][1] - this->A[2][0]*this->A[0][1];
		case 3: return this->A[0][0]*this->A[1][1] - this->A[1][0]*this->A[0][1];
				}
				break;
	}
	return 0;
}

double TMatr3::det() const
{
	return this->A[0][0]*this->minor(1,1) - this->A[0][1]*this->minor(1,2) + this->A[0][2]*this->minor(1,3);
}

TVect3 TMatr3::operator * (const TVect3 & b) const
{
	return TVect3( this->A[0][0]*b.r[0] + this->A[0][1]*b.r[1] + this->A[0][2]*b.r[2],
		this->A[1][0]*b.r[0] + this->A[1][1]*b.r[1] + this->A[1][2]*b.r[2],
		this->A[2][0]*b.r[0] + this->A[2][1]*b.r[1] + this->A[2][2]*b.r[2]);
}

TMatr3 TMatr3::operator * (const TMatr3 & A) const  // умножение матриц
{
	return TMatr3( this->A[0][0]*A.A[0][0]+this->A[0][1]*A.A[1][0]+this->A[0][2]*A.A[2][0],
		this->A[0][0]*A.A[0][1]+this->A[0][1]*A.A[1][1]+this->A[0][2]*A.A[2][1],
		this->A[0][0]*A.A[0][2]+this->A[0][1]*A.A[1][2]+this->A[0][2]*A.A[2][2],

		this->A[1][0]*A.A[0][0]+this->A[1][1]*A.A[1][0]+this->A[1][2]*A.A[2][0],
		this->A[1][0]*A.A[0][1]+this->A[1][1]*A.A[1][1]+this->A[1][2]*A.A[2][1],
		this->A[1][0]*A.A[0][2]+this->A[1][1]*A.A[1][2]+this->A[1][2]*A.A[2][2],

		this->A[2][0]*A.A[0][0]+this->A[2][1]*A.A[1][0]+this->A[2][2]*A.A[2][0],
		this->A[2][0]*A.A[0][1]+this->A[2][1]*A.A[1][1]+this->A[2][2]*A.A[2][1],
		this->A[2][0]*A.A[0][2]+this->A[2][1]*A.A[1][2]+this->A[2][2]*A.A[2][2]);
}

TMatr3 TMatr3::operator * (const double & a) const
{
	return TMatr3( this->A[0][0]*a, this->A[0][1]*a, this->A[0][2]*a,
		this->A[1][0]*a, this->A[1][1]*a, this->A[1][2]*a,
		this->A[2][0]*a, this->A[2][1]*a, this->A[2][2]*a);
}

TMatr3 TMatr3::operator - () const
{
	return TMatr3( -this->A[0][0], -this->A[0][1], -this->A[0][2],
		-this->A[1][0], -this->A[1][1], -this->A[1][2],
		-this->A[2][0], -this->A[2][1], -this->A[2][2]);
}

TMatr3 TMatr3::operator ~ () const
{
	return TMatr3( this->A[0][0], this->A[1][0], this->A[2][0],
		this->A[0][1], this->A[1][1], this->A[2][1],
		this->A[0][2], this->A[1][2], this->A[2][2]);
}

TVect3 TMatr3::row(const int i) const
{

	return ((i<1)||(i>3)) ? TVect3(0,0,0)
		: TVect3(this->A[i-1][0],this->A[i-1][1],this->A[i-1][2]);
}

TVect3 TMatr3::column(const int i) const
{
	return ((i<1)||(i>3)) ? TVect3(0,0,0)
		: TVect3(this->A[0][i-1],this->A[1][i-1],this->A[2][i-1]);
}

TMatr3 TMatr3::operator / (const double & a) const
{
	double b=1.0/a;
	return TMatr3(this->A[0][0]*a,this->A[0][1]*a,this->A[0][2]*a,
		this->A[1][0]*a,this->A[1][1]*a,this->A[1][2]*a,
		this->A[2][0]*a,this->A[2][1]*a,this->A[2][2]*a);
}

TMatr3 TMatr3::operator + (const TMatr3 & A) const
{
	return TMatr3(this->A[0][0]+A.A[0][0],this->A[0][1]+A.A[0][1],this->A[0][2]+A.A[0][2],
		this->A[1][0]+A.A[1][0],this->A[1][1]+A.A[1][1],this->A[1][2]+A.A[1][2],
		this->A[2][0]+A.A[2][0],this->A[2][1]+A.A[2][1],this->A[2][2]+A.A[2][2]);
}

TMatr3 TMatr3::operator - (const TMatr3 & A) const
{
	return TMatr3(this->A[0][0]-A(0,0),this->A[0][1]-A(0,1),this->A[0][2]-A(0,2),
		this->A[1][0]-A(1,0),this->A[1][1]-A(1,1),this->A[1][2]-A(1,2),
		this->A[2][0]-A(2,0),this->A[2][1]-A(2,1),this->A[2][2]-A(2,2));
}

void   TMatr3::operator += (const TMatr3 & A)
{
	this->A[0][0]+=A(0,0); this->A[0][1]+=A(0,1); this->A[0][2]+=A(0,2);
	this->A[1][0]+=A(1,0); this->A[1][1]+=A(1,1); this->A[1][2]+=A(1,2);
	this->A[2][0]+=A(2,0); this->A[2][1]+=A(2,1); this->A[2][2]+=A(2,2);
}

void   TMatr3::operator -= (const TMatr3 & A)
{
	this->A[0][0]-=A(0,0); this->A[0][1]-=A(0,1); this->A[0][2]-=A(0,2);
	this->A[1][0]-=A(1,0); this->A[1][1]-=A(1,1); this->A[1][2]-=A(1,2);
	this->A[2][0]-=A(2,0); this->A[2][1]-=A(2,1); this->A[2][2]-=A(2,2);
}

void   TMatr3::operator /=(const double & a)
{
	double D=this->det();
	if(D==0) {
		(*this) = 0;
	}
	else{
		double b=a/D;
		TMatr3 B(minor(1,1),-minor(2,1),minor(3,1),
			-minor(1,2),minor(2,2),-minor(3,2),
			minor(1,3),-minor(2,3),minor(3,3));
		(*this) = B*b;
	}
}

//-----------------------------------------------------------------------------------
double TVect3::operator () (const int i) const
{
	if((i<1)||(i>3)) return 0;
	return r[i-1];
}

TVect3 TVect3::operator %  (const TVect3 & a) const
{
	return TVect3(this->r[1]*a.r[2] - this->r[2]*a.r[1],
		this->r[2]*a.r[0] - this->r[0]*a.r[2],
		this->r[0]*a.r[1] - this->r[1]*a.r[0]);
}

double TVect3::operator * (const TVect3 & a) const
{
	double S=0;
	for(int i=0; i<3; i++) S+=this->r[i]*a.r[i];
	return S;
}

TVect3 TVect3::operator + (const TVect3 & a) const
{
	return TVect3(this->r[0]+a.r[0],this->r[1]+a.r[1],this->r[2]+a.r[2]);
}

TVect3 TVect3::operator - (const TVect3 & a) const
{
	return TVect3(this->r[0]-a.r[0],this->r[1]-a.r[1],this->r[2]-a.r[2]);
}

TVect3 TVect3::operator * (const double & a) const
{
	return TVect3(this->r[0]*a,this->r[1]*a,this->r[2]*a);
}

TVect3 TVect3::operator / (const double & a) const
{
	return TVect3(this->r[0]/a,this->r[1]/a,this->r[2]/a);
}

TVect3 TVect3::operator + (const double & a) const
{
	return TVect3(this->r[0]+a,this->r[1]+a,this->r[2]+a);
}

TVect3 TVect3::operator - (const double & a) const
{
	return TVect3(this->r[0]-a,this->r[1]-a,this->r[2]-a);
}

void   TVect3::operator = (const TVect3 & a)
{
	this->r[0] = a.r[0]; this->r[1] = a.r[1]; this->r[2] = a.r[2];
}

void   TVect3::operator = (const double & a)
{
	this->r[0] = this->r[1] = this->r[2] = a;
}

void   TVect3::operator += (const TVect3 & a)
{
	this->r[0] += a.r[0]; this->r[1] += a.r[1]; this->r[2] += a.r[2];
}

void   TVect3::operator -= (const TVect3 & a)
{
	this->r[0] -= a.r[0]; this->r[1] -= a.r[1]; this->r[2] -= a.r[2];
}

void   TVect3::operator *= (const double & a)
{
	this->r[0] *= a; this->r[1] *= a; this->r[2] *= a;
}

void   TVect3::operator /= (const double & a)
{
	this->r[0] /= a; this->r[1] /= a; this->r[2] /= a;
}

TVect3 TVect3::operator - () const
{
	return TVect3(-this->r[0],-this->r[1],-this->r[2]);
}

TVect3 TVect3::operator + () const
{
	return TVect3(this->r[0],this->r[1],this->r[2]);
}

double TVect3::norm() const
{
	return sqrt(sqr(this->r[0])+sqr(this->r[1])+sqr(this->r[2]));
}

double TVect3::operator ^ (const TVect3 & a) const
{
	return (this->r[0] * a.r[0] + this->r[1] * a.r[1] + this->r[2] * a.r[2]) / (a.norm() * this->norm());
}

TVect3 TVect3::operator || (const TVect3 & etha) const
{
	double netha = etha.norm();
	double mult = (this->r[0]*etha.r[0]+this->r[1]*etha.r[1]+this->r[2]*etha.r[2])/sqr(netha);
	return TVect3(etha.r[0]*mult,etha.r[1]*mult,etha.r[2]*mult);
}

void TVect3::resolute(const TVect3 & etha, TVect3 & rt, TVect3 & rp) const
{
	rt = (*this)||etha;
	rp = (*this) - rt;
}
