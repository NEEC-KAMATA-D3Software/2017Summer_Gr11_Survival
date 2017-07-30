#include "Death_P.h"
#include "ObjectManager.h"
#include "ExplosionEffect.h"
#include "Player.h"
#include "DxLib.h"


Death_P::Death_P(ObjManagerP _ObjManagerPtr) :
	m_ObjManagerPtr(_ObjManagerPtr)
{ }

Death_P::~Death_P() {}

void Death_P::initialize(Player& thisTarget) {
	//ëÃÇÃê^ÇÒíÜÇ©ÇÁèoÇÈÇÊÇ§
	m_Explosion = std::make_shared<ExplosionEffect>();
	m_Explosion->getProperty().PositionC = thisTarget.getProperty().PositionC + Float2(-16, -4);
	m_Explosion->getProperty().BeforeP = thisTarget.getProperty().BeforeP;
	m_Explosion->getProperty().CurrentHeight = thisTarget.getProperty().CurrentHeight;
	m_Explosion->getProperty().CurrentLevel = thisTarget.getProperty().CurrentLevel;
	m_ObjManagerPtr->addObject(m_Explosion);
}

eTrans Death_P::action(Player& thisTarget, std::shared_ptr<StateBase<Player>>& nextState) {
	if (m_Explosion->getProperty().IsDead) {
		thisTarget.getProperty().IsDead = true;
	}
	nextState = std::make_shared<Death_P>(*this);
	return eTrans::TOTHIS;
}

void Death_P::exitAction(Player& thisTarget) { }

void Death_P::draw() { }

void Death_P::drawDebug() { 
	DrawString(550, 140, "NormalState : Death", GetColor(255, 0, 0));
}