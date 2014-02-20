/*
 * DBDataUtil.cpp
 *
 *  Created on: 2014-2-16
 *      Author: Hali
 */

#include "DBDataUtil.h"
#include "dragonbones/objects/SkinData.h"
#include "dragonbones/objects/BoneData.h"
#include "dragonbones/objects/SlotData.h"
#include "dragonbones/objects/TransformTimeline.h"
#include "dragonbones/objects/AnimationData.h"
#include "dragonbones/objects/TransformFrame.h"
#include "dragonbones/objects/ArmatureData.h"
#include "TransformUtil.h"
#include <vector>
#include <math.h>

DBTransform DBDataUtil::_helpTransform1;
DBTransform DBDataUtil::_helpTransform2;

DBDataUtil::DBDataUtil() {
	// TODO Auto-generated constructor stub

}

DBDataUtil::~DBDataUtil() {
	// TODO Auto-generated destructor stub
}

void DBDataUtil::transformArmatureData(ArmatureData* armatureData) {
	const std::vector<BoneData*> & boneDataList = armatureData->getBoneDataList();
	uint i = boneDataList.size();
	BoneData* boneData = NULL;
	BoneData* parentBoneData = NULL;
	while (i--) {
		boneData = boneDataList[i];
		if (!boneData->parent.empty()) {
			parentBoneData = armatureData->getBoneData(boneData->parent);
			if (parentBoneData != NULL) {
				boneData->transform = boneData->global;
				TransformUtil::transformPointWithParent(boneData->transform, parentBoneData->global);
			}
		}
	}
}

void DBDataUtil::transformArmatureDataAnimations(ArmatureData* armatureData) {
	const std::vector<AnimationData*> & animationDataList = armatureData->getAnimationDataList();
	uint i = animationDataList.size();
	while (i--) {
		transformAnimationData(animationDataList[i], armatureData);
	}
}

void DBDataUtil::transformAnimationData(AnimationData* animationData, ArmatureData* armatureData) {
	const std::vector<SkinData*> & skinDatas = armatureData->getSkinDataList();
	SkinData* skinData = skinDatas[0];
	const std::vector<BoneData*> & boneDataList = armatureData->getBoneDataList();
	const std::vector<SlotData*> & slotDataList = skinData->getSlotDataList();
	uint i = boneDataList.size();

	BoneData* boneData = NULL;
	TransformTimeline* timeline = NULL;
	SlotData* slotData = NULL;
	TransformTimeline* parentTimeline = NULL;

	DBTransform* originTransform;
	Point originPivot;
	uint frameListLength;

	TransformFrame* frame = NULL;
	TransformFrame* prevFrame = NULL;

	while (i--) {
		boneData = boneDataList[i];
		timeline = animationData->getTimeline(boneData->name);
		if (!timeline) {
			continue;
		}

		for (uint slotDataIndex = 0; slotDataIndex < slotDataList.size(); slotDataIndex++) {
			slotData = slotDataList[slotDataIndex];
			if (slotData->parent == boneData->name) {
				break;
			}
		}

		parentTimeline = !boneData->parent.empty() ? animationData->getTimeline(boneData->parent) : NULL;

		const std::vector<Frame*> & frameList = timeline->getFrameList();

		originTransform = NULL;
		prevFrame = NULL;
		frameListLength = frameList.size();
		for (uint j = 0; j < frameListLength; j++) {
			frame = (TransformFrame*)frameList[j];
			if (parentTimeline) {
				//tweenValues to transform.
				_helpTransform1 = frame->global;

				//get transform from parent timeline.
				getTimelineTransform(parentTimeline, frame->position, &_helpTransform2);
				TransformUtil::transformPointWithParent(_helpTransform1, _helpTransform2);

				//transform to tweenValues.
				frame->transform = _helpTransform1;
			} else {
				frame->transform = frame->global;
			}

			frame->transform.x -= boneData->transform.x;
			frame->transform.y -= boneData->transform.y;
			frame->transform.skewX -= boneData->transform.skewX;
			frame->transform.skewY -= boneData->transform.skewY;
			frame->transform.scaleX -= boneData->transform.scaleX;
			frame->transform.scaleY -= boneData->transform.scaleY;

			if (!timeline->transformed) {
				if (slotData) {
					frame->zOrder -= slotData->zOrder;
				}
			}

			if (!originTransform) {
				originTransform = &timeline->originTransform;
				*originTransform = frame->transform;
				originTransform->skewX = TransformUtil::formatRadian(originTransform->skewX);
				originTransform->skewY = TransformUtil::formatRadian(originTransform->skewY);
				originPivot = timeline->originPivot;
				originPivot.x = frame->pivot.x;
				originPivot.y = frame->pivot.y;
			}

			frame->transform.x -= originTransform->x;
			frame->transform.y -= originTransform->y;
			frame->transform.skewX = TransformUtil::formatRadian(frame->transform.skewX - originTransform->skewX);
			frame->transform.skewY = TransformUtil::formatRadian(frame->transform.skewY - originTransform->skewY);
			frame->transform.scaleX -= originTransform->scaleX;
			frame->transform.scaleY -= originTransform->scaleY;

			if (!timeline->transformed) {
				frame->pivot.x -= originPivot.x;
				frame->pivot.y -= originPivot.y;
			}

			if (prevFrame) {
				float dLX = frame->transform.skewX - prevFrame->transform.skewX;

				if (prevFrame->tweenRotate) {

					if (prevFrame->tweenRotate > 0) {
						if (dLX < 0) {
							frame->transform.skewX += M_PI * 2;
							frame->transform.skewY += M_PI * 2;
						}

						if (prevFrame->tweenRotate > 1) {
							frame->transform.skewX += M_PI * 2 * (prevFrame->tweenRotate - 1);
							frame->transform.skewY += M_PI * 2 * (prevFrame->tweenRotate - 1);
						}
					} else {
						if (dLX > 0) {
							frame->transform.skewX -= M_PI * 2;
							frame->transform.skewY -= M_PI * 2;
						}

						if (prevFrame->tweenRotate < 1) {
							frame->transform.skewX += M_PI * 2 * (prevFrame->tweenRotate + 1);
							frame->transform.skewY += M_PI * 2 * (prevFrame->tweenRotate + 1);
						}
					}
				} else {
					frame->transform.skewX = prevFrame->transform.skewX
							+ TransformUtil::formatRadian(frame->transform.skewX - prevFrame->transform.skewX);
					frame->transform.skewY = prevFrame->transform.skewY
							+ TransformUtil::formatRadian(frame->transform.skewY - prevFrame->transform.skewY);
				}
			}

			prevFrame = frame;
		}
		timeline->transformed = true;
	}
}

