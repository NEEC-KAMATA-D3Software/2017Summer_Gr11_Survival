#include "MoveState_P.h"
#include "Parameter.h"
#include "StageManager.h"
#include "Player.h"
#include "Death_P.h"

#define PI 3.1415926

MoveState_P::MoveState_P(InputP _inputPtr, ContrP _contrPtr, ObjManagerP _ObjManagerPtr):
	m_InputStatePtr(_inputPtr),
	m_ContrStatePtr(_contrPtr),
	m_ObjManagerPtr(_ObjManagerPtr),
	speed(Parameter::PlayerMoveSpeed),
	BeforeVs(Parameter::SquareVelocitys),
	VelocityCs(Parameter::RhombVelocitys)
{ }

MoveState_P::~MoveState_P() {}

void MoveState_P::initialize(Player& thisTarget) {}

eTrans MoveState_P::action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) {
	checkVelocity(thisTarget);
	isMoveAble(thisTarget);

	if (thisTarget.getProperty().HP <= 0) {
		nextState = std::make_shared<Death_P>(m_ObjManagerPtr);
		return eTrans::TONEXT;
	}
	nextState = std::make_shared<MoveState_P>(*this);
	return eTrans::TOTHIS;
}


void MoveState_P::exitAction(Player& thisTarget) { }

void MoveState_P::checkVelocity(Player& thisTarget) {
	int directionNo = (int)thisTarget.getProperty().Direction;
	thisTarget.getProperty().BeforeV = BeforeVs[directionNo];
	thisTarget.getProperty().VelocityC = VelocityCs[directionNo];
}

void MoveState_P::moveBefore(Player& thisTarget) {
	thisTarget.getProperty().BeforeP += thisTarget.getProperty().BeforeV;
}

void MoveState_P::move(Player& thisTarget) {
	thisTarget.getProperty().PositionC += thisTarget.getProperty().VelocityC;
}

bool MoveState_P::isMoveAble(Player& thisTarget) {
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

bool MoveState_P::isMoveAbleOne(Player& thisTarget) {
	float colRadius = Parameter::CollitionRadius_Player;

	//StageäOÇÕÇ¢ÇØÇ»Ç¢
	Float2 playerPoint = thisTarget.getNextPoint(colRadius);
	if (playerPoint.X < 0 || playerPoint.Y < 0) {
		return false;
	}
	if (playerPoint.X >= StageManager::MaxX ||
		playerPoint.Y >= StageManager::MaxY) {
		return false;
	}

	//è·äQï®Ç™Ç†ÇÈÇ∆Ç¢ÇØÇ»Ç¢
	for (int y = 0; y < StageManager::MaxY; y++) {
		for (int x = 0; x < StageManager::MaxX; x++) {
			if (thisTarget.getProperty().CollitionMap[(int)playerPoint.Y][(int)playerPoint.X] >= 8) {
				return false;
			}
		}
	}
	return true;
}

void MoveState_P::draw() {

}

void MoveState_P::drawDebug() {
	DrawString(550, 140, "NormalState : Move", GetColor(255, 0, 0));
}
