#include "AttackState_P.h"
#include "AttackWaitState_P.h"
#include "BlueCirqueEffect.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Ball.h"
#include "DxLib.h"


AttackState_P::AttackState_P(InputP _inputPtr, ContrP _contrPtr, ObjManagerP _ObjManagerPtr) :
	m_InputStatePtr(_inputPtr),
	m_ContrStatePtr(_contrPtr),
	m_ObjManagerPtr(_ObjManagerPtr)
{ }

AttackState_P::~AttackState_P() {}

void AttackState_P::initialize(Player& thisTarget) {
	m_ObjManagerPtr->addObject(creatEffect(thisTarget));
	m_ObjManagerPtr->addObject(creatObject(thisTarget));
}

eTrans AttackState_P::action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) {
	if (m_Cirque->getProperty().IsDead) {
		nextState = std::make_shared<AttackWaitState_P>(m_InputStatePtr, m_ContrStatePtr, m_ObjManagerPtr);
		return eTrans::TONEXT;
	}
	nextState = std::make_shared<AttackState_P>(*this);
	return eTrans::TOTHIS;
}

std::shared_ptr<GameObject> AttackState_P::creatObject(Player& thisTarget) {
	std::shared_ptr<GameObject> b(new Ball(m_ObjManagerPtr));
	//‘Ì‚Ì^‚ñ’†‚©‚çËo‚·‚é‚æ‚¤
	b->getProperty().PositionC = thisTarget.getProperty().PositionC + Float2(8, 25);
	b->getProperty().BeforeP = thisTarget.getProperty().BeforeP;

	int directionNo = (int)thisTarget.getProperty().Direction == (int)eDirectionP::NONE ?
		(int)thisTarget.getProperty().DirectBefore :
		(int)thisTarget.getProperty().Direction;

	b->getProperty().BeforeV = Parameter::SquareVelocitys[directionNo];
	b->getProperty().VelocityC = Parameter::RhombVelocitys[directionNo];

	b->getProperty().CurrentHeight = thisTarget.getProperty().CurrentHeight;
	b->getProperty().CurrentLevel = thisTarget.getProperty().CurrentLevel;
	b->getProperty().ID = thisTarget.getProperty().ID;
	return b;
}

std::shared_ptr<GameObject> AttackState_P::creatEffect(Player& thisTarget) {
	//‘Ì‚Ì^‚ñ’†‚É—ˆ‚é‚æ‚¤
	m_Cirque = std::make_shared<BlueCirqueEffect>();
	m_Cirque->getProperty().PositionC = thisTarget.getProperty().PositionC + Float2(-6, 8);
	m_Cirque->getProperty().BeforeP = thisTarget.getProperty().BeforeP;
	m_Cirque->getProperty().CurrentHeight = thisTarget.getProperty().CurrentHeight;
	m_Cirque->getProperty().CurrentLevel = thisTarget.getProperty().CurrentLevel;
	m_Cirque->getProperty().Motion.setRange(0, 4);
	return m_Cirque;
}

void AttackState_P::exitAction(Player& thisTarget) { }

void AttackState_P::draw() { }

void AttackState_P::drawDebug() {
	DrawString(550, 160, "AttackState : Attack", GetColor(255, 0, 0));
}