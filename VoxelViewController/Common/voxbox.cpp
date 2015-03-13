
#include "voxbox.hpp"

//--------------------------------------------------------------------------------------------------------------------------
//                                                       VOXELCELL DEFINITIONS
//   Возможно определение VoxelBox размером 4.294.967.295 вокселей но с количеством используемых материалов до 255
//                                 размером в два раза меньшим но с количеством используемых материалов до 65535
//                                 при этом размер воксель-бокса ограничен размером доступной памяти
//   Выбор типа TVoxelCell производится автоматически из анализа количества ссылок на материалы используемых при описании
//                         воксель-бокса
//--------------------------------------------------------------------------------------------------------------------------

inline short int my_sign(const double& x)
{
	if (x>0) return 1;
	if (x<0) return -1;
	return 0;
}

inline double sqr(const double& x) { return x*x; }

unsigned int TVoxelBox::TVoxelCell::getIndex(const int i, const int j, const int k) const
{
	return i+SizeX*(j+k*SizeY);
}

TVoxelBox::TVoxelCell::TVoxelCell(const unsigned int& sizeX, const unsigned int& sizeY, const unsigned int& sizeZ):SizeX(sizeX),SizeY(sizeY),SizeZ(sizeZ)
{
	Size   = SizeX*SizeY*SizeZ;
}

unsigned int TVoxelBox::TVoxelCell::getSize() const
{
	return Size;
}

TVoxelBox::TVoxelCell::~TVoxelCell(){};

//---------------------------------------------------------------------------------------------------------------------------

TVoxelBox::TVoxelCell_int::TVoxelCell_int(const unsigned int& sizeX, const unsigned int& sizeY, const unsigned int& sizeZ ):TVoxelCell(sizeX,sizeY,sizeZ)
{
	value = NULL;
	if((Size>0)&&(Size<1073741824)){
		value = new unsigned short int [Size];
	}
	if(value == NULL){
		Size = 0;
	}
}

int TVoxelBox::TVoxelCell_int::getMaterial(const int i, const int j, const int k) const
{
	unsigned int idx = getIndex(i,j,k);
	if(idx>=Size) return -1;
	return (int ) (value[idx]);
}

int TVoxelBox::TVoxelCell_int::putMaterial(const int i, const int j, const int k, unsigned short int val)
{
	unsigned int idx = getIndex(i,j,k);
	if(idx>=Size) return -1;
	value[idx] = val;
	return idx;
}

int TVoxelBox::TVoxelCell_int::putMaterial(const unsigned int idx, unsigned short int val)
{
	if(idx>=Size) return -1;
	value[idx] = val;
	return idx;
}

void* TVoxelBox::TVoxelCell_int::address() const
{
	return (void*) value;
}

TVoxelBox::TVoxelCell_int::~TVoxelCell_int()
{
	delete []value;
	value = NULL;
	Size = 0;
}

//---------------------------------------------------------------------------------------------------------------------

TVoxelBox::TVoxelCell_char::TVoxelCell_char(const unsigned int& sizeX, const unsigned int& sizeY, const unsigned int& sizeZ ):TVoxelCell(sizeX,sizeY,sizeZ)
{
	value = NULL;
	value = new unsigned char [Size];
	if(value == NULL){
		Size = 0;
	}
}

int TVoxelBox::TVoxelCell_char::getMaterial(const int i, const int j, const int k) const
{
	unsigned int idx = getIndex(i,j,k);
	if(idx>=Size) return -1;
	return (int ) (value[idx]);
}

int TVoxelBox::TVoxelCell_char::putMaterial(const int i, const int j, const int k, unsigned short int val)
{
	if(val>255) return -1;
	unsigned int idx = getIndex(i,j,k);
	if(idx>=Size) return -1;
	value[idx] = (unsigned char ) val;
	return idx;
}

int TVoxelBox::TVoxelCell_char::putMaterial(const unsigned int idx, unsigned short int val)
{
	if((val>255)||(idx>=Size)) return -1;
	value[idx] = (unsigned char ) val;
	return idx;
}

void* TVoxelBox::TVoxelCell_char::address() const
{
	return (void*) value;
}

TVoxelBox::TVoxelCell_char::~TVoxelCell_char()
{
	delete []value;
	value = NULL;
	Size = 0;
}

//---------------------------------------------------------------------------------------------------------------------------

TVoxelBox::TVoxelCell_analys::TVoxelCell_analys(const unsigned int& sizeX, const unsigned int& sizeY, const unsigned int& sizeZ, unsigned char& Size_dec, unsigned short int*& dec):
TVoxelCell_char(sizeX,sizeY,sizeZ),size_decode(Size_dec),decode(dec)
{
}

int TVoxelBox::TVoxelCell_analys::getMaterial(const int i, const int j, const int k) const
{
	unsigned int idx = getIndex(i,j,k);
	if(idx>=Size) return -1;
	int val_idx = value[idx];
	if((val_idx<0)||(val_idx>size_decode)) return -1;
	return (int ) (decode[val_idx]);
}

