#include "glrenderviewport3D.h"
#include "../geometry/drawables/coordinateAxisLines.h"
#include "../geometry/drawables/box.h"

#include "../geometry/drawables/chip.h"
#include "../geometry/sceneprovider.h"
#include <time.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <iostream>

BEGIN_PV_NAMESPACE

GLRenderViewport3D::GLRenderViewport3D(GlutManager * glutManager, int setWidth,
		int setHeight, int setInitPositionX, int setInitPositionY,const char * title)
:m_arcballOn(true),m_worldCoordinateSysOn(false),m_chipDrawingOn(false),m_arcballRadius(175),m_panOn(false)
,m_rotateOn(false),m_spinOn(false),m_cameraLightning(false),m_hudOn(true),m_lowerHUD(""),m_backgroundGradientOn(true)
,m_backgroundCol(1.0,1.0,1.0),m_backgroundGradientLowCol(1.0,1.0,1.00)
,m_backgroundGradientUpCol(0.5,0.7,0.70) {

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

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH );
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

	SceneProvider sp = SceneProvider::getInstance();
	m_renderScene = sp.getScene();
	m_renderScene->init();
	m_renderScene->updateGL();

	Chip chip = Chip::getInstance();
	chip.initTextures();
}

void GLRenderViewport3D::CaptureScreenshotBMP() {

	cout<<"captureScreenshot"<<endl;
	glPixelStorei(GL_PACK_ALIGNMENT,1);

	// if (GetForegroundWindow() != m_WindowHandle) return;

	char cFileName[64];
	FILE *fScreenshot;
	int nSize = m_width * m_height * 3;

	GLubyte *pixels = new GLubyte [nSize];
	if (pixels == NULL) return;

	int nShot = 0;
	while (nShot < 64)
	{
		sprintf(cFileName,"screenshot_%d.bmp",nShot);
		fScreenshot = fopen(cFileName,"rb");
		if (fScreenshot == NULL) break;
		else fclose(fScreenshot);

		++nShot;
		if (nShot > 63)
		{
			cout<<"Screenshot limit of 64 reached. Remove some shots if you want to take more."<<endl;
			return;
		}
	}

	fScreenshot = fopen(cFileName,"wb");

	glReadPixels(0, 0, m_width, m_height, GL_RGB,
			GL_UNSIGNED_BYTE, pixels);

}

void GLRenderViewport3D::CaptureScreenshotTGA() {

	cout<<"captureScreenshot"<<endl;
	glPixelStorei(GL_PACK_ALIGNMENT,1);

	// if (GetForegroundWindow() != m_WindowHandle) return;

	char cFileName[64];
	FILE *fScreenshot;
	int nSize = m_width * m_height * 3;

	GLubyte *pixels = new GLubyte [nSize];
	if (pixels == NULL) return;

	int nShot = 0;
	while (nShot < 64)
	{
		sprintf(cFileName,"screenshot_%d.tga",nShot);
		fScreenshot = fopen(cFileName,"rb");
		if (fScreenshot == NULL) break;
		else fclose(fScreenshot);

		++nShot;
		if (nShot > 63)
		{
			cout<<"Screenshot limit of 64 reached. Remove some shots if you want to take more."<<endl;
			return;
		}
	}

	fScreenshot = fopen(cFileName,"wb");

	glReadPixels(0, 0, m_width, m_height, GL_RGB,
			GL_UNSIGNED_BYTE, pixels);

	//convert to BGR format
	unsigned char temp;
	int i = 0;
	while (i < nSize)
	{
		temp = pixels[i]; //grab blue
		pixels[i] = pixels[i+2];//assign red to blue
		pixels[i+2] = temp; //assign blue to red

		i += 3; //skip to next blue byte
	}

	unsigned char TGAheader[12]= {0,0,2,0,0,0,0,0,0,0,0,0};
	unsigned char header[6] = {m_width%256,m_width/256,
		m_height%256,m_height/256,24,0};

	fwrite(TGAheader, sizeof(unsigned char), 12, fScreenshot);
	fwrite(header, sizeof(unsigned char), 6, fScreenshot);
	fwrite(pixels, sizeof(GLubyte), nSize, fScreenshot);
	fclose(fScreenshot);

	delete [] pixels;

	return;
}

