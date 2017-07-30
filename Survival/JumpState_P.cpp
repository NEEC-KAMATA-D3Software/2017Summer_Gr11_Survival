#include "JumpState_P.h"
#include "FallState_P.h"
#include "Player.h"
#include "DxLib.h"

JumpState_P::JumpState_P(InputP _inputPtr, ContrP _contrPtr) :
	m_InputStatePtr(_inputPtr),
	m_ContrStatePtr(_contrPtr)
{}


JumpState_P::~JumpState_P() {}


void JumpState_P::initialize(Player& thisTarget) {


}

eTrans JumpState_P::action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) {
	if (!updateJump(thisTarget)) {
		nextState = std::make_shared<FallState_P>(m_InputStatePtr, m_ContrStatePtr);
		return eTrans::TONEXT;
	}

	nextState = std::make_shared<JumpState_P>(*this);
	return eTrans::TOTHIS;
}


void JumpState_P::exitAction(Player& thisTarget) {
	float m_JumpPower = Parameter::PlayerJumpPower;
}


bool JumpState_P::updateJump(Player& thisTarget) {
	thisTarget.getProperty().CurrentHeight += m_JumpPower;
	m_JumpPower *= 0.8f;
		
	if (m_JumpPower <= 0.5f){
		m_JumpPower = 0;
		return false;
	}
	return true;
}


void JumpState_P::draw() {

}

void JumpState_P::drawDebug() {
	DrawString(550, 120, "InterimState : Jump", GetColor(255, 0, 0));
}