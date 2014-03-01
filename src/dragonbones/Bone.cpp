/*
 * Bone.cpp
 *
 *  Created on: 2014-2-25
 *      Author: Hali
 */

#include "Bone.h"
#include "Slot.h"
#include <algorithm>

Bone::Bone() :
		_slot(NULL), _soundManager(NULL) {
	// TODO Auto-generated constructor stub
	scaleMode = 1;
	_scaleType = 2;
}

Bone::~Bone() {
	// TODO Auto-generated destructor stub
}

Slot* Bone::getSlot() {
	return _slot;
}

Armature* Bone::getChildArmature() {
	return _slot ? _slot->getChildArmature() : NULL;
}

/**
 * The DisplayObject of default Slot of this Bone instance.
 */
DisplayObject* Bone::getDisplay() {
	return _slot ? _slot->getDisplay() : NULL;
}

void Bone::setDisplay(DisplayObject* value) {
	if (_slot) {
		_slot->setDisplay(value);
	}
}

void Bone::setVisible(bool value) {
	if (this->_visible != value) {
		_visible = value;
		int i = _children.size();
		while (i--) {
			Slot* child = dynamic_cast<Slot*>(_children[i]);
			if (child) {
				child->updateVisible(_visible);
			}
		}
	}
}

void Bone::setArmature(Armature* value) {
	DBObject::setArmature(value);
	int i = _children.size();
	while (i--) {
		_children[i]->setArmature(_armature);
	}
}

void Bone::dispose() {

	if (!_children) {
		return;
	}

	DBObject::dispose();

	int i = _children.size();
	while (i--) {
		_children[i]->dispose();
	}
	_children.clear();

	_children = NULL;
	_slot = NULL;
	_tweenPivot = NULL;
}

bool Bone::contains(DBObject* child) {
	if (!child) {
		printf("[Bone] contains arg is NULL!!\n");
	}

	if (child == this) {
		return false;
	}
	DBObject* ancestor = child;
	while (ancestor != this && ancestor != NULL) {
		ancestor = ancestor->getParent();
	}
	return ancestor == this;
}

void Bone::addChild(DBObject* child) {
	if (!child) {
		printf("[Bone] addChild arg is NULL!!\n");
	}

	Bone* boneChild = dynamic_cast<Bone*>(child);

	if (child == this || (boneChild != NULL && boneChild->contains(this))) {
		printf(
				"[Bone] addChild An Bone cannot be added as a child to itself or one of its children (or children's children, etc.)!!\n");
	}

	if (child->getParent()) {
		child->getParent()->removeChild(child);
	}
	_children.push_back(child);
	child->setParent(this);
	child->setArmature(this->_armature);

	Slot* slotChild = dynamic_cast<Slot*>(child);
	if (!_slot && slotChild != NULL) {
		_slot = slotChild;
	}
}

void Bone::removeChild(DBObject* child) {
	if (!child) {
		printf("[Bone] removeChild arg is NULL!!\n");
	}

	std::vector<DBObject*>::iterator begin = _children.begin();
	std::vector<DBObject*>::iterator end = _children.end();

	std::vector<DBObject*>::iterator index = std::find(begin, end, child);
	if (index != end) {
		_children.erase(index);
		child->setParent(NULL);
		child->setArmature(NULL);

		if (child == _slot) {
			_slot = NULL;
		}
	} else {
		printf("[Bone] removeChild arg is not added!!\n");
	}
}

std::vector<Slot*> Bone::getSlots() {
	std::vector<Slot*> slotList;
	int i = _children.size();
	while (i--) {
		Slot* slot = dynamic_cast<Slot*>(_children[i]);
		if (slot) {
			slotList.push_back(slot);
		}
	}
	return slotList;
}

/** @private */
//void arriveAtFrame(Frame* frame, TimelineState* timelineState, AnimationState* animationState, bool isCross) {
//	if (frame) {
//		var
//		mixingType:int = animationState.getMixingTransform(name);
//		if (animationState.displayControl && (mixingType == 2 || mixingType == -1)) {
//			if (!displayController || displayController == animationState.name) {
//				var
//				tansformFrame:TransformFrame = frame
//				as TransformFrame;
//				if (_slot) {
//					var
//					displayIndex:int = tansformFrame.displayIndex;
//					if (displayIndex >= 0) {
//						if (!isNaN(tansformFrame.zOrder) && tansformFrame.zOrder != _slot._tweenZorder) {
//							_slot._tweenZorder = tansformFrame.zOrder;
//							this._armature._slotsZOrderChanged = true;
//						}
//					}
//					_slot.changeDisplay(displayIndex);
//					_slot.updateVisible(tansformFrame.visible);
//				}
//			}
//		}
//
//		if (frame.event && this._armature.hasEventListener(FrameEvent.BONE_FRAME_EVENT)) {
//			var
//			frameEvent: FrameEvent = new FrameEvent(FrameEvent.BONE_FRAME_EVENT);
//			frameEvent.bone = this;
//			frameEvent.animationState = animationState;
//			frameEvent.frameLabel = frame.event;
//			this._armature._eventList.push(frameEvent);
//		}
//
//		if (frame.sound && _soundManager.hasEventListener(SoundEvent.SOUND)) {
//			var
//			soundEvent: SoundEvent = new SoundEvent(SoundEvent.SOUND);
//			soundEvent.armature = this._armature;
//			soundEvent.animationState = animationState;
//			soundEvent.sound = frame.sound;
//			_soundManager.dispatchEvent(soundEvent);
//		}
//
//		if (frame.action) {
//		for each(var child:DBObject in _children)
//		{
//			if(child is Slot)
//			{
//				var childArmature:Armature = (child as Slot).childArmature;
//				if(childArmature)
//				{
//					childArmature.animation.gotoAndPlay(frame.action);
//				}
//			}
//		}
//	}
//} else {
//	if (_slot) {
//		_slot.changeDisplay(-1);
//	}
//}
//}
/** @private */
void Bone::updateColor(float aOffset, float rOffset, float gOffset, float bOffset, float aMultiplier, float rMultiplier,
		float gMultiplier, float bMultiplier, bool isColorChanged) {
	if (isColorChanged || _isColorChanged) {
//	_slot->_displayBridge.updateColor(aOffset, rOffset, gOffset, bOffset, aMultiplier, rMultiplier, gMultiplier,
//			bMultiplier);
	}
	_isColorChanged = isColorChanged;
}