/*
 void DrawCircle(float cx, float cy, float r, int num_segments)
 {
 glDisable(GL_LIGHTING);
 //glDisable(GL_DEPTH_TEST);
 glDisable(GL_LIGHT0);
 glDisable(GL_COLOR_MATERIAL);

 glPushAttrib( GL_ENABLE_BIT);
 glDisable( GL_BLEND);
 glPushMatrix();

 float theta = 2 * 3.1415926 / float(num_segments);
 float tangetial_factor = tanf(theta);//calculate the tangential factor

 float radial_factor = cosf(theta);//calculate the radial factor

 float x = r;//we start at angle = 0

 float y = 0;

 glBegin(GL_LINE_LOOP);
 for(int ii = 0; ii < num_segments; ii++)
 {
 glVertex2f(x + cx, y + cy);//output vertex

 //calculate the tangential vector
 //remember, the radial vector is (x, y)
 //to get the tangential vector we flip those coordinates and negate one of them

 float tx = -y;
 float ty = x;

 //add the tangential vector

 x += tx * tangetial_factor;
 y += ty * tangetial_factor;

 //correct using the radial factor

 x *= radial_factor;
 y *= radial_factor;
 }
 glEnd();

 glPopMatrix();
 glPopAttrib();

 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_COLOR_MATERIAL);

 }
 */
GLRenderViewport3D::~GLRenderViewport3D() {

	glutDestroyWindow(windowID);
}

void GLRenderViewport3D::setArballOn(Bool arcballOn) {

	m_arcballOn = arcballOn;
	CallBackDisplayFunc();
}

void GLRenderViewport3D::configureLightning() {

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	if(m_cameraLightning) {
		m_lightPos[0]=m_camera->eye()[0];
		m_lightPos[1]=m_camera->eye()[1];
		m_lightPos[2]=m_camera->eye()[2];
	}

	GLfloat lmodel_ambient[] = {0.4, 0.4, 0.4, 1.0};
	GLfloat local_view[] = {1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, local_view);

	float g_lightPos[4] = {m_lightPos[0], m_lightPos[1], m_lightPos[2], 1};
	glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);
}

void GLRenderViewport3D::renderBackgroundColor() {

	if(m_backgroundGradientOn) {
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_COLOR_MATERIAL);

		//Draw background quad
		glDisable(GL_DEPTH_TEST);
		glMatrixMode (GL_MODELVIEW);
		glPushMatrix ();
		glLoadIdentity ();
		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();
		glLoadIdentity ();
		glBegin (GL_QUADS);
		glColor3f(m_backgroundGradientUpCol[0],m_backgroundGradientUpCol[1],m_backgroundGradientUpCol[2]);
		glVertex3i (-1, -1, -1);
		glVertex3i (1, -1, -1);
		glColor3f(m_backgroundGradientLowCol[0],m_backgroundGradientLowCol[1],m_backgroundGradientLowCol[2]);
		glVertex3i (1, 1, -1);
		glVertex3i (-1, 1, -1);
		glEnd ();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);

		glPopMatrix ();
		glMatrixMode (GL_MODELVIEW);
		glPopMatrix ();

		glPushMatrix();
	} else
	glColor3f(m_backgroundCol[0],m_backgroundCol[1],m_backgroundCol[2]);
}

void GLRenderViewport3D::renderViewportGeometry() {

	render2DDisplay();
	//m_chip.drawGL3D();

	if(m_chipDrawingOn)
	{
		Chip chip = Chip::getInstance();
		chip.drawGL3D();
	}
}

void GLRenderViewport3D::render2DDisplay()
{

	if(m_hudOn) {
		// backup current model-view matrix
		glPushMatrix(); // save current modelview matrix
		glLoadIdentity(); // reset modelview matrix

		// set to 2D orthogonal projection
		glMatrixMode(GL_PROJECTION); // switch to projection matrix
		glPushMatrix(); // save current projection matrix
		glLoadIdentity(); // reset projection matrix
		gluOrtho2D(0, 400, 0, 300); // set to orthogonal projection

		float color[4] = {1, 1, 1, 1};

		stringstream ss;
		//ss << std::fixed << std::setprecision(3);

		// ss << "Display List: " << (dlUsed ? "on" : "off") << ends;
		//drawString(ss.str().c_str(), 1, 286, color, font);
		ss.str("");

		// display elapsed time in millisec
		// ss << "Time: " << timer.getElapsedTimeInMilliSec() << " ms" << ends;
		//drawString(ss.str().c_str(), 1, 272, color, font);
		ss.str("");

		ss << m_lowerHUD << ends;
		void *font = GLUT_BITMAP_8_BY_13;
		drawString(ss.str().c_str(), 1, 1, color, font);

		// restore projection matrix
		glPopMatrix(); // restore to previous projection matrix

		// restore modelview matrix
		glMatrixMode(GL_MODELVIEW); // switch to modelview matrix
		glPopMatrix(); // restore to previous modelview matrix

	}

	drawCircle(m_width/2, m_height/2,m_arcballRadius, 1000);

	if(0) {

		std::cout <<"m_arcballOn"<< endl;

		// backup current model-view matrix
		glPushMatrix(); // save current modelview matrix
		glLoadIdentity(); // reset modelview matrix

		// set to 2D orthogonal projection
		glMatrixMode(GL_PROJECTION); // switch to projection matrix
		glPushMatrix(); // save current projection matrix
		glLoadIdentity(); // reset projection matrix
		gluOrtho2D(0, m_width, 0, m_height); // set to orthogonal projection

		float color1[4] = {m_arcballColor[0], m_arcballColor[1], m_arcballColor[2], 1};
		glColor4fv(color1); // set text color
		drawCircle(m_width/2, m_height/2,m_arcballRadius, 1000);

		// restore projection matrix
		glPopMatrix(); // restore to previous projection matrix

		// restore modelview matrix
		glMatrixMode(GL_MODELVIEW); // switch to modelview matrix
		glPopMatrix(); // restore to previous modelview matrix

	}
}

