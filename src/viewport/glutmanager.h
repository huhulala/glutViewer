#ifndef GLUTMANAGER_H_
#define GLUTMANAGER_H_

#include <GL/glut.h>
#include "glutviewport.h"

#define MAX_NUMBER_OF_WINDOWS 256

/*!
 GLUT expects pointers to user-defined callback functions.  The GlutMaster
 object centralizes these into a single set of static callback functions
 through which events are tunneled to member functions in window objects
 that inherit from GlutWindow.  You add standard GLUT callback functions to
 your own derivative of the GlutWindow class by overloading the virtual
 functions in GlutWindow.

 GLUT is activated by:
 glutMaster->CallGlutMainLoop();

 To accomodate GLUT's idle function capability GlutMaster maintains two
 variables:
 currentIdleWindow
 idleFunctionEnabled

 with associated member functions to manipulate them.  The idle function
 is defined by overloading:
 GlutWindow::CallBackIdleFunc()
 Only one window at a time can be the active idle window.
 */
class GlutManager {

private:

	//! the instance
	static GlutManager* theInstance;

	static void CallBackDisplayFunc(void);
	static void CallBackIdleFunc(void);
	static void CallBackKeyboardFunc(unsigned char key, int x, int y);
	static void CallBackMotionFunc(int x, int y);
	static void CallBackMouseFunc(int button, int state, int x, int y);
	static void CallBackPassiveMotionFunc(int x, int y);
	static void CallBackReshapeFunc(int w, int h);
	static void CallBackSpecialFunc(int key, int x, int y);
	static void CallBackVisibilityFunc(int visible);

	static int currentIdleWindow;
	static int idleFunctionEnabled;

public:

	//! Get singleton instance
	static GlutManager& getInstance();

	GlutManager();
	~GlutManager();

	void glversion();
	void CallGlutCreateWindow(char * setTitle, GlutViewport * glutWindow);
	void CallGlutMainLoop(void);

	void DisableIdleFunction(void);
	void EnableIdleFunction(void);
	int IdleFunctionEnabled(void);

	int IdleSetToCurrentWindow(void);
	void SetIdleToCurrentWindow(void);
};

#endif /* GLUTMASTER_H_ */
