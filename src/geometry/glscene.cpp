#include "glscene.h"

//#define GL_GLEXT_PROTOTYPES


BEGIN_PV_NAMESPACE

extern double shared;
extern pthread_rwlock_t lock;

GLScene::GLScene():m_renderType(DISPLAYLIST) {
}

GLScene::~GLScene() {
	destroy();
}

void GLScene::init() {
	if(m_renderType==IMMEDIATE||m_renderType==DISPLAYLISTS)
	{
		for (int i = 0; i < m_vmeshes.size(); i++)
		m_vmeshes[i]->init();
	}
	else if(m_renderType==DISPLAYLIST)
	{
		m_listID = glGenLists(1);
	}
}

void GLScene::destroy() {
	if(m_renderType==IMMEDIATE||m_renderType==DISPLAYLISTS)
	{
		for (int i = 0; i < m_vmeshes.size(); i++)
		m_vmeshes[i]->destroy();
	}
	else if(m_renderType==DISPLAYLIST && m_listID != 0)
	{
		glDeleteLists(m_listID, 1);
	}
}

void GLScene::updateGL() {
	if(m_renderType==IMMEDIATE||m_renderType==DISPLAYLISTS)
	{
		for (int i = 0; i < m_vmeshes.size(); i++)
		m_vmeshes[i]->updateGL();
	}
	else if(m_renderType==DISPLAYLIST)
	{
		glNewList(m_listID, GL_COMPILE);
		for (int i = 0; i < m_vmeshes.size(); i++)
		m_vmeshes[i]->drawImmediate();
		glEndList();
	}
}

void GLScene::drawGL() const {
	if(m_renderType==IMMEDIATE||m_renderType==DISPLAYLISTS)
	{
		for (int i = 0; i < m_vmeshes.size(); i++)
		m_vmeshes[i]->drawGL();
	}
	else if(m_renderType==DISPLAYLIST)
	{
		glCallList(m_listID);
	}
}

void GLScene::clear() {
	if(m_renderType==IMMEDIATE||m_renderType==DISPLAYLISTS)
	{
		for (int i = 0; i < m_vmeshes.size(); i++)
		m_vmeshes[i]->clear();
	}
	else if(m_renderType==DISPLAYLIST)
	{
		glDeleteLists(m_listID, 1);
	}
}

void GLScene::add( Renderable* mesh) {

	if(m_renderType==IMMEDIATE||m_renderType==DISPLAYLIST)
	mesh->setMode(Renderable::IMMEDIATE);
	else if(m_renderType==DISPLAYLISTS)
	mesh->setMode(Renderable::DISPLAYLIST);

	m_vmeshes.push_back(mesh);
}

std::vector<Renderable*> GLScene::getRenderables() {
	return m_vmeshes;
}

END_PV_NAMESPACE
