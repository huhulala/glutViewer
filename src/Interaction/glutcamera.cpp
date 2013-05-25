#include "glutcamera.h"
#include <iostream>

BEGIN_PV_NAMESPACE

GlutCamera::GlutCamera()
{

}

GlutCamera::~GlutCamera() {

}

void GlutCamera::lookAtScene() {

	//if(Inherited::projectionMode()==PERSPECTIVE)
	  gluLookAt(Inherited::eye()[0], Inherited::eye()[1], Inherited::eye()[2],
			  Inherited::center()[0], Inherited::center()[1], Inherited::center()[2],
			  Inherited::up()[0], Inherited::up()[1], Inherited::up()[2]);

}

void GlutCamera::project(IVec2& viewSize) {

	// perspective projection
	if(Inherited::projectionMode()==PERSPECTIVE) {

		Inherited::setImageSize(viewSize[0],viewSize[1]);

		//FVec2 sample = FVec2(viewSize[0],viewSize[1]);
		//FMat4 projection = Inherited::projection(viewSize,sample);

		glViewport(0, 0, viewSize[0], viewSize[1]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		Float f = Inherited::fov();

		//glLoadMatrixf(projection); Inherited::fov()
		gluPerspective(f, (float)viewSize[0] / viewSize[1], Inherited::frustrum()[0], Inherited::frustrum()[1]);

	}

	// orthographic projection
	if(Inherited::projectionMode()==ORTHO2D) {

		std::cout<<viewSize[0]<<" "<<viewSize[1]<<std::endl;

		Inherited::setImageSize(viewSize[0],viewSize[1]);

		//FVec2 sample = FVec2(viewSize[0],viewSize[1]);
		//FMat4 projection = Inherited::projection(viewSize,sample);

		//glViewport(0, 0, viewSize[0], viewSize[1]);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//Float f = Inherited::fov();

		//glLoadMatrixf(projection); Inherited::fov()
		// set up an orthographic projection with the same near clip plane
		//glOrtho(0, viewSize[0] ,0 ,viewSize[1], -10, 10);

		//glOrtho((float)viewSize[0] / viewSize[1], Inherited::frustrum()[0], Inherited::frustrum()[1]);
		glOrtho(0.0f, viewSize[0], viewSize[1], 0.0f, 0.0f, 1000.0f);
		//gluLookAt (0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 100.0, -100.0);
	}

}

END_PV_NAMESPACE
