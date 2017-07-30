#pragma once
#ifndef _JUMPSTATE_P_H_
#define _JUMPSTATE_P_H_

#include <memory>
#include "StateBase.h"
#include "Parameter.h"

class Player;
class InputState;
class Controller;

using InputP = std::shared_ptr<InputState>;
using ContrP = std::shared_ptr<Controller>;

class JumpState_P : public StateBase<Player>{
public:
	JumpState_P(InputP _inputPtr, ContrP _contrPtr);
	~JumpState_P();

	virtual void draw() override;
	virtual void drawDebug() override;

protected:
	virtual void initialize(Player& thisTarget) override;
	virtual eTrans action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) override;
	virtual void exitAction(Player& thisTarget) override;

private:
	bool updateJump(Player& thisTarget);

private:
	InputP m_InputStatePtr;
	ContrP m_ContrStatePtr;
	float m_JumpPower = Parameter::PlayerJumpPower;
};

#endif // !_JUMPSTATE_P_H_
