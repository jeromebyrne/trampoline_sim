#ifndef FORWARDEULERINTEGRATOR_H
#define FORWARDEULERINTEGRATOR_H

#include "integrator.h"

class ForwardEulerIntegrator :
	public Integrator
{
public:
	ForwardEulerIntegrator(void);
	virtual ~ForwardEulerIntegrator(void);

	void Integrate(Vector3 acceleration, SimObject * simObject);

};

#endif