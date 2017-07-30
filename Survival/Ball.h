#pragma once
#ifndef _BALL_H_
#define _BALL_H_

#include <memory>
#include <array>
#include "StateBase.h"
#include "GameObject.h"

class ObjectManager;
using ObjManagerP = std::shared_ptr<ObjectManager>;

class Ball : public GameObject {
public:
	Ball(ObjManagerP _ObjManagerPtr);

	virtual void update() override;
	virtual void initialize() override;
	virtual void drawBody() override;
	virtual void drawShadow() override;
	virtual void drawDebug() override;

protected:
	virtual void checkCollitionData() override;

private:
	std::shared_ptr<StateBase<Ball>> m_BallStateNomalPtr;
};

#endif // !_BALL_H_
