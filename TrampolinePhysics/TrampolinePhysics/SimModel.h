#ifndef SIMMODEL_H
#define SIMMODEL_H

#include "simobject.h"
#include "Model.h"

class SimModel : public SimObject
{
private:
	Model * m_model;
public:
	inline Model * GetModel()
	{
		return m_model;
	}
	inline void SetModel(Model * value)
	{
		m_model = value;
	}

	SimModel(Model * model = 0, float mass = 1, SimObjectType type = ACTIVE);
	virtual ~SimModel(void);
	virtual void Update();
};

#endif