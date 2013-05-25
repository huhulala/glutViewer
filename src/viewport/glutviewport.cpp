/*
 * glutwindow.cpp
 *
 *  Created on: 19.02.2012
 *      Author: philipp
 */

#include "glutviewport.h"
#include "../base/math/mat4.h"
#include <GL/glut.h>

GlutViewport::GlutViewport(void) {

}

GlutViewport::~GlutViewport() {

}

void GlutViewport::CallBackDisplayFunc(void) {
	//dummy function
}

void GlutViewport::CallBackIdleFunc(void) {

	//dummy function
}

void GlutViewport::CallBackKeyboardFunc(unsigned char key, int x, int y) {
	//dummy function
}

void GlutViewport::CallBackMotionFunc(int x, int y) {
	//dummy function
}

void GlutViewport::CallBackMouseFunc(int button, int state, int x, int y) {
	//dummy function
}

void GlutViewport::CallBackPassiveMotionFunc(int x, int y) {
	//dummy function
}

void GlutViewport::CallBackReshapeFunc(int w, int h) {
	//dummy function
}

void GlutViewport::CallBackSpecialFunc(int key, int x, int y) {
	//dummy function
}

void GlutViewport::CallBackVisibilityFunc(int visible) {
	//dummy function
}

void GlutViewport::SetWindowID(int newWindowID) {

	windowID = newWindowID;
}

int GlutViewport::GetWindowID(void) {

	return (windowID);
}

FVec3 GlutViewport::worldToScreen(FVec3 worldPosition){

	FMat4 view = FMat4 ();
	FMat4 projection = FMat4 ();

	glGetFloatv(GL_MODELVIEW_MATRIX, view);
	glGetFloatv(GL_PROJECTION_MATRIX, projection);

	FMat4 viewProj =view * projection;

	FVec3 screen =viewProj.multAffineMatPoint(worldPosition) ;
	return screen;
}
