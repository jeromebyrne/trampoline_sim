#ifndef GAME_H
#define GAME_H

#include "SimModel.h"
#include "Simulation.h"

#include "Trampoline.h"
#include "SphereModel.h"

class Game
{
private:
	BasicCamera * camera;

	Simulation * m_physicsSim;

	Trampoline * m_trampoline;

	// the current render mode
	int m_renderMode;

	// the current properties of the trampoline
	int m_trampolineProperties;


	list<SimModel *> m_sphereList; // list of sphere simObjects

public:
	Game(void);
	~Game(void);
	
	void Initialise();
	void Update(Vector2 mouse);
	void Draw();

	void InitSpringScene();
	
	// draws a simple text hud
	void DrawHud();

};

#endif
