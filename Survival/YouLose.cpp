#include "DxLib.h"
#include"ResourceManager.h"
#include "GameDevice.h"
#include "InputState.h"
#include "Controller.h"

#include "YouLose.h"

YouLose::YouLose(std::shared_ptr<GameDevice> gameDevicePtr) :
	m_EndFlag(false),
	m_Timer(0.5f),
	m_IsVisual(true),
	m_InputStatePtr(gameDevicePtr->getInputState()),
	m_ContrStatePtr(gameDevicePtr->getContrState())
{ }

YouLose::~YouLose() {}

void YouLose::initialize() {
	m_ImgHandle = ResourceManager::getInstance()->getImage("YouLose");
	m_PromptHandle = ResourceManager::getInstance()->getImage("promptText");

	m_EndFlag = false;
	PlayMusic("Sound/TitleBGM1.mid", DX_PLAYTYPE_LOOP);
}

void YouLose::update() {
	if (m_InputStatePtr->wasKeyDown(KEY_INPUT_RETURN)) {
		PlaySoundMem(LoadSoundMem("Sound/selector.wav"), DX_PLAYTYPE_BACK);
		m_EndFlag = true;
	}
	if (m_ContrStatePtr->wasButtonDown(ePadCode::PAD_JUMP, 1)) {
		PlaySoundMem(LoadSoundMem("Sound/selector.wav"), DX_PLAYTYPE_BACK);
		m_EndFlag = true;
	}

	m_Timer.Update();
	if (m_Timer.IsTime()) {
		m_Timer.Initialize();
		m_IsVisual = !m_IsVisual;
	}
}

void YouLose::draw() {
	DrawGraph(110, 100, m_ImgHandle, TRUE);
	if (m_IsVisual) {
		DrawGraph(150, 450, m_PromptHandle, TRUE);
	}
}

void YouLose::drawDebug() { }

eScene YouLose::next() {
	return eScene::TITLE;
}

bool YouLose::isEnd() {
	return m_EndFlag;
}