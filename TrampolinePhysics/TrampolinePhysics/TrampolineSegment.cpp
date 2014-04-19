#include "precompiled.h"
#include "TrampolineSegment.h"

TrampolineSegment::TrampolineSegment(Model * model, float mass , SimObjectType type)
: SimModel(model,mass,type)
{
}

TrampolineSegment::~TrampolineSegment(void)
{
}
