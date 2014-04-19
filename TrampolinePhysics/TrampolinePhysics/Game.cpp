#include "precompiled.h"
#include "Game.h"

Game::Game(void): m_renderMode(FULL),m_trampolineProperties(MEDIUM)
{
	camera = new BasicCamera();

}

Game::~Game(void)
{
	
}

void Game::InitSpringScene()
{
	m_physicsSim = new Simulation(); // create a new simulation

	// add gravity and air resistance to the simulation
	m_physicsSim->AddGlobalForceGenerator(new Gravity());
	//m_physicsSim->AddGlobalForceGenerator(new Medium(-0.02)); // add air resistance

	// now create an integrator
	m_physicsSim->SetIntegrator(new ForwardEulerIntegrator());


	// create rigid body spheres
	//m_sphereList = new list<SimModel *>();
	int sphereTexture = Texture::GetInstance()->generateTexture("textures/cloth3.bmp");
	int sphereTexture2 = Texture::GetInstance()->generateTexture("textures/ball.bmp");
	int sphereTexture3 = Texture::GetInstance()->generateTexture("textures/ball2.bmp");
	int sphereTexture4 = Texture::GetInstance()->generateTexture("textures/cloth2.bmp");
	int sphereTexture5 = Texture::GetInstance()->generateTexture("textures/cloth4.bmp");



	SimModel * m_simSphere = new SimModel(new SphereModel(100,20,100,20,5,5,sphereTexture),5,ACTIVE);
	m_simSphere->SetCurrentVelocity(Vector3(0,10,0));
	m_sphereList.push_back(m_simSphere);// add to list

	SimModel * m_simSphere2 = new SimModel(new SphereModel(140,75,110,20,2,2,sphereTexture2),5,ACTIVE);
	m_simSphere2->SetCurrentVelocity(Vector3(0,-10,0));
	m_sphereList.push_back(m_simSphere2);// add to list

	SimModel * m_simSphere3 = new SimModel(new SphereModel(130,60,100,30,1,1,sphereTexture3),7,ACTIVE);
	m_simSphere3->SetCurrentVelocity(Vector3(7,0,0));
	m_sphereList.push_back(m_simSphere3);// add to list

	SimModel * m_simSphere4 = new SimModel(new SphereModel(110,80,95,25,1,1,sphereTexture4),6,ACTIVE);
	m_simSphere4->SetCurrentVelocity(Vector3(10,0,0));
	m_sphereList.push_back(m_simSphere4);// add to list

	SimModel * m_simSphere5 = new SimModel(new SphereModel(100,70,200,30,1,1,sphereTexture5),7,ACTIVE);
	m_simSphere5->SetCurrentVelocity(Vector3(0,0,-5));
	m_sphereList.push_back(m_simSphere5);// add to list

	
	//now add all the spheres to the simulation
	list<SimModel *> ::iterator current = m_sphereList.begin();

	for(;current != m_sphereList.end(); current++)
	{
		m_physicsSim->AddSimObject(*current);
	}

	// create and build our trampoline
	float segWidth = 15.0f;
	float stiffness = 40.0f;
	float damping = 2.0f;
	float restLength = 5;
	m_trampoline = new Trampoline(0,0,0,segWidth,stiffness,damping,restLength);

}

void Game::Initialise()
{
	// initialise our texture manager
	Texture::GetInstance()->Initialise(GLwindow::GetInstance()->GetHwndRef());

	InitSpringScene();

}

