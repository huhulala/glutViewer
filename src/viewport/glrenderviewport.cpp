#include "glrenderviewport.h"
#include "../geometry/drawables/coordinateAxisLines.h"
#include <iostream>

BEGIN_PV_NAMESPACE

GLRenderViewport::GLRenderViewport(GlutManager * glutManager, int setWidth,
		int setHeight, int setInitPositionX, int setInitPositionY, char * title)
:m_arcballOn(false),m_panOn(false),m_rotateOn(false),m_cameraLightning(true) {

	m_camera = new GlutCamera();
	m_camera->setCenter(0,0,-1);
	m_camera->setUp(0,1,0);

	m_lightPos[0]=0;
	m_lightPos[1]=0;
	m_lightPos[2]=0;

	m_width = setWidth;
	m_height = setHeight;

	m_initPositionX = setInitPositionX;
	m_initPositionY = setInitPositionY;

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(m_width, m_height);
	glutInitWindowPosition(m_initPositionX, m_initPositionY);

	// This may have to be moved to after the next line on some platforms
	glViewport(0, 0, m_width, m_height);

	glutManager->CallGlutCreateWindow(title, this);

	//SBglMatrixMode(GL_PROJECTION);
	///glOrtho(-80.0, 80.0, -80.0, 80.0, -500.0, 500.0);

	glEnable(GL_DEPTH_TEST);

	//glRotatef(60, 1, 1, 1);
	glColor4f(1.0, 0.0, 0.0, 1.0);
}

GLRenderViewport::~GLRenderViewport() {

	glutDestroyWindow(windowID);
}

void DrawCubeFace(float fSize)
{
	fSize /= 2.0;
	glBegin(GL_QUADS);
	glVertex3f(-fSize, -fSize, fSize); glTexCoord2f (0, 0);
	glVertex3f(fSize, -fSize, fSize); glTexCoord2f (1, 0);
	glVertex3f(fSize, fSize, fSize); glTexCoord2f (1, 1);
	glVertex3f(-fSize, fSize, fSize); glTexCoord2f (0, 1);
	glEnd();
}

void DrawWorldCoordinates (float fSize)
{
	/*
	 glPushMatrix();
	 glBegin(GL_LINES);
	 glVertex3f(-2,0,0);
	 glVertex3f(2,0,0);
	 glEnd;
	 glPopMatrix();
	 */
	float colorBronzeSpec[4] = {1.0, 1.0, 0.4, 1.0};
	float colorBlue[4] = {0.0, 0.2, 1.0, 1.0};
	float colorNone[4] = {0.0, 0.0, 0.0, 0.0};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colorBlue);
	glColor4fv(colorBlue);

	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor4fv(colorBlue);
	glVertex3f( 0, fSize,0);
	glVertex3f( 0,-fSize,0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor4fv(colorBlue);
	glVertex3f( fSize,0,0);
	glVertex3f( -fSize,0,0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glLineWidth(3);
	glColor4fv(colorBlue);
	glBegin(GL_LINES);
	glVertex3f( 0,0,fSize);
	glVertex3f( 0,0,-fSize);
	glEnd();
	glPopMatrix();

	// glDisable(GL_BLEND);
	// glEnable(GL_TEXTURE_2D);
}

void DrawCubeWithTextureCoords (float fSize)
{
	/*
	 glPushMatrix();
	 glBegin(GL_LINES);
	 glVertex3f(-2,0,0);
	 glVertex3f(2,0,0);
	 glEnd;
	 glPopMatrix();
	 */

	glPushMatrix();
	DrawCubeFace (fSize);
	glRotatef (90, 1, 0, 0);
	DrawCubeFace (fSize);
	glRotatef (90, 1, 0, 0);
	DrawCubeFace (fSize);
	glRotatef (90, 1, 0, 0);
	DrawCubeFace (fSize);
	glRotatef (90, 0, 1, 0);
	DrawCubeFace (fSize);
	glRotatef (180, 0, 1, 0);
	DrawCubeFace (fSize);
	glPopMatrix();
}

int i;
#define VIEWING_DISTANCE_MIN  1.5
#define TEXTURE_ID_CUBE 1
//static Float g_fViewDistance = 3 * VIEWING_DISTANCE_MIN;

static GLfloat g_fTeapotAngle = 0.0;
static GLfloat g_fTeapotAngle2 = 0.0;

void RenderObjects(void)
{
	float colorBronzeDiff[4] = {0.8, 0.6, 0.0, 1.0};
	float colorBronzeSpec[4] = {1.0, 1.0, 0.4, 1.0};
	float colorBlue[4] = {0.0, 0.2, 1.0, 1.0};
	float colorNone[4] = {0.0, 0.0, 0.0, 0.0};
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Main object (cube) ... transform to its coordinates, and render

	//glRotatef(15, 1, 0, 0);
	//glRotatef(45, 0, 1, 0);
	//glRotatef(g_fTeapotAngle, 0, 0, 1);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);


	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
	glColor4fv(colorBlue);

	//glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
	DrawCubeWithTextureCoords(1.0);
	// Child object (teapot) ... relative transform, and render
	glPushMatrix();
	glTranslatef(2, 0, 0);
	glRotatef(g_fTeapotAngle2, 1, 1, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	glColor4fv(colorBronzeDiff);
	glBindTexture(GL_TEXTURE_2D, 0);
	glutSolidTeapot(0.3);
	glPopMatrix();
	glPopMatrix();
}

void GLRenderViewport::configureLightning() {

	if(m_cameraLightning) {
		m_lightPos[0]=m_camera->eye()[0];
		m_lightPos[1]=m_camera->eye()[1];
		m_lightPos[2]=m_camera->eye()[2];
	}

	GLfloat lmodel_ambient[] = {0.4, 0.4, 0.4, 1.0};
	GLfloat local_view[] = {1.0};
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	//glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, local_view);

	float g_lightPos[4] = {m_lightPos[0], m_lightPos[1], m_lightPos[2], 1};
	glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);
}

void GLRenderViewport::renderViewportGeometry() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//DrawWorldCoordinates(10.0f);

	CoordinateAxisLines wcs = CoordinateAxisLines(1.0f);
	wcs.drawGL();

	glPopMatrix();
}

