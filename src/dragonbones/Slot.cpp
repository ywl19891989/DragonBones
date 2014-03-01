/*
 * Slot.cpp
 *
 *  Created on: 2014-2-26
 *      Author: Hali
 */

#include "Slot.h"
#include "display/IDisplayBridge.h"
#include "objects/DisplayData.h"

Slot::Slot(IDisplayBridge* displayBrideg) {
	// TODO Auto-generated constructor stub
	_displayBridge = displayBrideg;
	_displayIndex = -1;
	_scaleType = 1;

	_originZOrder = 0;
	_tweenZorder = 0;
	_offsetZOrder = 0;

	_isDisplayOnStage = false;
	_isHideDisplay = false;

	_blendMode = "normal";
	if (_displayBridge->getDisplay() != NULL) {
		_displayBridge->updateBlendMode(_blendMode);
	}
}

Slot::~Slot() {
	// TODO Auto-generated destructor stub
}

float Slot::getZOrder() {
	return _originZOrder + _tweenZorder + _offsetZOrder;
}

void Slot::setZOrder(float value) {
	if (getZOrder() != value) {
		_offsetZOrder = value - _originZOrder - _tweenZorder;
		if (this->_armature) {
			this->_armature->_slotsZOrderChanged = true;
		}
	}
}

std::string Slot::getBlendMode() {
	return _blendMode;
}

void Slot::setBlendMode(const std::string & value) {
	if (_blendMode != value) {
		_blendMode = value;
		if (_displayBridge->getDisplay()) {
			_displayBridge->updateBlendMode(_blendMode);
		}
	}
}

/**
 * The DisplayObject belonging to this Bone instance. Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
 */
void* Slot::getDisplay() {
	void* display = _displayList[_displayIndex];
	Armature* armatureObj = dynamic_cast<Armature*>(display);
	if (armatureObj != NULL) {
		return armatureObj->getDisplay();
	}
	return display;
}

void Slot::setDisplay(void* value) {
	_displayList[_displayIndex] = value;

	if (_displayBridge->getDisplay()) {
		_displayBridge->setDisplay(getDisplay());
	} else {
		_displayBridge->setDisplay(getDisplay());
		if (this->_armature) {
			_displayBridge->addDisplay(this->_armature->getDisplay());
			this->_armature->_slotsZOrderChanged = true;
		}
	}

	updateChildArmatureAnimation();

	if (!_isHideDisplay && _displayBridge->getDisplay()) {
		_isDisplayOnStage = true;
		_displayBridge->updateBlendMode(_blendMode);
	} else {
		_isDisplayOnStage = false;
	}
}

Armature* Slot::getChildArmature() {
	void* display = _displayList[_displayIndex];
	Armature* armatureObj = dynamic_cast<Armature*>(display);
	if (armatureObj != NULL) {
		return armatureObj;
	}
	return NULL;
}

void Slot::setChildArmature(Armature* value) {
	_displayList[_displayIndex] = value;
	if (value) {
		setDisplay(value->getDisplay());
	}
}

const std::vector<void*> & Slot::getDisplayList() {
	return _displayList;
}

void Slot::setDisplayList(std::vector<void*> & value) {
	_displayList.clear();
	unsigned int i = value.size();
	while (i--) {
		_displayList[i] = value[i];
	}

	if (_displayIndex >= 0) {
		int displayIndexBackup = _displayIndex;
		_displayIndex = -1;
		changeDisplay(displayIndexBackup);
	}
}

void Slot::changeDisplay(int displayIndex) {
	if (displayIndex < 0) {
		if (!_isHideDisplay) {
			_isHideDisplay = true;
			_displayBridge->removeDisplay();
			updateChildArmatureAnimation();
		}
	} else {
		bool changeShowState = false;
		if (_isHideDisplay) {
			_isHideDisplay = false;
			changeShowState = true;
			if (this->_armature) {
				_displayBridge->addDisplay(this->_armature->getDisplay());
				this->_armature->_slotsZOrderChanged = true;
			}
		}

		unsigned int length = _displayList.size();
		if (displayIndex >= length && length > 0) {
			displayIndex = length - 1;
		}
		if (_displayIndex != displayIndex) {
			_displayIndex = displayIndex;

			void* content = _displayList[_displayIndex];
			Armature* armatureObj = dynamic_cast<Armature*>(content);
			if (armatureObj != NULL) {
				setDisplay(armatureObj->getDisplay());
			} else {
				setDisplay(content);
			}

			if (_dislayDataList && _displayIndex <= _dislayDataList.size()) {
				this->_origin = _dislayDataList[_displayIndex]->transform;
			}
		} else if (changeShowState) {
			updateChildArmatureAnimation();
		}
	}

	if (!_isHideDisplay && _displayBridge->getDisplay()) {
		_isDisplayOnStage = true;
	} else {
		_isDisplayOnStage = false;
	}
}

void Slot::setVisible(bool value) {
	if (value != this->_visible) {
		this->_visible = value;
		updateVisible(this->_visible);
	}
}

void Slot::setArmature(Armature* value) {
	DBObject::setArmature(value);
	if (this->_armature) {
		this->_armature->_slotsZOrderChanged = true;
		_displayBridge->addDisplay(this->_armature->getDisplay());
	} else {
		_displayBridge->removeDisplay();
	}
}

void Slot::dispose() {
	if (!_displayBridge) {
		return;
	}

	DBObject::dispose();

	_displayBridge->dispose();
	_displayList.clear();

	_displayBridge = NULL;
	_displayList = NULL;
	_dislayDataList = NULL;
}

void Slot::update() {
	DBObject::update();

	if (_isDisplayOnStage) {
		float pivotX = _parent->_tweenPivot.x;
		float pivotY = _parent->_tweenPivot.y;
		if (pivotX || pivotY) {
			Matrix* parentMatrix = _parent->_globalTransformMatrix;
			this->_globalTransformMatrix->tx += parentMatrix->a * pivotX + parentMatrix->c * pivotY;
			this->_globalTransformMatrix->ty += parentMatrix->b * pivotX + parentMatrix->d * pivotY;
		}

		_displayBridge->updateTransform(this->_globalTransformMatrix, this->_global);
	}
}

void Slot::updateVisible(bool value) {
	_displayBridge->setVisible(_parent->getVisible() && getVisible() && value);
}

void Slot::updateChildArmatureAnimation() {
	Armature* childArmature = this->getChildArmature();

	if (childArmature) {
		Animation* childAnimation = childArmature->getAnimation();
		Animation* thisArmatureAnimation = this->_armature->getAnimation();
		if (_isHideDisplay) {
			childAnimation->stop();
			childAnimation->_lastAnimationState = NULL;
		} else {
			if (this->_armature && thisArmatureAnimation->lastAnimationState
					&& childAnimation->hasAnimation(thisArmatureAnimation->lastAnimationState.name)) {
				childAnimation->gotoAndPlay(thisArmatureAnimation->lastAnimationState.name);
			} else {
				childAnimation->play();
			}
		}
	}
}

void Slot::changeDisplayList(std::vector<void*> & displayList) {
	this->setDisplayList(displayList);
}
