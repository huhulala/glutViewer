#include "box.h"

BEGIN_PV_NAMESPACE

Box::Box(FVec3 pos,FVec3 extend):m_center(pos),m_halfExtend(extend) {
}

Box::~Box() {
	destroy();
}

void Box::init() {
	if (Inherited::m_renderType==DISPLAYLIST)
	m_listID = glGenLists(1);
}

void Box::destroy() {
	if (Inherited::m_renderType == DISPLAYLIST && m_listID != 0)
	glDeleteLists(m_listID, 1);
}

void Box::updateGL() {
	if (Inherited::m_renderType == DISPLAYLIST) {
		glNewList(m_listID, GL_COMPILE);
		drawImmediate();
		glEndList();
	} else if (Inherited::m_renderType == IMMEDIATE) {
		drawImmediate();
	}
}

void Box::drawImmediate() const {

	glPushMatrix();

	GLfloat mat_diffuse[] = {1.0, 0.3, 0.3, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glTranslatef(m_center[0],m_center[1],m_center[2]);

	// Draw the cube Using quads
	glBegin(GL_QUADS);

	glNormal3d(0, 1, 0);
	glVertex3f(m_halfExtend[0],m_halfExtend[1],-m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], m_halfExtend[1], -m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], m_halfExtend[1], m_halfExtend[2]);
	glVertex3f(m_halfExtend[0],m_halfExtend[1], m_halfExtend[2]);

	glNormal3d(0, -1, 0);
	glVertex3f(m_halfExtend[0], -m_halfExtend[1], m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], -m_halfExtend[1], m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], -m_halfExtend[1], -m_halfExtend[2]);
	glVertex3f(m_halfExtend[0], -m_halfExtend[1], -m_halfExtend[2]);

	glNormal3d(0, 0, 1);
	glVertex3f(m_halfExtend[0], m_halfExtend[1], m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], m_halfExtend[1], m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], -m_halfExtend[1],m_halfExtend[2]);
	glVertex3f(m_halfExtend[0], -m_halfExtend[1], m_halfExtend[2]);

	glNormal3d(0, 0, -1);
	glVertex3f(m_halfExtend[0], -m_halfExtend[1], -m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], -m_halfExtend[1], -m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], m_halfExtend[1], -m_halfExtend[2]);
	glVertex3f(m_halfExtend[0], m_halfExtend[1], -m_halfExtend[2]);

	glNormal3d(1, 0, 0);
	glVertex3f(-m_halfExtend[0], m_halfExtend[1], m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], m_halfExtend[1], -m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], -m_halfExtend[1], -m_halfExtend[2]);
	glVertex3f(-m_halfExtend[0], -m_halfExtend[1], m_halfExtend[2]);

	glNormal3d(-1, 0, 0);
	glVertex3f(m_halfExtend[0], m_halfExtend[1], -m_halfExtend[2]);
	glVertex3f(m_halfExtend[0], m_halfExtend[1], m_halfExtend[2]);
	glVertex3f(m_halfExtend[0], -m_halfExtend[1], m_halfExtend[2]);
	glVertex3f(m_halfExtend[0], -m_halfExtend[1], -m_halfExtend[2]);

	glEnd();

	glPopMatrix();

}

const FVec3 Box::center() {
	return m_center;
}

const FVec3 Box::extend() {
	return m_halfExtend;
}

void Box::drawGL() const {

	float color1[4] = {0.6, 0.3, 1.0, 1};
	glColor4fv(color1); // set  color

	if (Inherited::m_renderType == DISPLAYLIST)
	glCallList(m_listID);
	else if (Inherited::m_renderType == IMMEDIATE)
	drawImmediate();
}

void Box::clear() {
	if (Inherited::m_renderType == DISPLAYLIST)
	glDeleteLists(m_listID, 1);
}

END_PV_NAMESPACE
