#ifndef MEDIUM_H
#define MEDIUM_H

#include "forcegenerator.h"

class Medium : public ForceGenerator
{
private:
	float m_dragCoefficient;
public:

	inline float DragCoefficient()
	{
		return m_dragCoefficient; 
	}
	inline void SetDragCoefficient(float value)
	{
		m_dragCoefficient = value;
	}


	inline virtual void ApplyForce(SimObject * simObject)
	{
		Vector3 vel = simObject->CurrentVelocity() * m_dragCoefficient;

		simObject->SetResultantForce(simObject->ResultantForce() + vel);
	}

	Medium(float dragCoefficient = 0);
	~Medium(void);
};

#endif
