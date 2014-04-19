#include "precompiled.h"
#include "Model.h"

Model::Model(float x , float y , float z , float width , float height, float breadth, int texture ):m_position(x,y,z),m_width(width),
			m_height(height), m_texture(texture), m_breadth(breadth), m_obj(gluNewQuadric())
{
	m_vertices[0] = Vector3(m_position.X - m_width/2, m_position.Y , m_position.Z - m_breadth/2);
	m_vertices[1] = Vector3(m_position.X + m_width/2, m_position.Y , m_position.Z - m_breadth/2);
	m_vertices[2] = Vector3(m_position.X + m_width/2, m_position.Y , m_position.Z + m_breadth/2);
	m_vertices[3] = Vector3(m_position.X - m_width/2, m_position.Y , m_position.Z + m_breadth/2);
}

Model::~Model(void)
{
}

// draws a sphere by default
void Model::Draw()
{

		//glBindTexture(GL_TEXTURE_2D, m_texture);
;
		m_vertices[0] = Vector3(m_position.X - m_width/2, m_position.Y , m_position.Z - m_breadth/2);
		m_vertices[1] = Vector3(m_position.X + m_width/2, m_position.Y , m_position.Z - m_breadth/2);
		m_vertices[2] = Vector3(m_position.X + m_width/2, m_position.Y , m_position.Z + m_breadth/2);
		m_vertices[3] = Vector3(m_position.X - m_width/2, m_position.Y , m_position.Z + m_breadth/2);
				
		glTexCoord2i(0,0); glVertex3f(m_vertices[0].X, m_vertices[0].Y , m_vertices[0].Z);
		glTexCoord2i(0,1); glVertex3f(m_vertices[1].X, m_vertices[1].Y , m_vertices[1].Z);
		glTexCoord2i(1,1); glVertex3f(m_vertices[2].X, m_vertices[2].Y , m_vertices[2].Z);
		glTexCoord2i(1,0); glVertex3f(m_vertices[3].X, m_vertices[3].Y , m_vertices[3].Z);
			
}
