#ifndef GEOMETRYPROVIDER_H_
#define GEOMETRYPROVIDER_H_

#include "renderable.h"
#include "glmesh.h"
#include "glscene.h"
#include "drawables/box.h"
#include "../base/types/types.h"

BEGIN_PV_NAMESPACE

class SceneProvider {
public:

	//Get singleton instance
	static SceneProvider& getInstance();

	//! Creates a cube
	GLMesh* createCube();

	//! Creates a cube
	GLScene* getScene();

protected:
private:
	//! the instance
	static SceneProvider* instance;

	//! Private Constructor
	SceneProvider();

	//! The scene
	GLScene* m_scene;

};

END_PV_NAMESPACE

#endif /* GEOMETRYPROVIDER_H_ */
