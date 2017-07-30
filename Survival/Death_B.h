#pragma once
#ifndef _DEATH_B_H_
#define _DEATH_B_H_

#include <memory>
#include "StateBase.h"

class Ball;
class ObjectManager;

using ObjManagerP = std::shared_ptr<ObjectManager>;

class Death_B : public StateBase<Ball> {
public:
	Death_B(ObjManagerP _ObjManagerPtr);
	~Death_B();

	virtual void draw() override;
	virtual void drawDebug() override;

protected:
	virtual void initialize(Ball& thisTarget) override;
	virtual eTrans action(Ball& thisTarget, std::shared_ptr<StateBase<Ball>>& nextState) override;
	virtual void exitAction(Ball& thisTarget) override;	

private:
	ObjManagerP m_ObjManagerPtr;
	std::shared_ptr<GameObject> m_Rupture;
};

#endif // !_DEATH_B_H_
