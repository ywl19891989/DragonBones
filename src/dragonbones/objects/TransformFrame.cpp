/*
 * TransformFrame.cpp
 *
 *  Created on: 2014-2-19
 *      Author: Hali
 */

#include "TransformFrame.h"

TransformFrame::TransformFrame() {
	// TODO Auto-generated constructor stub
	tweenEasing = 0;
	tweenRotate = 0;
	displayIndex = 0;
	visible = true;
	zOrder = 0;
}

TransformFrame::~TransformFrame() {
	// TODO Auto-generated destructor stub
}

void TransformFrame::dispose() {
	Frame::dispose();
}
