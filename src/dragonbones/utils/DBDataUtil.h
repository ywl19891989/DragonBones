/*
 * DBDataUtil.h
 *
 *  Created on: 2014-2-16
 *      Author: Hali
 */

#ifndef DBDATAUTIL_H_
#define DBDATAUTIL_H_

#include "dragonbones/objects/DBTransform.h"

class ArmatureData;
class AnimationData;
class DBDataUtil {
public:
	DBDataUtil();
	virtual ~DBDataUtil();

	static void transformArmatureData(ArmatureData* armatureData);

	static void transformArmatureDataAnimations(ArmatureData* armatureData);

	static void transformAnimationData(AnimationData* animationData, ArmatureData* armatureData);

private:
	static const DBTransform _helpTransform1;
	static const DBTransform _helpTransform2;
};

#endif /* DBDATAUTIL_H_ */
