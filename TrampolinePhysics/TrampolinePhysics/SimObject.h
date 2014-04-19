#ifndef SIMOBJECT_H
#define SIMOBJECT_H

class SimObject
{
private:
	float m_mass;
	SimObjectType m_simObjectType;

protected:
	Vector3 m_currentPosition;
	Vector3 m_previousPosition;
	Vector3 m_currentVelocity;
	Vector3 m_resultantForce;

public:

	SimObject(float mass = 1, SimObjectType type = ACTIVE);
	~SimObject(void);

	virtual void Update()
	{
		//if(m_resultantForce.Length() < 10)
		//{
		//	m_currentVelocity = Vector3(0,0,0);
		//	//m_previousPosition = m_currentPosition;

		//	//m_resultantForce = Vector3(0,0,0);
		//}
	}

	inline Vector3 ResultantForce()
	{
		return m_resultantForce;
	}

	inline void SetResultantForce(Vector3 value)
	{
		m_resultantForce = value;
	}

	inline void ResetForces()
	{
		m_resultantForce.X = 0;
		m_resultantForce.Y = 0;
		m_resultantForce.Z = 0;
	}

	inline float Mass()
	{ return m_mass; }

	inline void SetMass(float value)
	{ m_mass = value;}

	inline SimObjectType GetSimObjectType()
	{ return m_simObjectType; }

	inline void SetSimObjectType(SimObjectType value)
	{ m_simObjectType = value; }

	inline Vector3 CurrentPosition()
	{ return m_currentPosition; }

	inline void SetCurrentPosition(Vector3 value)
	{ m_currentPosition = value; }

	inline Vector3 PreviousPosition()
	{ return m_previousPosition; }

	inline void SetPreviousPosition(Vector3 value)
	{ m_previousPosition = value; }

	inline Vector3 CurrentVelocity()
	{ return m_currentVelocity; }

	inline void SetCurrentVelocity(Vector3 value)
	{ m_currentVelocity = value; }

	inline float CurrentX()
	{ return m_currentPosition.X; }

	inline float CurrentY()
	{ return m_currentPosition.Y; }

	inline float CurrentZ()
	{ return m_currentPosition.Z; }

	inline void SetCurrentX(float value)
	{ m_currentPosition.X = value; }

	inline void SetCurrentY(float value)
	{ m_currentPosition.Y = value; }

	inline void SetCurrentZ(float value)
	{ m_currentPosition.Z = value; }

};

#endif
