#ifndef VOXELRES_PROCESS
#define VOXELRES_PROCESS

#include "voxbox.hpp"

class TVoxelRes
{
private:
	TVoxelBox* m_voxelBox;
	unsigned int m_resultId;
	unsigned int m_particleId;
	double m_hist;
	double* m_value;
	float m_minValue;
	float m_maxValue;

public:
	TVoxelRes(TVoxelBox* voxelBox);
	virtual ~TVoxelRes();

	void Init(const char* voxelResFileName);
	unsigned int getResultID() { return m_resultId; }
	unsigned int getParticleID() { return m_particleId; }
	double getHist() { return m_hist; }
	float getMinValue() const;
	float getMaxValue() const;
	float getValue(int i, int j, int k) const;
	float getNormValue(int i, int j, int k) const;
	int getColorValue(float value, bool isolines, int levels) const;
	int getColorValue(int i, int j, int k, bool isolines, int levels) const;
};

#endif
