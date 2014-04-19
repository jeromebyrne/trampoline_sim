#ifndef TRAMPOLINESEGMENT_H
#define TRAMPOLINESEGMENT_H

#include "simmodel.h"

class TrampolineSegment : public SimModel
{
public:
	TrampolineSegment(Model * model = 0, float mass = 1, SimObjectType type = ACTIVE);
	virtual ~TrampolineSegment(void);
};

#endif
