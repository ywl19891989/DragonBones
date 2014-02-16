/*
 * SlotData.h
 *
 *  Created on: 2014-2-16
 *      Author: Hali
 */

#ifndef SLOTDATA_H_
#define SLOTDATA_H_

#include <vector>
#include <string>

class DisplayData;
class SlotData {
public:
	SlotData();
	virtual ~SlotData();

	std::string name;
	std::string parent;
	float zOrder;
	std::string blendMode;

	void dispose();

	const std::vector<DisplayData*> & getDisplayDataList();
	void addDisplayData(DisplayData* displayData);
	DisplayData* getDisplayData(std::string displayName);

private:
	std::vector<DisplayData*> _displayDataList;

};

#endif /* SLOTDATA_H_ */
