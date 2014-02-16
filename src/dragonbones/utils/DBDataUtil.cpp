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
#include "dragonbones/objects/ArmatureData.h"
#include "TransformUtil.h"
#include <vector>

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
//	const std::vector<SkinData*> & skinDatas = armatureData->getSkinDataList();
//	SkinData* skinData = skinDatas[0];
//	const std::vector<BoneData*> & boneDataList = armatureData->getBoneDataList();
//	const std::vector<SlotData*> & slotDataList = skinData->getSlotDataList();
//	uint i = boneDataList.size();

//	BoneData* boneData = NULL;
//	TransformTimeline* timeline = NULL;
//	SlotData* slotData = NULL;
//	DisplayData* displayData;
//	TransformTimeline* parentTimeline = NULL;
//	var
//	frameList:Vector.<Frame>;
//	var
//	originTransform: DBTransform;
//	var
//	originPivot: Point;
//	var
//	prevFrame: TransformFrame;
//	var
//	frameListLength: uint;
//	var
//	frame: TransformFrame;
//
//	while (i--) {
//		boneData = boneDataList[i];
//		timeline = animationData.getTimeline(boneData.name);
//		if (!timeline) {
//			continue;
//		}
//
//		slotData = null;
//		for each(slotData in slotDataList)
//		{
//			if(slotData.parent == boneData.name)
//			{
//				break;
//			}
//		}
//
//		parentTimeline = boneData.parent ? animationData.getTimeline(boneData.parent) : null;
//
//		frameList = timeline.frameList;
//
//		originTransform = null;
//		originPivot = null;
//		prevFrame = null;
//		frameListLength = frameList.length;
//		for(var j:int = 0;j < frameListLength;
//				j++
//				)
//				{
//					frame = frameList[j] as TransformFrame;
//					if(parentTimeline)
//					{
//						//tweenValues to transform.
//						_helpTransform1.copy(frame.global);
//
//						//get transform from parent timeline.
//						getTimelineTransform(parentTimeline, frame.position, _helpTransform2);
//						TransformUtil.transformPointWithParent(_helpTransform1, _helpTransform2);
//
//						//transform to tweenValues.
//						frame.transform.copy(_helpTransform1);
//					}
//					else
//					{
//						frame.transform.copy(frame.global);
//					}
//
//					frame.transform.x -= boneData.transform.x;
//					frame.transform.y -= boneData.transform.y;
//					frame.transform.skewX -= boneData.transform.skewX;
//					frame.transform.skewY -= boneData.transform.skewY;
//					frame.transform.scaleX -= boneData.transform.scaleX;
//					frame.transform.scaleY -= boneData.transform.scaleY;
//
//					if(!timeline.transformed)
//					{
//						if(slotData)
//						{
//							frame.zOrder -= slotData.zOrder;
//						}
//					}
//
//					if(!originTransform)
//					{
//						originTransform = timeline.originTransform;
//						originTransform.copy(frame.transform);
//						originTransform.skewX = TransformUtil.formatRadian(originTransform.skewX);
//						originTransform.skewY = TransformUtil.formatRadian(originTransform.skewY);
//						originPivot = timeline.originPivot;
//						originPivot.x = frame.pivot.x;
//						originPivot.y = frame.pivot.y;
//					}
//
//					frame.transform.x -= originTransform.x;
//					frame.transform.y -= originTransform.y;
//					frame.transform.skewX = TransformUtil.formatRadian(frame.transform.skewX - originTransform.skewX);
//					frame.transform.skewY = TransformUtil.formatRadian(frame.transform.skewY - originTransform.skewY);
//					frame.transform.scaleX -= originTransform.scaleX;
//					frame.transform.scaleY -= originTransform.scaleY;
//
//					if(!timeline.transformed)
//					{
//						frame.pivot.x -= originPivot.x;
//						frame.pivot.y -= originPivot.y;
//					}
//
//					if(prevFrame)
//					{
//						var dLX:Number = frame.transform.skewX - prevFrame.transform.skewX;
//
//						if(prevFrame.tweenRotate)
//						{
//
//							if(prevFrame.tweenRotate > 0)
//							{
//								if(dLX < 0)
//								{
//									frame.transform.skewX += Math.PI * 2;
//									frame.transform.skewY += Math.PI * 2;
//								}
//
//								if(prevFrame.tweenRotate > 1)
//								{
//									frame.transform.skewX += Math.PI * 2 * (prevFrame.tweenRotate - 1);
//									frame.transform.skewY += Math.PI * 2 * (prevFrame.tweenRotate - 1);
//								}
//							}
//							else
//							{
//								if(dLX > 0)
//								{
//									frame.transform.skewX -= Math.PI * 2;
//									frame.transform.skewY -= Math.PI * 2;
//								}
//
//								if(prevFrame.tweenRotate < 1)
//								{
//									frame.transform.skewX += Math.PI * 2 * (prevFrame.tweenRotate + 1);
//									frame.transform.skewY += Math.PI * 2 * (prevFrame.tweenRotate + 1);
//								}
//							}
//						}
//						else
//						{
//							frame.transform.skewX = prevFrame.transform.skewX + TransformUtil.formatRadian(frame.transform.skewX - prevFrame.transform.skewX);
//							frame.transform.skewY = prevFrame.transform.skewY + TransformUtil.formatRadian(frame.transform.skewY - prevFrame.transform.skewY);
//						}
//					}
//
//					prevFrame = frame;
//				}
//				timeline.transformed = true;
//			}
}

