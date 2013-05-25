#ifndef PV__CHIP_H_
#define PV__CHIP_H_

#include "../../base/types/types.h"
#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <vector>

BEGIN_PV_NAMESPACE

/*!
 Class that draws the basic chip rectangle and visualizes the temperature distribution by dynamic
 texture creation.
 */
class Chip {
public:

	//Get singleton instance
	static Chip& getInstance();

	void initTextures();

	void initTexture(int ID,char *filename);

	//! Method that draws the chip for 3D viewports
	void drawGL3D() const;

	//! Method that draws the chip for 2D viewports
	void drawGL2D() const;

	//! Get draw textured flag
	Bool drawTextured() const;

	//! Set draw textured flag
	void setDrawTextured(Bool drawTextured);

	bool createCheckerboardTexture();

private:

	//! the instance
	static Chip* instance;

	//! Constructor
	Chip();

	struct Image {
		unsigned long sizeX;
		unsigned long sizeY;
		char *data;
	};

	//! Qick and dirty bmp loader for testing purpose
	Int loadBMP(char *filename, Image *image) const;

	Bool m_textured;

	//! the temperature array array
	vector<vector<Int> > m_temperature;

	vector<vector<double> > m_colors;
};

END_PV_NAMESPACE

#endif /* CHIP_H_ */
