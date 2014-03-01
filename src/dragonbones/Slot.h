/*
 * Slot.h
 *
 *  Created on: 2014-2-26
 *      Author: Hali
 */

#ifndef SLOT_H_
#define SLOT_H_

#include "core/DBObject.h"
#include <vector>
#include <string>

class DisplayData;
class IDisplayBridge;
class Slot: public DBObject {
public:
	Slot(IDisplayBridge* displayBrideg);
	virtual ~Slot();

	std::vector<DisplayData*> _dislayDataList;

	IDisplayBridge* _displayBridge;

	float _originZOrder;

	float _tweenZorder;

	bool _isDisplayOnStage;

	float getZOrder();
	void setZOrder(float value);

	std::string getBlendMode();
	void setBlendMode(const std::string & value);

	/**
	 * The DisplayObject belonging to this Bone instance. Instance type of this object varies from flash.display.DisplayObject to startling.display.DisplayObject and subclasses.
	 */
	void* getDisplay();
	void setDisplay(void* value);
	void changeDisplay(int displayIndex);

	/**
	 * The sub-armature of this Slot instance.
	 */
	Armature* getChildArmature();
	void setChildArmature(Armature* value);

	/**
	 * The DisplayObject list belonging to this Slot instance.
	 */
	const std::vector<void*> & getDisplayList();
	void setDisplayList(std::vector<void*> & value);

	void setVisible(bool value);
	void setArmature(Armature* value);

	void dispose();

	void update();

	void updateVisible(bool value);

	/**
	 * Change all DisplayObject attached to this Bone instance.
	 * @param	displayList An array of valid DisplayObject to attach to this Bone.
	 */
	void changeDisplayList(std::vector<void*> & displayList);

private:
	bool _isHideDisplay;
	float _offsetZOrder;
	int _displayIndex;
	std::string _blendMode;

	std::vector<void*> _displayList;

	void updateChildArmatureAnimation();
};

#endif /* SLOT_H_ */
