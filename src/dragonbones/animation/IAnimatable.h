/*
 * IAnimatable.h
 *
 *  Created on: 2014-3-1
 *      Author: Hali
 */

#ifndef IANIMATABLE_H_
#define IANIMATABLE_H_

class IAnimatable {
public:
	IAnimatable();
	virtual ~IAnimatable();

	virtual void advanceTime(float passedTime);
};

#endif /* IANIMATABLE_H_ */
