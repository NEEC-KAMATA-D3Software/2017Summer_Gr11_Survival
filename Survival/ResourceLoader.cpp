#include "ResourceLoader.h"

ResourceLoader::ResourceLoader():
	m_Counter(0),
	m_MaxNum(0),
	m_EndFlag(false)
{}

ResourceLoader::~ResourceLoader() {}

void ResourceLoader::setResouces(const std::vector<std::vector<std::string>>&  resouces) {
	m_Resouces = resouces;
	m_MaxNum = m_Resouces.size();
}

void ResourceLoader::update() {
	loadResource(m_Counter);
	m_Counter++;
	m_EndFlag = m_Counter >= m_MaxNum;
}

void ResourceLoader::loadResource(int counter) {
	m_Resouces = m_Resouces;
	if (m_Resouces[counter][0] == "Image/") {
		ResourceManager::getInstance()->loadImage(m_Resouces[counter][0] + m_Resouces[counter][1]);
	}
}

int ResourceLoader::getMaxCount() {
	return m_MaxNum;
}

int ResourceLoader::getCurrentCount() {
	return m_Counter;
}

float ResourceLoader::getLoadingRate() {
	return static_cast<float>(m_Counter) / static_cast<float>(m_MaxNum);
}

bool ResourceLoader::isEnd() {
	return m_EndFlag;
}