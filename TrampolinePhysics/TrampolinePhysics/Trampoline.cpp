#include "precompiled.h"
#include "Trampoline.h"
#include "simulation.h"

Trampoline::Trampoline(float x, float y, float z, float segWidth, float stiffness, float damping , float restLength)
: m_position(x,y,z), m_segWidth(segWidth), m_stiffness(stiffness), m_damping(damping), m_restLength(restLength),
m_currRenderMode(FULL)
{
	BuildTrampoline();
}

Trampoline::~Trampoline(void)
{
}

void Trampoline::BuildTrampoline()
{
	int segTypes[ROWS][COLUMNS] = {
	4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2};

	// textures
	m_clothTexture = Texture::GetInstance()->generateTexture("textures/cloth.bmp");
	m_metalTexture = Texture::GetInstance()->generateTexture("textures/cloth3.bmp");

	// the position of each tile 
	float tile_x = m_position.X, tile_z = m_position.Y;

	// create all of our segments using the types stored in the array (0 = active, 1 = passive)
	for(int i = 0; i < ROWS; i++)
	{
		// set the tile x position back to the top left corner (track position)
		tile_x = m_position.X;

		for(int count = 0; count < COLUMNS; count++)
		{
			// if this is an ACTIVE segment
			if(segTypes[i][count] == 0)
			{
				TrampolineSegment seg(
					new Model(m_position.X + tile_x, m_position.Y, m_position.Z + tile_z,m_segWidth ,m_segWidth ,m_segWidth,m_clothTexture),
					0.5f,
					ACTIVE
					);

				m_segmentArray[i][count] = seg;

				Simulation::AddSimObject(&(m_segmentArray[i][count]));
			}
			// if this is a PASSIVE segment
			else if(segTypes[i][count] == 1 || segTypes[i][count] == 2 ||
				    segTypes[i][count] == 3 || segTypes[i][count] == 4)
			{
				TrampolineSegment seg(
					new Model(m_position.X + tile_x, m_position.Y, m_position.Z + tile_z,m_segWidth,m_segWidth ,m_segWidth ,m_metalTexture),
					1000,
					PASSIVE
					);

				m_segmentArray[i][count] = seg;

				Simulation::AddSimObject(&(m_segmentArray[i][count]));
			}

			// increment the tile x position to the next tile
			tile_x += m_segWidth;
		}// end of inner for

		// increment the tile position y position to the next tile
		tile_z += m_segWidth;
		
	}// end of outer for

	// now connect our segments with springs
	for(int i = 0; i < ROWS; i++)
	{
		for(int count = 0; count < COLUMNS; count++)
		{
			// if this is an ACTIVE segment
			if(segTypes[i][count] == 0)
			{
				// we create 2 springs, one to the right neighbour and to the neighbour below
				if( i < ROWS - 2)
				{
					Simulation::AddSpring(m_stiffness,m_damping,&(m_segmentArray[i][count]),&(m_segmentArray[i + 1][count]),m_restLength);
				}
				if(count < COLUMNS - 2)
				{
					Simulation::AddSpring(m_stiffness,m_damping,&(m_segmentArray[i][count]),&(m_segmentArray[i][count + 1]),m_restLength);
				}
			}

			// if its passive and the top of the trampoline frame
			// then we create a spring going from this DOWN to the next segment 
			else if(segTypes[i][count] == 1)
			{
				// dont connect to passive segment
				if(segTypes[i + 1][count] != 4)
				{
					Simulation::AddSpring(m_stiffness,m_damping,&(m_segmentArray[i][count]),&(m_segmentArray[i + 1][count]),m_restLength);
				}
			}
			else if(segTypes[i][count] == 2)
			{
				// dont connect to passive segment
				if(segTypes[i][count - 1] != 3)
				{
					Simulation::AddSpring(m_stiffness,m_damping,&(m_segmentArray[i][count]),&(m_segmentArray[i][count - 1]),m_restLength);
				}
			}
			else if(segTypes[i][count] == 3)
			{
				// dont connect to passive segment
				if(segTypes[i - 1][count] != 4)
				{
					Simulation::AddSpring(m_stiffness,m_damping,&(m_segmentArray[i][count]),&(m_segmentArray[i - 1][count]),m_restLength);
				}
			}
			else if(segTypes[i][count] == 4)
			{
				// dont connect to passive segment
				if(segTypes[i][count + 1] != 1)
				{
					Simulation::AddSpring(m_stiffness,m_damping,&(m_segmentArray[i][count]),&(m_segmentArray[i][count + 1]),m_restLength);
				}
			}
		}
	}

}

