#ifndef VOXELBOX_PROCESS
#define VOXELBOX_PROCESS

#include <windows.h>
#include <float.h>
#include <math.h>

#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "geompart.hpp"
#include "syntaxis.inc"

enum TVoxelBoxTypes
{
	AUTOMATIC_VoxelBoxType = 0,
	ONEBYTE_VoxelBoxType   = 1,
	TWOBYTE_VoxelBoxType   = 2,
	ANALYS_VoxelBoxType    = 3
};

class Exception
{
public:
	Exception(std::string err)
		: m_err(err)
	{ }

public:
	std::string m_err;
};

class TVoxelBox
{
	// �������� ����� ��� �������� ����������� �����
	//_______________________________________________________________________________________________________
	class TVoxelCell {	// TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell
	protected :
		unsigned int  Size;          // ������ �������
		const unsigned int& SizeX;       // ������ �� OX (���������� �������� �����)
		const unsigned int& SizeY;       // ������ �� OY (���������� �������� �����)
		const unsigned int& SizeZ;       // ������ �� OZ (���������� �������� �����)
	public :
		virtual int getMaterial(const int i, const int j, const int k) const = 0;
		virtual int putMaterial(const int i, const int j, const int k, unsigned short int val) = 0;
		virtual int putMaterial(const unsigned int i, unsigned short int val) = 0;
		unsigned int getIndex(const int i, const int j, const int k) const;
		unsigned int getSize() const;
		virtual void* address() const = 0;
		TVoxelCell(const unsigned int& sizeX, const unsigned int& sizeY, const unsigned int& sizeZ);
		virtual ~TVoxelCell();
	};  // TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell
	//______________________________________________________________________________________________________________
	class TVoxelCell_char : public TVoxelCell {  // TVoxelCell_char  TVoxelCell_char  TVoxelCell_char  TVoxelCell_char
	protected :
		unsigned char* value;
	public :
		int getMaterial(const int i, const int j, const int k) const;
		int putMaterial(const int i, const int j, const int k, unsigned short int val);
		int putMaterial(const unsigned int i, unsigned short int val);
		TVoxelCell_char(const unsigned int& sizeX, const unsigned int& sizeY, const unsigned int& sizeZ);
		void* address() const;
		~TVoxelCell_char();
	};// TVoxelCell_char  TVoxelCell_char  TVoxelCell_char  TVoxelCell_char  TVoxelCell_char  TVoxelCell_char
	//_________________________________________________________________________________________________________
	class TVoxelCell_int : public TVoxelCell {  // TVoxelCell_int  TVoxelCell_int  TVoxelCell_int  TVoxelCell_int
	protected :
		unsigned short int* value;
	public :
		int getMaterial(const int i, const int j, const int k) const;
		int putMaterial(const int i, const int j, const int k, unsigned short int val);
		int putMaterial(const unsigned int i, unsigned short int val);
		TVoxelCell_int(const unsigned int& sizeX, const unsigned int& sizeY, const unsigned int& sizeZ);
		void* address() const;
		~TVoxelCell_int();
	};// TVoxelCell_int  TVoxelCell_int  TVoxelCell_int  TVoxelCell_int  TVoxelCell_int  TVoxelCell_int
	//______________________________________________________________________________________________________________________________
	class TVoxelCell_analys : public  TVoxelCell_char {  // TVoxelCell_analys  TVoxelCell_analys  TVoxelCell_analys  TVoxelCell_analys
	protected :
		unsigned char& size_decode;  // ������ ������� ��� �������������
		unsigned short int*& decode;   // ������ ������������ ��������������� ���������� (����������) -> (�������)
	public :
		int getMaterial(const int i, const int j, const int k) const;
		int putMaterial(const int i, const int j, const int k, unsigned short int val);
		int putMaterial(const unsigned int i, unsigned short int val);
		TVoxelCell_analys(const unsigned int& sizeX, const unsigned int& sizeY, const unsigned int& sizeZ, unsigned char& Size_dec, unsigned short int*& dec);
		void* address() const;
		~TVoxelCell_analys();
	};// TVoxelCell_analys  TVoxelCell_analys  TVoxelCell_analys  TVoxelCell_analys  TVoxelCell_analys  TVoxelCell_analys

