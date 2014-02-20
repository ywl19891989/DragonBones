/*
 * Timeline.cpp
 *
 *  Created on: 2014-2-19
 *      Author: Hali
 */

#include "Timeline.h"
#include "Frame.h"
#include <algorithm>
#include <stdio.h>

Timeline::Timeline() {
	_duration = 0;
	_scale = 1;
}

Timeline::~Timeline() {
	// TODO Auto-generated destructor stub
}

const FrameArr & Timeline::getFrameList() {
	return _frameList;
}

float Timeline::getDuration() {
	return _duration;
}

void Timeline::setDuration(float value) {
	_duration = value >= 0 ? value : 0;
}

float Timeline::getScale() {
	return _scale;
}

void Timeline::setScale(float value) {
	_scale = value >= 0 ? value : 1;
}

void Timeline::dispose() {
	int i = _frameList.size();
	while (i--) {
		_frameList[i]->dispose();
		delete _frameList[i];
	}
	_frameList.clear();
}

void Timeline::addFrame(Frame* frame) {
	if (!frame) {
		printf("[Timeline] addFrame arg == NULL is invalid!\n");
	}

	typedef FrameArr::iterator FrameArrIt;
	FrameArrIt begin = _frameList.begin();
	FrameArrIt end = _frameList.end();
	FrameArrIt it = std::find(begin, end, frame);

	if (it == end) {
		_frameList.push_back(frame);
	} else {
		printf("[Timeline] addFrame arg is already added!\n");
	}
}
