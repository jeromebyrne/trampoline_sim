#ifndef SIMULATION_H
#define SIMULATION_H

#include "integrator.h"
#include "Spring.h"

class Simulation
{
private:
protected:
	static list<SimObject *> m_simObjects; // a list of all the sim objects in the world
	list<ForceGenerator *> m_globalForceGenerators; // a list of all the forces in the simulation
	static list<Spring *> m_springs; // a list of all springs
	Integrator * m_integrator; // our integrator
public:
	
	static inline void AddSpring(float stiffness, float damping, SimObject * objA, SimObject * objB, float restLength)
	{
		Spring * s = new Spring(stiffness,damping,objA,objB,restLength);
		m_springs.push_back(s);
	}
	
	static inline void AddSimObject(SimObject * simObject)
	{
		m_simObjects.push_back(simObject);
	}

	inline void AddGlobalForceGenerator(ForceGenerator * f)
	{
		m_globalForceGenerators.push_back(f);
	}
	static inline list<Spring *> * Springs()
	{
		return &m_springs;
	}
	static inline list<SimObject *> SimObjects()
	{
		return m_simObjects;
	}
	static inline void SetSimObjects(list<SimObject *> value)
	{
		m_simObjects = value;
	}

	inline Integrator * GetIntegrator()
	{
		return m_integrator;
	}
	inline void SetIntegrator(Integrator * value)
	{
		m_integrator = value;
	}
	
	virtual void Update();

	void Integrate();

	void ResetForces();

	Simulation(void);
	~Simulation(void);
};

#endif
