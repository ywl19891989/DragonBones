/*
 * Timeline.h
 *
 *  Created on: 2014-2-19
 *      Author: Hali
 */

#ifndef TIMELINE_H_
#define TIMELINE_H_

#include <vector>

class Frame;

typedef std::vector<Frame*> FrameArr;

class Timeline {
public:
	Timeline();
	virtual ~Timeline();

	const FrameArr & getFrameList();

	float getDuration();
	void setDuration(float value);

	float getScale();
	void setScale(float value);

	virtual void dispose();

	void addFrame(Frame* frame);

private:
	FrameArr _frameList;
	float _duration;
	float _scale;
};

#endif /* TIMELINE_H_ */
