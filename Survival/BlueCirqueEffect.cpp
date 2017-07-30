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
	//�̂̐^�񒆂���o��悤
}

void BlueCirqueEffect::checkCollitionData() {
	m_Property.CollitionMap = StageManager::getFloor(m_Property.CurrentLevel + 1);	//����Level�̈����`�F�b�N
}

void BlueCirqueEffect::drawBody() {
	//�{�̕`��
	int effectImg = ResourceManager::getInstance()->getGroupImg(m_Property.ImgName, m_Property.Motion.getCursor());
	DrawGraph(m_Property.PositionC.X, m_Property.PositionC.Y - m_Property.CurrentHeight, effectImg, TRUE); //�����ɍ��킹�ĕ`��
}

void BlueCirqueEffect::drawShadow() { }

void BlueCirqueEffect::drawDebug() { }
