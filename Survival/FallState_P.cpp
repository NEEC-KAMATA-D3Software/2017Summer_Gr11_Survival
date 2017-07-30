#include "FallState_P.h"
#include "NoneState_P.h"
#include "Player.h"
#include "DxLib.h"


FallState_P::FallState_P(InputP _inputPtr, ContrP _contrPtr) :
	m_InputStatePtr(_inputPtr),
	m_ContrStatePtr(_contrPtr),
	speedY(1)
{}

FallState_P::~FallState_P() { }

void FallState_P::initialize(Player& thisTarget) { }

eTrans FallState_P::action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) {
	if (updateFall(thisTarget)) {
		nextState = std::make_shared<FallState_P>(*this);
		return eTrans::TOTHIS;
	}
	nextState = std::make_shared<NoneState_P>(m_InputStatePtr, m_ContrStatePtr);
	return eTrans::TONEXT;
}


bool FallState_P::updateFall(Player& thisTarget) {
	Float2 playerPoint = thisTarget.getProperty().CurrentPoint;
	speedY *= 1.2f;
	for (int i = 0; i < (int)speedY; i++) {
		if (thisTarget.getProperty().CollitionMap[(int)playerPoint.Y][(int)playerPoint.X] < 8 &&
			thisTarget.getProperty().CollitionMap[(int)playerPoint.Y][(int)playerPoint.X] > 0 &&
			(int)thisTarget.getProperty().CurrentHeight == thisTarget.getProperty().CurrentLevel * Parameter::LevelHeight
			)
		{
			thisTarget.getProperty().CurrentHeight = thisTarget.getProperty().CurrentLevel * Parameter::LevelHeight;
			return false;
		}
		thisTarget.getProperty().CurrentHeight--;
		thisTarget.checkCollitionData();
	}
	return true;
}

void FallState_P::exitAction(Player& thisTarget) { }

void FallState_P::draw() { }

void FallState_P::drawDebug() {
	DrawString(550, 120, "InterimState : Fall", GetColor(255, 0, 0));
}