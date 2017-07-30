#pragma once
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "DxLib.h"
#include <vector>

enum class ePadCode {
	PAD_UP = 0,
	PAD_RIGHT,
	PAD_DOWN,
	PAD_LEFT,
	PAD_ATTACK,
	PAD_JUMP,
	PAD_BACK,
	PAD_NONE,
};

class Controller {
public:
	Controller();
	~Controller();

	bool wasButtonDown(ePadCode code, int id);
	bool wasButtonUp(ePadCode code, int id);
	bool isButtonDown(ePadCode code, int id);
	void updateButton();

private:
	DINPUT_JOYSTATE m_PadState;
	std::vector<std::vector<bool>> m_ContrStateCurrent;
	std::vector<std::vector<bool>> m_ContrStatePrevious;

};

#endif // !_CONTROLLER_H_
