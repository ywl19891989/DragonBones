/*
 * Armature.cpp
 *
 *  Created on: 2014-2-27
 *      Author: Hali
 */

#include "Armature.h"
#include "Slot.h"
#include "Bone.h"
#include <algorithm>
#include "display/IDisplayBridge.h"
#include "core/DBObject.h"
#include "animation/Animation.h"

Armature::Armature(void* display) :
		userData(NULL) {
	_display = display;

	_animation = new Animation(this);
	_slotsZOrderChanged = false;

	_needUpdate = false;
}

Armature::~Armature() {
	// TODO Auto-generated destructor stub
}

void* Armature::getDisplay() {
	return _display;
}

Animation* Armature::getAnimation() {
	return _animation;
}

void Armature::dispose() {
	if (!_animation) {
		return;
	}

	userData = NULL;

	_animation->dispose();

	for (unsigned int i = 0; i < _slotList.size(); i++) {
		Slot* slot = _slotList[i];
		slot->dispose();
	}

	for (unsigned int i = 0; i < _boneList.size(); i++) {
		Bone* bone = _boneList[i];
		bone->dispose();
	}

	_slotList.clear();
	_boneList.clear();
	_eventList.clear();

	_animation = NULL;

	//_display = null;
}

void Armature::invalidUpdate() {
	_needUpdate = true;
}

void Armature::advanceTime(float passedTime) {
	unsigned int i;
	Slot* slot;
	Armature* childArmature;
	if (_animation->getIsPlaying() || _needUpdate) {
		_needUpdate = false;
		_animation->advanceTime(passedTime)
		passedTime *= _animation->getTimeScale();

		i = _boneList.size();
		while (i--) {
			_boneList[i]->update();
		}

		i = _slotList.size();
		while (i--) {
			slot = _slotList[i];
			slot->update();
			if (slot->_isDisplayOnStage) {
				childArmature = slot->getChildArmature();
				if (childArmature) {
					childArmature->advanceTime(passedTime);
				}
			}
		}

		if (_slotsZOrderChanged) {
			updateSlotsZOrder();

//			if (hasEventListener(ArmatureEvent::Z_ORDER_UPDATED)) {
//				dispatchEvent(new ArmatureEvent(ArmatureEvent::Z_ORDER_UPDATED));
//			}
		}

		if (_eventList.size()) {
			for (unsigned int i = 0; i < _eventList.size(); i++) {
				//Event* event = _eventList[i];
				//dispatchEvent(event);
			}
			_eventList.clear();
		}
	} else {
		passedTime *= _animation->getTimeScale();
		i = _slotList.size();
		while (i--) {
			slot = _slotList[i];
			if (slot->_isDisplayOnStage) {
				childArmature = slot->getChildArmature();
				if (childArmature) {
					childArmature->advanceTime(passedTime);
				}
			}
		}
	}
}

vector<Slot*> & Armature::getSlots() {
	return _slotList;
}

vector<Bone*> & Armature::getBones() {
	return _boneList;
}

Slot* Armature::getSlot(string slotName) {
	unsigned int i = _slotList.size();
	while (i--) {
		if (_slotList[i]->name == slotName) {
			return _slotList[i];
		}
	}
	return NULL;
}

Slot* Armature::getSlotByDisplay(void* display) {
	if (display) {
		unsigned int i = _slotList.size();
		while (i--) {
			if (_slotList[i]->getDisplay() == display) {
				return _slotList[i];
			}
		}
	}
	return NULL;
}

void Armature::removeSlot(Slot* slot) {
	if (slot == NULL) {
		//TODO log arg error
		return;
	}

	vector<Slot*>::iterator begin = _slotList.begin();
	vector<Slot*>::iterator end = _slotList.end();
	vector<Slot*>::iterator it = std::find(begin, end, slot);

	if (it != end) {
		slot->getParent()->removeChild(slot);
	} else {
		//TODO log not found error
		return;
	}
}

void Armature::removeSlotByName(string slotName) {
	if (slotName.empty()) {
		return;
	}

	Slot* slot = getSlot(slotName);
	if (slot) {
		removeSlot(slot);
	}
}

Bone* Armature::getBone(string boneName) {
	unsigned int i = _boneList.size();
	while (i--) {
		if (_boneList[i]->name == boneName) {
			return _boneList[i];
		}
	}
	return NULL;
}

Bone* Armature::getBoneByDisplay(void* display) {
	Slot* slot = getSlotByDisplay(display);
	return slot ? slot->getParent() : NULL;
}

void Armature::removeBone(Bone* bone) {
	if (!bone) {
		//TODO log arg null error
		return;
	}

	vector<Bone*>::iterator begin = _boneList.begin();
	vector<Bone*>::iterator end = _boneList.end();
	vector<Bone*>::iterator it = std::find(begin, end, bone);

	if (it != end) {
		if (bone->getParent() != NULL) {
			bone->getParent()->removeChild(bone);
		} else {
			bone->setArmature(NULL);
		}
	} else {
		//TODO log not found error
	}
}

