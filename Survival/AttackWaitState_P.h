#pragma once
#ifndef _ATTACKWAITSTATE_P_H_
#define _ATTACKWAITSTATE_P_H_

#include <memory>
#include "StateBase.h"

class Player;
class InputState;
class Controller;
class ObjectManager;

using InputP = std::shared_ptr<InputState>;
using ContrP = std::shared_ptr<Controller>;
using ObjManagerP = std::shared_ptr<ObjectManager>;

class AttackWaitState_P : public StateBase<Player> {
public:
	AttackWaitState_P(InputP _inputPtr, ContrP _contrPtr, ObjManagerP _ObjManagerPtr);
	~AttackWaitState_P();

	virtual void draw() override;
	virtual void drawDebug() override;

protected:
	virtual void initialize(Player& thisTarget) override;
	virtual eTrans action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) override;
	virtual void exitAction(Player& thisTarget) override;

private:
	InputP m_InputStatePtr;
	ContrP m_ContrStatePtr;
	ObjManagerP m_ObjManagerPtr;
};

#endif // !_ATTACKWAITSTATE_P_H_
