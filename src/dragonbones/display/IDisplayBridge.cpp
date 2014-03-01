/*
 * IDisplayBridge.cpp
 *
 *  Created on: 2014-3-1
 *      Author: Hali
 */

#include "IDisplayBridge.h"
#include "dragonbones/objects/DBTransform.h"
#include "dragonbones/utils/TransformUtil.h"

IDisplayBridge::IDisplayBridge() {
	// TODO Auto-generated constructor stub

}

IDisplayBridge::~IDisplayBridge() {
	// TODO Auto-generated destructor stub
}

bool IDisplayBridge::geVisible() {
	return false;
}

void IDisplayBridge::setVisible(bool value) {

}

void* IDisplayBridge::getDisplay() {
	return NULL;
}

void IDisplayBridge::setDisplay(void* value) {

}

void IDisplayBridge::dispose() {

}

void IDisplayBridge::updateTransform(Matrix* matrix, DBTransform* transform) {

}

void IDisplayBridge::updateColor(float aOffset, float rOffset, float gOffset, float bOffset, float aMultiplier,
		float rMultiplier, float gMultiplier, float bMultiplier) {

}

void IDisplayBridge::updateBlendMode(string blendMode) {

}

void IDisplayBridge::addDisplay(void* container, int/* index = -1*/) {

}

void IDisplayBridge::removeDisplay() {

}
