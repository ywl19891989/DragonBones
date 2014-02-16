/*
 * ArmatureData.h
 *
 *  Created on: 2014-2-15
 *      Author: Hali
 */

#ifndef ARMATUREDATA_H_
#define ARMATUREDATA_H_

#include <vector>
#include <string>

typedef unsigned int uint;

class SkinData;
class BoneData;
class AnimationData;
class ArmatureData {
public:

	std::string name;

	ArmatureData();
	virtual ~ArmatureData();

	const std::vector<BoneData*> & getBoneDataList();
	const std::vector<SkinData*> & getSkinDataList();
	const std::vector<AnimationData*> & getAnimationDataList();

	void dispose();

	void addAnimationData(AnimationData* animationData);
	AnimationData* getAnimationData(std::string animationName);

	void addSkinData(SkinData* skinData);
	SkinData* getSkinData(std::string skinName);

	void sortBoneDataList();
	BoneData* getBoneData(std::string boneName);
	void addBoneData(BoneData* boneData);

private:

	typedef std::vector<BoneData*> BoneDataList;
	typedef std::vector<BoneData*>::iterator BoneDataListIt;
	typedef std::vector<SkinData*> SkinDataList;
	typedef std::vector<SkinData*>::iterator SkinDataListIt;
	typedef std::vector<AnimationData*> AnimationDataList;
	typedef std::vector<AnimationData*>::iterator AnimationDataListIt;

	BoneDataList _boneDataList;
	SkinDataList _skinDataList;
	AnimationDataList _animationDataList;
};

#endif /* ARMATUREDATA_H_ */