//public static function getTimelineTransform(timeline:TransformTimeline, position:Number, retult:DBTransform):void
//{
//	var frameList:Vector.<Frame> = timeline.frameList;
//	var i:int = frameList.length;
//
//	var currentFrame:TransformFrame;
//	var tweenEasing:Number;
//	var progress:Number;
//	var nextFrame:TransformFrame;
//	while(i --)
//	{
//		currentFrame = frameList[i] as TransformFrame;
//		if(currentFrame.position <= position && currentFrame.position + currentFrame.duration > position)
//		{
//			tweenEasing = currentFrame.tweenEasing;
//			if(i == frameList.length - 1 || isNaN(tweenEasing) || position == currentFrame.position)
//			{
//				retult.copy(currentFrame.global);
//			}
//			else
//			{
//				progress = (position - currentFrame.position) / currentFrame.duration;
//				if(tweenEasing)
//				{
//					progress = TimelineState.getEaseValue(progress, tweenEasing);
//				}
//
//				nextFrame = frameList[i + 1] as TransformFrame;
//
//				retult.x = currentFrame.global.x + (nextFrame.global.x - currentFrame.global.x) * progress;
//				retult.y = currentFrame.global.y + (nextFrame.global.y - currentFrame.global.y) * progress;
//				retult.skewX = TransformUtil.formatRadian(currentFrame.global.skewX + (nextFrame.global.skewX - currentFrame.global.skewX) * progress);
//				retult.skewY = TransformUtil.formatRadian(currentFrame.global.skewY + (nextFrame.global.skewY - currentFrame.global.skewY) * progress);
//				retult.scaleX = currentFrame.global.scaleX + (nextFrame.global.scaleX - currentFrame.global.scaleX) * progress;
//				retult.scaleY = currentFrame.global.scaleY + (nextFrame.global.scaleY - currentFrame.global.scaleY) * progress;
//			}
//			break;
//		}
//	}
//}

//public static function addHideTimeline(animationData:AnimationData, armatureData:ArmatureData):void
//{
//	var boneDataList:Vector.<BoneData> =armatureData.boneDataList;
//	var i:int = boneDataList.length;
//
//	var boneData:BoneData;
//	var boneName:String;
//	while(i --)
//	{
//		boneData = boneDataList[i];
//		boneName = boneData.name;
//		if(!animationData.getTimeline(boneName))
//		{
//			animationData.addTimeline(TransformTimeline.HIDE_TIMELINE, boneName);
//		}
//	}
//}
