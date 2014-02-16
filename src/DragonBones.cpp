//============================================================================
// Name        : DragonBones.cpp
// Author      : wenlong
// Version     :
// Copyright   : All copyrights reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include "json.h"
#include "dragonbones/objects/ObjectDataParser.h"

using namespace std;

char* getFileData(const char* fullPath, const char* pszMode, unsigned long * pSize) {
	char * pBuffer = NULL;
	*pSize = 0;
	do {
		// read the file from hardware
		FILE *fp = fopen(fullPath, pszMode);

		fseek(fp, 0, SEEK_END);
		*pSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		pBuffer = new char[*pSize];
		*pSize = fread(pBuffer, sizeof(unsigned char), *pSize, fp);
		fclose(fp);
	} while (0);

	if (!pBuffer) {
		std::string msg = "Get data from file(";
		msg.append(fullPath).append(") failed!");

		printf("[getFileData] %s\n", msg.c_str());
	}
	return pBuffer;
}

int main() {

	Json::Reader reader;
	Json::Value json_object;

	unsigned long fsize = 0;
	char* content = getFileData("res/dragonbones/skeleton.json", "rt", &fsize);

	if(!content){
		printf("getFileData error!\n");
		return 0;
	}

	if(!reader.parse(content, json_object, false)){
		printf("parse error!\n");
		return 0;
	}

	printf("parse success!\n");

	ObjectDataParser::parseSkeletonData(json_object);

	return 0;
}
