#pragma once
#ifndef _RESOURCELOADER_H_
#define _RESOURCELOADER_H_

#include <array>
#include <string>
#include "ResourceManager.h"

using StringArray = std::array<std::array<std::string, 2>, 100>;

class ResourceLoader {
public:
	ResourceLoader();
	~ResourceLoader();

	void setResouces(const std::vector<std::vector<std::string>>&  resouces);

	void update();
	void loadResource(int counter);
	int getMaxCount();
	int getCurrentCount();
	float getLoadingRate();
	bool isEnd();

private:
	std::unique_ptr<ResourceManager> m_ResourceMananer;
	std::vector<std::vector<std::string>> m_Resouces;
	int m_Counter;
	int m_MaxNum;
	bool m_EndFlag;
};

#endif // !_RESOURCELOADER_H_
