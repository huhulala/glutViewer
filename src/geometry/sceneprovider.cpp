#include "sceneprovider.h"

BEGIN_PV_NAMESPACE

SceneProvider* SceneProvider::instance = 0;

GLMesh* SceneProvider::createCube() {

	return 0;
}

SceneProvider& SceneProvider::getInstance() {
	if (!instance)
	instance = new SceneProvider();
	return *instance;
}

GLScene* SceneProvider::getScene() {
	return m_scene;
}

SceneProvider::SceneProvider() {

	m_scene = new GLScene();
	int count = 5;
	int finalCount = 0;
	for (int i = -count; i < count; ++i) {
		for (int j = -count; j < count; ++j) {
			finalCount ++;
			FVec3 extends = FVec3(0.3,0.02,0.3);
			FVec3 pos = FVec3(i,0,j);
			Box* wcs = new Box(pos,extends);
			m_scene->add(wcs);
		}
	}
	cout<<"elements: "<<finalCount<<endl;

}

END_PV_NAMESPACE