int TVoxelBox::TVoxelCell_analys::putMaterial(const int i, const int j, const int k, unsigned short int val)
{
	unsigned int idx = getIndex(i,j,k);
	if(idx>=Size) return -1;
	int code = -1;
	for(int l=0; l<=size_decode; l++){
		if(decode[l]==val) {
			code = l;
			break;
		}
	}
	if(code==-1) return -1;
	value[idx] = (unsigned char ) code;
	return idx;
}

int TVoxelBox::TVoxelCell_analys::putMaterial(const unsigned int idx, unsigned short int val)
{
	if((val>255)||(idx>=Size)) return -1;
	value[idx] = (unsigned char ) val;
	return idx;
}

void* TVoxelBox::TVoxelCell_analys::address() const
{
	return (void*) value;
}

TVoxelBox::TVoxelCell_analys::~TVoxelCell_analys()
{
	delete []value;
	value = NULL;
	Size = 0;
}

//--------------------------------------------------------------------------------------------------------------------------
//                                                КОНЕЦ ОПИСАНИЯ TVoxelCell
//     ***************************************************************************************************************
//
//                                                 VOXELBOX  DEFINITIONS
//--------------------------------------------------------------------------------------------------------------------------

TVoxelBox::TVoxelBox():SizeX(Size[0]),SizeY(Size[1]),SizeZ(Size[2])
{
	VoxelCell = NULL;
	decode    = NULL;
	size_decode = 0;
	SizeX = SizeY = SizeZ = 0;
}

TVoxelBox::~TVoxelBox()
{
	if (decode != NULL)
	{
		delete []decode;
		decode = NULL;
	}

	if (VoxelCell != NULL)
	{
		delete VoxelCell;
		VoxelCell = NULL;
	}
}

// инициализация объекта типа TVoxelBox производится из файла под именем : voxelBoxFileName
// тип представления данных определяется в самом файле
void TVoxelBox::Init(const char* voxelBoxFileName)
{
	FILE* fin = fopen(voxelBoxFileName, "rb");
	if (fin == NULL)
		throw Exception("Не могу открыть файл!");

	unsigned char cbuffer;

	// читаем тип представления
	fread(&cbuffer,sizeof(unsigned char), 1, fin);
	if ((cbuffer < 0) || (cbuffer > 3))
	{
		fclose(fin);
		throw Exception("Type of data is invalid!");
	}

	Type = (TVoxelBoxTypes)cbuffer;

	// читаем размер вокселя 3*double
	fread(VoxelSize,sizeof(double), 3, fin);
	// читаем количество вокселей
	fread(Size,sizeof(unsigned int), 3, fin);
	// размеры бокса
	double Lx = SizeX * VoxelSize[0];
	double Ly = SizeY * VoxelSize[1];
	double Lz = SizeZ * VoxelSize[2];

	toCenter.x(0.5*Lx);
	toCenter.y(0.5*Ly);
	toCenter.z(0.5*Lz);

	decode = NULL;

	switch (Type)
	{
	case AUTOMATIC_VoxelBoxType:
		{
			// идентификация материалов производится через декодировку
			// считываем размер декодирующего массива
			fread(&cbuffer,sizeof (unsigned char ),1,fin);
			if ((cbuffer<0)||(cbuffer>255))
			{
				fclose(fin);
				throw Exception("Size of decode array is invalid!");
			}
			size_decode = cbuffer;
			decode = new unsigned short int [size_decode];
			// считываем массив декодировки
			fread(decode,sizeof (unsigned short int ),size_decode,fin);
			// инициализируем массив ссылок на материалы
			VoxelCell = new TVoxelCell_analys(SizeX,SizeY,SizeZ,size_decode,decode);
			void* addr = VoxelCell->address();
			unsigned int SizeData = VoxelCell->getSize();
			fread(addr,sizeof (unsigned char ),SizeData,fin);
			break;
		}
	case ONEBYTE_VoxelBoxType:
		{
			VoxelCell = new  TVoxelCell_char(SizeX,SizeY,SizeZ);
			void* addr = VoxelCell->address();
			unsigned int SizeData = VoxelCell->getSize();
			fread(addr,sizeof (unsigned char ),SizeData,fin);
			break;
		}
	case TWOBYTE_VoxelBoxType:
		{
			VoxelCell = new  TVoxelCell_int(SizeX,SizeY,SizeZ);
			void* addr = VoxelCell->address();
			unsigned int SizeData = VoxelCell->getSize();
			fread(addr,sizeof (unsigned short int ),SizeData,fin);
			break;
		}
	case ANALYS_VoxelBoxType :
		{
			unsigned short int buffer; // буфер для считывания данных из файла
			// декодирующего массива в файле нет поэтому анализируем вначале данные
			long curPosition;
			unsigned short int counter=0;
			unsigned int SizeData = SizeX * SizeY * SizeZ;
			size_decode = 255;
			decode = new unsigned short int [size_decode+1];
			VoxelCell = new  TVoxelCell_analys(SizeX,SizeY,SizeZ,size_decode,decode);
			curPosition = ftell(fin); // запомнили позицию файла
			for(unsigned int i=0; i<SizeData; i++)
			{
				// формируем декодировщик
				fread(&buffer,sizeof (unsigned short int ),1,fin);
				if(counter)
				{
					unsigned short int j;
					int maxCounter = (counter>=256) ? 256 : counter;
					for(j=0; j<maxCounter; j++)
					{
						// осуществляем поиск индекса в уже существующих
						if(decode[j]==buffer) break;
					}
					if(j==counter)
					{
						// не нашлось такого индекса, заносим его
						if(counter==256)
						{
							counter++;
							break;
						}
						decode[counter++] = buffer;
					}
					VoxelCell->putMaterial(i,j);
				}
				else
				{
					decode[counter] = buffer;
					VoxelCell->putMaterial(i,counter);
					counter++;
				}
			}
			// делаем проверку на тип инициализации
			if (counter>256)
			{
				// количество индексов превысило 256, создаем VoxelCell типа TVoxelCell_int
				delete VoxelCell;
				size_decode = 0;
				delete []decode;
				decode = NULL;
				// инициализируем новую переменную
				VoxelCell = new  TVoxelCell_int(SizeX,SizeY,SizeZ);
				void* addr = VoxelCell->address();
				unsigned int SizeData = VoxelCell->getSize();
				fseek(fin,curPosition,SEEK_SET); // установили файл в запомненую позицию
				fread(addr,sizeof (unsigned short int ),SizeData,fin);
			}
			else
			{
				size_decode = (unsigned char ) (counter - 1);
			}
			break;
		}
	default:
		{
			fclose(fin);
			throw Exception("Type of data is invalid!");
		}
	}

	fclose(fin);
}

