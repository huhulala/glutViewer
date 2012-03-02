#ifndef PV_GLUTCAMERA_H
#define PV_GLUTCAMERA_H

#include <GL/glut.h>

#include "camera.h"
#include "../base/types/types.h"
#include "../base/math/mat4.h"
#include "../base/math/vec2.h"
#include "../base/math/vec3.h"

BEGIN_PV_NAMESPACE

//! This class represents a virtual camera
class GlutCamera:public Camera
{
public:
	//! Define a type for the parent class
	typedef Camera Inherited;

	GlutCamera();
	virtual ~GlutCamera();

	void lookAtScene();

	void project(IVec2& viewSize) ;

protected:


private:

};

END_PV_NAMESPACE

#endif

