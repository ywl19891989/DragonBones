/*
 * SkeletonData.h
 *
 *  Created on: 2014-2-15
 *      Author: Hali
 */

#ifndef SKELETONDATA_H_
#define SKELETONDATA_H_

#include "Point.h"
#include <vector>
#include <string>
#include <map>

class ArmatureData;
class SkeletonData {
public:
	SkeletonData();
	virtual ~SkeletonData();

	std::vector<std::string> getArmatureNames();

	const std::vector<ArmatureData*> & getArmatureDataList();

	void dispose();

	ArmatureData* getArmatureData(std::string armatureName);

	void addArmatureData(ArmatureData* armatureData);

	void removeArmatureData(ArmatureData* armatureData);

	void removeArmatureDataByName(std::string armatureName);

	const Point & getSubTexturePivot(std::string subTextureName);

	const Point & addSubTexturePivot(float x, float y, std::string subTextureName);

	void removeSubTexturePivot(std::string subTextureName);

	std::string name;

private:
	std::map<std::string, Point> _subTexturePivots;
	std::vector<ArmatureData*> _armatureDataList;

	typedef std::vector<ArmatureData*> ArmatureDataArr;
};

#endif /* SKELETONDATA_H_ */
