#pragma once
#ifndef _DEATH_P_H_
#define _DEATH_P_H_

#include <memory>
#include "StateBase.h"

class Player;
class GameObject;
class ObjectManager;

using ObjManagerP = std::shared_ptr<ObjectManager>;

class Death_P : public StateBase<Player> {
public:
	Death_P(ObjManagerP _ObjManagerPtr);
	~Death_P();

	virtual void draw() override;
	virtual void drawDebug() override;

protected:
	virtual void initialize(Player& thisTarget) override;
	virtual eTrans action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) override;
	virtual void exitAction(Player& thisTarget) override;

private:
	ObjManagerP m_ObjManagerPtr;
	std::shared_ptr<GameObject> m_Explosion;
};

#endif // !_DEATH_P_H_
