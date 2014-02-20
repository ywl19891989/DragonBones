/*
 * TransformFrame.h
 *
 *  Created on: 2014-2-19
 *      Author: Hali
 */

#ifndef TRANSFORMFRAME_H_
#define TRANSFORMFRAME_H_

#include "Frame.h"
#include "ColorTransform.h"
#include "DBTransform.h"
#include "Point.h"

class TransformFrame: public Frame {
public:
	TransformFrame();
	virtual ~TransformFrame();

	float tweenEasing;
	int tweenRotate;
	int displayIndex;
	bool visible;
	float zOrder;

	DBTransform global;
	DBTransform transform;
	Point pivot;
	ColorTransform color;

	void dispose();
};

#endif /* TRANSFORMFRAME_H_ */
