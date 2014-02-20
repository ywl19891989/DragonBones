/*
 * AnimationData.cpp
 *
 *  Created on: 2014-2-19
 *      Author: Hali
 */

#include "AnimationData.h"
#include "TransformTimeline.h"
#include <stdio.h>

AnimationData::AnimationData() {
	loop = 0;
	tweenEasing = -1;
	_fadeTime = 0;
	frameRate = 0;
}

AnimationData::~AnimationData() {
	// TODO Auto-generated destructor stub
}

const TimelineDict & AnimationData::getTimelines() {
	return _timelines;
}

float AnimationData::getFadeInTime() {
	return _fadeTime;
}

void AnimationData::setFadeInTime(float value) {
	_fadeTime = value;
}

void AnimationData::dispose() {
	Timeline::dispose();

	TimelineDict::iterator it = _timelines.begin();

	while (it != _timelines.end()) {
		Timeline* timeline = it->second;
		timeline->dispose();
		delete timeline;
	}
	_timelines.clear();
}

TransformTimeline* AnimationData::getTimeline(const std::string & timelineName) {
	return (TransformTimeline*) _timelines[timelineName];
}

void AnimationData::addTimeline(TransformTimeline* timeline, const std::string & timelineName) {
	if (!timeline) {
		printf("[AnimationData] addTimeline arg is NULL!\n");
	}

	_timelines[timelineName] = timeline;
}
