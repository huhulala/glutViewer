#ifndef GLRENDERVIEWPORT3D_H_
#define GLRENDERVIEWPORT3D_H_

#include "glutmanager.h"
#include "../base/types/types.h"
#include "../Interaction/glutcamera.h"
#include "../geometry/drawables/chip.h"
#include "../geometry/glscene.h"
#include "../base/math/vec3.h"
#include "../base/color/col3.h"

BEGIN_PV_NAMESPACE

/*!
 *  Concrete GlutViewport. Here the callback wrappers from glutmanager.h are implemented.
 *  The class manages a glut ogl context.
 */
class GLRenderViewport3D: public GlutViewport {
public:

	//! Constructor
	GLRenderViewport3D(GlutManager * glutMaster, int setWidth, int setHeight,
			int setInitPositionX, int setInitPositionY, const char * title);

	//! Rendering is going on here
	~GLRenderViewport3D();

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

	//! Captures a tga screenshot and saves it to the working dir
	void CaptureScreenshotTGA();

	//! Captures a bmp screenshot and saves it to the working dir
	void CaptureScreenshotBMP();

	void renderViewportGeometry();

	//! Idle callback
	void StartIdle(GlutManager * glutMaster);

	//! Set arcball
	void setArballOn(Bool arcballOn);

private:

	//! The chip drawable
	//Chip m_chip;

	//! Current window size
	int m_height, m_width;

	//! Initial Position
	int m_initPositionX, m_initPositionY;

	IVec2 m_mouseStartPos;

	//! Position of light
	FVec3 m_lightPos;

	//! Is 2D arcball drawing active
	Bool m_arcballOn;

	//! Is 3D world coordinate system drawing active
	Bool m_worldCoordinateSysOn;

	//! Is 3D world coordinate system drawing active
	Bool m_chipDrawingOn;

	//! Flag controlling the arcball color
	Bool m_motionChange;

	//! The arcball color
	UCCol3 m_arcballColor;

	//! The arcball radius
	Int m_arcballRadius;

	//! Is pan active
	Bool m_panOn;

	//! Is rotate active
	Bool m_rotateOn;

	//! Is rotate active
	Bool m_spinOn;

	//! Is zoom active
	Bool m_zoomOn;

	//! Is HUD drawing active
	Bool m_hudOn;

	//! The lower hud string
	String m_lowerHUD;

	//! Should the light position set to pov?
	Bool m_cameraLightning;

	//! The camera projecting the scene
	Camera* m_camera;

	//! The scene to render
	GLScene* m_renderScene;

	//! Should use background gradient?
	Bool m_backgroundGradientOn;

	//! the background color
	FCol3 m_backgroundCol;

	//! the lower gradient background color
	FCol3 m_backgroundGradientLowCol;

	//! the upper gradient background color
	FCol3 m_backgroundGradientUpCol;

	//! Render gradient background
	void renderBackgroundColor();

	//! Light setting
	void configureLightning(void);

	//! Idle callback
	void render2DDisplay();

	//! Draws a string
	void drawString(const char *str, int x, int y, float color[4], void *font);

	//! Draws a circle
	void drawCircle(float x, float y, float r, int segments);

};

END_PV_NAMESPACE

#endif /* GLRENDERVIEWPORT_H_ */