void Trampoline::Draw()
{
	if(m_currRenderMode == FULL)
	{
		DrawCloth();
	}
	else if(m_currRenderMode == WIREFRAME)
	{
		DrawLines();
	}
	else if(m_currRenderMode == COLLISION)
	{
		DrawLines();
		DrawCollisionPlanes();
	}
	
	// apply a force to the middle segment
	if(GetAsyncKeyState('W') < 0)
	{

		m_segmentArray[9][9].SetResultantForce(Vector3(0,250,0));
		m_segmentArray[9][10].SetResultantForce(Vector3(0,250,0));
		m_segmentArray[9][11].SetResultantForce(Vector3(0,250,0));
		m_segmentArray[10][9].SetResultantForce(Vector3(0,250,0));
		m_segmentArray[10][10].SetResultantForce(Vector3(0,400,0));
		m_segmentArray[10][11].SetResultantForce(Vector3(0,250,0));
		m_segmentArray[11][9].SetResultantForce(Vector3(0,250,0));
		m_segmentArray[11][10].SetResultantForce(Vector3(0,250,0));
		m_segmentArray[11][11].SetResultantForce(Vector3(0,250,0));
	}
	else if(GetAsyncKeyState('S') < 0)
	{
		m_segmentArray[9][9].SetResultantForce(Vector3(0,-250,0));
		m_segmentArray[9][10].SetResultantForce(Vector3(0,-250,0));
		m_segmentArray[9][11].SetResultantForce(Vector3(0,-250,0));
		m_segmentArray[10][9].SetResultantForce(Vector3(0,-250,0));
		m_segmentArray[10][10].SetResultantForce(Vector3(0,-400,0));
		m_segmentArray[10][11].SetResultantForce(Vector3(0,-250,0));
		m_segmentArray[11][9].SetResultantForce(Vector3(0,-250,0));
		m_segmentArray[11][10].SetResultantForce(Vector3(0,-250,0));
		m_segmentArray[11][11].SetResultantForce(Vector3(0,-250,0));
	}

	if(GetAsyncKeyState('A') < 0)
	{
		m_segmentArray[9][9].SetResultantForce(Vector3(250,0,0));
		m_segmentArray[9][10].SetResultantForce(Vector3(250,0,0));
		m_segmentArray[9][11].SetResultantForce(Vector3(250,0,0));
		m_segmentArray[10][9].SetResultantForce(Vector3(250,0,0));
		m_segmentArray[10][10].SetResultantForce(Vector3(400,0,0));
		m_segmentArray[10][11].SetResultantForce(Vector3(250,0,0));
		m_segmentArray[11][9].SetResultantForce(Vector3(250,0,0));
		m_segmentArray[11][10].SetResultantForce(Vector3(250,0,0));
		m_segmentArray[11][11].SetResultantForce(Vector3(250,0,0));
	}
	else if(GetAsyncKeyState('D') < 0)
	{
		m_segmentArray[9][9].SetResultantForce(Vector3(-250,0,0));
		m_segmentArray[9][10].SetResultantForce(Vector3(-250,0,0));
		m_segmentArray[9][11].SetResultantForce(Vector3(-250,0,0));
		m_segmentArray[10][9].SetResultantForce(Vector3(-250,0,0));
		m_segmentArray[10][10].SetResultantForce(Vector3(-400,0,0));
		m_segmentArray[10][11].SetResultantForce(Vector3(-250,0,0));
		m_segmentArray[11][9].SetResultantForce(Vector3(-250,0,0));
		m_segmentArray[11][10].SetResultantForce(Vector3(-250,0,0));
		m_segmentArray[11][11].SetResultantForce(Vector3(-250,0,0));
	}
}

