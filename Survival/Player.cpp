#include "DxLib.h"

#include "ResourceManager.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "GameDevice.h"
#include "InputState.h"
#include "Controller.h"

#include "MoveState_P.h"
#include "NoneState_P.h"
#include "AttackWaitState_P.h"

#include "Parameter.h"
#include "Matrix2.h"
#include "Player.h"

#define PI 3.1415926
#define Speed Parameter::PlayerMoveSpeed;

Player::Player(std::shared_ptr<GameDevice> gameDevicePtr, std::shared_ptr<ObjectManager> objManager, int num) :
	m_InputStatePtr(gameDevicePtr->getInputState()),
	m_ContrStatePtr(gameDevicePtr->getContrState()),
	m_AttackStatePtr(new AttackWaitState_P(m_InputStatePtr, m_ContrStatePtr, objManager)),
	m_NormalStatePtr(new MoveState_P(m_InputStatePtr, m_ContrStatePtr, objManager)),
	m_InterimStatePtr(new NoneState_P(m_InputStatePtr, m_ContrStatePtr))
{ 
	GameObject::m_ObjectManager = objManager;
	m_Property.Tag = eTag::PLAYER;
	m_Property.ID = num;
	m_Property.ImgName = "Player" + std::to_string(m_Property.ID);
	m_Property.CollitionRadius = Parameter::CollitionRadius_Player;
}

void Player::initialize() {
	GameObject::initialize();
	if (m_Property.ID == 1) {
		m_Property.PositionC = getStartPosition()
			+ Float2(Parameter::HalfTileWidth, 0)	//センターラインをとる
			- Float2(Parameter::CharaSize / 4, Parameter::CharaSize - 5);	//座標は画像の足元に
	}
	if (m_Property.ID == 2) {
		Float2 offsetBefore = Float2(0, (StageManager::MaxY - 1) * Parameter::BeforeSize);
		Float2 offsetPosition = Parameter::RhombVelocitys[5] * (StageManager::MaxY - 1) * 0.8f * 1.2549f * Parameter::BeforeSize;
		m_Property.BeforeP = offsetBefore;
		m_Property.PositionC = getStartPosition()
			+ Float2(Parameter::HalfTileWidth, 0)	//センターラインをとる
			- Float2(Parameter::CharaSize / 4, Parameter::CharaSize - 5)	//座標は画像の足元に
			+ offsetPosition;
	}

	

	m_NormalStatePtr = std::make_shared<MoveState_P>(m_InputStatePtr, m_ContrStatePtr, GameObject::m_ObjectManager);
	m_InterimStatePtr = std::make_shared<NoneState_P>(m_InputStatePtr, m_ContrStatePtr);
	m_AttackStatePtr = std::make_shared<AttackWaitState_P>(m_InputStatePtr, m_ContrStatePtr, GameObject::m_ObjectManager);
}

void Player::update() {
	GameObject::update();
	m_InterimStatePtr = m_InterimStatePtr->update(*this);
	m_NormalStatePtr = m_NormalStatePtr->update(*this);
	m_AttackStatePtr = m_AttackStatePtr->update(*this);
	DirectionCheck();
}

Float2 Player::getStartPosition() {
	Float2 halfTile = Parameter::HalfTile;
	Float2 screenCenter = Parameter::ScreenCenter;
	float halfStageY = StageManager::MaxY * Parameter::HalfTileHeight;

	//stageの中心はscreenの中心に来るよう
	Float2 startP = screenCenter - Float2(0, halfStageY) - halfTile;
	return startP;
}

void Player::drawBody() {
	//本体描画
	if (m_Property.HP > 0) {
		int playerImg = ResourceManager::getInstance()->getGroupImg(m_Property.ImgName, m_Property.Motion.getCursorTri());
		DrawGraph(m_Property.PositionC.X, m_Property.PositionC.Y - m_Property.CurrentHeight, playerImg, TRUE); //ジャンプ高さに合わせて描画	
	}
	std::string label = "P" + std::to_string(m_Property.ID);
	int labelImg = ResourceManager::getInstance()->getImage(label);
	DrawGraph(m_Property.PositionC.X, m_Property.PositionC.Y - m_Property.CurrentHeight - 20, labelImg, TRUE);

	//状態描画
	m_NormalStatePtr->draw();
	m_InterimStatePtr->draw();
	m_AttackStatePtr->draw();
}

