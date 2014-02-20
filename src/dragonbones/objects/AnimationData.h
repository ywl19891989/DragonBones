/*
 * AnimationData.h
 *
 *  Created on: 2014-2-19
 *      Author: Hali
 */

#ifndef ANIMATIONDATA_H_
#define ANIMATIONDATA_H_

#include "Timeline.h"
#include <string>
#include <map>

class TransformTimeline;
typedef std::map<std::string, TransformTimeline*> TimelineDict;

class AnimationData: public Timeline {
public:
	AnimationData();
	virtual ~AnimationData();

	int frameRate;
	std::string name;
	int loop;
	float tweenEasing;

	const TimelineDict & getTimelines();

	float getFadeInTime();
	void setFadeInTime(float value);

	void dispose();

	TransformTimeline* getTimeline(const std::string & timelineName);
	void addTimeline(TransformTimeline* timeline, const std::string & timelineName);

private:
	TimelineDict _timelines;
	float _fadeTime;
};

#endif /* ANIMATIONDATA_H_ */
