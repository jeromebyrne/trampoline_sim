#ifndef INTEGRATOR_H
#define INTEGRATOR_H


class Integrator
{
private:
protected:
	float m_fixedTimeStep;
public:

	inline float FixedTimeStep()
	{
		return m_fixedTimeStep;
	}
	inline void SetFixedTimeStep(float value)
	{
		m_fixedTimeStep = value;
	}
	
	virtual void Integrate(Vector3 acceleration, SimObject * simObject) {};

	Integrator(void);
	~Integrator(void);
};

#endif
