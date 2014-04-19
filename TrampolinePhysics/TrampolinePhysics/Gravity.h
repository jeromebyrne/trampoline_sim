#ifndef GRAVITY_H
#define GRAVITY_H

#include "forcegenerator.h"

class Gravity : public ForceGenerator
{
private:
	Vector3 m_acceleration;
public:
	Gravity(float accelX = 0, float accelY = -19.21f, float accelZ = 0);
	virtual ~Gravity(void);

	// apply a gravitational force on a simObject
	void ApplyForce(SimObject * simObject)
	{
		float mass = simObject->Mass();

		Vector3 force = m_acceleration * mass;

		simObject->SetResultantForce(simObject->ResultantForce() + force );
	}

	inline Vector3 Acceleration()
	{
		return m_acceleration;
	}
	inline void SetAcceleration(Vector3 value)
	{
		m_acceleration = value;
	}
	inline void SetAccelX(float value)
	{
		m_acceleration.X = value;
	}
	inline void SetAccelY(float value)
	{
		m_acceleration.Y = value;
	}
	inline void SetAccelZ(float value)
	{
		m_acceleration.Z = value;
	}
};

#endif
