/*
 * BoneData.h
 *
 *  Created on: 2014-2-15
 *      Author: Hali
 */

#ifndef BONEDATA_H_
#define BONEDATA_H_

#include <string>
#include "DBTransform.h"

class BoneData {
public:
	BoneData();
	virtual ~BoneData();

	std::string name;
	std::string parent;
	float length;
	DBTransform global;
	DBTransform transform;
	int scaleMode;
	bool fixedRotation;

	void dispose();
};

#endif /* BONEDATA_H_ */
