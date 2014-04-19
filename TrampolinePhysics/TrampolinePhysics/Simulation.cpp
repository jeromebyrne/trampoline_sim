#include "precompiled.h"
#include "Simulation.h"
#include "forwardeulerintegrator.h"

list<SimObject *> Simulation :: m_simObjects;
list<Spring *> Simulation :: m_springs;

Simulation::Simulation(void)
{
	//create a default integrator
	m_integrator = new ForwardEulerIntegrator();
}

Simulation::~Simulation(void)
{
}
void Simulation::Update()
{
	list<Spring *> ::iterator springCurrent = m_springs.begin();

	SimObject * s = 0; // need to create this to satisfy the applyForce function parameter (not used)

	// iterate through our springs and apply force
	for(;springCurrent != m_springs.end(); springCurrent++)
	{
		(*springCurrent)->ApplyForce(*s);
	}


	list<SimObject *>::iterator simObjCurrent = m_simObjects.begin();

	// iterate through each simObject - apply forces to objects
	for(;simObjCurrent != m_simObjects.end(); simObjCurrent++)
	{
		// onlu update active objects
		if((*simObjCurrent)->GetSimObjectType() == ACTIVE)
		{
			// now iterate through all global force generators

			list<ForceGenerator *>::iterator forceGenCurrent = m_globalForceGenerators.begin();

			for(;forceGenCurrent != m_globalForceGenerators.end(); forceGenCurrent++)
			{
				// apply the forces to the sim objects
				(*forceGenCurrent)->ApplyForce(*simObjCurrent);
			}
		}
	}//end of outer for

}

void Simulation::Integrate()
{
	Vector3 acceleration;

	list<SimObject *>::iterator simObjCurrent = m_simObjects.begin();
	// iterate through sim objects and integrate

	for(; simObjCurrent != m_simObjects.end(); simObjCurrent++)
	{
		if((*simObjCurrent)->GetSimObjectType() == ACTIVE)
		{
			// find the acceleration
			float mass = (*simObjCurrent)->Mass();
			acceleration = (*simObjCurrent)->ResultantForce() / mass;

			// integrate
			m_integrator->Integrate(acceleration,*simObjCurrent);
		}
	}

	// iterate through sim objects and call their update function
	for(simObjCurrent = m_simObjects.begin(); simObjCurrent != m_simObjects.end(); simObjCurrent++)
	{
		(*simObjCurrent)->Update();
	}

}

void Simulation::ResetForces()
{
	list<SimObject *>::iterator simObjCurrent = m_simObjects.begin();

	// iterate through sim objects and reset the forces
	for(; simObjCurrent != m_simObjects.end(); simObjCurrent++)
	{
		if((*simObjCurrent)->GetSimObjectType() == ACTIVE)
		{
			(*simObjCurrent)->ResetForces();
		}
	}
}

