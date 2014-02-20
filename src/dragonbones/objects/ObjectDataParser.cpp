/*
 * ObjectDataParser.cpp
 *
 *  Created on: 2014-2-14
 *      Author: Hali
 */

#include "ObjectDataParser.h"
#include "dragonbones/utils/ConstValues.h"
#include "dragonbones/utils/DBDataUtil.h"
#include "dragonbones/core/DragonBones.h"
#include "Point.h"
#include "Frame.h"
#include "BoneData.h"
#include "SkinData.h"
#include "SlotData.h"
#include "DBTransform.h"
#include "DisplayData.h"
#include "SkeletonData.h"
#include "ArmatureData.h"
#include "AnimationData.h"
#include "TransformTimeline.h"
#include "Transformframe.h"
#include "ColorTransform.h"
#include <string>
#include <stdio.h>

using namespace std;

SkeletonData* ObjectDataParser::parseSkeletonData(Json::Value & rawData) {

	double version = rawData[ConstValues::A_VERSION].asDouble();

	if (version != DragonBones::DATA_VERSION) {
		printf("[ObjectDataParser] Nonsupport version %f!\n", version);
	}

	unsigned int frameRate = rawData[ConstValues::A_FRAME_RATE].asUInt();

	SkeletonData* data = new SkeletonData();
	data->name = rawData[ConstValues::A_NAME].asCString();

	Json::Value & armature = rawData[ConstValues::ARMATURE];

	printf("armature size %u\n", armature.size());
	for (unsigned int i = 0; i < armature.size(); i++) {
		Json::Value & armatureObject = armature[i];
		data->addArmatureData(parseArmatureData(armatureObject, data, frameRate));
	}

	return data;
}

ArmatureData* ObjectDataParser::parseArmatureData(Json::Value & armatureObject, SkeletonData* data,
		unsigned int frameRate) {
	ArmatureData* armatureData = new ArmatureData();
	armatureData->name = armatureObject[ConstValues::A_NAME].asCString();

	Json::Value & bones = armatureObject[ConstValues::BONE];

	for (unsigned int i = 0; i < bones.size(); i++) {
		Json::Value & boneObject = bones[i];
		armatureData->addBoneData(parseBoneData(boneObject));
	}

	Json::Value & skins = armatureObject[ConstValues::SKIN];
	for (unsigned int i = 0; i < skins.size(); i++) {
		Json::Value & skinObject = skins[i];
		armatureData->addSkinData(parseSkinData(skinObject, data));
	}

	DBDataUtil::transformArmatureData(armatureData);
	armatureData->sortBoneDataList();

	Json::Value & animitions = armatureObject[ConstValues::ANIMATION];
	for (unsigned int i = 0; i < animitions.size(); i++) {
		Json::Value & animationObject = animitions[i];
		armatureData->addAnimationData(parseAnimationData(animationObject, armatureData, frameRate));
	}

	return armatureData;
}

BoneData * ObjectDataParser::parseBoneData(Json::Value & boneObject) {
	BoneData* boneData = new BoneData;

	boneData->name = boneObject[ConstValues::A_NAME].asCString();
	boneData->parent = boneObject.isMember(ConstValues::A_PARENT) ? boneObject[ConstValues::A_PARENT].asCString() : "";
	boneData->length = boneObject.isMember(ConstValues::A_LENGTH) ? boneObject[ConstValues::A_LENGTH].asInt() : 0;
	Json::Value & scaleModeObj = boneObject[ConstValues::A_SCALE_MODE];
	if (scaleModeObj != Json::Value::null) {
		int scaleMode = scaleModeObj.asInt();
		boneData->scaleMode = scaleMode;
	}
	bool inheritRotation = boneObject[ConstValues::A_FIXED_ROTATION].asBool();
	if (inheritRotation) {
		boneData->fixedRotation = inheritRotation;
	}

	parseTransform(boneObject[ConstValues::TRANSFORM], boneData->global);
	boneData->transform = boneData->global;

	return boneData;
}

