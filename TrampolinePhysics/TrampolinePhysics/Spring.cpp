#include "precompiled.h"
#include "Spring.h"

Spring::Spring(float stiffness , float damping , SimObject * objA , SimObject * objB , float restLength )
: m_stiffness(stiffness),m_damping(damping),m_simObjectA(objA),m_simObjectB(objB),m_restLength(restLength),
	m_direction(0,0,0),m_currentLength(restLength),m_force(0,0,0)
 
{
}

Spring::~Spring(void)
{
}

// NOTE: does not use simObject passed in
void Spring::ApplyForce(SimObject &simObject)
{
	m_direction = m_simObjectA->CurrentPosition() - m_simObjectB->CurrentPosition();

	// check for zero vector
	if(m_direction.Length() != 0)
	{
		m_currentLength = m_direction.Length();

		// normalise
		m_direction.Normalise();

		// add spring force
		float currMinusRest = m_currentLength - m_restLength;
		Vector3 force = m_direction * currMinusRest;
		float stiffness = -m_stiffness;
		m_force = force * stiffness;

		// add spring damping
		Vector3 objVelA = m_simObjectA->CurrentVelocity();
		Vector3 objVelB = m_simObjectB->CurrentVelocity();
		Vector3 VelA_minus_velB = objVelA - objVelB;

		force = VelA_minus_velB * (-m_damping);
		m_force = m_force + force;


		// now apply the force to both objects (equal and opposite)
		Vector3 objAforce = m_simObjectA->ResultantForce() + m_force;
		Vector3 objBforce = m_simObjectB->ResultantForce() - m_force;
		
		m_simObjectA->SetResultantForce(objAforce);
		m_simObjectB->SetResultantForce(objBforce);

	}
}


