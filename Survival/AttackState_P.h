#pragma once
#ifndef _ATTACKSTATE_P_H_
#define _ATTACKSTATE_P_H_

#include <memory>
#include "StateBase.h"

class ObjectManager;
class InputState;
class Controller;
class GameObject;
class Player;

using InputP = std::shared_ptr<InputState>;
using ContrP = std::shared_ptr<Controller>;
using ObjManagerP = std::shared_ptr<ObjectManager>;

class AttackState_P : public StateBase<Player> {
public:
	AttackState_P(InputP _inputPtr, ContrP _contrPtr, ObjManagerP _ObjManagerPtr);
	~AttackState_P();

	virtual void draw() override;
	virtual void drawDebug() override;

protected:
	virtual void initialize(Player& thisTarget) override;
	virtual eTrans action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) override;
	virtual void exitAction(Player& thisTarget) override;

private:
	std::shared_ptr<GameObject> creatObject(Player& thisTarget);
	std::shared_ptr<GameObject> creatEffect(Player& thisTarget);

private:
	InputP m_InputStatePtr;
	ContrP m_ContrStatePtr;
	ObjManagerP m_ObjManagerPtr;
	std::shared_ptr<GameObject> m_Cirque;
};

#endif // !_ATTACKSTATE_P_H_
