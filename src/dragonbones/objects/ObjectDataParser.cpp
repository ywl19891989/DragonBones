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
#include "BoneData.h"
#include "SkinData.h"
#include "SlotData.h"
#include "DisplayData.h"
#include "SkeletonData.h"
#include "ArmatureData.h"
#include "DBTransform.h"
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
		Json::Value & animationObject = skins[i];
		armatureData->addAnimationData(parseAnimationData(animationObject, armatureData, frameRate));
	}

	return armatureData;
}

BoneData * ObjectDataParser::parseBoneData(Json::Value & boneObject) {
	BoneData* boneData = new BoneData;

	boneData->name = boneObject[ConstValues::A_NAME].asCString();
	boneData->parent = boneObject[ConstValues::A_PARENT].asCString();
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
	skinData->name = skinObject[ConstValues::A_NAME].asCString();

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
		uint frameRate) {
	AnimationData* animData = NULL;

	return animData;
}
