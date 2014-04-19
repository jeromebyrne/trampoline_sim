#include "precompiled.h"
#include "SphereModel.h"

SphereModel::SphereModel(float x, float y , float z, float width , float height , float breadth , int texture)
: Model(x,y,z,width,height,breadth,texture)
{
}

SphereModel::~SphereModel(void)
{
}
void SphereModel::Draw()
{
	// start lighting
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { -1.0, 1.0, 1.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// end lighting

	gluQuadricTexture(m_obj,GL_TRUE); // turn on texture coordinates for the quartic objecr
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glPushMatrix();

	glTranslatef(m_position.X, m_position.Y,m_position.Z);
	gluSphere(m_obj,m_width,15,15);

	glPopMatrix();

	glDisable ( GL_LIGHTING ) ; // end lighting
}
