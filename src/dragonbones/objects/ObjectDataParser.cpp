/*
 * ObjectDataParser.cpp
 *
 *  Created on: 2014-2-14
 *      Author: Hali
 */

#include "ObjectDataParser.h"
#include "dragonbones/utils/ConstValues.h"
#include "dragonbones/core/DragonBones.h"
#include "Point.h"
#include "BoneData.h"
#include "SkinData.h"
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

//	DBDataUtil.transformArmatureData(armatureData);
//	armatureData.sortBoneDataList();

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
	SkinData* skinData = NULL;

	return skinData;
}

AnimationData* ObjectDataParser::parseAnimationData(Json::Value & animationObject, ArmatureData* armatureData,
		uint frameRate) {
	AnimationData* animData = NULL;

	return animData;
}
