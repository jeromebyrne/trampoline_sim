#ifndef FORCEGENERATOR_H
#define FORCEGENERATOR_H

class ForceGenerator
{
private:

public:
	ForceGenerator(void);
	~ForceGenerator(void);

	virtual void ApplyForce(SimObject * simObject) {};
};

#endif
