/*
 * Point.h
 *
 *  Created on: 2014-2-15
 *      Author: Hali
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	Point(float x = 0, float y = 0);
	virtual ~Point();

	void set(float x, float y);

	float x;
	float y;
};

#endif /* POINT_H_ */
