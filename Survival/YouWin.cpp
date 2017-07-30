#include "DxLib.h"
#include "ResourceManager.h"
#include "GameDevice.h"
#include "InputState.h"
#include "Controller.h"
#include "GameConst.h"
#include "Selector.h"
#include "YouWin.h"
#include <string>

YouWin::YouWin(std::shared_ptr<GameDevice> gameDevicePtr) :
	m_EndFlag(false),
	m_Timer(0.5f),
	m_IsVisual(true), 
	nextScene(eScene::TITLE),
	m_InputStatePtr(gameDevicePtr->getInputState()),
	m_SelectManagerPtr(new Selector(gameDevicePtr, 2)),
	m_ContrStatePtr(gameDevicePtr->getContrState())
{ }

YouWin::~YouWin() {}

void YouWin::initialize() {
	m_ImgHandle = ResourceManager::getInstance()->getImage("YouWin");
	m_PromptHandle = ResourceManager::getInstance()->getImage("promptText");

	m_EndFlag = false;
	PlayMusic("Sound/TitleBGM1.mid", DX_PLAYTYPE_LOOP);
	m_SelectManagerPtr->initialize();
	m_IsVisual = false;
	m_Timer.Initialize();
}

void YouWin::update() {
	m_SelectManagerPtr->update();

	if (m_SelectManagerPtr->isSelected()) {
		nextScene = m_SelectManagerPtr->getSelection() == 0 ? eScene::GAMEPLAY : eScene::TITLE;
		m_EndFlag = true;
		return;
	}

	m_Timer.Update();
	if (m_Timer.IsTime()) {
		m_Timer.Initialize();
		m_IsVisual = !m_IsVisual;
	}
}

void YouWin::draw() {
	DrawGraph(110, 70, m_ImgHandle, TRUE);
	
	int R, G, B;
	if (GameConst::Winner == 1) {
		R = 0;
		G = 130;
		B = 230;
	}
	else if (GameConst::Winner == 2) {
		R = 255;
		G = 180;
		B = 70;
	}
	std::string result = "Winner:P" + std::to_string(GameConst::Winner);
	DrawExtendString(310, 300, 2.5f, 2.0f, result.c_str(), GetColor(R, G, B));


	DrawGraph(150, 360, ResourceManager::getInstance()->getImage("TryAgain"), TRUE);
	DrawGraph(150, 410, ResourceManager::getInstance()->getImage("BackToTitle"), TRUE);

	int _X = 220;
	int _Y = 0;
	if (m_SelectManagerPtr->getSelection() == 0) {
		_Y = 360;
	} else {
		_Y = 410;
	}
	if (m_IsVisual) {
		DrawGraph(_X, _Y, ResourceManager::getInstance()->getImage("Mask"), TRUE);
	}

}

void YouWin::drawDebug() { }

eScene YouWin::next() {
	return nextScene;
}

bool YouWin::isEnd() {
	return m_EndFlag;
}