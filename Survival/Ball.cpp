#include "DxLib.h"

#include "ResourceManager.h"
#include "StageManager.h"
#include "Matrix2.h"

#include "Ball.h"
#include "MoveState_B.h"

Ball::Ball(ObjManagerP _ObjManagerPtr) :
	m_BallStateNomalPtr(new MoveState_B(_ObjManagerPtr))
{ 
	m_Property.Motion = Range(0, 4, 0.1f);
	m_Property.ImgName = "ball";
	m_Property.Tag = eTag::ENEMY;
	m_Property.CollitionRadius = Parameter::CollitionRadius_Ball;
	GameObject::m_ObjectManager = _ObjManagerPtr;
	PlaySoundMem(LoadSoundMem("Sound/shootSound.wav"), DX_PLAYTYPE_BACK);
}

void Ball::initialize() {
	GameObject::initialize();
	m_BallStateNomalPtr = std::make_shared<MoveState_B>(GameObject::m_ObjectManager);
}

void Ball::update() {
	GameObject::update();
	m_BallStateNomalPtr = m_BallStateNomalPtr->update(*this);
}

void Ball::checkCollitionData() {
	m_Property.CollitionMap = StageManager::getFloor(m_Property.CurrentLevel + 1);	//����Level�̈����`�F�b�N
}

void Ball::drawBody() {
	//�{�̕`��
	if (m_Property.HP > 0) {
		int ballImg = ResourceManager::getInstance()->getImage(m_Property.ImgName);
		DrawGraph(m_Property.PositionC.X, m_Property.PositionC.Y - m_Property.CurrentHeight, ballImg, TRUE); //�����ɍ��킹�ĕ`��
	}
	//��ԕ`��
	m_BallStateNomalPtr->draw();
}

void Ball::drawShadow() {
	//�e�`��
	int ballShadow = ResourceManager::getInstance()->getImage("ballShadow");
	DrawGraph(m_Property.PositionC.X, m_Property.PositionC.Y + 25 - m_Property.ShadowHeight, ballShadow, TRUE);	//45: ������e�`��ʒu�܂ł̋���
}

void Ball::drawDebug() {
	//Ball�̈ʒu��\��
	int redPImg = ResourceManager::getInstance()->getImage("PlayerPoint");
	DrawGraph(m_Property.BeforeP.X - 4, m_Property.BeforeP.Y - 4, redPImg, TRUE);
}
