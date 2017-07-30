#include "Selector.h"
#include "GameDevice.h"
#include "InputState.h"
#include "Controller.h"
#include "DxLib.h"

Selector::Selector(std::shared_ptr<GameDevice> _device, int _count, bool _isLoop) :
	m_selectCount(_count),
	m_SelecteNum(0),
	m_IsSelected(false),
	m_IsLoop(_isLoop),
	m_InputStatePtr(_device->getInputState()),
	m_ContrStatePtr(_device->getContrState())
{ }

Selector::~Selector() {}

void Selector::initialize() {
	m_IsSelected = false;
	m_SelecteNum = 0;
}

void Selector::update() {
	if (m_InputStatePtr->wasKeyDown(KEY_INPUT_RETURN)) {
		m_IsSelected = true;
	}
	if (m_ContrStatePtr->wasButtonDown(ePadCode::PAD_JUMP, 1)) {
		m_IsSelected = true;
	}

	if (m_IsSelected) { 
		PlaySoundMem(LoadSoundMem("Sound/selector.wav"), DX_PLAYTYPE_BACK);
		return; 
	}

	next();
	forward();

	if (m_IsLoop) {	warp(); } 
	else { clamp(); }
}

void Selector::setCount(int _max) {
	m_selectCount = _max;
}

bool Selector::isSelected() {
	return m_IsSelected;
}

int Selector::getSelection() {
	return m_SelecteNum;
}


void Selector::warp() {
	if (m_SelecteNum >= m_selectCount) {
		m_SelecteNum = 0;
	}
	else if (m_SelecteNum < 0) {
		m_SelecteNum = m_selectCount - 1;
	}
}

void Selector::clamp() {
	if (m_SelecteNum >= m_selectCount) {
		m_SelecteNum = m_selectCount - 1;
	}
	else if (m_SelecteNum < 0) {
		m_SelecteNum = 0;
	}
}

void Selector::next() {
	bool isAct = false;
	if (m_InputStatePtr->wasKeyDown(KEY_INPUT_RIGHT)) {
		isAct = true;
	}
	else if(m_InputStatePtr->wasKeyDown(KEY_INPUT_DOWN)) {
		isAct = true;
	}
	if (m_ContrStatePtr->wasButtonDown(ePadCode::PAD_RIGHT, 1)) {
		isAct = true;
	}
	else if (m_ContrStatePtr->wasButtonDown(ePadCode::PAD_DOWN, 1)) {
		isAct = true;
	}

	if (isAct) {
		m_SelecteNum++;
		PlaySoundMem(LoadSoundMem("Sound/selector.wav"), DX_PLAYTYPE_BACK);
	}
}

void Selector::forward() {
	bool isAct = false;
	if (m_InputStatePtr->wasKeyDown(KEY_INPUT_LEFT)) {
		isAct = true;
	}
	else if (m_InputStatePtr->wasKeyDown(KEY_INPUT_UP)) {
		isAct = true;
	}
	if (m_ContrStatePtr->wasButtonDown(ePadCode::PAD_LEFT, 1)) {
		isAct = true;
	}
	else if (m_ContrStatePtr->wasButtonDown(ePadCode::PAD_UP, 1)) {
		isAct = true;
	}

	if (isAct) {
		m_SelecteNum--;
		PlaySoundMem(LoadSoundMem("Sound/selector.wav"), DX_PLAYTYPE_BACK);
	}
}