void GLRenderViewport3D::drawString(const char *str, int x, int y, float color[4], void *font)
{
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
	glDisable(GL_LIGHTING); // need to disable lighting for proper text color

	glColor4fv(color); // set text color
	glRasterPos2i(x, y); // place text position

	// loop all characters in the string
	while(*str)
	{
		glutBitmapCharacter(font, *str);
		++str;
	}

	glEnable(GL_LIGHTING);
	glPopAttrib();
}

void GLRenderViewport3D::drawCircle(float x, float y, float r, int segments)
{
	glDisable(GL_DEPTH_TEST);
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glLoadIdentity ();
	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();
	glLoadIdentity ();

	glBegin(GL_LINES);
	for ( float angle = 0; angle <= 2*3.142; angle+=3.142/30)
	{
		glVertex3f(100.0 * cos (angle) / 2, 0, 100.0 * sin (angle) / 2);
		glVertex3f(100.0 * cos (angle + 3.142/30) / 2, 0, 100.0 * sin (angle + 3.142/30) / 2);
	}
	glEnd();

	glPopMatrix ();
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}

void GLRenderViewport3D::CallBackDisplayFunc(void) {

	// Set up the stationary light
	configureLightning();

	glDisable(GL_TEXTURE_2D);

	// Clear frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	//Render view aligned quad
	renderBackgroundColor();

	// Set up viewing transformation, looking down -Z axis
	m_camera->lookAtScene();

	// Render grid, hud and arcball geometry
	renderViewportGeometry();

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	// Render the scene
	if(m_renderScene)
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	m_renderScene->drawGL();

	if(m_worldCoordinateSysOn) {

		//m_camera->print();

		FVec3 up = m_camera->up();
		up.normalize();

		FVec3 normal = m_camera->normal();
		normal.normalize();

		FVec3 eye = m_camera->eye();
		//eye.normalize();

		std::cout <<"eye: "<<eye[0]<<" "<< eye[1]<<" "<<eye[2]<< endl;

		FVec3 view = m_camera->center()-m_camera->eye();
		FVec3 upper =m_camera->view()^normal;
		upper.normalize();

		std::cout <<"upper: "<<upper[0]<<" "<< upper[1]<<" "<<upper[2]<< endl;

		//FVec3 center = eye - center;


		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0, 0.0f,0);
		glVertex3f(upper[0], upper[1],upper[2]);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0, 0.0f,0);
		glVertex3f(m_camera->normal().normalized()[0], m_camera->normal().normalized()[1],m_camera->normal().normalized()[2]);
		glEnd();

		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0, 0.0f,0);
		glVertex3f(m_camera->up().normalized()[0], m_camera->up().normalized()[1],m_camera->up().normalized()[2]);
		glEnd();

		/*
		 glColor3f(1.0, 1.0, 0.0);
		 glBegin(GL_LINE_STRIP);
		 glVertex3f(-30, 0.0f,0);
		 glVertex3f(30, 0.0f,0);
		 glEnd();

		 glColor3f(0.0, 1.0, 0.0);
		 glBegin(GL_LINE_STRIP);
		 glVertex3f( 0.0f, -30,0);
		 glVertex3f( 0.0f, 30,0);
		 glEnd();

		 glColor3f(1.0, 0.0, 0.0);
		 glBegin(GL_LINE_STRIP);
		 glVertex3f( 0.0f, 0.0f ,-30);
		 glVertex3f( 0.0f, 0.0f ,30);
		 glEnd();
		 */

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

	}

	glPopMatrix();

	// Make sure changes appear onscreen
	glutSwapBuffers();

	//m_camera->calculateNormal();
}

void GLRenderViewport3D::CallBackReshapeFunc(int w, int h) {

	m_width = w;
	m_height = h;

	//set arcball radius
	if(m_width>m_height)
	m_arcballRadius = m_height/2-20;
	else
	m_arcballRadius = m_width/2-20;

	IVec2 viewSize = IVec2(w,h);
	m_camera->project(viewSize);

	glMatrixMode(GL_MODELVIEW);
	CallBackDisplayFunc();
}

