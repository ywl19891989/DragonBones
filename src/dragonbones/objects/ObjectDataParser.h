/*
 * ObjectDataParser.h
 *
 *  Created on: 2014-2-14
 *      Author: Hali
 */

#ifndef OBJECTDATAPARSER_H_
#define OBJECTDATAPARSER_H_

#include "json.h"

class Point;
class SkinData;
class SlotData;
class BoneData;
class DisplayData;
class DBTransform;
class ArmatureData;
class SkeletonData;
class AnimationData;
class ObjectDataParser {
public:
	ObjectDataParser();
	virtual ~ObjectDataParser();

	static SkeletonData* parseSkeletonData(Json::Value & rawData);

private:

	typedef unsigned int uint;

	static ArmatureData* parseArmatureData(Json::Value & armatureObject, SkeletonData* data, uint frameRate);

	static BoneData* parseBoneData(Json::Value & boneObject);

	static SkinData* parseSkinData(Json::Value & skinObject, SkeletonData* data);

	static AnimationData* parseAnimationData(Json::Value & animationObject, ArmatureData* armatureData, uint frameRate);

	static void parseTransform(Json::Value & transformObject, DBTransform & transform, Point* pivot = NULL);

	static SlotData* parseSlotData(Json::Value & slotObject, SkeletonData* data);

	static DisplayData* parseDisplayData(Json::Value & displayObject, SkeletonData* data);
};

#endif /* OBJECTDATAPARSER_H_ */