void DBDataUtil::getTimelineTransform(TransformTimeline* timeline, float position, DBTransform* result) {
	const std::vector<Frame*> & frameList = timeline->getFrameList();
	uint i = frameList.size();

	TransformFrame* currentFrame;
	float tweenEasing;
	float progress;
	TransformFrame* nextFrame;
	while (i--) {
		currentFrame = (TransformFrame*) frameList[i];
		if (currentFrame->position <= position && currentFrame->position + currentFrame->duration > position) {
			tweenEasing = currentFrame->tweenEasing;
			if (i == frameList.size() - 1 || tweenEasing < 0 || position == currentFrame->position) {
				result = &currentFrame->global;
			} else {
				progress = (position - currentFrame->position) / currentFrame->duration;
				if (tweenEasing) {
					//TODO
					//progress = TimelineState.getEaseValue(progress, tweenEasing);
				}

				nextFrame = (TransformFrame*) frameList[i + 1];

				result->x = currentFrame->global.x + (nextFrame->global.x - currentFrame->global.x) * progress;
				result->y = currentFrame->global.y + (nextFrame->global.y - currentFrame->global.y) * progress;
				result->skewX = TransformUtil::formatRadian(
						currentFrame->global.skewX + (nextFrame->global.skewX - currentFrame->global.skewX) * progress);
				result->skewY = TransformUtil::formatRadian(
						currentFrame->global.skewY + (nextFrame->global.skewY - currentFrame->global.skewY) * progress);
				result->scaleX = currentFrame->global.scaleX
						+ (nextFrame->global.scaleX - currentFrame->global.scaleX) * progress;
				result->scaleY = currentFrame->global.scaleY
						+ (nextFrame->global.scaleY - currentFrame->global.scaleY) * progress;
			}
			break;
		}
	}
}

void DBDataUtil::addHideTimeline(AnimationData* animationData, ArmatureData* armatureData) {
	const std::vector<BoneData*> & boneDataList = armatureData->getBoneDataList();
	uint i = boneDataList.size();

	BoneData* boneData = NULL;
	std::string boneName;
	while (i--) {
		boneData = boneDataList[i];
		boneName = boneData->name;
		if (!animationData->getTimeline(boneName)) {
			animationData->addTimeline(&TransformTimeline::HIDE_TIMELINE, boneName);
		}
	}
}
