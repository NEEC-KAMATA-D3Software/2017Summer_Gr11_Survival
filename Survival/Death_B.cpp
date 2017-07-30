#include "RuptureEffect.h"
#include "ObjectManager.h"
#include "Death_B.h"
#include "Ball.h"
#include "DxLib.h"

Death_B::Death_B(ObjManagerP _ObjManagerPtr):
	m_ObjManagerPtr(_ObjManagerPtr) 
{ }

Death_B::~Death_B() {}

void Death_B::initialize(Ball& thisTarget) { 
	m_Rupture = std::make_shared<RuptureEffect>();
	m_Rupture->getProperty().PositionC = thisTarget.getProperty().PositionC - Float2(4, 4);
	m_Rupture->getProperty().BeforeP = thisTarget.getProperty().BeforeP;
	m_Rupture->getProperty().CurrentHeight = thisTarget.getProperty().CurrentHeight;
	m_Rupture->getProperty().CurrentLevel = thisTarget.getProperty().CurrentLevel;
	m_ObjManagerPtr->addObject(m_Rupture);
}

eTrans Death_B::action(Ball& thisTarget, std::shared_ptr<StateBase<Ball>>& nextState) {
	if (m_Rupture->getProperty().IsDead) {
		thisTarget.getProperty().IsDead = true;
	}
	nextState = std::make_shared<Death_B>(*this);
	return eTrans::TOTHIS;
}

void Death_B::exitAction(Ball& thisTarget) { }

void Death_B::draw() { }

void Death_B::drawDebug() { }
