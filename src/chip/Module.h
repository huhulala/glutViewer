/*
 * Module.h
 *
 *  Created on: Jan 11, 2011
 *      Author: mes
 */


#ifndef _Module_h
#define _Module_h

enum orientation { N, E, S, W };   // N...North; E...East; S...South; W...West
								   // additional options: FN...flipped North; FE...flipped East; FS...flipped South; FW...flipped West

class Module {

protected:

	unsigned int objectname;	// module name (integer between 0 and numModules)
	double width;				// module width
	double height;				// module height
	double area;				// module area
	//double density;
	double weight;				// weight for legalization
	double pins;				// number of pins
	orientation moduleOrientation;	// module orientation (can be rotated)
	bool cellType; 					// 1...macro cells; 0...standard cells;
	bool type;						// 1...fixed; 0...movable;

	double centerPosition_x;		// x-coordinate of center position
	double centerPosition_y;		// y-coordinate of center position
	//double movement;

	void calculateModuleArea();								// area = width*height

public:

    Module();

    // getter and setter
	void setWidth( double );
	void setHeight( double );
	void setObjectName ( unsigned int );
	void setType( bool );
	void setCellType( bool );
	void setCenterPosition_x(double x){centerPosition_x = x;}
	void setCenterPosition_y(double y){centerPosition_y = y;}

	double getWidth() const;
	double getHeight() const;
	unsigned int getObjectName() const;
	bool getType() const;
	bool getCellType() const;
	double getWeight() const;
	double getArea() const;

	double getCenterPosition_x() const {return centerPosition_x;}
	double getCenterPosition_y() const {return centerPosition_y;}

	orientation getModuleOrientation() const
	{
	     return moduleOrientation;
	}

	void setModuleOrientation(orientation modOr)
	{
	    this->moduleOrientation = modOr;
	}





};

#endif

