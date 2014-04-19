#include "precompiled.h"
#include "SimObject.h"

SimObject::SimObject(float mass, SimObjectType type):m_mass(mass),m_simObjectType(type),m_currentPosition(0,0,0),
					m_previousPosition(0,0,0),m_currentVelocity(0,0,0), m_resultantForce(0,0,0)
{

}

SimObject::~SimObject(void)
{
}
