/*
 * Point.cpp
 *
 *  Created on: 2014-2-15
 *      Author: Hali
 */

#include "Point.h"

Point::Point(float x/* = 0*/, float y/* = 0*/) :
		x(x), y(y) {
	// TODO Auto-generated constructor stub

}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

void Point::set(float x, float y){
	this->x = x;
	this->y = y;
}