// draw the trampoline as lines
void Trampoline::DrawLines()
{
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_LINES);

	// draw lines
	for(int i =0; i<ROWS; i++)
	{
		for(int count = 0; count < COLUMNS; count++)
		{
			// draw lines
			if(m_segmentArray[i][count].GetSimObjectType() == ACTIVE)
			{
					Vector3 thisPos = m_segmentArray[i][count].CurrentPosition() ;
					Vector3 nextPos = m_segmentArray[i + 1][count].CurrentPosition() ;
					Vector3 nextPos2 = m_segmentArray[i][count + 1].CurrentPosition() ;
					
					glVertex3f(thisPos.X , thisPos.Y ,thisPos.Z);
					glVertex3f(nextPos.X ,nextPos.Y,nextPos.Z);

					glVertex3f(thisPos.X, thisPos.Y ,thisPos.Z);
					glVertex3f(nextPos2.X,nextPos2.Y,nextPos2.Z);
			}
		}
	}
	glEnd(); // end drawing lines
}

// draw the trampoline as a continuous piece of cloth
void Trampoline::DrawCloth()
{
	glEnable(GL_TEXTURE_2D);
	glEnable ( GL_LIGHTING ) ;
	glBindTexture(GL_TEXTURE_2D, m_clothTexture);

	glBegin(GL_QUADS);

	// draw quads
	for(int i =0; i<ROWS ; i++)
	{
		for(int count = 0; count < COLUMNS; count++)
		{
			// if its active
			if(m_segmentArray[i][count].GetSimObjectType() == ACTIVE)
			{
				Vector3 pos1 = m_segmentArray[i][count].CurrentPosition();
				Vector3 pos2 = m_segmentArray[i + 1][count].CurrentPosition();
				Vector3 pos3 = m_segmentArray[i + 1][count + 1].CurrentPosition();
				Vector3 pos4 = m_segmentArray[i][count + 1].CurrentPosition();

				Vector3 normal1 = CalcNormal(pos1,pos2,pos3);

				glTexCoord2i(0,0); glNormal3f(normal1.X,normal1.Y,normal1.Z); glVertex3f(pos1.X , pos1.Y , pos1.Z); 
				glTexCoord2i(0,1); glNormal3f(normal1.X,normal1.Y,normal1.Z); glVertex3f(pos2.X , pos2.Y , pos2.Z);
				glTexCoord2i(1,1); glNormal3f(normal1.X,normal1.Y,normal1.Z); glVertex3f(pos3.X , pos3.Y , pos3.Z);
				glTexCoord2i(1,0); glNormal3f(normal1.X,normal1.Y,normal1.Z); glVertex3f(pos4.X , pos4.Y , pos4.Z);
			}

			// if its passive (the frame)
			else
			{
				//m_segmentArray[i][count].GetModel()->Draw();
			}
		}
	}
	glEnd(); // end drawing quads

	glDisable ( GL_LIGHTING ) ;
}

// draw the collision planes of the trampoline
void Trampoline::DrawCollisionPlanes()
{
	// draw the collision quads
	glBindTexture(GL_TEXTURE_2D, m_metalTexture);
	glBegin(GL_QUADS);

	for(int i =0; i<ROWS ; i++)
	{
		for(int count = 0; count < COLUMNS ; count++)
		{
			m_segmentArray[i][count].GetModel()->Draw();
		}
	}

	glEnd();
}

