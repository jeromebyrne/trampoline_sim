#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

#define COLUMNS 20
#define ROWS 20

#include "TrampolineSegment.h"

class Trampoline
{
private:

	int m_clothTexture;
	int m_metalTexture;

	Vector3 m_position;

	float m_segWidth; // width of the individual segments

	float m_stiffness;
	float m_damping;
	float m_restLength;

	int m_currRenderMode;

	// 2d array of trampoline segments
	TrampolineSegment m_segmentArray[ROWS][COLUMNS];

	// draw the trampoline as lines
	void DrawLines();

	// draw the trampoline as a continuous piece of cloth
	void DrawCloth();

	// draw the collision planes of the trampoline
	void DrawCollisionPlanes();

	void BuildTrampoline();

	// calculate the normal of 3 points
	Vector3 CalcNormal(Vector3 p1, Vector3 p2, Vector3 p3);

public:
	Trampoline(float x = 0, float y = 0, float z = 0, float segWidth = 1, float stiffness = 10, float damping = 1, float restLength = 0);
	~Trampoline(void);

	// calculate the accumalated force of the trampoline
	Vector3 CalculateTotalForce();

	void SetRenderMode(int value)
	{
		m_currRenderMode = value;
	}
	
	inline float SegWidth()
	{
		return m_segWidth;
	}
	inline void SetStiffness(float value)
	{
		m_stiffness = value;

	}

	inline void SetDamping(float value)
	{
		m_damping = value;
	}

	inline void SetRestLength(float value)
	{
		m_restLength = value;
	}

	// apply changes made to stiffness, damping etc
	void ApplyChanges();

	void Draw();

	void ResolveCollisions(SimModel * simObject);
};

#endif
