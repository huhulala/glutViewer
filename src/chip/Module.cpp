/*
 * Module.cpp
 *
 *  Created on: Jan 11, 2011
 *      Author: mes
 */

#include "Module.h"
#include <iostream>

Module::Module():
	objectname(0),
	width(0),
	height(0),
	area(0),
	//density(0),
	weight(0),
	pins(0),
	moduleOrientation(E),
	cellType(0), 			// 1...macro cells; 0...standard cells;
	type(0),				// 1...fixed; 0...movable;
	centerPosition_x(0),
	centerPosition_y(0)
	//movement(0),
{

}


void Module::setWidth( double value )
{
	width = value;
	calculateModuleArea();
}

void Module::setHeight( double value )
{
	height = value;
	calculateModuleArea();
}

void Module::setObjectName( unsigned int value )
{
	objectname = value;
}

void Module::setType( bool value )
{
	type = value;
}

void Module::setCellType( bool value )
{
	cellType = value;
}

double Module::getWidth() const
{
	return width;
}


double Module::getHeight() const
{
	return height;
}

unsigned int Module::getObjectName() const
{
	return objectname;
}

bool Module::getType() const
{
	return type;
}

bool Module::getCellType() const
{
	return cellType;
}

double Module::getWeight() const
{
	return weight;
}

double Module::getArea() const
{
	return area;
}

void Module::calculateModuleArea()
{
	area = width * height;
}
