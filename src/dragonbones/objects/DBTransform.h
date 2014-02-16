/*
 * DBTransform.h
 *
 *  Created on: 2014-2-16
 *      Author: Hali
 */

#ifndef DBTRANSFORM_H_
#define DBTRANSFORM_H_

#include <string>

class DBTransform {
public:
	/**
	 * Creat a new DBTransform instance.
	 */
	DBTransform();
	virtual ~DBTransform();

	/**
	 * Copy all properties from this DBTransform instance to the passed DBTransform instance.
	 * @param	node
	 */
	DBTransform(const DBTransform & transform);

	/**
	 * Position on the x axis.
	 */
	float x;
	/**
	 * Position on the y axis.
	 */
	float y;
	/**
	 * Skew on the x axis.
	 */
	float skewX;
	/**
	 * skew on the y axis.
	 */
	float skewY;
	/**
	 * Scale on the x axis.
	 */
	float scaleX;
	/**
	 * Scale on the y axis.
	 */
	float scaleY;
	/**
	 * The rotation of that DBTransform instance.
	 */
	float getRotation();

	void setRotation(float value);

	/**
	 * Get a string representing all DBTransform property values.
	 * @return String All property values in a formatted string.
	 */
	std::string toString();
};

#endif /* DBTRANSFORM_H_ */
