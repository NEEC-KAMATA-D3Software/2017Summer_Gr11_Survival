#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <memory>
#include "DxLib.h"
#include "GameObject.h"
#include "StateBase.h"

class GameDevice;
class InputState;
class Controller;
class ObjectManager;

class Player : public GameObject {
public:
	Player(std::shared_ptr<GameDevice> gameDevicePtr, std::shared_ptr<ObjectManager> objManager, int Num = 1);

	virtual void update() override;
	virtual void initialize() override;
	virtual void drawBody() override;
	virtual void drawShadow() override;
	virtual void drawDebug() override;

private:
	void DirectionCheck();
	Float2 getStartPosition();

private:
	std::shared_ptr<InputState> m_InputStatePtr;
	std::shared_ptr<Controller> m_ContrStatePtr;
	std::shared_ptr<StateBase<Player>> m_AttackStatePtr;
	std::shared_ptr<StateBase<Player>> m_InterimStatePtr;
	std::shared_ptr<StateBase<Player>> m_NormalStatePtr;
	
	std::array<int, 4> m_Keycords{
		KEY_INPUT_UP,
		KEY_INPUT_RIGHT,
		KEY_INPUT_DOWN,
		KEY_INPUT_LEFT
	};
};

#endif // !_PLAYER_H_
