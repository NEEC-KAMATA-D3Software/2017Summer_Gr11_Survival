#pragma once
#ifndef _FALLSTATE_P_H_
#define _FALLSTATE_P_H_

#include <memory>
#include "StateBase.h"

class InputState;
class Controller;
class Player;

using InputP = std::shared_ptr<InputState>;
using ContrP = std::shared_ptr<Controller>;

class FallState_P : public StateBase<Player> {
public:
	FallState_P(InputP _inputPtr, ContrP _contrPtr);
	~FallState_P();

	virtual void draw() override;
	virtual void drawDebug() override;

protected:
	virtual void initialize(Player& thisTarget) override;
	virtual eTrans action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) override;
	virtual void exitAction(Player& thisTarget) override;

private:
	bool updateFall(Player& thisTarget);

private:
	InputP m_InputStatePtr;
	ContrP m_ContrStatePtr;
	float speedY;
};

#endif // !_FALLSTATE_P_H_
