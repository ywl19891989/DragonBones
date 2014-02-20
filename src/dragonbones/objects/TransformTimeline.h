/*
 * TransformTimeline.h
 *
 *  Created on: 2014-2-19
 *      Author: Hali
 */

#ifndef TRANSFORMTIMELINE_H_
#define TRANSFORMTIMELINE_H_

#include "Timeline.h"
#include "DBTransform.h"
#include "Point.h"

class TransformTimeline: public Timeline {
public:
	TransformTimeline();
	virtual ~TransformTimeline();

	static const TransformTimeline HIDE_TIMELINE;

	bool transformed;

	DBTransform originTransform;
	Point originPivot;

	float getOffset();
	void setOffset(float value);

	void dispose();

private:
	float _offset;
};

#endif /* TRANSFORMTIMELINE_H_ */
