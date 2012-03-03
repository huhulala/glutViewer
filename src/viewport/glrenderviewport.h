#ifndef GLRENDERVIEWPORT_H_
#define GLRENDERVIEWPORT_H_

#include "glutmanager.h"
#include "../Interaction/glutcamera.h"
#include "../base/math/vec3.h"

BEGIN_PV_NAMESPACE

/*!
 *  Concrete GlutViewport. Here the callback wrappers from glutmanager.h are implemented.
 *  The class manages a glut ogl context.
 */
class GLRenderViewport: public GlutViewport {
public:

	//! Constructor
	GLRenderViewport(GlutManager * glutMaster, int setWidth, int setHeight,
			int setInitPositionX, int setInitPositionY, char * title);

	//! Rendering is going on here
	~GLRenderViewport();

	//! Rendering is going on here
	void CallBackDisplayFunc(void);

	//! Rendering is going on here
	void CallBackReshapeFunc(int w, int h);

	//! Rendering is going on here
	void CallBackIdleFunc(void);

	//! Rendering is going on here
	void CallBackMouseFunc(int button, int state, int x, int y);

	//! Keyboard callback
	void CallBackKeyboardFunc(unsigned char key, int x, int y);

	//! Mouse motion callback
	void CallBackMotionFunc(int x, int y);

	void renderViewportGeometry();

	//! Idle callback
	void StartIdle(GlutManager * glutMaster);

private:
	//! Current
	int m_height, m_width;

	//! Initial Position
	int m_initPositionX, m_initPositionY;

	IVec2 m_mouseStartPos;

	//! Position of light
	FVec3 m_lightPos;

	//! Should the light position set to pov?
	Bool m_arcballOn;

	//! Should the light position set to pov?
	Bool m_panOn;

	Bool m_rotateOn;

	Bool m_zoomOn;

	//! Should the light position set to pov?
	Bool m_cameraLightning;

	//! The camera projecting the scene
	Camera* m_camera;

	GLfloat phi;
	GLfloat theta;

	//! Light setting
	void configureLightning(void);

};

END_PV_NAMESPACE

#endif /* GLRENDERVIEWPORT_H_ */
