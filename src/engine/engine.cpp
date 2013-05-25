#include "engine.h"
#include "../opengl/pbuffer.h"

BEGIN_PV_NAMESPACE

Engine* Engine::instance = 0;

Engine& Engine::getInstance() {
	if (!instance)
	instance = new Engine();
	return *instance;
}

Engine::Engine():m_vpCnt(0),m_activeViewport(NULL) {

}

Int Engine::create3DViewport(String name,IVec2& position, IVec2& viewSize) {

	m_vpCnt++;

	pv::Engine engine = pv::Engine::getInstance();
	GlutManager glutMaster = GlutManager::getInstance();
	pv::GLRenderViewport3D * vp = new pv::GLRenderViewport3D(&glutMaster,
			viewSize[0], viewSize[1], position[0], position[1], name.c_str());

	m_3dviewportNameMap[name]=vp;
	m_3dviewportIdMap[m_vpCnt]=vp;
	return m_vpCnt;
}

void Engine::startMainLoop() {

	GlutManager glutMaster = GlutManager::getInstance();
	glutMaster.CallGlutMainLoop();
	glutMaster.glversion();
}

Int Engine::create2DViewport(String name,IVec2& position, IVec2& viewSize) {

	m_vpCnt++;

	pv::Engine engine = pv::Engine::getInstance();
	GlutManager glutMaster = GlutManager::getInstance();
	pv::GLRenderViewport2D * vp = new pv::GLRenderViewport2D(m_vpCnt,&glutMaster,
			viewSize[0], viewSize[1], position[0], position[1], name.c_str());

	m_2dviewportNameMap[name]=vp;
	m_2dviewportIdMap[m_vpCnt]=vp;
	return m_vpCnt;
}

//! Returns viewport
GLRenderViewport3D* Engine::viewport(String name) {

}

//! Returns viewport
GLRenderViewport3D* Engine::viewport(Int id) {

}

//! Returns viewport
GLRenderViewport3D* Engine::activeViewport() {
	if(m_activeViewport)
	return m_activeViewport;
}

//! Returns viewport
vector<GLRenderViewport3D*>::iterator Engine::viewports() {

}

Bool Engine::renderViewportCapture(int viewport){

}

END_PV_NAMESPACE
