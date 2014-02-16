/*
 * ArmatureData.cpp
 *
 *  Created on: 2014-2-15
 *      Author: Hali
 */

#include "ArmatureData.h"
#include "BoneData.h"
#include "SkinData.h"
#include <algorithm>
#include <stdio.h>
#include <map>

ArmatureData::ArmatureData() {

}

ArmatureData::~ArmatureData() {
	// TODO Auto-generated destructor stub
}

void ArmatureData::dispose() {
	uint i = _boneDataList.size();
	while (i--) {
		_boneDataList[i]->dispose();
	}

	i = _skinDataList.size();
	while (i--) {
		_skinDataList[i]->dispose();
	}

	i = _animationDataList.size();
	while (i--) {
//		_animationDataList[i]->dispose();
	}
	_boneDataList.clear();
	_skinDataList.clear();
	_animationDataList.clear();
}

const std::vector<AnimationData*> & ArmatureData::getAnimationDataList() {
	return _animationDataList;
}

void ArmatureData::addAnimationData(AnimationData* animationData) {
	if (!animationData) {
		printf("[ArmatureData] addAnimationData arg is NULL!\n");
	}

	AnimationDataListIt begin = _animationDataList.begin();
	AnimationDataListIt end = _animationDataList.end();
	AnimationDataListIt it = std::find(begin, end, animationData);

	if (it == end) {
		_animationDataList.push_back(animationData);
	} else {
		printf("[ArmatureData] addAnimationData arg is already added!\n");
	}
}

AnimationData* ArmatureData::getAnimationData(std::string animationName) {
	uint i = _animationDataList.size();
	while (i--) {
//		if (_animationDataList[i].name == animationName) {
//			return _animationDataList[i];
//		}
	}
	return NULL;
}

const std::vector<SkinData*> & ArmatureData::getSkinDataList() {
	return _skinDataList;
}

void ArmatureData::addSkinData(SkinData* skinData) {
	if (!skinData) {
		printf("[ArmatureData] addSkinData arg is NULL!\n");
	}

	SkinDataListIt begin = _skinDataList.begin();
	SkinDataListIt end = _skinDataList.end();
	SkinDataListIt it = std::find(begin, end, skinData);

	if (it == end) {
		_skinDataList.push_back(skinData);
	} else {
		printf("[ArmatureData] addSkinData arg is already added!\n");
	}
}

SkinData* ArmatureData::getSkinData(std::string skinName) {
	uint i = _skinDataList.size();
	while (i--) {
		if (_skinDataList[i]->name == skinName) {
			return _skinDataList[i];
		}
	}

	return NULL;
}

typedef struct __helpBoneStruct {
	int level;
	BoneData* boneData;
} HelpBoneSturct;

int boneDataCmp(const HelpBoneSturct & a, const HelpBoneSturct& b) {
	if (a.level < b.level) {
		return 1;
	} else if (b.level < a.level) {
		return -1;
	}
	return 0;
}

void ArmatureData::sortBoneDataList() {
	uint i = _boneDataList.size();
	if (i == 0) {
		return;
	}

	std::vector<HelpBoneSturct> helpArray;

	while (i--) {
		BoneData* boneData = _boneDataList[i];
		int level = 0;
		BoneData* parentData = boneData;
		while (parentData && !parentData->parent.empty()) {
			level++;
			parentData = getBoneData(parentData->parent);
		}
		HelpBoneSturct h;
		h.level = level;
		h.boneData = boneData;
		helpArray[i] = h;
	}

	sort(helpArray.begin(), helpArray.end(), boneDataCmp);

	i = helpArray.size();
	while (i--) {
		_boneDataList[i] = helpArray[i].boneData;
	}
}

const std::vector<BoneData*> & ArmatureData::getBoneDataList() {
	return _boneDataList;
}

BoneData* ArmatureData::getBoneData(std::string boneName) {
	uint i = _boneDataList.size();
	while (i--) {
		if (_boneDataList[i]->name == boneName) {
			return _boneDataList[i];
		}
	}
	return NULL;
}

void ArmatureData::addBoneData(BoneData* boneData) {
	if (!boneData) {
		printf("[ArmatureData] addBoneData arg is NULL!\n");
	}

	BoneDataListIt begin = _boneDataList.begin();
	BoneDataListIt end = _boneDataList.end();
	BoneDataListIt it = std::find(begin, end, boneData);

	if (it == end) {
		_boneDataList.push_back(boneData);
	} else {
		printf("[ArmatureData] addBoneData arg is already added!\n");
	}
}
