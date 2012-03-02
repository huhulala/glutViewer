#include "grid.h".h"
#include <GL/glut.h>

BEGIN_PV_NAMESPACE

Grid::Grid(Float size): m_size(size) {
}

void Grid::draw() {
	//if (is_hidden)
	//	return;

	glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);

	glPushAttrib( GL_ENABLE_BIT);
	glDisable( GL_BLEND);
	glPushMatrix();
	//glTranslated(-1.3, -1.3, -1.3);
	glBegin( GL_LINES);
	// x: red
	glColor3f(1.0, 0.0, 0.0);
	glNormal3f(1., 0., 0.);
	glVertex3f(0., 0., 0.);
	glVertex3f(m_size, 0., 0.);
	// y: green
	glColor3f(0.0, 1.0, 0.0);
	glNormal3f(0., 1., 0.);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., m_size, 0.);
	// z: blue
	glColor3f(0.0, 0.0, 1.0);
	glNormal3f(0., 0., 1.);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., 0.,m_size);
	glEnd();



	glPopMatrix();
	glPopAttrib();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

END_PV_NAMESPACE