void ObjectDataParser::parseTransform(Json::Value & transformObject, DBTransform & transform, Point* pivot/* = NULL*/) {
	if (transformObject != Json::Value::null) {
		transform.x = transformObject[ConstValues::A_X].asDouble();
		transform.y = transformObject[ConstValues::A_Y].asDouble();
		transform.skewX = transformObject[ConstValues::A_SKEW_X].asDouble() * ConstValues::ANGLE_TO_RADIAN;
		transform.skewY = transformObject[ConstValues::A_SKEW_Y].asDouble() * ConstValues::ANGLE_TO_RADIAN;
		transform.scaleX = transformObject[ConstValues::A_SCALE_X].asDouble();
		transform.scaleY = transformObject[ConstValues::A_SCALE_Y].asDouble();
		if (pivot) {
			pivot->x = transformObject[ConstValues::A_PIVOT_X].asDouble();
			pivot->y = transformObject[ConstValues::A_PIVOT_Y].asDouble();
		}
	}
}

SkinData * ObjectDataParser::parseSkinData(Json::Value & skinObject, SkeletonData * data) {
	SkinData* skinData = new SkinData();
	int nameVal = skinObject[ConstValues::A_NAME].asInt();
	char temp[64];
	sprintf(temp, "%d", nameVal);
	skinData->name = temp;

	Json::Value & slots = skinObject[ConstValues::SLOT];

	for (uint i = 0; i < slots.size(); i++) {
		Json::Value & slotObject = slots[i];
		skinData->addSlotData(parseSlotData(slotObject, data));
	}

	return skinData;
}

SlotData* ObjectDataParser::parseSlotData(Json::Value & slotObject, SkeletonData* data) {
	SlotData* slotData = new SlotData();
	slotData->name = slotObject[ConstValues::A_NAME].asCString();
	slotData->parent = slotObject[ConstValues::A_PARENT].asCString();
	slotData->zOrder = slotObject[ConstValues::A_Z_ORDER].asDouble();
	if (!slotObject.isMember(ConstValues::A_BLENDMODE)) {
		slotData->blendMode = "normal";
	} else {
		slotData->blendMode = slotObject[ConstValues::A_BLENDMODE].asCString();
	}

	Json::Value & displays = slotObject[ConstValues::DISPLAY];

	for (uint i = 0; i < displays.size(); i++) {
		Json::Value & displayObject = displays[i];
		slotData->addDisplayData(parseDisplayData(displayObject, data));
	}

	return slotData;
}

DisplayData* ObjectDataParser::parseDisplayData(Json::Value & displayObject, SkeletonData* data) {
	DisplayData* displayData = new DisplayData();
	displayData->name = displayObject[ConstValues::A_NAME].asCString();
	displayData->type = displayObject[ConstValues::A_TYPE].asCString();

	displayData->pivot = data->addSubTexturePivot(0, 0, displayData->name);

	parseTransform(displayObject[ConstValues::TRANSFORM], displayData->transform, &(displayData->pivot));

	return displayData;
}

AnimationData* ObjectDataParser::parseAnimationData(Json::Value & animationObject, ArmatureData* armatureData,
		int frameRate) {
	AnimationData* animationData = new AnimationData();
	if(animationObject[ConstValues::A_NAME].isString()){
		animationData->name = animationObject[ConstValues::A_NAME].asCString();
	}else if(animationObject[ConstValues::A_NAME].isInt()){
		char temp[64];
		sprintf(temp, "%d", animationObject[ConstValues::A_NAME].asInt());
		animationData->name = temp;
	}
	animationData->frameRate = frameRate;
	animationData->loop = animationObject[ConstValues::A_LOOP].asInt();
	animationData->setFadeInTime(animationObject[ConstValues::A_FADE_IN_TIME].asDouble());
	animationData->setDuration(animationObject[ConstValues::A_DURATION].asDouble() / frameRate);
	animationData->setScale(animationObject[ConstValues::A_SCALE].asDouble());

	if (animationObject.isMember(ConstValues::A_TWEEN_EASING)) {
		float tweenEase = animationObject[ConstValues::A_TWEEN_EASING].asDouble();
		animationData->tweenEasing = tweenEase;
	}

	parseTimeline(animationObject, animationData, ObjectDataParser::parseMainFrame, frameRate);

	TransformTimeline* timeline = NULL;
	std::string timelineName;
	Json::Value & timelines = animationObject[ConstValues::TIMELINE];
	for (uint i = 0; i < timelines.size(); i++) {
		Json::Value & timelineObject = timelines[i];
		timeline = parseTransformTimeline(timelineObject, animationData->getDuration(), frameRate);
		timelineName = timelineObject[ConstValues::A_NAME].asCString();
		animationData->addTimeline(timeline, timelineName);
	}

	//DBDataUtil::addHideTimeline(animationData, armatureData);
	DBDataUtil::transformAnimationData(animationData, armatureData);

	return animationData;
}

