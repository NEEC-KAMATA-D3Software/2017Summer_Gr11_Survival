#include "GameDevice.h"
#include "ResourceManager.h"
#include "Loading.h"
#include "DxLib.h"
#include "CSVReader.h"

Loading::Loading(std::shared_ptr<GameDevice> gameDevicePtr):
	m_Timer(Timer(0.3f)),
	m_EndFlag(false),
	m_IsVisual(true),
	m_ResourceLoader(),
	list(StringList())
{
	m_LoadingHandle = LoadGraph("Image/loading.png", TRUE);
}

Loading::~Loading() { }

void Loading::initialize() {
	list = CSVReader::ReadStrIntCSV("Images");

	for (int j = 0; j < list.size(); j++) {
		std::string name = list[j][0] + ".png";
		name = name;
		list[j][0] = "Image/";
		list[j].push_back(name);
	}
	m_ResourceLoader.setResouces(list);
	ResourceManager::getInstance()->loadGroupData();
}

void Loading::update() {
	m_Timer.Update();
	if (m_Timer.IsTime()) { 
		m_Timer.Initialize();
		m_IsVisual = !m_IsVisual; 
	}
	m_ResourceLoader.update();
	if(m_ResourceLoader.isEnd()){
		m_EndFlag = true;
		m_IsVisual = true;
	}
}

void Loading::draw() {
	if (m_IsVisual) {
		DrawGraph(115, 120, m_LoadingHandle, TRUE);
	}
}

void Loading::drawDebug() {
	DrawFormatString(0, 0, GetColor(255, 0, 0), "LoadingRate : %.0f %%", m_ResourceLoader.getLoadingRate() * 100);
}

eScene Loading::next() {
	return eScene::TITLE;
}

bool Loading::isEnd() {
	return m_EndFlag;
}