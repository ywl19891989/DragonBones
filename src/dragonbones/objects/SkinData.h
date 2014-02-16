/*
 * SkinData.h
 *
 *  Created on: 2014-2-15
 *      Author: Hali
 */

#ifndef SKINDATA_H_
#define SKINDATA_H_

#include <vector>
#include <string>

class SlotData;
class SkinData {
public:
	SkinData();
	virtual ~SkinData();

	const std::vector<SlotData*> & getSlotDataList();

	void dispose();

	SlotData* getSlotData(std::string slotName);

	void addSlotData(SlotData* slotData);

	std::string name;

private:
	std::vector<SlotData*> _slotDataList;
	typedef unsigned int uint;
};

#endif /* SKINDATA_H_ */
