#include "chip.h"
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <unistd.h>     // needed to sleep.
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
BEGIN_PV_NAMESPACE

GLuint texture[3];

Chip* Chip::instance = 0;

Chip::Chip():m_textured(false) {
	//LoadGLTextures();

	Int count = 128;
	for (int i = 0; i < count; ++i) {
		vector<Int> columns;
		for (int j = 0; j < count; ++j) {
			columns.push_back( rand() % 22);
		}
		m_temperature.push_back(columns);
	}

	string line;
	std::ifstream myfile ("Data/color3.scheme");
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline (myfile,line);

			string::size_type posOfSpace = line.find('#');
			if (posOfSpace == string::npos) {
				if(line!="#end") {

					posOfSpace = line.find(' ');

					string::size_type posOfSpace = line.find(' ');
					String kelvin = line.substr(0,posOfSpace);
					line = line.substr(posOfSpace+2);

					posOfSpace = line.find(' ');
					String r = line.substr(0,posOfSpace);
					line = line.substr(posOfSpace+1);

					posOfSpace = line.find(' ');
					String g = line.substr(0,posOfSpace);
					line = line.substr(posOfSpace+2);

					posOfSpace = line.find(' ');
					String b = line.substr(0,posOfSpace);
					line = line.substr(posOfSpace+2);

					double rd = atof(r.c_str());
					double gd = atof(g.c_str());
					double bd = atof(b.c_str());

					cout<<rd<<" "<<gd<<" "<<bd<<endl;

					vector<double> color;
					color.push_back(rd);
					color.push_back(gd);
					color.push_back(bd);
					m_colors.push_back(color);
				}
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

Chip& Chip::getInstance() {
	if (!instance)
	instance = new Chip();
	return *instance;
}

bool Chip::createCheckerboardTexture()
{
	//Checkerboard pixels
	const int CHECKERBOARD_WIDTH = 128;
	const int CHECKERBOARD_HEIGHT = 128;
	const int CHECKERBOARD_PIXEL_COUNT = CHECKERBOARD_WIDTH * CHECKERBOARD_HEIGHT;
	GLuint checkerBoard[ CHECKERBOARD_PIXEL_COUNT ];

	Int count = 128;
	for (int i = 0; i < count; ++i) {

		for (int j = 0; j < count; ++j) {
			//cout<<i*count + j<<" // ";

			//Get the individual color components
			GLubyte* colors = (GLubyte*)&checkerBoard[ i*count + j ];

			Int temp = m_temperature[i][j];
			vector<double> color = m_colors.at(temp);
			cout<<temp<<endl;
			cout<<"color: "<<color.at(0)<<endl;

			colors[ 0 ] = color.at(0);
			colors[ 1 ] = color.at(1);
			colors[ 2 ] = color.at(2);
			colors[ 3 ] = 0xFF;

			/*
			 if(m_temperature[i][j]%2==0) {

			 //Set pixel to white
			 colors[ 0 ] = 0xFF;
			 colors[ 1 ] = 0xFF;
			 colors[ 2 ] = 0x00;
			 colors[ 3 ] = 0xFF;
			 }
			 else
			 {
			 //Set pixel to red
			 colors[ 0 ] = 0xFF;
			 colors[ 1 ] = 0x00;
			 colors[ 2 ] = 0xFF;
			 colors[ 3 ] = 0xFF;
			 }
			 */
		}
		//	cout<<endl;
	}

	/*
	 for( int i = 0; i < CHECKERBOARD_PIXEL_COUNT; ++i )
	 {

	 if(i % 128 == 0){
	 if(flag==0)
	 flag = 1;
	 else
	 flag = 0;
	 }

	 cout<<"Flag "<<flag<<endl;


	 //Get the individual color components
	 GLubyte* colors = (GLubyte*)&checkerBoard[ i ];

	 //If the 5th bit of the x and y offsets of the pixel do not match
	 //if( i / 128 & 16 ^ i % 128 & 16 )
	 if( flag==0)
	 {
	 //Set pixel to white
	 colors[ 0 ] = 0xFF;
	 colors[ 1 ] = 0xFF;
	 colors[ 2 ] = 0x00;
	 colors[ 3 ] = 0xFF;
	 }
	 else
	 {
	 //Set pixel to red
	 colors[ 0 ] = 0xFF;
	 colors[ 1 ] = 0x00;
	 colors[ 2 ] = 0xFF;
	 colors[ 3 ] = 0xFF;
	 }
	 }
	 */

	//Generate texture ID
	glGenTextures( 1, &texture[0] );

	//Bind texture ID
	glBindTexture( GL_TEXTURE_2D, texture[0] );

	//Generate texture
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, CHECKERBOARD_WIDTH, CHECKERBOARD_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerBoard );

	//Set texture parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	//Unbind texture
	//glBindTexture( GL_TEXTURE_2D, NULL );

	//Check for error
	GLenum error = glGetError();
	if( error != GL_NO_ERROR )
	{
		printf( "Error loading texture frompixels! %s\n", gluErrorString( error ) );
		return false;
	}

	return true;
}

void Chip::initTextures() {

	initTexture(0,"Data/test2.bmp");
	initTexture(1,"Data/test2.bmp");
	initTexture(2,"Data/test3.bmp");
}

void Chip::initTexture(int ID,char *filename) {

	// Load Texture
	Image *image;

	// allocate space for texture
	image = (Image *) malloc(sizeof(Image));
	if (image == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!loadBMP(filename, image)) {
		exit(1);
	}

	// Create Texture
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glGenTextures(1, &texture[ID]);
	glBindTexture(GL_TEXTURE_2D, texture[ID]); // 2d texture (x and y size)


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0,
			GL_BGR_EXT, GL_UNSIGNED_BYTE,image->data);

	GLenum res = glGetError();
	cout<<"Res1: "<<res<<endl;
}