void Game::Update(Vector2 mouse)
{
	// update the physics simulation
	m_physicsSim->Update();

	static int lastTimeSpacePressed = 0;
	int switchTime = 300;

	if(GetAsyncKeyState(VK_SPACE) < 0 && GetTickCount() > lastTimeSpacePressed + switchTime)
	{
		if(m_renderMode == FULL)
		{
			m_renderMode = WIREFRAME;
		}
		else if(m_renderMode == WIREFRAME)
		{
			m_renderMode = COLLISION;
		}
		else if(m_renderMode == COLLISION)
		{
			m_renderMode = FULL;
		}
		lastTimeSpacePressed = GetTickCount();
		m_trampoline->SetRenderMode(m_renderMode);
	}

	static int lastTime_p_pressed = 0;

	if(GetAsyncKeyState('P') < 0 && GetTickCount() > lastTime_p_pressed + switchTime)
	{
		if(m_trampolineProperties == VERY_LOOSE)
		{
			m_trampolineProperties = LOOSE;

			// set to loose properties
			m_trampoline->SetRestLength(m_trampoline->SegWidth() / 1.3f);
			m_trampoline->SetStiffness(10.0f);
			m_trampoline->SetDamping(1.0f);
		}
		else if(m_trampolineProperties == LOOSE)
		{
			m_trampolineProperties = MEDIUM;

			// set to medium properties
			m_trampoline->SetRestLength(m_trampoline->SegWidth() / 2.0f);
			m_trampoline->SetStiffness(45.0f);
			m_trampoline->SetDamping(2.0f);
		}
		else if(m_trampolineProperties == MEDIUM)
		{
			m_trampolineProperties = TIGHT;

			// set to tight properties
			m_trampoline->SetRestLength(0);
			m_trampoline->SetStiffness(90.0f);
			m_trampoline->SetDamping(5.0f);
		}
		else if(m_trampolineProperties == TIGHT)
		{
			m_trampolineProperties = VERY_LOOSE;

			// set to very loose properties
			m_trampoline->SetRestLength(m_trampoline->SegWidth());
			m_trampoline->SetStiffness(3.0f);
			m_trampoline->SetDamping(1.0f);
		}
		lastTime_p_pressed = GetTickCount();
		m_trampoline->ApplyChanges();
	}
	
	// do collision detection for all rigid bodies
	list<SimModel *> ::iterator current = m_sphereList.begin();

	for(; current != m_sphereList.end(); current++)
	{
		m_trampoline->ResolveCollisions(*current);
		
		// do collision detection between spheres
		list<SimModel *> ::iterator i = m_sphereList.begin();

		for(;i != m_sphereList.end(); i++)
		{
			if((*i) != (*current))
			{
				// get the distance between the objects
				float distance = (*i)->CurrentPosition().Distance((*current)->CurrentPosition());

				float desiredDistance = (*i)->GetModel()->m_width + (*current)->GetModel()->m_width;

				
				if(distance < desiredDistance)
				{
					// we have a collision

					// push apart by the overlap
					float overlap = (distance - desiredDistance);

					Vector3 vec = (*i)->CurrentPosition() - (*current)->CurrentPosition();
					vec.Normalise();

					vec = (vec * overlap) ;

					(*current)->SetCurrentPosition((*current)->CurrentPosition() + vec);

					vec.Normalise();

					Vector3 force1 = vec * -(*current)->CurrentVelocity().Length();
					Vector3 force2 = vec * (*i)->CurrentVelocity().Length();

					(*current)->SetCurrentVelocity(force2 );
					(*i)->SetCurrentVelocity(force1 );
				}
			}
		}
	}

	m_physicsSim->Integrate();
	m_physicsSim->ResetForces();

	
}

void Game::Draw()
{
	// update our camera view before we draw
	camera->Update();

	m_trampoline->Draw();	

	// draw sphere list
	list<SimModel *>::iterator current = m_sphereList.begin();

	for(;current != m_sphereList.end(); current++)
	{
		(*current)->GetModel()->Draw();
	}
}

// draws a simple text hud
void Game::DrawHud()
{
	glPushMatrix();
	glTranslatef(-1,0,0);
	GLwindow::GetInstance()->Print("Press Space to scroll render Mode ");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,-0.5,0);

	GLwindow::GetInstance()->Print("Press 'P' to scroll trampoline properties");

	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1,-1,0);

	GLwindow::GetInstance()->Print("W,A,S,D to manipulate trampoline");

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,-7,0);
	
	if(m_trampolineProperties == VERY_LOOSE)
	{
		GLwindow::GetInstance()->Print("Trampoline Properties: VERY LOOSE");
	}
	else if(m_trampolineProperties == LOOSE)
	{
		GLwindow::GetInstance()->Print("Trampoline Properties: LOOSE");
	}
	else if(m_trampolineProperties == MEDIUM)
	{
		GLwindow::GetInstance()->Print("Trampoline Properties: NORMAL");
	}
	else if(m_trampolineProperties == TIGHT)
	{
		GLwindow::GetInstance()->Print("Trampoline Properties: TIGHT");
	}

	glPopMatrix();
}