void ObjectDataParser::parseTimeline(Json::Value & timelineObject, Timeline* timeline, FrameParseFunc frameParser,
		int frameRate) {
	float position;
	Frame* frame = NULL;
	Json::Value & frames = timelineObject[ConstValues::FRAME];
	for (uint i = 0; i < frames.size(); i++) {
		Json::Value & frameObject = frames[i];
		frame = frameParser(frameObject, frameRate);
		frame->position = position;
		timeline->addFrame(frame);
		position += frame->duration;
	}
	if (frame) {
		frame->duration = timeline->getDuration() - frame->position;
	}
}

TransformTimeline* ObjectDataParser::parseTransformTimeline(Json::Value &timelineObject, float duration,
		int frameRate) {
	TransformTimeline* timeline = new TransformTimeline();
	timeline->setDuration(duration);

	parseTimeline(timelineObject, timeline, ObjectDataParser::parseTransformFrame, frameRate);

	timeline->setScale(timelineObject[ConstValues::A_SCALE].asDouble());
	timeline->setOffset(timelineObject[ConstValues::A_OFFSET].asDouble());

	return timeline;
}

Frame* ObjectDataParser::parseMainFrame(Json::Value & frameObject, int frameRate) {
	Frame* frame = new Frame();
	parseFrame(frameObject, frame, frameRate);
	return frame;
}

void ObjectDataParser::parseFrame(Json::Value & frameObject, Frame* frame, int frameRate) {
	frame->duration = frameObject[ConstValues::A_DURATION].asDouble() / frameRate;

#define Get_IF_HASMEMBER(a, b) if(frameObject.isMember(b)){frame->a = frameObject[b].asCString();}

	Get_IF_HASMEMBER(action, ConstValues::A_ACTION);
	Get_IF_HASMEMBER(event, ConstValues::A_EVENT);
	Get_IF_HASMEMBER(sound, ConstValues::A_SOUND);
}

Frame* ObjectDataParser::parseTransformFrame(Json::Value & frameObject, int frameRate) {
	TransformFrame* frame = new TransformFrame();
	parseFrame(frameObject, frame, frameRate);

	int hide = frameObject[ConstValues::A_HIDE].asInt();
	frame->visible = (hide != 1);

	if (frameObject.isMember(ConstValues::A_TWEEN_EASING)) {
		float tweenEase = frameObject[ConstValues::A_TWEEN_EASING].asDouble();
		frame->tweenEasing = tweenEase;
	}

	frame->tweenRotate = frameObject[ConstValues::A_TWEEN_ROTATE].asInt();
	frame->displayIndex = frameObject[ConstValues::A_DISPLAY_INDEX].asInt();
	//
	frame->zOrder = frameObject[ConstValues::A_Z_ORDER].asDouble();

	parseTransform(frameObject[ConstValues::TRANSFORM], frame->global, &frame->pivot);
	frame->transform = frame->global;

	if (frameObject.isMember(ConstValues::COLOR_TRANSFORM)) {
		Json::Value & colorTransformObject = frameObject[ConstValues::COLOR_TRANSFORM];
		frame->color.alphaOffset = colorTransformObject[ConstValues::A_ALPHA_OFFSET].asDouble();
		frame->color.redOffset = colorTransformObject[ConstValues::A_RED_OFFSET].asDouble();
		frame->color.greenOffset = colorTransformObject[ConstValues::A_GREEN_OFFSET].asDouble();
		frame->color.blueOffset = colorTransformObject[ConstValues::A_BLUE_OFFSET].asDouble();

		frame->color.alphaMultiplier = colorTransformObject[ConstValues::A_ALPHA_MULTIPLIER].asDouble() * 0.01f;
		frame->color.redMultiplier = colorTransformObject[ConstValues::A_RED_MULTIPLIER].asDouble() * 0.01f;
		frame->color.greenMultiplier = colorTransformObject[ConstValues::A_GREEN_MULTIPLIER].asDouble() * 0.01f;
		frame->color.blueMultiplier = colorTransformObject[ConstValues::A_BLUE_MULTIPLIER].asDouble() * 0.01f;
	}

	return frame;
}
