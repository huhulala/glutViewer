#include "glutcamera.h"
#include <iostream>

BEGIN_PV_NAMESPACE

GlutCamera::GlutCamera()
{


}

GlutCamera::~GlutCamera() {

}

void GlutCamera::lookAtScene() {

	gluLookAt(Inherited::eye()[0], Inherited::eye()[1], Inherited::eye()[2],
			Inherited::center()[0], Inherited::center()[1], Inherited::center()[2],
			Inherited::up()[0], Inherited::up()[1], Inherited::up()[2]);

}

void GlutCamera::project(IVec2& viewSize) {

	Inherited::setImageSize(viewSize[0],viewSize[1]);



	//FVec2 sample = FVec2(viewSize[0],viewSize[1]);
	//FMat4 projection = Inherited::projection(viewSize,sample);

	glViewport(0, 0, viewSize[0], viewSize[1]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Float f = Inherited::fov();
	std::cout<<f<<endl;

	//glLoadMatrixf(projection); Inherited::fov()
	gluPerspective(f, (float)viewSize[0] / viewSize[1], Inherited::frustrum()[0], Inherited::frustrum()[1]);
}

END_PV_NAMESPACE
