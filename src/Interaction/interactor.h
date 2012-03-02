#ifndef PV_INTERACTOR_H_
#define PV_INTERACTOR_H_

#include <GL/glut.h>

#include "../base/types/types.h"
#include "../base/math/mat4.h"
#include "../base/math/vec2.h"
#include "../base/math/vec3.h"

BEGIN_PV_NAMESPACE

//! This class represents an abstract interactor. I
// It manages the mouse/camera  interaction.
class Interactor
{
public:
	Interactor();
	virtual ~Interactor();
private:
	//! The camera projecting the scene
	Camera* m_camera;

};

#endif /* INTERACTOR_H_ */
