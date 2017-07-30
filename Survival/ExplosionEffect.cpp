#include "DxLib.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect()
{
	m_Property.Motion.setRange(0, 9);
	m_Property.Motion.setTimer(0.08f);
	m_Property.Motion.setLoop(false);
	PlaySoundMem(LoadSoundMem("Sound/Explosion.wav"), DX_PLAYTYPE_BACK);
}

void ExplosionEffect::initialize() {
	GameObject::initialize();
}

void ExplosionEffect::update() {
	GameObject::update();
	m_Property.IsDead = m_Property.Motion.IsLast();
}

void ExplosionEffect::checkCollitionData() {
	m_Property.CollitionMap = StageManager::getFloor(m_Property.CurrentLevel + 1);	//所在Levelの一個上をチェック
}

void ExplosionEffect::drawBody() {
	//本体描画
	int effectImg = ResourceManager::getInstance()->getGroupImg("PlayerDead", m_Property.Motion.getCursor());
	DrawGraph(m_Property.PositionC.X, m_Property.PositionC.Y - m_Property.CurrentHeight, effectImg, TRUE); //高さに合わせて描画
}

void ExplosionEffect::drawShadow() { }

void ExplosionEffect::drawDebug() { }
