/*
 * Frame.h
 *
 *  Created on: 2014-2-19
 *      Author: Hali
 */

#ifndef FRAME_H_
#define FRAME_H_

#include <string>

class Frame {
public:
	Frame();
	virtual ~Frame();

	float position;
	float duration;

	std::string action;
	std::string event;
	std::string sound;

	virtual void dispose();

};

#endif /* FRAME_H_ */
