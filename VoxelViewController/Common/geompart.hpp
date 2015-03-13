#ifndef GEOMPARTICLEPROCCESS
#define GEOMPARTICLEPROCCESS

#include "tvect3.hpp"

/*    Main structure for space coordinate discriptions   */
struct TPartical {  // Coordinates of particlе for geometry
	double x;
	double y;
	double z;
	double Cx;
	double Cy;
	double Cz;
	unsigned char GeomID; // идентификатор геометрии 0 - комбинаторна€, 1,... - номер "воксель бокса"
	unsigned short int i,j,k; //номер €чейки дл€ воксельной геометрии

	void toPoint(TVect3& V) { V.x(x);  V.y(y);  V.z(z); };
	void toDirect(TVect3& V){ V.x(Cx); V.y(Cy); V.z(Cz); };
	void Point(const TVect3& V) {  x = V.x();  y = V.y();  z = V.z(); };
	void Direct(const TVect3& V) { Cx = V.x(); Cy = V.y(); Cz = V.z(); };
	TPartical(void) { x=y=z=Cx=Cy=Cz=0; GeomID=i=j=k=0; };
	TPartical(const double & x, const double & y, const double & z,
		const double & Cx, const double & Cy, const double & Cz)
	{
		this -> x = x; this -> y = y; this -> z = z;
		this -> Cx = Cx; this -> Cy = Cy; this -> Cz = Cz;
		GeomID=i=j=k=0;
	}
};

#endif
