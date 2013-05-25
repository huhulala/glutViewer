#ifndef GLRENDERVIEWPORT2D_H_
#define GLRENDERVIEWPORT2D_H_

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
class GLRenderViewport2D: public GlutViewport {
public:

	typedef struct tagVertex
	{
		double east;
		double north;
		double elev;
	}VERTEX, *LPVERTEX;

	//! Constructor
	GLRenderViewport2D(UInt ID,GlutManager * glutMaster, int setWidth, int setHeight,
			int setInitPositionX, int setInitPositionY, const char * title);

	//! Rendering is going on here
	~GLRenderViewport2D();

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

	//! Idle callback
	void StartIdle(GlutManager * glutMaster);

	//! Captures a tga screenshot and saves it to the working dir
	void CaptureScreenshot();

	void SetupOrtho(int cx, int cy);

	void DrawZoomRect();

private:

	//! The chip drawable
	//Chip m_chip;

	const UInt m_ID;

	GLdouble xOrg;
	GLdouble xMax;
	GLdouble yOrg;
	GLdouble yMax;
	GLdouble zMax;
	GLdouble m_PixelX;
	GLdouble m_PixelY;

	GLdouble m_currentScale;
	GLdouble m_zoomFactor;

	VERTEX m_StartPoint;
	VERTEX m_EndPoint;
	VERTEX m_MovePoint;
	VERTEX m_PrevZoomLeft;
	VERTEX m_PrevZoomRight;

	Bool m_FirstPickPoint;

	//! Current window size
	int m_height, m_width;

	//! Initial Position
	int m_initPositionX, m_initPositionY;

	IVec2 m_mouseStartPos;

	FVec2 m_totalMoved;

	FVec2 m_totalMovedCurrent;

	//! Is pan active
	Bool m_panOn;

	//! Is rotate active
	Bool m_rotateOn;

	//! Is zoom active
	Bool m_zoomOn;

	//Bool m_translateOn;

	//! Is HUD drawing active
	Bool m_translateOn;

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
	void draw2DScene();

};

END_PV_NAMESPACE

#endif /* GLRENDERVIEWPORT_H_ */
