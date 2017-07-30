#include "DxLib.h"
#include"ResourceManager.h"
#include "GameConst.h"

#include "GameDevice.h"
#include "InputState.h"
#include "Controller.h"
#include "Selector.h"

#include "Title.h"

Title::Title(std::shared_ptr<GameDevice> gameDevicePtr) :
	m_EndFlag(false),
	m_InputStatePtr(gameDevicePtr->getInputState()),
	m_ContrStatePtr(gameDevicePtr->getContrState()),
	m_SelectManagerPtr(new Selector(gameDevicePtr, 3)),
	m_Timer(Timer(0.3f)),
	m_IsVisual(false)
{ }

Title::~Title() {}

void Title::initialize() {
	m_TitleImg = ResourceManager::getInstance()->getImage("title");
	m_MultyPlayImg = ResourceManager::getInstance()->getImage("MultyPlay");
	m_CooperateImg = ResourceManager::getInstance()->getImage("Cooperate");
	m_SingleImg = ResourceManager::getInstance()->getImage("Single");
	m_MaskImg = ResourceManager::getInstance()->getImage("Mask");
	
	m_Selection.push_back(m_SingleImg);
	m_Selection.push_back(m_CooperateImg);
	m_Selection.push_back(m_MultyPlayImg);
	m_EndFlag = false;

	m_SelectManagerPtr->initialize();
	PlayMusic("Sound/TitleBGM1.mid", DX_PLAYTYPE_LOOP);
	m_Timer.Initialize();
	m_IsVisual = false;
}

void Title::update() {
	m_SelectManagerPtr->update();
	
	if (m_SelectManagerPtr->isSelected()) {
		GameConst::setMode((eGameMode)m_SelectManagerPtr->getSelection());
		m_EndFlag = true;
		return;
	}

	m_Timer.Update();
	if (m_Timer.IsTime()) {
		m_Timer.Initialize();
		m_IsVisual = !m_IsVisual;
	}
}

void Title::draw() {
	DrawGraph(120, 50, m_TitleImg, TRUE);
	DrawGraph(250, 310, m_Selection[0], TRUE);
	DrawGraph(250, 390, m_Selection[1], TRUE);
	DrawGraph(250, 470, m_Selection[2], TRUE);

	int _X = 250;
	int _Y = 0;
	if (m_SelectManagerPtr->getSelection() == 0) {
		_Y = 310;
	}
	else if (m_SelectManagerPtr->getSelection() == 1) {
		_Y = 390;
	} 
	else {
		_Y = 470;
	}
	if (m_IsVisual) {
		DrawGraph(_X, _Y, m_MaskImg, TRUE);
	}
}

void Title::drawDebug() {

}

eScene Title::next() {
	return eScene::GAMEPLAY;
}

bool Title::isEnd() {
	return m_EndFlag;
}