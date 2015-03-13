
#include "voxres.hpp"

TVoxelRes::TVoxelRes(TVoxelBox* voxelBox)
{
	m_value = NULL;
	m_voxelBox = voxelBox;
	m_maxValue = FLT_MIN;
	m_minValue = FLT_MAX;
}

TVoxelRes::~TVoxelRes()
{
	if (m_value != NULL)
		delete []m_value;
}

void TVoxelRes::Init(const char* voxelResFileName)
{
	FILE* fin = fopen(voxelResFileName, "rb");
	if (fin == NULL)
		throw Exception("Не могу открыть файл!");

	fseek(fin, sizeof(int), 0);

	fread(&m_resultId, sizeof(unsigned int), 1, fin);
	fread(&m_particleId, sizeof(unsigned int), 1, fin);
	fread(&m_hist, sizeof(double), 1, fin);

	double dx, dy, dz;
	fread(&dx, sizeof(double), 1, fin);
	fread(&dy, sizeof(double), 1, fin);
	fread(&dz, sizeof(double), 1, fin);

	unsigned int sx, sy, sz;
	fread(&sx, sizeof(unsigned int), 1, fin);
	fread(&sy, sizeof(unsigned int), 1, fin);
	fread(&sz, sizeof(unsigned int), 1, fin);

	if (sx != m_voxelBox->getSizeX() ||
		sy != m_voxelBox->getSizeY() ||
		sz != m_voxelBox->getSizeZ())
	{
		throw Exception("Файл результатов не соответсвует файлу воксельбокса!");
	}

	m_value = new double[m_voxelBox->getSize()];
	fread((void*)m_value, sizeof(double), m_voxelBox->getSize(), fin);

	for (unsigned int i = 0; i < m_voxelBox->getSize(); i++)
	{
		float value = m_value[i];

		if (m_minValue > value)
			m_minValue = value;

		if (m_maxValue < value)
			m_maxValue = value;
	}

	fclose(fin);
}

float TVoxelRes::getMinValue() const
{
	return m_minValue;
}

float TVoxelRes::getMaxValue() const
{
	return m_maxValue;
}

float TVoxelRes::getValue(int i, int j, int k) const
{
	return m_value[m_voxelBox->getIndex(i, j, k)];
}

int TVoxelRes::getColorValue(int i, int j, int k, bool isolines, int levels) const
{
	return getColorValue(getNormValue(i, j, k), isolines, levels);
}

int TVoxelRes::getColorValue(float value, bool isolines, int levels) const
{
	if (isolines)
		value = (((float)((int)(value*(levels))))/(levels));

	if (value < FLT_MIN)
		return -1;
	else if (value < 0.2)
		return RGB(0, 0, value*5*170+85);
	else if (value < 0.4)
		return RGB(0, ((value-0.2)*5)*255, 255);
	else if (value < 0.6)
		return RGB(((value-0.4)*5)*255, 255, (1.0-((value-0.4)*5))*255);
	else if (value < 0.8)
		return RGB(255, (1.0-((value-0.6)*5.0))*255, 0);
	else
		return RGB((1.0-((value-0.8)*5.0))*170+85, 0, 0);
}

float TVoxelRes::getNormValue(int i, int j, int k) const
{
	return (getValue(i, j, k) - m_minValue) / (m_maxValue - m_minValue);
}