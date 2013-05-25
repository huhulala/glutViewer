#include "grid.h"
#include <GL/glut.h>

BEGIN_PV_NAMESPACE

Grid::Grid(Float size): m_size(size) {
}

void Grid::drawGL()const {
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
	int size=10;
	for (int i = -size; i <= size; ++i) {

		glColor3f(0.3, 0.3, 0.3);
		glNormal3f(1., 0., 0.);
		glVertex3f(-size, 0., i);
		glVertex3f(size, 0., i);

		glNormal3f(0., 0., 1.);
		glVertex3f(i, 0., size);
		glVertex3f(i, 0., -size);
	}

	glColor3f(0.3, 0.3, 0.3);
	glNormal3f(1., 0., 0.);
	glVertex3f(0, 3., 0);
	glVertex3f(0, 0., 0);

	glEnd();

	glPopMatrix();
	glPopAttrib();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

END_PV_NAMESPACE
