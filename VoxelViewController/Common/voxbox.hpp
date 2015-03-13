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
	// ОСНОВНОЙ КЛАСС ДЛЯ ОПИСАНИЯ ВОКСЕЛЬНОГО БОКСА
	//_______________________________________________________________________________________________________
	class TVoxelCell {	// TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell  TVoxelCell
	protected :
		unsigned int  Size;          // размер массива
		const unsigned int& SizeX;       // размер по OX (количество вокселей вдоль)
		const unsigned int& SizeY;       // размер по OY (количество вокселей вдоль)
		const unsigned int& SizeZ;       // размер по OZ (количество вокселей вдоль)
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
		unsigned char& size_decode;  // размер массива для декодирования
		unsigned short int*& decode;   // массив соответствий идентификаторов материалов (внутренний) -> (внешний)
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
	TVect3 toCenter;         // вектор центра воксельного бокса (Lx/2,Ly/2,Lz/2) относительно системы координат воксельного бокса
	// необходимо предусмотреть поворот бокса в пространстве

	// размер воксель-бокса в количестве вокселей вдоль координатных осей
	unsigned int Size[3];
	unsigned int& SizeX;      // размер по OX (количество вокселей вдоль)
	unsigned int& SizeY;      // размер по OY (количество вокселей вдоль)
	unsigned int& SizeZ;      // размер по OZ (количество вокселей вдоль)

	double VoxelSize[3];      // размеры вокселя вдоль координатных осей

	TVoxelCell* VoxelCell;    // указатель на массив ссылок на материалы

	TVoxelBoxTypes Type;          // - тип представления воксель-бокса
	unsigned char size_decode;   // размер массива для декодирования - 1
	unsigned short int* decode;  // массив соответствий идентификаторов материалов (внутренний) -> (внешний)

public :
	TVoxelBox(); // инициализация объекта (только пустой инициализатор)
	~TVoxelBox();

	// чтение данных, описывающих VoxelBox и инициализация объекта
	void Init(const char* voxelBoxFileName);
	// Type - тип представления воксель-бокса :
	//    0 - (AUTOMATIC_VoxelBoxType)
	//         в файле содержится декодировщик индексов
	//    1 - (ONEBYTE_VoxelBoxType)
	//         файл содержит ссылки на материалы используя тип (unsigned char),
	//         что позволяет сэкономить на размере файла
	//    2 - (TWOBYTE_VoxelBoxType)
	//         файл содержит ссылки на материалы используя тип (unsigned short int).
	//         Используется тогда, когда заведомо известно что количество ссылок
	//         на материалы больше 255поэтому не требуется проведения анализа
	//    3 - (ANALYS_VoxelBoxType) автоматическое определение:
	//         файл должен описывать ссылки на материалы используя тип (unsigned short int),
	//         но тип данных в представлении VoxelBox будет зависеть от количество ссылок
	//         на материалы, используемых при описании VoxelBox если их меньше или равно 255
	//         то будет использоваться тип (unsigned char), что позволит описать в 2 раза
	//         больше вокселей чем при использовании типа (unsigned short int)
	double BoxSizeX();   // выдать размеры VoxelBox по оси X
	double BoxSizeY();   // выдать размеры VoxelBox по оси Y
	double BoxSizeZ();   // выдать размеры VoxelBox по оси Z

	// вычислить полный индекс по ijk
	unsigned int getIndex(const int i, const int j, const int k) const;
	// дать длинну данных
	unsigned int getSize() const;
	// перевести координаты в ijk
	int xyz_to_ijk(const double& x, const double& y, const double& z,unsigned short int& i, unsigned short int& j, unsigned short int& k) const;
	// дать координаты воксельбокса
	int center(double& x, double& y, double& z) const;
	// дать размеры вокселя
	int CellSize(double& x, double& y, double& z) const;
	// дать количество вокселей в каждом из направлений
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
