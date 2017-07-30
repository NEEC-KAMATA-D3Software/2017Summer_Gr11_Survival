#pragma once
#ifndef _MOVESTATE_B_H_
#define _MOVESTATE_B_H_

#include <memory>
#include "StateBase.h"
#include "Parameter.h"

class Ball;
class ObjectManager;

using ObjManagerP = std::shared_ptr<ObjectManager>;

class MoveState_B : public StateBase<Ball> {
public:
	MoveState_B(ObjManagerP _ObjManagerPtr);
	~MoveState_B();

	virtual void draw() override;
	virtual void drawDebug() override;

protected:
	virtual void initialize(Ball& thisTarget) override;
	virtual eTrans action(Ball& thisTarget, std::shared_ptr<StateBase<Ball>>& nextState) override;
	virtual void exitAction(Ball& thisTarget) override;

private:
	void moveBefore(Ball& thisTarget);
	void move(Ball& thisTarget);
	bool isMoveAble(Ball& thisTarget);
	bool isMoveAbleOne(Ball& thisTarget);

private:
	float speed = Parameter::BallSpeed;
	ObjManagerP m_ObjManagerPtr;
};

#endif // !_MOVESTATE_B_H_
