#ifndef GLUTVIEWPORT_H_
#define GLUTVIEWPORT_H_

#include "../base/math/vec3.h"
/*!
 *  An abstract GLUT Viewport class object. Inherit from this to implement concrete viewport
 *  callbacks.
 */
class GlutViewport {
protected:

	int windowID;

public:

	GlutViewport(void);
	~GlutViewport();

	virtual void CallBackDisplayFunc();
	virtual void CallBackIdleFunc(void);
	virtual void CallBackKeyboardFunc(unsigned char key, int x, int y);
	virtual void CallBackMotionFunc(int x, int y);
	virtual void CallBackMouseFunc(int button, int state, int x, int y);
	virtual void CallBackPassiveMotionFunc(int x, int y);
	virtual void CallBackReshapeFunc(int w, int h);
	virtual void CallBackSpecialFunc(int key, int x, int y);
	virtual void CallBackVisibilityFunc(int visible);

	void SetWindowID(int newWindowID);
	int GetWindowID(void);

	FVec3 worldToScreen(FVec3 worldPosition);

};

#endif /* GLUTVIEWPORT_H_ */
