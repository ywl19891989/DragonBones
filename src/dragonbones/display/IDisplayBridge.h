/*
 * IDisplayBridge.h
 *
 *  Created on: 2014-3-1
 *      Author: Hali
 */

#ifndef IDISPLAYBRIDGE_H_
#define IDISPLAYBRIDGE_H_

#include <string>

using namespace std;

class Matrix;
class DBTransform;
class IDisplayBridge {
public:
	IDisplayBridge();
	virtual ~IDisplayBridge();

	virtual bool geVisible();
	virtual void setVisible(bool value);

	/**
	 * Indicates the original display object relative to specific display engine.
	 */
	virtual void* getDisplay();
	virtual void setDisplay(void* value);

	/**
	 * Cleans up resources used by this IDisplayBridge instance.
	 */
	virtual void dispose();

	/**
	 * Updates the transform of the display object
	 * @param	matrix
	 * @param	transform
	 */
	virtual void updateTransform(Matrix* matrix, DBTransform* transform);

	/**
	 * Updates the color of the display object
	 * @param	a
	 * @param	r
	 * @param	g
	 * @param	b
	 * @param	aM
	 * @param	rM
	 * @param	gM
	 * @param	bM
	 */
	virtual void updateColor(float aOffset, float rOffset, float gOffset, float bOffset, float aMultiplier,
			float rMultiplier, float gMultiplier, float bMultiplier);

	/**
	 * Update the blend mode of the display object
	 * @param blendMode The blend mode to use.
	 */
	virtual void updateBlendMode(string blendMode);

	/**
	 * Adds the original display object to another display object.
	 * @param	container
	 * @param	index
	 */
	virtual void addDisplay(void* container, int index = -1);

	/**
	 * remove the original display object from its parent.
	 */
	virtual void removeDisplay();
};

#endif /* IDISPLAYBRIDGE_H_ */
