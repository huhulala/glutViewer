#include "glmesh.h"

BEGIN_PV_NAMESPACE

GLMesh::GLMesh() :
	m_mode(IMMEDIATE) {
}

GLMesh::~GLMesh() {
	destroy();
}

void GLMesh::init() {
	if (m_mode)
		m_listID = glGenLists(1);
}

void GLMesh::destroy() {
	if (m_mode == DISPLAYLIST && m_listID != 0)
		glDeleteLists(m_listID, 1);
}

void GLMesh::updateGL() {
	if (m_mode == DISPLAYLIST) {
		glNewList(m_listID, GL_COMPILE);
		drawImmediate();
		glEndList();
	} else if (m_mode == IMMEDIATE) {
		drawImmediate();
	}
}

void GLMesh::drawImmediate() const {


}

void GLMesh::drawGL() const {
	if (m_mode == DISPLAYLIST)
		glCallList(m_listID);
	else if (m_mode == IMMEDIATE)
		drawImmediate();
}

void GLMesh::clear() {
	if (m_mode == DISPLAYLIST)
		glDeleteLists(m_listID, 1);
}

END_PV_NAMESPACE
