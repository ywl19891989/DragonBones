/*
 * SlotData.cpp
 *
 *  Created on: 2014-2-16
 *      Author: Hali
 */

#include "SlotData.h"
#include "DisplayData.h"
#include <stdio.h>
#include <algorithm>

typedef unsigned int uint;

SlotData::SlotData() {
	zOrder = 0;
	blendMode = "normal";
}

SlotData::~SlotData() {
	// TODO Auto-generated destructor stub
}

void SlotData::dispose() {
	uint i = _displayDataList.size();
	while (i--) {
		_displayDataList[i]->dispose();
	}
	_displayDataList.clear();
}

const std::vector<DisplayData*> & SlotData::getDisplayDataList() {
	return _displayDataList;
}

void SlotData::addDisplayData(DisplayData* displayData) {
	if (!displayData) {
		printf("[SlotData] addDisplayData arg is NULL!\n");
	}

	typedef std::vector<DisplayData*>::iterator DisplayDataArrIt;
	DisplayDataArrIt begin = _displayDataList.begin();
	DisplayDataArrIt end = _displayDataList.end();
	DisplayDataArrIt it = std::find(begin, end, displayData);

	if (it == end) {
		_displayDataList.push_back(displayData);
	} else {
		printf("[SlotData] addDisplayData arg is already added!!\n");
	}
}

DisplayData* SlotData::getDisplayData(std::string displayName) {
	uint i = _displayDataList.size();
	while (i--) {
		if (_displayDataList[i]->name == displayName) {
			return _displayDataList[i];
		}
	}

	return NULL;
}