void Trampoline::ApplyChanges()
{
	list<Spring *>::iterator current = Simulation::Springs()->begin();

	for(; current != Simulation::Springs()->end() ; current++)
	{
		(*current)->SetDamping(m_damping);
		(*current)->SetStiffness(m_stiffness);
		(*current)->SetRestLength(m_restLength);
	}
}

Vector3 Trampoline::CalculateTotalForce()
{
	Vector3 totalForce = Vector3(0,0,0);

	for(int i = 0; i < ROWS; i++)
	{
		for(int count = 0; count < COLUMNS; count++)
		{
			totalForce += m_segmentArray[i][count].ResultantForce();
		}
	}

	return totalForce;
}

void Trampoline::ResolveCollisions(SimModel * simObject)
{
	Vector3 collisionForce(0,0,0); // the total colliding force
	int numCollisions = 0;// the number of collisions made
	for(int i = 0; i < ROWS; i++)
	{
		for(int count = 0; count < COLUMNS; count++)
		{
			if(m_segmentArray[i][count].GetSimObjectType() == ACTIVE)
			{
				Vector3 segPos = m_segmentArray[i][count].CurrentPosition();
				Vector3 objPos = simObject->CurrentPosition();

				float segLeft = segPos.X - m_segWidth/2;
				float segRight = segPos.X + m_segWidth/2;
				float segTop = segPos.Z + m_segWidth/2;
				float segBottom = segPos.Z - m_segWidth/2;
				float objWidth = simObject->GetModel()->m_width;
				
				// there is a collision
				if(segPos.Distance(objPos) < objWidth + 1 ||
				   (simObject->CurrentX() < segRight &&
				   simObject->CurrentX() > segLeft &&
				   simObject->CurrentZ() > segBottom &&
				   simObject->CurrentZ() < segTop &&
				   simObject->CurrentY()- objWidth < segPos.Y))
				{
					Vector3 segForce = m_segmentArray[i][count].ResultantForce();
					Vector3 objForce = simObject->ResultantForce();
					
					//if(simObject->CurrentVelocity().Dot(Vector3(0,1,0)) < 0)
					//{
						
						if(objPos.Y < segPos.Y && objForce.Y < 0)
						{
							//bool brkpt = true;
							simObject->SetCurrentY(segPos.Y + objWidth / 10);
						}
						if(objForce.Length() > 1)
						{
							collisionForce += (segForce * 1.2);

							m_segmentArray[i][count].SetResultantForce((objForce * 1.2));	
						}
						else
						{
							//collisionForce += (segForce * 1.2);
							
							//m_segmentArray[i][count].SetCurrentVelocity(m_segmentArray[i][count].CurrentVelocity() * 0.5);

							//m_segmentArray[i][count].SetCurrentVelocity(Vector3(0,0,0));

							//m_segmentArray[i][count].SetResultantForce(Vector3(0,0,0));
						}
					//}

					numCollisions++;
				}
			}
		}// end of inner for

	}// end of outer for

	if(numCollisions > 0)
	{
		/*collisionForce.X = collisionForce.X / numCollisions;
		collisionForce.Y = collisionForce.Y / numCollisions;
		collisionForce.Z = collisionForce.Z / numCollisions;*/

		
		if(collisionForce.Length() > 1 && collisionForce.Y > 0)
		{
			simObject->SetResultantForce(collisionForce);
		}
		else
		{
			//simObject->SetCurrentVelocity(Vector3(0,0,0));
			simObject->SetResultantForce(Vector3(0,9.81,0));

			//simObject->SetCurrentVelocity(simObject->CurrentVelocity() * 0.5);
		}
		
	}
	
}

Vector3 Trampoline::CalcNormal(Vector3 p1, Vector3 p2, Vector3 p3)
{
	Vector3 v1, v2;

	// calculate 2 vectors lying on the surface
	v1 = p2 - p1;
	v2 = p3 -p2;


	// calculate cross product of two vectors
	Vector3 result = v1.Cross(v2);
	
	// make unit length
	result.Normalise();

	return result;
}


