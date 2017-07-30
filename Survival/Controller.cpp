#include "Controller.h"



Controller::Controller()
{ 
	for (int i = 1; i < 5; i++) {
		m_ContrStateCurrent.push_back({ false, false, false, false, false, false, false });
	}
	for (int i = 1; i < 5; i++) {
		m_ContrStatePrevious.push_back({ false, false, false, false, false, false, false });
	}
}

Controller::~Controller() {
	m_ContrStateCurrent.clear();
	m_ContrStatePrevious.clear();
}

void Controller::updateButton() {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < (int)ePadCode::PAD_NONE; i++) {
			m_ContrStatePrevious[j][i] = m_ContrStateCurrent[j][i];
		}
	}
	
	for (int i = 0; i < 4; i++) {
		if (GetJoypadDirectInputState(i, &m_PadState) == 0) {
			m_ContrStateCurrent[i][(int)ePadCode::PAD_LEFT] = m_PadState.X < -200;	// || m_PadState.POV[0] == 27000
			m_ContrStateCurrent[i][(int)ePadCode::PAD_RIGHT] = m_PadState.X > 200;	// || m_PadState.POV[0] == 9000
			m_ContrStateCurrent[i][(int)ePadCode::PAD_UP] = m_PadState.Y < -200;	// || m_PadState.POV[0] == 0
			m_ContrStateCurrent[i][(int)ePadCode::PAD_DOWN] = m_PadState.Y > 200;	// || m_PadState.POV[0] == 18000
			m_ContrStateCurrent[i][(int)ePadCode::PAD_JUMP] = m_PadState.Buttons[0] ? true : false;
			m_ContrStateCurrent[i][(int)ePadCode::PAD_ATTACK] = m_PadState.Buttons[1] ? true : false;
			m_ContrStateCurrent[i][(int)ePadCode::PAD_BACK] = m_PadState.Buttons[6] ? true : false;
		}
		else {
			for (int j = 0; j < (int)ePadCode::PAD_NONE; j++) {
				m_ContrStateCurrent[i][j] = false;
			}
		}
	}
}

bool Controller::wasButtonDown(ePadCode code, int id) {
	return !m_ContrStatePrevious[id][(int)code] && m_ContrStateCurrent[id][(int)code];
}

bool Controller::wasButtonUp(ePadCode code, int id) {
	return m_ContrStatePrevious[id][(int)code] && !m_ContrStateCurrent[id][(int)code];
}

bool Controller::isButtonDown(ePadCode code, int id) {
	return m_ContrStatePrevious[id][(int)code] && m_ContrStateCurrent[id][(int)code];
}