	//___________________________________________________________________________________________________________________

private :
	std::vector<int> m_materials;
	static std::map<int, int> m_colorMap;

protected :
	TVect3 toCenter;         // ������ ������ ����������� ����� (Lx/2,Ly/2,Lz/2) ������������ ������� ��������� ����������� �����
	// ���������� ������������� ������� ����� � ������������

	// ������ �������-����� � ���������� �������� ����� ������������ ����
	unsigned int Size[3];
	unsigned int& SizeX;      // ������ �� OX (���������� �������� �����)
	unsigned int& SizeY;      // ������ �� OY (���������� �������� �����)
	unsigned int& SizeZ;      // ������ �� OZ (���������� �������� �����)

	double VoxelSize[3];      // ������� ������� ����� ������������ ����

	TVoxelCell* VoxelCell;    // ��������� �� ������ ������ �� ���������

	TVoxelBoxTypes Type;          // - ��� ������������� �������-�����
	unsigned char size_decode;   // ������ ������� ��� ������������� - 1
	unsigned short int* decode;  // ������ ������������ ��������������� ���������� (����������) -> (�������)

public :
	TVoxelBox(); // ������������� ������� (������ ������ �������������)
	~TVoxelBox();

	// ������ ������, ����������� VoxelBox � ������������� �������
	void Init(const char* voxelBoxFileName);
	// Type - ��� ������������� �������-����� :
	//    0 - (AUTOMATIC_VoxelBoxType)
	//         � ����� ���������� ������������ ��������
	//    1 - (ONEBYTE_VoxelBoxType)
	//         ���� �������� ������ �� ��������� ��������� ��� (unsigned char),
	//         ��� ��������� ���������� �� ������� �����
	//    2 - (TWOBYTE_VoxelBoxType)
	//         ���� �������� ������ �� ��������� ��������� ��� (unsigned short int).
	//         ������������ �����, ����� �������� �������� ��� ���������� ������
	//         �� ��������� ������ 255������� �� ��������� ���������� �������
	//    3 - (ANALYS_VoxelBoxType) �������������� �����������:
	//         ���� ������ ��������� ������ �� ��������� ��������� ��� (unsigned short int),
	//         �� ��� ������ � ������������� VoxelBox ����� �������� �� ���������� ������
	//         �� ���������, ������������ ��� �������� VoxelBox ���� �� ������ ��� ����� 255
	//         �� ����� �������������� ��� (unsigned char), ��� �������� ������� � 2 ����
	//         ������ �������� ��� ��� ������������� ���� (unsigned short int)
	double BoxSizeX();   // ������ ������� VoxelBox �� ��� X
	double BoxSizeY();   // ������ ������� VoxelBox �� ��� Y
	double BoxSizeZ();   // ������ ������� VoxelBox �� ��� Z

	// ��������� ������ ������ �� ijk
	unsigned int getIndex(const int i, const int j, const int k) const;
	// ���� ������ ������
	unsigned int getSize() const;
	// ��������� ���������� � ijk
	int xyz_to_ijk(const double& x, const double& y, const double& z,unsigned short int& i, unsigned short int& j, unsigned short int& k) const;
	// ���� ���������� ������������
	int center(double& x, double& y, double& z) const;
	// ���� ������� �������
	int CellSize(double& x, double& y, double& z) const;
	// ���� ���������� �������� � ������ �� �����������
	int CellsNumber(unsigned int& Nx, unsigned int& Ny, unsigned int& Nz) const;

	int getMaterial(const int i, const int j, const int k) const;
	int putMaterial(const int i, const int j, const int k, unsigned short int val);
	int putMaterial(const unsigned int i, unsigned short int val);

	unsigned int getSizeX() const { return SizeX; }
	unsigned int getSizeY() const { return SizeY; }
	unsigned int getSizeZ() const { return SizeZ; }

	double getBoxSizeX() const { return VoxelSize[0]; }
	double getBoxSizeY() const { return VoxelSize[1]; }
	double getBoxSizeZ() const { return VoxelSize[2]; }

	static void setColorValue(int material, int color);
	static int getColorValue(int material);
	static std::map<int, int> getColorMap() { return m_colorMap; }

	void putMaterial(const unsigned int material);
	void clearMaterials() { m_materials.clear(); }
	std::vector<int> getMaterials() { return m_materials; }
};

#endif
