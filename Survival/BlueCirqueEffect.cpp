#include "DxLib.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "BlueCirqueEffect.h"

BlueCirqueEffect::BlueCirqueEffect()
{
	m_Property.ImgName = "CirqueEffect";
	m_Property.Motion.setRange(0, 4);
	m_Property.Motion.setTimer(0.08f);
	m_Property.Motion.setLoop(false);
	PlaySoundMem(LoadSoundMem("Sound/Cirque.wav"), DX_PLAYTYPE_BACK);
}

void BlueCirqueEffect::initialize() {
	GameObject::initialize();
}

void BlueCirqueEffect::update() {
	GameObject::update();
	m_Property.IsDead = m_Property.Motion.IsLast();
	//体の真ん中から出るよう
}

void BlueCirqueEffect::checkCollitionData() {
	m_Property.CollitionMap = StageManager::getFloor(m_Property.CurrentLevel + 1);	//所在Levelの一個上をチェック
}

void BlueCirqueEffect::drawBody() {
	//本体描画
	int effectImg = ResourceManager::getInstance()->getGroupImg(m_Property.ImgName, m_Property.Motion.getCursor());
	DrawGraph(m_Property.PositionC.X, m_Property.PositionC.Y - m_Property.CurrentHeight, effectImg, TRUE); //高さに合わせて描画
}

void BlueCirqueEffect::drawShadow() { }

void BlueCirqueEffect::drawDebug() { }
