/*
 * glutwindow.cpp
 *
 *  Created on: 19.02.2012
 *      Author: philipp
 */

#include "glutviewport.h"

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