double TVoxelBox::BoxSizeX()   // выдать размеры VoxelBox по оси X
{
	return VoxelSize[0]*SizeX;
}

double TVoxelBox::BoxSizeY()   // выдать размеры VoxelBox по оси Y
{
	return VoxelSize[1]*SizeY;
}

double TVoxelBox::BoxSizeZ()   // выдать размеры VoxelBox по оси Z
{
	return VoxelSize[2]*SizeZ;
}

unsigned int TVoxelBox::getIndex(const int i, const int j, const int k) const
{
	return VoxelCell->getIndex(i, j, k);
}

unsigned int TVoxelBox::getSize() const
{
	return VoxelCell->getSize();
}

int TVoxelBox::xyz_to_ijk(const double& x, const double& y, const double& z, unsigned short int& i, unsigned short int& j, unsigned short int& k) const
{
	int si = (int) floor(x / VoxelSize[0]);
	if((si<0)||(si>=SizeX)) return 1;
	i = (unsigned short int ) si;
	si = (int) floor(y / VoxelSize[1]);
	if((si<0)||(si>=SizeY)) return 1;
	j = (unsigned short int ) si;
	si = (int) floor(z / VoxelSize[2]);
	if((si<0)||(si>=SizeZ)) return 1;
	k = (unsigned short int ) si;
	return 0;
}

int TVoxelBox::center(double& x, double& y, double& z) const
{
	x = toCenter.x();
	y = toCenter.y();
	z = toCenter.z();
	return 0;
}

int TVoxelBox::CellSize(double& x, double& y, double& z) const
{
	x = VoxelSize[0];
	y = VoxelSize[1];
	z = VoxelSize[2];
	return 0;
}

int TVoxelBox::CellsNumber(unsigned int& Nx, unsigned int& Ny, unsigned int& Nz) const
{
	Nx = Size[0];
	Ny = Size[1];
	Nz = Size[2];
	return 0;
}

int TVoxelBox::getMaterial(const int i, const int j, const int k) const
{
	return VoxelCell->getMaterial(i, j, k);
}

int TVoxelBox::putMaterial(const int i, const int j, const int k, unsigned short int val)
{
	return VoxelCell->putMaterial(i, j, k, val);
}

int TVoxelBox::putMaterial(const unsigned int i, unsigned short int val)
{
	return VoxelCell->putMaterial(i, val);
}

void TVoxelBox::putMaterial(const unsigned int material)
{
	if (std::find(m_materials.begin(), m_materials.end(), material) == m_materials.end())
		m_materials.push_back(material);
}

std::map<int, int> TVoxelBox::m_colorMap;

void TVoxelBox::setColorValue(int material, int color)
{
	if (material > 0)
		m_colorMap[material] = color;
}

int TVoxelBox::getColorValue(int material)
{
	if (m_colorMap.find(material) != m_colorMap.end())
		return m_colorMap[material];
	else if (material > 0)
		return ((material%20)*255)/20;
	else
		return -1;
}
