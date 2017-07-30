#include "DxLib.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "RuptureEffect.h"

RuptureEffect::RuptureEffect()
{
	m_Property.ImgName = "ballDead";
	m_Property.Motion.setRange(0, 5);
	m_Property.Motion.setTimer(0.1f);
	m_Property.Motion.setLoop(false);
	PlaySoundMem(LoadSoundMem("Sound/Rupture.wav"), DX_PLAYTYPE_BACK);
}

void RuptureEffect::initialize() {
	GameObject::initialize();
}

void RuptureEffect::update() {
	GameObject::update();
	m_Property.IsDead = m_Property.Motion.IsLast();
}

void RuptureEffect::checkCollitionData() {
	m_Property.CollitionMap = StageManager::getFloor(m_Property.CurrentLevel + 1);	//所在Levelの一個上をチェック
}

void RuptureEffect::drawBody() {
	//本体描画
	int effectImg = ResourceManager::getInstance()->getGroupImg(m_Property.ImgName, m_Property.Motion.getCursor());
	DrawGraph(m_Property.PositionC.X, m_Property.PositionC.Y - m_Property.CurrentHeight, effectImg, TRUE); //高さに合わせて描画
}

void RuptureEffect::drawShadow() { }

void RuptureEffect::drawDebug() { }
