#include "AttackWaitState_P.h"
#include "AttackState_P.h"

#include "InputState.h"
#include "Controller.h"
#include "Player.h"


AttackWaitState_P::AttackWaitState_P(InputP _inputPtr, ContrP _contrPtr, ObjManagerP _ObjManagerPtr) :
	m_InputStatePtr(_inputPtr),
	m_ContrStatePtr(_contrPtr),
	m_ObjManagerPtr(_ObjManagerPtr)
{}


AttackWaitState_P::~AttackWaitState_P() {}


void AttackWaitState_P::initialize(Player& thisTarget) {
}


eTrans AttackWaitState_P::action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) {
	if (thisTarget.getProperty().HP <= 0) {
		nextState = std::make_shared<AttackWaitState_P>(*this);
		return eTrans::TOTHIS;
	}

	//Attack‚É‘JˆÚ
	if (m_InputStatePtr->wasKeyDown(KEY_INPUT_Z) ||
		m_ContrStatePtr->wasButtonDown(ePadCode::PAD_ATTACK, thisTarget.getProperty().ID)
		) {
		nextState = std::make_shared<AttackState_P>(m_InputStatePtr, m_ContrStatePtr, m_ObjManagerPtr);
		return eTrans::TONEXT;
	}

	nextState = std::make_shared<AttackWaitState_P>(*this);
	return eTrans::TOTHIS;
}


void AttackWaitState_P::exitAction(Player& thisTarget) {


}

void AttackWaitState_P::draw() {

}

void AttackWaitState_P::drawDebug() {
	DrawString(550, 160, "AttackState : None", GetColor(255, 0, 0));
}
