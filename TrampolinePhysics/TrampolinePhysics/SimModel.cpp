#include "precompiled.h"
#include "SimModel.h"

SimModel::SimModel(Model * model, float mass, SimObjectType type): SimObject(mass,type), m_model(model)
{
	if(model != 0)
	{
		m_currentPosition = model->Position();
		m_previousPosition = model->Position();
	}
}

SimModel::~SimModel(void)
{
}
void SimModel::Update()
{
	SimObject::Update();
	m_model->SetPosition(this->CurrentPosition());
}
