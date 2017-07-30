#pragma once
#ifndef _GAMEDEVICE_H_
#define _GAMEDEVICE_H_

#include <memory>

class InputState;
class Controller;

class GameDevice {
public:
	GameDevice();
	~GameDevice();

	void initialize();
	void update();
	std::shared_ptr<InputState> getInputState();
	std::shared_ptr<Controller> getContrState();

private:
	std::shared_ptr<InputState> m_InputStatePtr;
	std::shared_ptr<Controller> m_ContrStatePtr;
};

#endif // !_GAMEDEVICE_H_
