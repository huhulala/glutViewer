#ifndef GEOMETRYPROVIDER_H_
#define GEOMETRYPROVIDER_H_

#include "glmesh.h"

class SceneProvider {
public:

	//Get singleton instance
	static SceneProvider& getInstance();

	//! Creates a cube
	GLMesh* createCube();

protected:
private:
	//! the instance
	static SceneProvider* instance;

	//! Private Constructor
	SceneProvider() {
	}

};

#endif /* GEOMETRYPROVIDER_H_ */