void Chip::drawGL3D()const {

	for (int var = 0; var < 3; ++var) {

		double heigth = var*5;

		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture[var]);
		glBegin(GL_POLYGON);
		glNormal3d(0, -1, 0);
		glTexCoord2f(0, 0);
		glVertex3f(-10.0,heigth,-10.0);

		glTexCoord2f(1, 0);
		glVertex3f( 10.0,heigth,-10.0);

		glTexCoord2f(1, 1);
		glVertex3f( 10.0,heigth, 10.0);

		glTexCoord2f(0, 1);
		glVertex3f(-10.0,heigth, 10.0);
		glEnd();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

	}
}

Bool Chip::drawTextured() const
{
	return m_textured;
}

void Chip::setDrawTextured(Bool m_textured)
{
	this->m_textured = m_textured;
	if(m_textured)
	glEnable(GL_TEXTURE_2D);
	else
	glDisable(GL_TEXTURE_2D);
}

void Chip::drawGL2D()const {

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_FAN); // this is the fastest way to draw a rectangle
	glTexCoord2f(0.0,0.0); glVertex2f(25.0,25.0);
	glTexCoord2f(1.0,0.0); glVertex2f(25.0,-25.0);
	glTexCoord2f(1.0,1.0); glVertex2f(-25.0,-25.0);
	glTexCoord2f(0.0,1.0); glVertex2f(-25.0,25.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

Int Chip::loadBMP(char *filename, Image *image) const {

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
	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}
	printf("Width of %s: %lu\n", filename, image->sizeX);

	// read the height
	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}
	printf("Height of %s: %lu\n", filename, image->sizeY);

	// calculate the size (assuming 24 bits or 3 bytes per pixel).
	size = image->sizeX * image->sizeY * 3;

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
	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}

	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
		temp = image->data[i];
		image->data[i] = image->data[i+2];
		image->data[i+2] = temp;
	}

	// we're done.
	return 1;

}

END_PV_NAMESPACE

