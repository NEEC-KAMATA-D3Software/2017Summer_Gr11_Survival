#pragma once
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "Parameter.h"
#include <unordered_map>
#include <string>
#include <memory>

using StringIntMap = std::unordered_map<std::string, int>;
using StringIntsMap = std::unordered_map<std::string, std::unique_ptr<int[]> >;

class ResourceManager {
public:
	~ResourceManager();

	static ResourceManager* getInstance();
	void loadImage(const std::string& name);
	void loadGroupData();
	
	int getImage(const std::string& name);
	int getGroupImg(const std::string& name, int num);
	int getMapImage(const int num);
	void clear();
	
private:
	ResourceManager();

private:
	static std::unique_ptr<ResourceManager> mInstance;
	int mapData[Parameter::MapDataCount];
	StringIntMap Images;
	StringIntsMap GroupImgs;
};

#endif // !_RESOURCEMANAGER_H_