void GLRenderViewport3D::CallBackKeyboardFunc(unsigned char key, int x, int y) {

	switch (key) {

		case 's':
		CaptureScreenshotBMP();
		break;

		case 'c':
		m_chipDrawingOn = !m_chipDrawingOn;
		glutPostRedisplay();
		break;

		case 'w':
		m_worldCoordinateSysOn = !m_worldCoordinateSysOn;
		glutPostRedisplay();
		break;

		case 'q':
		glClearColor (1.0, 0.0, 0.0, 0.0);
		break;

		case 'r':
		m_camera->roll(0.1f);
		break;

		default:
		break;
	}
	glutPostRedisplay();
}

void GLRenderViewport3D::CallBackIdleFunc(void) {

	//glRotatef(0.25, 1, 1, 2);
	//CallBackDisplayFunc();
}

void GLRenderViewport3D::StartIdle(GlutManager * glutMaster) {

	glutMaster->SetIdleToCurrentWindow();
	glutMaster->EnableIdleFunction();
}

void GLRenderViewport3D::CallBackMouseFunc(int button, int state, int x, int y) {

	if(button==1 && state==0 )
	{
		IVec2 currentPos = IVec2(-x, y);
		m_panOn = true;
		m_mouseStartPos = currentPos;
	}
	else
	m_panOn = false;

	if(button==0 && state==0 )
	{
		IVec2 currentPos = IVec2(x, y);

		setArballOn(true);
		m_motionChange = true;
		m_mouseStartPos = currentPos;

		IVec2 middlePos = IVec2(m_width/2, m_height/2);
		IVec2 middleOffset = middlePos - currentPos;
		int radius = middleOffset.length();
		if(radius>m_arcballRadius) {
			m_arcballColor= {0,0,1};
			m_spinOn = true;
		}
		else if(radius<=m_arcballRadius && m_motionChange)
		{
			m_arcballColor= {1,1,0};
			m_rotateOn = true;
		}

	}
	else
	{
		m_rotateOn = false;
		m_spinOn = false;
		setArballOn(false);
		m_motionChange = false;
	}

	if(button==2 && state==0 ) {
		IVec2 currentPos = IVec2(x, y);
		m_zoomOn = true;
		m_mouseStartPos = currentPos;
	}
	else
	m_zoomOn = false;

	if(!m_zoomOn && !m_arcballOn)
		m_lowerHUD = "";

	if(button==3)
	m_camera->dolly(0.2);
	if(button==4)
	m_camera->dolly(-0.2);
	CallBackDisplayFunc();
}

void GLRenderViewport3D::CallBackMotionFunc(int x, int y) {

	if(m_panOn)
	{
		IVec2 currentPos = IVec2(-x, y);
		IVec2 offset = currentPos - m_mouseStartPos;

		m_camera->pan(1.5f,offset[0],offset[1], m_mouseStartPos, currentPos);
		m_lowerHUD = "pan";
		CallBackDisplayFunc();
		m_mouseStartPos = currentPos;
	}
	else if(m_arcballOn)
	{
		IVec2 middlePos = IVec2(m_width/2, m_height/2);
		IVec2 currentPos = IVec2(x, y);
		IVec2 middleOffset = middlePos - currentPos;
		IVec2 offset = currentPos - m_mouseStartPos;
		Int radius = middleOffset.length();

		if(radius>m_arcballRadius && m_motionChange)
		m_arcballColor= {0,0,1};
		else if(radius<=m_arcballRadius && m_motionChange)
		m_arcballColor= {1,1,0};

		if(m_spinOn) {
			std::cout<<"SPIN"<<endl;
			m_lowerHUD = "spin";
			m_camera->spinCamera(x,y,m_mouseStartPos[0],m_mouseStartPos[1]);
		}
		else if(m_rotateOn)
		{
			std::cout<<"ROTATE"<<endl;
			m_lowerHUD = "rotate";
			m_camera->rotate(0.01,offset[0],offset[1]);
		}

		CallBackDisplayFunc();
		m_mouseStartPos = currentPos;
	}
	else if(m_zoomOn)
	{

		//double sens = ((90.0 - m_camera->fov()) * pow(1.03, 90.0 - m_camera->fov())) + 40.0;

		IVec2 currentPos = IVec2(x, y);
		IVec2 offset = currentPos - m_mouseStartPos;

		//if(offset[1]>0)
		m_camera->zoom(offset[1],0.020);
		//else
		//m_camera->zoom(offset[1],0.97);

		m_lowerHUD = "zoom";
		CallBackReshapeFunc(m_width, m_height);
		CallBackDisplayFunc();
		m_mouseStartPos = currentPos;
	}
	else
	m_lowerHUD = "";

	//m_camera->print();
	m_motionChange = false;
}

END_PV_NAMESPACE
