/*
 * TransformTimeline.cpp
 *
 *  Created on: 2014-2-19
 *      Author: Hali
 */

#include "TransformTimeline.h"

#define NULL 0

const TransformTimeline TransformTimeline::HIDE_TIMELINE;

TransformTimeline::TransformTimeline() {
	_offset = 0;
	transformed = false;
}

TransformTimeline::~TransformTimeline() {
	// TODO Auto-generated destructor stub
}

float TransformTimeline::getOffset() {
	return _offset;
}

void TransformTimeline::setOffset(float value) {
	_offset = value;
	while (_offset < 0) {
		_offset += 1;
	}
}

void TransformTimeline::dispose() {
	if (this == &HIDE_TIMELINE) {
		return;
	}
	TransformTimeline::dispose();
}
