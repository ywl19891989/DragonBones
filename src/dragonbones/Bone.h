/*
 * Bone.h
 *
 *  Created on: 2014-2-25
 *      Author: Hali
 */

#ifndef BONE_H_
#define BONE_H_

#include "core/DBObject.h"
#include "objects/Point.h"
#include <vector>

class Slot;
class SoundEventManager;
class DisplayObject;
class Bone: public DBObject {

public:
	//0/1/2
	int scaleMode;
	std::string displayController;

public:
	Bone();
	virtual ~Bone();

	/**
	 * The default Slot of this Bone instance.
	 */
	Slot* getSlot();

	/**
	 * The sub-armature of default Slot of this Bone instance.
	 */
	Armature* getChildArmature();

	/**
	 * The DisplayObject of default Slot of this Bone instance.
	 */
	DisplayObject* getDisplay();
	void setDisplay(DisplayObject* value);

	void setVisible(bool value);

	void setArmature(Armature* value);

	void dispose();

	bool contains(DBObject* child);
	void addChild(DBObject* child);
	void removeChild(DBObject* child);

	/**
	 * Get all Slot instance associated with this bone.
	 * @return A Vector.&lt;Slot&gt; instance.
	 * @see dragonBones.Slot
	 */
	std::vector<Slot*> getSlots();

	void updateColor(float aOffset, float rOffset, float gOffset, float bOffset, float aMultiplier, float rMultiplier,
		float gMultiplier, float bMultiplier, bool isColorChanged);

private:
	SoundEventManager* _soundManager;

	Point _tweenPivot;

	std::vector<DBObject*> _children;

	Slot* _slot;
};

#endif /* BONE_H_ */
