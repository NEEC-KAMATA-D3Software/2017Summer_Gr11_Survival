#pragma once
#ifndef _NONESTATE_P_H_
#define _NONESTATE_P_H_

#include <memory>
#include "StateBase.h"

class Player;
class InputState;
class Controller;

using InputP = std::shared_ptr<InputState>;
using ContrP = std::shared_ptr<Controller>;

class NoneState_P : public StateBase<Player> {
public:
	NoneState_P(InputP _inputPtr, ContrP _contrPtr);
	~NoneState_P();

	virtual void draw() override;
	virtual void drawDebug() override;

protected:
	virtual void initialize(Player& thisTarget) override;
	virtual eTrans action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) override;
	virtual void exitAction(Player& thisTarget) override;

private:
	InputP m_InputStatePtr;
	ContrP m_ContrStatePtr;
};

#endif // !_NONESTATE_P_H_
