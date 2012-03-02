#include "sceneprovider.h"


SceneProvider* SceneProvider::instance = 0;

GLMesh* SceneProvider::createCube() {

	return 0;
}

SceneProvider& SceneProvider::getInstance() {
	if (!instance)
		instance = new SceneProvider();
	return *instance;
}


