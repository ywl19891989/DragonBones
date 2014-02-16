/*
 * DBTransform.cpp
 *
 *  Created on: 2014-2-16
 *      Author: Hali
 */

#include "DBTransform.h"
#include <stdio.h>

DBTransform::DBTransform() {
	x = 0;
	y = 0;
	skewX = 0;
	skewY = 0;
	scaleX = 1;
	scaleY = 1;
}

DBTransform::~DBTransform() {
	// TODO Auto-generated destructor stub
}

DBTransform::DBTransform(const DBTransform & transform) {
	x = transform.x;
	y = transform.y;
	skewX = transform.skewX;
	skewY = transform.skewY;
	scaleX = transform.scaleX;
	scaleY = transform.scaleY;
}

float DBTransform::getRotation() {
	return skewX;
}

void DBTransform::setRotation(float value) {
	skewX = skewY = value;
}

std::string DBTransform::toString() {
	char temp[256];
	sprintf(temp, "x:%.6f y:%.6f skewX:%.6f skewY:%.6f scaleX:%.6f scaleY:%.6f", x, y, skewX, skewY, scaleX, scaleY);
	std::string str = temp;
	return str;
}
