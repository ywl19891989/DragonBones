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
class Frame;
class Timeline;
class SkinData;
class SlotData;
class BoneData;
class DisplayData;
class DBTransform;
class ArmatureData;
class SkeletonData;
class AnimationData;
class TransformTimeline;
class ObjectDataParser {
public:
	ObjectDataParser();
	virtual ~ObjectDataParser();

	static SkeletonData* parseSkeletonData(Json::Value & rawData);

private:

	typedef unsigned int uint;

	typedef Frame* (*FrameParseFunc)(Json::Value & frameObject, int frameRate);

	static ArmatureData* parseArmatureData(Json::Value & armatureObject, SkeletonData* data, uint frameRate);

	static BoneData* parseBoneData(Json::Value & boneObject);

	static SkinData* parseSkinData(Json::Value & skinObject, SkeletonData* data);

	static AnimationData* parseAnimationData(Json::Value & animationObject, ArmatureData* armatureData, int frameRate);

	static void parseTransform(Json::Value & transformObject, DBTransform & transform, Point* pivot = NULL);

	static SlotData* parseSlotData(Json::Value & slotObject, SkeletonData* data);

	static DisplayData* parseDisplayData(Json::Value & displayObject, SkeletonData* data);

	static void parseTimeline(Json::Value & timelineObject, Timeline* timeline, FrameParseFunc frameParser,
			int frameRate);

	static TransformTimeline* parseTransformTimeline(Json::Value &timelineObject, float duration, int frameRate);

	static void parseFrame(Json::Value & frameObject, Frame* frame, int frameRate);

	static Frame* parseTransformFrame(Json::Value & frameObject, int frameRate);

	static Frame* parseMainFrame(Json::Value & frameObject, int frameRate);
};

#endif /* OBJECTDATAPARSER_H_ */