void GLRenderViewport::CallBackDisplayFunc(void) {

	i++;
	cout << "frame: " <<i<< endl;

	//m_camera->calculateNormal();

	//m_camera->setEye(0.0f,0.0f,-g_fViewDistance);

	// Clear frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set up viewing transformation, looking down -Z axis
	glLoadIdentity();

	//m_camera->print();
	m_camera->lookAtScene();

	// Set up the stationary light
	configureLightning();
	// Render the scene
	RenderObjects();
	// Render the scene
	renderViewportGeometry();
	// Make sure changes appear onscreen
	glutSwapBuffers();

	m_camera->calculateNormal();
}

void GLRenderViewport::CallBackReshapeFunc(int w, int h) {

	m_width = w;
	m_height = h;
	IVec2 viewSize = IVec2(w,h);
	m_camera->project(viewSize);

	glMatrixMode(GL_MODELVIEW);
	CallBackDisplayFunc();
}

Float angle = 0.0;
Float delta = 0.0;
Float pitch = 0.0;

void GLRenderViewport::CallBackKeyboardFunc(unsigned char key, int x, int y) {

	cout << "CallBackKeyboardFunc" <<endl;
	switch (key) {
		case 'q':
		glClearColor (1.0, 0.0, 0.0, 0.0);
		break;

		case 'r':
		glClearColor (0.0, 1.0, 0.0, 0.0);
		break;

		case 'a':
		m_camera->moveLeft(0.5);
		break;

		case 'd':
		m_camera->moveRight(0.5);
		break;

		case 'w':
		m_camera->moveUp(0.5);
		break;

		case 'x':
		m_camera->moveDown(0.5);
		break;

		case 'c':
		angle += 0.0005;
		m_camera->zoom(0.9);
		CallBackReshapeFunc(m_width, m_height);
		break;

		case 'v':
		pitch += 0.0005;
		m_camera->zoom(1.1);
		CallBackReshapeFunc(m_width, m_height);
		break;

		case 'b':
		delta += 0.0005;
		m_camera->yaw(delta);
		break;

		case 'e':
		angle -= 0.0005;
		m_camera->roll(angle);
		break;

		case 'f':
		pitch -= 0.0005;
		m_camera->pitch(pitch);
		break;

		case 'g':
		delta -= 0.0005;
		m_camera->yaw(delta);
		break;

		default:
		break;
	}
	glutPostRedisplay();
}

void GLRenderViewport::CallBackIdleFunc(void) {

	//glRotatef(0.25, 1, 1, 2);
	//CallBackDisplayFunc();
}

void GLRenderViewport::StartIdle(GlutManager * glutMaster) {

	glutMaster->SetIdleToCurrentWindow();
	glutMaster->EnableIdleFunction();
}

void GLRenderViewport::CallBackMouseFunc(int button, int state, int x, int y) {

	std::cout << "CallBackMouseFunc" << button<<" "<<state<< std::endl;

	if(button==1 && state==0 ) {
		IVec2 currentPos = IVec2(-x, y);
		m_panOn = true;
		m_mouseStartPos = currentPos;
	} else
	m_panOn = false;

	if(button==0 && state==0 ) {
		IVec2 currentPos = IVec2(x, y);
		m_rotateOn = true;
		m_mouseStartPos = currentPos;
	} else
	m_rotateOn = false;

	if(button==2 && state==0 ) {
		IVec2 currentPos = IVec2(x, y);
		m_zoomOn = true;
		m_mouseStartPos = currentPos;
	} else
	m_zoomOn = false;

	if(button==3)
	m_camera->dolly(0.5);
	if(button==4)
	m_camera->dolly(-0.5);
	CallBackDisplayFunc();
}

void GLRenderViewport::CallBackMotionFunc(int x, int y) {

	if(m_panOn) {

		IVec2 currentPos = IVec2(-x, y);
		IVec2 offset = currentPos - m_mouseStartPos;

		m_camera->pan(1.3f,offset[0],offset[1]);
		CallBackDisplayFunc();
		m_mouseStartPos = currentPos;
	}
	if(m_rotateOn) {

		double sens = ((90.0 - m_camera->fov()) * pow(1.03, 90.0 - m_camera->fov())) + 40.0;

		IVec2 currentPos = IVec2(x, y);
		IVec2 offset = currentPos - m_mouseStartPos;

		m_camera->rotate(sens,offset[0],offset[1]);
		CallBackDisplayFunc();
		m_mouseStartPos = currentPos;
	}
	if(m_zoomOn) {

		//double sens = ((90.0 - m_camera->fov()) * pow(1.03, 90.0 - m_camera->fov())) + 40.0;

		IVec2 currentPos = IVec2(x, y);
		IVec2 offset = currentPos - m_mouseStartPos;

		if(offset[1]>0)
		m_camera->zoom(1.03);
		else
			m_camera->zoom(0.97);

		CallBackReshapeFunc(m_width, m_height);
		CallBackDisplayFunc();
		m_mouseStartPos = currentPos;
	}

}

END_PV_NAMESPACE
