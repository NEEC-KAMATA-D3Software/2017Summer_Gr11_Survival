#include "MoveState_B.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "Death_B.h"
#include "Ball.h"

MoveState_B::MoveState_B(ObjManagerP _ObjManagerPtr):
	m_ObjManagerPtr(_ObjManagerPtr)
{ }

MoveState_B::~MoveState_B() {}

void MoveState_B::initialize(Ball& thisTarget) { }

eTrans MoveState_B::action(Ball& thisTarget, std::shared_ptr<StateBase<Ball>>& nextState) {
	if (!isMoveAble(thisTarget) || thisTarget.getProperty().HP <= 0) {
		nextState = std::make_shared<Death_B>(m_ObjManagerPtr);
		thisTarget.getProperty().HP = 0;
		return eTrans::TONEXT;
	}
	nextState = std::make_shared<MoveState_B>(*this);
	return eTrans::TOTHIS;
}

void MoveState_B::exitAction(Ball& thisTarget) { }

void MoveState_B::moveBefore(Ball& thisTarget) {
	thisTarget.getProperty().BeforeP += thisTarget.getProperty().BeforeV;
}

void MoveState_B::move(Ball& thisTarget) {
	thisTarget.getProperty().PositionC += thisTarget.getProperty().VelocityC;
}

bool MoveState_B::isMoveAble(Ball& thisTarget) {
	for (int i = 0; i < speed; i++) {
		if (isMoveAbleOne(thisTarget)) { 
			move(thisTarget);
			moveBefore(thisTarget);
		}
		else {
			return false;
		}
	}
	return true;
}

bool MoveState_B::isMoveAbleOne(Ball& thisTarget) {
	Float2 ballPoint = thisTarget.getNextPoint(Parameter::CollitionRadius_Ball);
	if (ballPoint.X < 0 || ballPoint.Y < 0) {
		return false;
	}
	if (ballPoint.X >= StageManager::MaxX ||
		ballPoint.Y >= StageManager::MaxY) {
		return false;
	}
	for (int y = 0; y < StageManager::MaxY; y++) {
		for (int x = 0; x < StageManager::MaxX; x++) {
			if (thisTarget.getProperty().CollitionMap[(int)ballPoint.Y][(int)ballPoint.X] == 5) {
				return false;
			}
			if (thisTarget.getProperty().CollitionMap[(int)ballPoint.Y][(int)ballPoint.X] == 6) {
				return false;
			}
		}
	}
	return true;
}

void MoveState_B::draw() { }

void MoveState_B::drawDebug() { }
