#include "glutmanager.h"
#include "glutviewport.h"
#include <stdio.h>

GlutViewport * viewPorts[MAX_NUMBER_OF_WINDOWS];

int GlutManager::currentIdleWindow = 0;
int GlutManager::idleFunctionEnabled = 0;

//singleton impl
GlutManager* GlutManager::theInstance = 0;

GlutManager& GlutManager::getInstance() {
	if (!theInstance)
		theInstance = new GlutManager();
	return *theInstance;
}

GlutManager::GlutManager() {

	// Create dummy variables
	char * dummy_argv[1];
	dummy_argv[0] = "run";
	int dummy_argc = 1;

	// Initialize GLUT
	glutInit(&dummy_argc, dummy_argv);
}

GlutManager::~GlutManager() {

}

void GlutManager::CallBackDisplayFunc(void) {

	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackDisplayFunc();
}

void GlutManager::CallBackIdleFunc(void) {

	if (idleFunctionEnabled && currentIdleWindow) {
		glutSetWindow(currentIdleWindow);
		viewPorts[currentIdleWindow]->CallBackIdleFunc();
	}
}

void GlutManager::CallBackKeyboardFunc(unsigned char key, int x, int y) {

	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackKeyboardFunc(key, x, y);
}

void GlutManager::CallBackMotionFunc(int x, int y) {

	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackMotionFunc(x, y);
}

void GlutManager::CallBackMouseFunc(int button, int state, int x, int y) {

	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackMouseFunc(button, state, x, y);
}

void GlutManager::CallBackPassiveMotionFunc(int x, int y) {

	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackPassiveMotionFunc(x, y);
}

void GlutManager::CallBackReshapeFunc(int w, int h) {

	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackReshapeFunc(w, h);
}

void GlutManager::CallBackSpecialFunc(int key, int x, int y) {

	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackSpecialFunc(key, x, y);
}

void GlutManager::CallBackVisibilityFunc(int visible) {

	int windowID = glutGetWindow();
	viewPorts[windowID]->CallBackVisibilityFunc(visible);
}

void *xmalloc(size_t size) {
	register void *value = malloc(size);

	if (value == 0) {
		fprintf(stderr, "xmalloc: virtual memory exhausted");
		exit(1);
	}

	return value;
}

//  Display the menu item
void showMenuItem(int val);

void setupMenus() {
	int subMenuCount; //  Count of sub menus
	int menuItemCount; //  Count of menu items in a submenu
	int *menuIds; //  Submenu IDs
	char str[256]; //  The string of the current menu item
	int i, j; //  Iterators

	//  Generate a random value for submenu count
	subMenuCount = rand() % 20;

	//  Allocate memory for the submenu IDs
	menuIds = (int *) xmalloc(subMenuCount * sizeof(int));

	//  Create all the sub menus
	for (i = 0; i < subMenuCount; i++)
		menuIds[i] = glutCreateMenu(showMenuItem);

	for (i = 1; i < subMenuCount; i++) {
		//  Set sub menu string
		sprintf(str, "SubMenu %d", i);

		//  Add the current submenu to previous submenu
		glutSetMenu(menuIds[i - 1]);
		glutAddSubMenu(str, menuIds[i]);

		//  New menu item count for the new submenu
		menuItemCount = rand() % 20;

		//  Add menu items to the current submenu
		for (j = 1; j < menuItemCount; j++) {
			sprintf(str, "Menu Item %d", j);
			glutAddMenuEntry(str, j);
		}
	}

	//  Set main menu as the current menu
	glutSetMenu(menuIds[0]);

	//  Attach the menu to the RMB
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void showMenuItem(int val) {
	printf("Menu Item: %d\n", val);
}

void setupMenus1() {
	int subMenuCount; //  Count of sub menus
	int menuItemCount; //  Count of menu items in a submenu
	int *menuIds; //  Submenu IDs
	char str[256]; //  The string of the current menu item
	int i, j; //  Iterators

	//  Generate a random value for submenu count
	subMenuCount = rand() % 20;

	//  Allocate memory for the submenu IDs
	menuIds = (int *) xmalloc(subMenuCount * sizeof(int));

	//  Create all the sub menus
	for (i = 0; i < subMenuCount; i++)
		menuIds[i] = glutCreateMenu(showMenuItem);

	for (i = 1; i < subMenuCount; i++) {
		//  Set sub menu string
		sprintf(str, "SubMenu %d", i);

		//  Add the current submenu to previous submenu
		glutSetMenu(menuIds[i - 1]);
		glutAddSubMenu(str, menuIds[i]);

		//  New menu item count for the new submenu
		menuItemCount = rand() % 20;

		//  Add menu items to the current submenu
		for (j = 1; j < menuItemCount; j++) {
			sprintf(str, "Menu Item %d", j);
			glutAddMenuEntry(str, j);
		}
	}

	//  Set main menu as the current menu
	glutSetMenu(menuIds[0]);

	//  Attach the menu to the RMB
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

#define TEXTURE_ID_CUBE 1

void InitGraphics(void)
{
   //int width, height;
  // int nComponents;
   //void* pTextureImage;
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);



   /*
   // Create texture for cube; load marble texture from file and bind it
   pTextureImage = read_texture("marble.rgb", &width, &height, &nComponents);
   glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
   gluBuild2DMipmaps(GL_TEXTURE_2D,     // texture to specify
                     GL_RGBA,           // internal texture storage format
                     width,             // texture width
                     height,            // texture height
                     GL_RGBA,           // pixel format
                     GL_UNSIGNED_BYTE,	// color component format
                     pTextureImage);    // pointer to texture image
   glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
   glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   */
}


void GlutManager::CallGlutCreateWindow(char * setTitle,
		GlutViewport * glutWindow) {

	// Open new window, record its windowID ,
	int windowID = glutCreateWindow(setTitle);
	glutWindow->SetWindowID(windowID);

	// Store the address of new window in global array
	// so GlutMaster can send events to propoer callback functions.
	viewPorts[windowID] = glutWindow;

	InitGraphics();

	// Hand address of universal static callback functions to Glut.
	// This must be for each new window, even though the address are constant.
	glutDisplayFunc(CallBackDisplayFunc);
	glutIdleFunc(CallBackIdleFunc);
	glutKeyboardFunc(CallBackKeyboardFunc);
	glutSpecialFunc(CallBackSpecialFunc);
	glutMouseFunc(CallBackMouseFunc);
	glutMotionFunc(CallBackMotionFunc);
	glutPassiveMotionFunc(CallBackPassiveMotionFunc);
	glutReshapeFunc(CallBackReshapeFunc);
	glutVisibilityFunc(CallBackVisibilityFunc);
	setupMenus();
}

void GlutManager::CallGlutMainLoop(void) {
	glutMainLoop();
}

void GlutManager::DisableIdleFunction(void) {
	idleFunctionEnabled = 0;
}

void GlutManager::EnableIdleFunction(void) {
	idleFunctionEnabled = 1;
}

int GlutManager::IdleFunctionEnabled(void) {

	// Is idle function enabled?
	return (idleFunctionEnabled);
}

int GlutManager::IdleSetToCurrentWindow(void) {

	// Is current idle window same as current window?
	return (currentIdleWindow == glutGetWindow());
}

void GlutManager::glversion() {

	printf("\nOpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("\tglGetError: %x\n", glGetError());
	printf("OpenGL Extensionen: %s\n", glGetString(GL_EXTENSIONS));
	printf("\tglGetError: %x\n", glGetError());
}

void GlutManager::SetIdleToCurrentWindow(void) {

	currentIdleWindow = glutGetWindow();
}
