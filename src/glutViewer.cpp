//============================================================================
// Name        : glutViewer.cpp
// Author      : phu
// Version     :
// Copyright   : Your copyright notice
// Description : demo main class
//============================================================================

#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include <GL/glut.h>

#include "viewport/glutmanager.h"
#include "viewport/glutviewport.h"
#include "viewport/glrenderviewport3D.h"

#include "chip/Array.h"
#include "chip/Module.h"

#include "engine/engine.h"

using namespace std;

double shared = 2.4;
pthread_rwlock_t lock;
Array<Module*> *moduleList;

static void* glutThreadFunc(void* v) {


	pthread_rwlock_rdlock(&lock);
	std::cout << shared << std::endl;
	pthread_rwlock_unlock(&lock);

	pv::Engine engine = pv::Engine::getInstance();
	IVec2 pos = IVec2(200, 100);
	IVec2 viewSize = IVec2(640, 480);
	engine.create3DViewport("Placer Viewer 24", pos, viewSize);
}

int main(int argc, char **argv) {

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		//Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	if (GLEW_ARB_vertex_program) {
		// It is safe to use the ARB_vertex_program extension here.
		printf("GLEW_ARB_vertex_program ");
	}

	if (0) {
		pthread_t glutThreadId;
		pthread_create(&glutThreadId, NULL, glutThreadFunc, 0);

		while (true) {
			//cout << "thread runing" << endl;
			sleep(100);
		}
	} else {
		pv::Engine engine = pv::Engine::getInstance();
		IVec2 pos = IVec2(250, 250);
		IVec2 pos1 = IVec2(200, 200);
		IVec2 viewSize = IVec2(640, 480);
		IVec2 viewSize2 = IVec2(120, 120);
		engine.create3DViewport("Glut Viewer 3D", pos1, viewSize);
		engine.create2DViewport("Glut Viewer 2D", pos, viewSize2);
		engine.startMainLoop();

	}
	return 0;
}
