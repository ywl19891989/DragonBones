/*
 * SkinData.cpp
 *
 *  Created on: 2014-2-15
 *      Author: Hali
 */

#include "SkinData.h"
#include <algorithm>
#include <stdio.h>

SkinData::SkinData() {
	// TODO Auto-generated constructor stub

}

SkinData::~SkinData() {
	// TODO Auto-generated destructor stub
}

const std::vector<SlotData*> & SkinData::getSlotDataList() {
	return _slotDataList;
}

void SkinData::dispose() {
//	uint i = _slotDataList.size();
//	while (i--) {
//		_slotDataList[i]->dispose();
//	}
	_slotDataList.clear();
}

SlotData* SkinData::getSlotData(std::string slotName) {
	uint i = _slotDataList.size();
	while (i--) {
//		if (_slotDataList[i].name == slotName) {
//			return _slotDataList[i];
//		}
	}
	return NULL;
}

void SkinData::addSlotData(SlotData* slotData) {
	if (!slotData) {
		printf("[SkinData] addSlotData arg inValid is NULL!\n");
	}

	std::vector<SlotData*>::iterator begin = _slotDataList.begin();
	std::vector<SlotData*>::iterator end = _slotDataList.end();
	std::vector<SlotData*>::iterator it = std::find(begin, end, slotData);

	if (it == end) {
		_slotDataList.push_back(slotData);
	} else {
		printf("[SkinData] addSlotData arg already added!\n");
	}
}
