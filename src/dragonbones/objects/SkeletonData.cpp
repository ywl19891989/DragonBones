/*
 * SkeletonData.cpp
 *
 *  Created on: 2014-2-15
 *      Author: Hali
 */

#include "SkeletonData.h"
#include "ArmatureData.h"
#include <algorithm>
#include <stdio.h>

typedef unsigned int uint;

SkeletonData::SkeletonData() {
	// TODO Auto-generated constructor stub

}

SkeletonData::~SkeletonData() {
	// TODO Auto-generated destructor stub
}

std::vector<std::string> SkeletonData::getArmatureNames() {
	std::vector<std::string> nameList;
	for (uint i = 0; i < _armatureDataList.size(); i++) {
		ArmatureData* armatureData = _armatureDataList[i];
		nameList[i] = armatureData->name;
	}
	return nameList;
}

const std::vector<ArmatureData*> & SkeletonData::getArmatureDataList() {
	return _armatureDataList;
}

void SkeletonData::dispose() {
	for (uint i = 0; i < _armatureDataList.size(); i++) {
		ArmatureData* armatureData = _armatureDataList[i];
		armatureData->dispose();
		delete armatureData;
	}

	_armatureDataList.clear();
	_subTexturePivots.clear();
}

ArmatureData* SkeletonData::getArmatureData(std::string armatureName) {
	uint i = _armatureDataList.size();
	while (i--) {
		if (_armatureDataList[i]->name == armatureName) {
			return _armatureDataList[i];
		}
	}

	return NULL;
}

void SkeletonData::addArmatureData(ArmatureData* armatureData) {
	if (!armatureData) {
		printf("[SekletonData]: addArmatureData argument is NULL!\n");
	}

	ArmatureDataArr::iterator begin = _armatureDataList.begin();
	ArmatureDataArr::iterator end = _armatureDataList.end();

	ArmatureDataArr::iterator it = std::find(begin, end, armatureData);

	if (it == end) {
		_armatureDataList.push_back(armatureData);
	} else {
		printf("[SekletonData]: addArmatureData already added!\n");
	}
}

void SkeletonData::removeArmatureData(ArmatureData* armatureData) {

	ArmatureDataArr::iterator begin = _armatureDataList.begin();
	ArmatureDataArr::iterator end = _armatureDataList.end();

	ArmatureDataArr::iterator it = std::find(begin, end, armatureData);
	if (it != end) {
		_armatureDataList.erase(it);
	}
}

void SkeletonData::removeArmatureDataByName(std::string armatureName) {

	ArmatureData* data = getArmatureData(armatureName);

	if (data != NULL) {
		removeArmatureData(data);
	}
}

const Point & SkeletonData::getSubTexturePivot(std::string subTextureName) {
	return _subTexturePivots[subTextureName];
}

const Point & SkeletonData::addSubTexturePivot(float x, float y, std::string subTextureName) {
	Point & point = _subTexturePivots[subTextureName];
	point.set(x, y);

	return point;
}

void SkeletonData::removeSubTexturePivot(std::string subTextureName) {
	if (!subTextureName.empty()) {
		std::map<std::string, Point>::iterator it = _subTexturePivots.find(subTextureName);
		if (it != _subTexturePivots.end()) {
			_subTexturePivots.erase(it);
		}
	} else {
		_subTexturePivots.clear();
	}
}