void Armature::removeBoneByName(string boneName) {
	if (boneName.empty()) {
		return;
	}

	Bone* bone = getBone(boneName);
	if (bone) {
		removeBone(bone);
	}
}

/**
 * Add a DBObject instance to this Armature instance.
 * @param	A DBObject instance
 * @param	(optional) The parent's name of this DBObject instance.
 * @see dragonBones.core.DBObject
 */
void Armature::addChild(DBObject* object, string parentName/* = ""*/) {
	if (object == NULL) {
		//TODO log arg null error
		return;
	}

	if (!parentName.empty()) {
		Bone* boneParent = getBone(parentName);
		if (boneParent) {
			boneParent->addChild(object);
		} else {
			//TODO log not found error
		}
	} else {
		if (object->getParent() != NULL) {
			object->getParent()->removeChild(object);
		}
		object->setArmature(this);
	}
}

void Armature::addBone(Bone* bone, string parentName/* = ""*/) {
	addChild(bone, parentName);
}

void Armature::updateSlotsZOrder() {
	std::sort(_slotList.begin(), _slotList.end(), Armature::sortSlot);
	unsigned int i = _slotList.size();
	Slot* slot = NULL;
	while (i--) {
		slot = _slotList[i];
		if (slot->_isDisplayOnStage) {
			slot->_displayBridge->addDisplay(getDisplay());
		}
	}

	_slotsZOrderChanged = false;
}

void Armature::addDBObject(DBObject* object) {
	Slot* slot = dynamic_cast<Slot*>(object);
	Bone* bone = dynamic_cast<Bone*>(object);
	if (slot != NULL) {
		vector<Slot*>::iterator begin = _slotList.begin();
		vector<Slot*>::iterator end = _slotList.end();
		vector<Slot*>::iterator it = std::find(begin, end, slot);

		if (it == end) {
			_slotList.push_back(slot);
		}
	} else if (bone != NULL) {
		vector<Bone*>::iterator begin = _boneList.begin();
		vector<Bone*>::iterator end = _boneList.end();
		vector<Bone*>::iterator it = std::find(begin, end, bone);

		if (it == end) {
			_boneList.push_back(bone);
			sortBoneList();
		}
	}
}

void Armature::removeDBObject(DBObject* object) {
	Slot* slot = dynamic_cast<Slot*>(object);
	Bone* bone = dynamic_cast<Bone*>(object);
	if (slot != NULL) {
		vector<Slot*>::iterator begin = _slotList.begin();
		vector<Slot*>::iterator end = _slotList.end();
		vector<Slot*>::iterator it = std::find(begin, end, slot);

		if (it != end) {
			_slotList.erase(it);
		}
	} else if (bone != NULL) {
		vector<Bone*>::iterator begin = _boneList.begin();
		vector<Bone*>::iterator end = _boneList.end();
		vector<Bone*>::iterator it = std::find(begin, end, bone);

		if (it != end) {
			_boneList.erase(it);
		}
	}
}

void Armature::sortBoneList() {
	unsigned int i = _boneList.size();
	if (i == 0) {
		return;
	}

	_helpArray.clear();
	_helpArray.resize(i);
	int level = 0;
	Bone* bone = NULL;
	Bone* boneParent = NULL;
	while (i--) {
		level = 0;
		bone = _boneList[i];
		boneParent = bone;
		while (boneParent) {
			level++;
			boneParent = boneParent->getParent();
		}
		_helpArray[i].level = level;
		_helpArray[i].bone = bone;
	}

	std::sort(_helpArray.begin(), _helpArray.end(), Armature::sortHelp);
	//_helpArray.sortOn("level", Array.NUMERIC | Array.DESCENDING);

	i = _helpArray.size();
	while (i--) {
		_boneList[i] = _helpArray[i].bone;
	}
	_helpArray.clear();
}

void Armature::arriveAtFrame(Frame* frame, TimelineState* timelineState, AnimationState* animationState, bool isCross)
{
//	if(frame->event && hasEventListener(FrameEvent.ANIMATION_FRAME_EVENT))
//	{
//		var frameEvent:FrameEvent = new FrameEvent(FrameEvent.ANIMATION_FRAME_EVENT);
//		frameEvent.animationState = animationState;
//		frameEvent.frameLabel = frame.event;
//		_eventList.push(frameEvent);
//	}
//
//	if(frame.sound && _soundManager.hasEventListener(SoundEvent.SOUND))
//	{
//		var soundEvent:SoundEvent = new SoundEvent(SoundEvent.SOUND);
//		soundEvent.armature = this;
//		soundEvent.animationState = animationState;
//		soundEvent.sound = frame.sound;
//		_soundManager.dispatchEvent(soundEvent);
//	}
//
//	if(frame.action)
//	{
//		if(animationState.isPlaying)
//		{
//			animation.gotoAndPlay(frame.action);
//		}
//	}
}

int Armature::sortSlot(Slot* slot1, Slot* slot2) {
	return slot2->getZOrder() - slot1->getZOrder();
}

int Armature::sortHelp(HelpStruct & h1, HelpStruct& h2) {
	return h1.level - h2.level;
}
