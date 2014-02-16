/*
 * DisplayData.h
 *
 *  Created on: 2014-2-16
 *      Author: Hali
 */

#ifndef DISPLAYDATA_H_
#define DISPLAYDATA_H_

#include <string>
#include "DBTransform.h"
#include "Point.h"

class DisplayData {
public:
	DisplayData();
	virtual ~DisplayData();

	static const std::string ARMATURE;
	static const std::string IMAGE;

	std::string name;
	std::string type;
	DBTransform transform;
	Point pivot;

	void dispose();
};

#endif /* DISPLAYDATA_H_ */
