#pragma once
#ifndef _MOVESTATE_P_H_
#define _MOVESTATE_P_H_

#include <array>
#include "StateBase.h"
#include "Vector2.h"

class Player;
class InputState;
class Controller;
class ObjectManager;

using InputP = std::shared_ptr<InputState>;
using ContrP = std::shared_ptr<Controller>;
using ObjManagerP = std::shared_ptr<ObjectManager>;

class MoveState_P : public StateBase<Player> {
public:
	MoveState_P(InputP _inputPtr, ContrP _contrPtr, ObjManagerP _ObjManagerPtr);
	~MoveState_P();

	virtual void draw() override;
	virtual void drawDebug() override;

protected:
	virtual void initialize(Player& thisTarget) override;
	virtual eTrans action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) override;
	virtual void exitAction(Player& thisTarget) override;

private:
	void checkVelocity(Player& thisTarget);
	void moveBefore(Player& thisTarget);
	void move(Player& thisTarget);
	bool isMoveAble(Player& thisTarget);
	bool isMoveAbleOne(Player& thisTarget);

private:
	InputP m_InputStatePtr;
	ContrP m_ContrStatePtr;
	ObjManagerP m_ObjManagerPtr;
	float speed;

	//eDirectionP順(8方向登録)
	//描画タイルとあたり判定タイルのサイズの比を常数にした
	std::array<Float2, 9> BeforeVs;
	std::array<Float2, 9> VelocityCs;
};

#endif // !_MOVESTATE_P_H_
