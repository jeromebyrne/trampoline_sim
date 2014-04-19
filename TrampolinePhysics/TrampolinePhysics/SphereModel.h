#ifndef SPHEREMODEL_H
#define SPHEREMODEL_H

#include "model.h"

class SphereModel : public Model
{
private:

public:
	SphereModel(float x = 0, float y = 0, float z = 0, float width = 10, float height = 10, float breadth = 10, int texture = 0);
	~SphereModel(void);
	void Draw();
};

#endif
