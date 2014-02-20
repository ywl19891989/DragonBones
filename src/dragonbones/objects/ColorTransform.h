/*
 * ColorTransform.h
 *
 *  Created on: 2014-2-19
 *      Author: Hali
 */

#ifndef COLORTRANSFORM_H_
#define COLORTRANSFORM_H_

class ColorTransform {
public:
	ColorTransform();
	virtual ~ColorTransform();

	float alphaOffset;
	float redOffset;
	float greenOffset;
	float blueOffset;

	float alphaMultiplier;
	float redMultiplier;
	float greenMultiplier;
	float blueMultiplier;

};

#endif /* COLORTRANSFORM_H_ */
