#include "glrenderviewport2D.h"
#include "../geometry/drawables/coordinateAxisLines.h"
#include "../geometry/drawables/box.h"

#include "../geometry/drawables/grid.h"
#include "../geometry/sceneprovider.h"
#include <time.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <iostream>

BEGIN_PV_NAMESPACE

/* storage for one texture  */
GLuint texture1[1];

/* Image type - contains height, width, and data */
struct Image1 {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
};
typedef struct Image1 Image1;

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int ImageLoad1(char *filename, Image1 *image1) {
	FILE *file;
	unsigned long size; // size of the image in bytes.
	unsigned long i; // standard counter.
	unsigned short int planes; // number of planes in image (must be 1)
	unsigned short int bpp; // number of bits per pixel (must be 24)
	char temp; // temporary color storage for bgr-rgb conversion.

	// make sure the file is there.
	if ((file = fopen(filename, "rb"))==NULL)
	{
		printf("File Not Found : %s\n",filename);
		return 0;
	}

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// read the width
	if ((i = fread(&image1->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}
	printf("Width of %s: %lu\n", filename, image1->sizeX);

	// read the height
	if ((i = fread(&image1->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}
	printf("Height of %s: %lu\n", filename, image1->sizeY);

	// calculate the size (assuming 24 bits or 3 bytes per pixel).
	size = image1->sizeX * image1->sizeY * 3;

	// read the planes
	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}
	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	// read the bpp
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);
		return 0;
	}
	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	// read the data.
	image1->data = (char *) malloc(size);
	if (image1->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}

	if ((i = fread(image1->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
		temp = image1->data[i];
		image1->data[i] = image1->data[i+2];
		image1->data[i+2] = temp;
	}

	// we're done.
	return 1;
}

GLenum res;

void LoadGLTextures1() {
	// Load Texture
	Image1 *image1;

	// allocate space for texture
	image1 = (Image1 *) malloc(sizeof(Image1));
	if (image1 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad1("Data/test.bmp", image1)) {
		exit(1);
	}

	// Create Texture
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glGenTextures(1, &texture1[0]);
	glBindTexture(GL_TEXTURE_2D, texture1[0]); // 2d texture (x and y size)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image1->sizeX, image1->sizeY, 0,
			GL_BGR_EXT, GL_UNSIGNED_BYTE,image1->data);

	res = glGetError();
	cout<<"Res1: "<<res<<endl;
	// 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
	// border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
};

GLRenderViewport2D::GLRenderViewport2D(UInt ID,GlutManager * glutManager, int setWidth,
		int setHeight, int setInitPositionX, int setInitPositionY,const char * title)
:m_ID(ID),m_panOn(false),m_rotateOn(false),m_translateOn(false),
m_backgroundGradientOn(true),m_backgroundCol(1.0,1.0,1.0)
,m_backgroundGradientLowCol(1.0,1.0,1.00),m_backgroundGradientUpCol(0.5,0.7,0.70) {

	m_totalMovedCurrent[0]=0;
	m_totalMovedCurrent[1]=0;
	m_totalMovedCurrent[2]=0;

	m_currentScale = 1.0;

	m_StartPoint.east = m_StartPoint.north = m_StartPoint.elev = 0.0;
	m_EndPoint.east = m_EndPoint.north = m_EndPoint.elev = 0.0;
	m_MovePoint.east = m_MovePoint.north = m_MovePoint.elev = 0.0;

	m_width = setWidth;
	m_height = setHeight;

	m_initPositionX = setInitPositionX;
	m_initPositionY = setInitPositionY;

	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(m_width, m_height);
	glutInitWindowPosition(m_initPositionX, m_initPositionY);

	// This may have to be moved to after the next line on some platforms
	glViewport(0, 0, m_width, m_height);

	glutManager->CallGlutCreateWindow(title, this);

	//SBglMatrixMode(GL_PROJECTION);
	///glOrtho(-80.0, 80.0, -80.0, 80.0, -500.0, 500.0);


	//glEnable(GL_COLOR_MATERIAL);


	SceneProvider sp = SceneProvider::getInstance();
	m_renderScene = sp.getScene();
	m_renderScene->init();
	m_renderScene->updateGL();
	//configureLightning();

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
	//LoadGLTextures1();
	//m_chip.initTexture();
	Chip chip = Chip::getInstance();
	chip.createCheckerboardTexture();

	//Sets the clear color. Again, the values are in RGBA float format
	//glClearColor(1.0f, 0.8f, 0.0f, 1.0f);

	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glEnable(GL_TEXTURE_2D);


}

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

GLRenderViewport2D::~GLRenderViewport2D() {

	glutDestroyWindow(windowID);
}

void GLRenderViewport2D::configureLightning() {

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat lmodel_ambient[] = {0.4, 0.4, 0.4, 1.0};
	GLfloat local_view[] = {1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, local_view);

	float g_lightPos[4] = {0.0f, 0.0f,3.0f, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);
}

void GLRenderViewport2D::renderBackgroundColor() {

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

void GLRenderViewport2D::SetupOrtho(int cx, int cy)
{
	if( 0 >= cx || 0 >= cy ) return;

	glViewport(0, 0, cx, cy);

	m_width = cx;
	m_height = cy;

	// select the viewing volumn
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	// Now that the viewport dimensions are set up,
	//  we can set up the projection matrix.
	// select the viewing volumn
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	GLdouble dx = xMax - xOrg;
	GLdouble dy = yMax - yOrg;
	double aspect_ratio;
	if(fabs(dx) > 0.001 || fabs(dy) > 0.001)//Controls how far you can zoom in
	{
		if(dx >= dy)
		{

			GLdouble dY = dx * m_height / m_width;
			GLdouble yMax = yOrg + dY;
			glOrtho( xOrg, xMax, yOrg, yMax, -zMax, zMax);
		}
		else
		{
			GLdouble dX = dy * m_width / m_height;
			GLdouble xMax = xOrg + dX;
			glOrtho( xOrg, xMax, yOrg, yMax, -zMax, zMax);

		}
	}
	// switch back to the modelview matrix and clear it
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

void GLRenderViewport2D::draw2DScene() {

	std::vector<Renderable*> renderables = m_renderScene->getRenderables();
	for( std::vector<Renderable*>::iterator it = renderables.begin(); it != renderables.end(); ++it )
	{
		Renderable* ra = dynamic_cast<Renderable*>((*it));
		Box* box = dynamic_cast<Box*>(ra);
		if(box != 0) {

			Float centerX = (box->center()[0])*0.2;
			Float centerY = (box->center()[1])*0.2;
			Float centerZ = (box->center()[2])*0.2;

			//Float extendX = box->extend()[0];
			//Float extendY = box->extend()[1];
			//Float extendZ = box->extend()[2];

			std::cout<<"center!!!"<<centerX<<" "<<centerY<<" "<<centerZ<<endl;

			glBegin(GL_QUADS); // Draw A Quad
			glColor3f(1, 0, 0);
			glVertex3f(centerX-0.03f, centerZ+0.03f, 0.3f); // Top Left
			glVertex3f(centerX+0.03f, centerZ+0.03f, 0.3f); // Top Right
			glVertex3f( centerX+0.03f, centerZ-0.03f, 0.3f); // Bottom Right
			glVertex3f(centerX-0.03f, centerZ-0.03f, 0.3f); // Bottom Left
			glEnd();

		}
	}
}

void GLRenderViewport2D::CallBackDisplayFunc(void) {

	// Clear frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render view aligned quad
	//renderBackgroundColor();

	glLoadIdentity();
	glPushMatrix();

	cout<<"m_currentScale "<<m_currentScale<<endl;
	glTranslated(m_totalMoved[0],- m_totalMoved[1], 0);
	glScaled(m_currentScale, m_currentScale, 1);

	Chip chip = Chip::getInstance();
	chip.drawGL2D();

	glDisable(GL_DEPTH_TEST);
	draw2DScene();
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();




	if(m_FirstPickPoint)
	DrawZoomRect();

	// Set up the stationary light
	//configureLightning();

	// Make sure changes appear onscreen
	glutSwapBuffers();

	/*
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	//glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texture1[0]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_FAN); // this is the fastest way to draw a rectangle
	glTexCoord2f(0.0,0.0); glVertex2f(25.0,25.0);
	glTexCoord2f(1.0,0.0); glVertex2f(25.0,-25.0);
	glTexCoord2f(1.0,1.0); glVertex2f(-25.0,-25.0);
	glTexCoord2f(0.0,1.0); glVertex2f(-25.0,25.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();
	*/

	//SetupOrtho(m_width,m_height);

	// Clear frame buffer and depth buffer
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render view aligned quad
	//renderBackgroundColor();

	//glLoadIdentity();
	//glPushMatrix();

	//cout<<"m_currentScale "<<m_currentScale<<endl;


	//m_chip.drawGL2D();

	//glTranslated(m_totalMoved[0],- m_totalMoved[1], 0);
	//glScaled(m_currentScale, m_currentScale, 1);






	//m_renderScene->drawGL();

	//glDisable(GL_DEPTH_TEST);
	//draw2DScene();
	//glEnable(GL_DEPTH_TEST);
	//glPopMatrix();

	//if(m_FirstPickPoint)
	//	DrawZoomRect();

	// Set up the stationary light
	//configureLightning();

	// Make sure changes appear onscreen
	//glutSwapBuffers();


//	glutSwapBuffers();

}

void GLRenderViewport2D::CallBackReshapeFunc(int w, int h) {

	//set arcball radius
	m_width = w;
	m_height = h;

	//SetupOrtho(w,h);
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CallBackDisplayFunc();
}

void GLRenderViewport2D::CallBackKeyboardFunc(unsigned char key, int x, int y) {

	cout << "CallBackKeyboardFunc" <<endl;
	switch (key) {

		case 's':
		CaptureScreenshot();
		break;

		default:
		break;
	}
	glutPostRedisplay();
}

void GLRenderViewport2D::CaptureScreenshot() {

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
	//glRotatef(0.25, 1, 1, 2);
	//CallBackDisplayFunc();
}

void GLRenderViewport2D::CallBackIdleFunc(void) {

	//glRotatef(0.25, 1, 1, 2);
	//CallBackDisplayFunc();
}

void GLRenderViewport2D::StartIdle(GlutManager * glutMaster) {

	glutMaster->SetIdleToCurrentWindow();
	glutMaster->EnableIdleFunction();
}

void GLRenderViewport2D::DrawZoomRect()
{
	::glColor3d(0.0,0.0,1.0);
	::glBegin(GL_LINE_LOOP);
	::glVertex2d(m_StartPoint.east, m_StartPoint.north);
	::glVertex2d(m_EndPoint.east, m_StartPoint.north);
	::glVertex2d(m_EndPoint.east, m_EndPoint.north);
	::glVertex2d(m_StartPoint.east, m_EndPoint.north);
	::glEnd();
}

void GLRenderViewport2D::CallBackMouseFunc(int button, int state, int x, int y) {

	int mod = glutGetModifiers();
	Bool ctrPressed = false;
	if (mod == GLUT_ACTIVE_CTRL)
	ctrPressed = true;
	else
	ctrPressed = false;

	IVec2 currentPos = IVec2(x, y);
	if(ctrPressed && button==0 && state==0 )
	{
		m_panOn = true;
		IVec2 currentPos = IVec2(x, y);

		GLdouble modelMatrix[16];
		GLdouble projMatrix[16];
		GLint viewport[4];
		GLdouble objx, objy, objz;
		glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		glGetIntegerv(GL_VIEWPORT, viewport);

		y = m_height - y;
		gluUnProject(x, y, 0,
				modelMatrix, projMatrix, viewport,
				&objx, &objy, &objz);

		m_EndPoint.east = m_StartPoint.east = objx;
		m_EndPoint.north = m_StartPoint.north = objy;
		m_EndPoint.elev = m_StartPoint.elev = objz;
		m_FirstPickPoint = TRUE;

		DrawZoomRect();

	}
	else if(ctrPressed && button==0 && state==1 )
	{
		m_FirstPickPoint= false;
		m_panOn = false;
	}

	if(!ctrPressed && button==0 && state==0 )
	{
		cout<<"button 2 pressed"<<endl;
		m_translateOn = true;
		m_mouseStartPos[0]=0.0f;
		m_mouseStartPos[1]=0.0f;
		m_totalMoved = m_totalMovedCurrent;
	}
	else if(!ctrPressed && button==0 && state==1 )
	{
		cout<<"button 2 released"<<endl;
		m_translateOn = false;
		m_totalMovedCurrent = m_totalMoved;
		cout<<"m_totalMovedCurrent "<<m_totalMovedCurrent[0]<<" "<<m_totalMovedCurrent[1]<<endl;

	}

	if(button==1 && state==0 )
	{
		cout<<"button 1 pressed"<<endl;
		m_zoomOn = true;
	}
	else if(button==1 && state==1 )
	{
		cout<<"button 1 released"<<endl;
		m_zoomOn = false;
	}

	if(button==3 && state==0 )
	{
		cout<<"button 1 pressed"<<endl;
		m_currentScale+=0.03;
	}

	if(button==4 && state==0 )
	{
		cout<<"button 1 pressed"<<endl;
		m_currentScale-=0.03;
	}

	m_mouseStartPos = currentPos;
	CallBackDisplayFunc();
}

void GLRenderViewport2D::CallBackMotionFunc(int x, int y) {

	if(m_panOn)
	{
		if(m_FirstPickPoint)
		DrawZoomRect();

		//m_totalMoved[0] = x;
		//m_totalMoved[1] = y;
		GLdouble modelMatrix[16];
		GLdouble projMatrix[16];
		GLint viewport[4];
		GLdouble objx, objy, objz;

		glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		glGetIntegerv(GL_VIEWPORT, viewport);

		y = m_height - y;
		gluUnProject(x, y, 0,
				modelMatrix, projMatrix, viewport,
				&objx, &objy, &objz);

		m_EndPoint.east = m_MovePoint.east = objx;
		m_EndPoint.north = m_MovePoint.north = objy;
		m_EndPoint.elev = m_MovePoint.elev = objz;

		if(m_FirstPickPoint)
		DrawZoomRect();

		CallBackDisplayFunc();
		//m_mouseStartPos = currentPos;
	}
	else if(m_rotateOn)
	{
		IVec2 middlePos = IVec2(m_width/2, m_height/2);
		IVec2 currentPos = IVec2(x, y);
		IVec2 middleOffset = middlePos - currentPos;
		IVec2 offset = currentPos - m_mouseStartPos;
		Int radius = middleOffset.length();

		//if(radius>m_arcballRadius )
		//m_camera->spinCamera(x,y,m_mouseStartPos[0],m_mouseStartPos[1]);
		//else if(radius<=m_arcballRadius)
		//m_camera->rotate(0.01,offset[0],offset[1]);

		CallBackDisplayFunc();
		m_mouseStartPos = currentPos;
	}
	else if(m_zoomOn)
	{
		IVec2 currentPos = IVec2(x, y);
		IVec2 offset = currentPos - m_mouseStartPos;

		if(offset[1]>0)
		m_currentScale+=0.015;
		else
		m_currentScale-=0.015;

		CallBackDisplayFunc();
		m_mouseStartPos = currentPos;
	}
	else if(m_translateOn)
	{
		IVec2 currentPos = IVec2(x, y);
		IVec2 offset = currentPos - m_mouseStartPos;

		m_totalMoved[0] = m_totalMovedCurrent[0]+(float)offset[0]/10;
		m_totalMoved[1] = m_totalMovedCurrent[1]+(float)offset[1]/10;

		cout<<"current "<<x<<" "<<y<<endl;
		cout<<"translate "<<offset[0]<<" "<<offset[1]<<endl;
		CallBackDisplayFunc();
	}
}

END_PV_NAMESPACE
