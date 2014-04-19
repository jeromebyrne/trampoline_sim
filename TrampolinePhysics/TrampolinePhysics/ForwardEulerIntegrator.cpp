#include "precompiled.h"
#include "ForwardEulerIntegrator.h"

ForwardEulerIntegrator::ForwardEulerIntegrator(void)
{
}

ForwardEulerIntegrator::~ForwardEulerIntegrator(void)
{
}

void ForwardEulerIntegrator::Integrate(Vector3 acceleration, SimObject * simObject)
{
	// calculate the new position using the velocity at current time
	Vector3 newPos = simObject->CurrentPosition();
	Vector3 currVel =  simObject->CurrentVelocity() * m_fixedTimeStep;
	newPos = newPos + currVel;

	simObject->SetCurrentPosition(newPos);

	// calculate the new velocity using the acceleration at the current time
	Vector3 newVel = simObject->CurrentVelocity();
	acceleration = acceleration * m_fixedTimeStep;
	newVel = newVel + acceleration;

	simObject->SetCurrentVelocity(newVel);
}
