/*
 * Armature.h
 *
 *  Created on: 2014-2-27
 *      Author: Hali
 */

#ifndef ARMATURE_H_
#define ARMATURE_H_

#include "animation/IAnimatable.h"
#include <string>
#include <vector>

using namespace std;


class Slot;
class Event;
class Bone;
class Frame;
class TimelineState;
class AnimationState;
class Animation;
class DBObject;
class SoundEventManager;

typedef struct __helpStruct {
	int level;
	Bone* bone;
} HelpStruct;

class Armature: public IAnimatable {
public:
	Armature(void* displayObject);
	virtual ~Armature();

	/**
	 * The name of this DBObject instance's Armature instance.
	 */
	string name;

	/**
	 * An object that can contain any user extra data.
	 */
	void* userData;

	bool _slotsZOrderChanged;

	vector<Slot*> _slotList;
	vector<Bone*> _boneList;
	vector<Event*> _eventList;

	/**
	 * Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
	 */
	void* getDisplay();

	/**
	 * An Animation instance
	 * @see dragonBones.animation.Animation
	 */
	Animation* getAnimation();

	/**
	 * Cleans up any resources used by this DBObject instance.
	 */
	void dispose();

	void invalidUpdate();

	/**
	 * Update the animation using this method typically in an ENTERFRAME Event or with a Timer.
	 * @param	The amount of second to move the playhead ahead.
	 */
	void advanceTime(float passedTime);

	/**
	 * Get all Slot instance associated with this armature.
	 * @return A Vector.&lt;Slot&gt; instance.
	 * @see dragonBones.Slot
	 */
	vector<Slot*> & getSlots();

	/**
	 * Get all Bone instance associated with this armature.
	 * @return A Vector.&lt;Bone&gt; instance.
	 * @see dragonBones.Bone
	 */
	vector<Bone*> & getBones();

	/**
	 * Retrieves a Slot by name
	 * @param	The name of the Bone to retrieve.
	 * @return A Slot instance or null if no Slot with that name exist.
	 * @see dragonBones.Slot
	 */
	Slot* getSlot(string slotName);

	/**
	 * Gets the Slot associated with this DisplayObject.
	 * @param	Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
	 * @return A Slot instance.
	 * @see dragonBones.Slot
	 */
	Slot* getSlotByDisplay(void* display);

	/**
	 * Remove a Slot instance from this Armature instance.
	 * @param	The Slot instance to remove.
	 * @see dragonBones.Slot
	 */
	void removeSlot(Slot* slot);

	/**
	 * Remove a Slot instance from this Armature instance.
	 * @param	The name of the Slot instance to remove.
	 * @see dragonBones.Slot
	 */
	void removeSlotByName(string slotName);

	/**
	 * Retrieves a Bone by name
	 * @param	The name of the Bone to retrieve.
	 * @return A Bone instance or null if no Bone with that name exist.
	 * @see dragonBones.Bone
	 */
	Bone* getBone(string boneName);

	/**
	 * Gets the Bone associated with this DisplayObject.
	 * @param	Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
	 * @return A Bone instance.
	 * @see dragonBones.Bone
	 */
	Bone* getBoneByDisplay(void* display);

	/**
	 * Remove a Bone instance from this Armature instance.
	 * @param	The Bone instance to remove.
	 * @see	dragonBones.Bone
	 */
	void removeBone(Bone* bone);

	/**
	 * Remove a Bone instance from this Armature instance.
	 * @param	The name of the Bone instance to remove.
	 * @see dragonBones.Bone
	 */
	void removeBoneByName(string boneName);

	/**
	 * Add a DBObject instance to this Armature instance.
	 * @param	A DBObject instance
	 * @param	(optional) The parent's name of this DBObject instance.
	 * @see dragonBones.core.DBObject
	 */
	void addChild(DBObject* object, string parentName = std::string(""));

	/**
	 * Add a Bone instance to this Armature instance.
	 * @param	A Bone instance
	 * @param	(optional) The parent's name of this Bone instance.
	 * @see dragonBones.Bone
	 */
	void addBone(Bone* bone, string parentName = "");

	/**
	 * Update the z-order of the display.
	 */
	void updateSlotsZOrder();

	void addDBObject(DBObject* object);
	void removeDBObject(DBObject* object);

	void sortBoneList();

	void arriveAtFrame(Frame* frame, TimelineState* timelineState, AnimationState* animationState, bool isCross);

protected:
	bool _needUpdate;

	void* _display;

	Animation* _animation;

private:
	static SoundEventManager* _soundManager;
	std::vector<HelpStruct> _helpArray;

	static int sortSlot(Slot* slot1, Slot* slot2);
	static int sortHelp(HelpStruct& h1, HelpStruct& h2);
};

#endif /* ARMATURE_H_ */