void Player::drawShadow() {
	//影描画
	int playerShadow = ResourceManager::getInstance()->getImage("shadow");
	DrawGraph(m_Property.PositionC.X, m_Property.PositionC.Y + 45 - m_Property.ShadowHeight, playerShadow, TRUE);	//45: 頭から影描画位置までの距離
}

void Player::drawDebug() {
	//プレーヤーの位置を表示
	int redPImg = ResourceManager::getInstance()->getImage("PlayerPoint");
	DrawGraph(m_Property.BeforeP.X - 4, m_Property.BeforeP.Y - 4, redPImg, TRUE);

	DrawFormatString(550,  0, GetColor(255, 0, 0), "P座標 : (%.2f, %.2f)", m_Property.PositionC.X, m_Property.PositionC.Y);
	DrawFormatString(550, 20, GetColor(255, 0, 0), "B座標 : (%.2f, %.2f)", m_Property.BeforeP.X, m_Property.BeforeP.Y);
	DrawFormatString(550, 40, GetColor(255, 0, 0), "JumpHeight : %.2f", m_Property.CurrentHeight);
	DrawFormatString(550, 60, GetColor(255, 0, 0), "CurrentLevel : %d", m_Property.CurrentLevel);
	DrawFormatString(550, 80, GetColor(255, 0, 0), "ShadowLevel : %d", m_Property.ShadowLevel);
	DrawFormatString(550, 160, GetColor(255, 0, 0), "PlayerHP : %d", m_Property.HP);

	DrawFormatString(550, 100, GetColor(255, 0, 0), "Point : (%d, %d)", 
		static_cast<int>(m_Property.CurrentPoint.X), 
		static_cast<int>(m_Property.CurrentPoint.Y));

	IntList current = StageManager::getFloor(m_Property.CurrentLevel);

	for (int y = 0; y < StageManager::MaxY; y++) {
		for (int x = 0; x < StageManager::MaxX; x++) {
			Float2 position = Float2(x, y) * Parameter::BeforeSize;
			int imgHandle = ResourceManager::getInstance()->getImage("debugMap");
			if (current[y][x] == 6) {
				DrawGraph(position.X, position.Y, imgHandle, TRUE);
			}
			if (current[y][x] == 5) {
				DrawGraph(position.X, position.Y, imgHandle, TRUE);
				DrawGraph(position.X, position.Y, imgHandle, TRUE);
			}
		}
	}
}

void Player::DirectionCheck() {
	int directionNo = 0;
	bool isUp = false;
	int keyCount = 0;

	//押された方向キーをチェック
	for (int i = 0; i < m_Keycords.size(); i++) {
		if (m_InputStatePtr->isKeyDown(m_Keycords[i])) {
			directionNo += i;
			if (i == 0)isUp = true;
			keyCount++;
		}
	}
	if (keyCount == 0) {
		for (int i = 0; i < 4; i++) {
			if (m_ContrStatePtr->isButtonDown((ePadCode)i, m_Property.ID)) {
				directionNo += i;
				if (i == 0)isUp = true;
				keyCount++;
			}
		}
	}

	//押されてない場合
	if (keyCount == 0) {
		directionNo = (int)eDirectionP::NONE;
	}
	//押されたキーは1つの場合
	else if (keyCount == 1) {
		directionNo *= 2;
	}
	//左と上が一緒に押された場合
	else if (directionNo == 3 && isUp) {
		directionNo = (int)eDirectionP::LEFTUP;
	}
	if ((int)m_Property.Direction == directionNo) { return; }
	m_Property.DirectBefore = m_Property.Direction;
	m_Property.Direction = (eDirectionP)directionNo;
	if (m_Property.Direction == eDirectionP::NONE) { return; }
	m_Property.Motion.setRange(directionNo * 3, directionNo * 3 + 2);
}
