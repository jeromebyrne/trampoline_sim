#ifndef SPRING_H
#define SPRING_H

#include "ForceGenerator.h"

class Spring : ForceGenerator
{
private:
	float m_damping;
	float m_stiffness;
	float m_restLength;
	SimObject * m_simObjectA;
	SimObject * m_simObjectB;

	Vector3 m_direction;
	float m_currentLength;
	Vector3 m_force;

public:

	void ApplyForce(SimObject &simObject);
	inline float Damping()
	{
		return m_damping;
	}
	inline void SetDamping(float value)
	{
		m_damping = value;
	}
	inline float Stiffness()
	{
		return m_stiffness;
	}
	inline void SetStiffness(float value)
	{
		m_stiffness = value;
	}
	inline void SetRestLength(float value)
	{
		m_restLength = value;
	}
	SimObject * SimObjectA()
	{
		return m_simObjectA;
	}
	void SetSimObjectA(SimObject * value)
	{
		m_simObjectA = value;
	}
	SimObject * SimObjectB()
	{
		return m_simObjectB;
	}
	void SetSimObjectB(SimObject* value)
	{
		m_simObjectB = value;
	}

	Spring(float stiffness = 2, float damping = 2, SimObject * objA = 0, SimObject * objB = 0, float restLength = 2);
	~Spring(void);

};

#endif
