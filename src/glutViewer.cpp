//============================================================================
// Name        : glutViewer.cpp
// Author      : phu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include <GL/glut.h>

#include "viewport/glutmanager.h"
#include "viewport/glutviewport.h"
#include "viewport/glrenderviewport.h"

GlutManager * glutMaster;
pv::GLRenderViewport * firstWindow = 0;
pv::GLRenderViewport * secondWindow = 0;

using namespace std;

int main(int argc, char **argv) {

	GlutManager glutMaster = GlutManager::getInstance();
	firstWindow = new pv::GLRenderViewport(&glutMaster, 640, 480, 200, 100,
			"Placer Viewer");

	glutMaster.glversion();
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	if (GLEW_ARB_vertex_program)
	{
	  /* It is safe to use the ARB_vertex_program extension here. */
		printf("GLEW_ARB_vertex_program ");
	}

	firstWindow->StartIdle(&glutMaster); // enable idle function
	glutMaster.CallGlutMainLoop();

	cout << "GlutViewport1" << endl; // prints lala
	return 0;
}
