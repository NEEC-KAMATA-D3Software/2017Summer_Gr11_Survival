#include "NoneState_P.h"
#include "JumpState_P.h"
#include "FallState_P.h"

#include "InputState.h"
#include "Controller.h"
#include "Player.h"


NoneState_P::NoneState_P(InputP _inputPtr, ContrP _contrPtr) :
	m_InputStatePtr(_inputPtr),
	m_ContrStatePtr(_contrPtr)
{}


NoneState_P::~NoneState_P() {}


void NoneState_P::initialize(Player& thisTarget) {
}


eTrans NoneState_P::action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) {
	if (thisTarget.getProperty().HP <= 0) {
		nextState = std::make_shared<NoneState_P>(*this);
		return eTrans::TOTHIS;
	}

	//Jump‚É‘JˆÚ
	if (m_InputStatePtr->wasKeyDown(KEY_INPUT_SPACE) ||
		m_ContrStatePtr->wasButtonDown(ePadCode::PAD_JUMP, thisTarget.getProperty().ID)
		) {
		nextState = std::make_shared<JumpState_P>(m_InputStatePtr, m_ContrStatePtr);
		return eTrans::TONEXT;
	}

	//Fall‚É‘JˆÚ
	Float2 playerPoint = thisTarget.getProperty().BeforeP / Parameter::BeforeSize;
	if (thisTarget.getProperty().CollitionMap[(int)playerPoint.Y][(int)playerPoint.X] == 0) {
		nextState = std::make_shared<FallState_P>(m_InputStatePtr, m_ContrStatePtr);
		return eTrans::TONEXT;
	}

	nextState = std::make_shared<NoneState_P>(*this);
	return eTrans::TOTHIS;
}


void NoneState_P::exitAction(Player& thisTarget) {


}

void NoneState_P::draw() {
	
}

void NoneState_P::drawDebug() {
	DrawString(550, 120, "InterimState : None", GetColor(255, 0, 0));
}
