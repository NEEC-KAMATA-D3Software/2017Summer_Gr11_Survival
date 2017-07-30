#include "InputState.h"
#include "DxLib.h"

InputState::InputState(){}

InputState::~InputState() {}

void InputState::updateKey() {
	for (int i = 0; i < 256; i++) {
		m_Previouskeys[i] = m_Currentkeys[i];
	}
	GetHitKeyStateAll(m_Currentkeys);
}

bool InputState::wasKeyDown(int keycode) {
	return m_Previouskeys[keycode] == 0 && m_Currentkeys[keycode] == 1;
}

bool InputState::wasKeyUp(int keycode) {
	return m_Previouskeys[keycode] == 1 && m_Currentkeys[keycode] == 0;
}

bool InputState::isKeyDown(int keycode) {
	return m_Previouskeys[keycode] == 1 && m_Currentkeys[keycode] == 1;
}