#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <memory>
#include "StageManager.h"
#include "Vector2.h"
#include "Range.h"

class ObjectManager;

enum class eDirectionP {
	UP = 0,
	RIGHTUP,
	RIGHT,
	RIGHTDOWN,
	DOWN,
	LEFTDOWN,
	LEFT,
	LEFTUP,
	NONE,
};

enum class eTag {
	PLAYER,
	ENEMY,
	ITEM,
	NONE,
};

class GameObject {
public:
	struct Property {
		Float2 PositionC = Float2::Zero();	//描画座標
		Float2 VelocityC = Float2::Zero();	//実際の移動（描画用）

		Float2 BeforeP = Float2::Zero();		//クォータービュー変換前座標（当たり判定用・初期値）
		Float2 BeforeV = Float2::Zero();	//マップチップ移動（当たり判定用）

		eDirectionP Direction = eDirectionP::NONE;		//今の方向
		eDirectionP DirectBefore = eDirectionP::NONE;	//前の方向

		IntList CollitionMap;		//今あたり判定有効の階層のMapchip
		float CollitionRadius = 1;
		Range Motion = Range(0, 2);		//アニメーション登録用

		int CurrentLevel = 0;		//チャラの所在階層
		float CurrentHeight = 0;	//キャラの所在高さ

		int ShadowLevel = 0;	//影の所在階層
		int ShadowHeight = 0;	//影の所在高さ
		
		std::string ImgName = "";
		
		bool IsDead = false;
		int HP = 1;
		int Power = 1;

		Float2 CurrentPoint = Float2::Zero();	//所在位置のMapchip番号

		eTag Tag = eTag::NONE;
		int ID = 0;
	};

	GameObject() {}
	~GameObject() {}

	virtual void update() {
		m_Property.Motion.update();
		m_Property.CurrentPoint = getProperty().BeforeP / Parameter::BeforeSize;
		checkCollitionData();
		checkShadowHeight();
	}

	virtual void initialize() {
		m_Property.BeforeP = Float2::One();
		m_Property.BeforeV = Float2::Zero();
		m_Property.Direction = eDirectionP::NONE;
		m_Property.DirectBefore = eDirectionP::DOWN;
		m_Property.ShadowLevel = 0;
		m_Property.CurrentLevel = 0;
		m_Property.IsDead = false;
	}

	virtual void setImg(std::string _imgName) {
		m_Property.ImgName = _imgName;
	}

	virtual void Hit(std::shared_ptr<GameObject> other) {
		m_Property.HP -= other->getProperty().Power;
	}

	virtual void drawBody() {}
	virtual void drawShadow() {}
	virtual void drawDebug() {}

	Property& getProperty() {
		return m_Property;
	}

	void setObjectManager(std::shared_ptr<ObjectManager> objManagerPtr) {
		m_ObjectManager = objManagerPtr;
	}

	std::shared_ptr<ObjectManager> getObjectManager() {
		return m_ObjectManager;
	}

	//足元からradiusの当たり範囲
	virtual Float2 getNextPoint(float radius = 1) {
		Float2 point = (m_Property.BeforeP + m_Property.BeforeV + m_Property.BeforeV * radius) / Parameter::BeforeSize;
		return point;
	}

	virtual void checkCollitionData() {
		m_Property.CurrentLevel = m_Property.CurrentHeight / Parameter::LevelHeight;
		m_Property.CollitionMap = StageManager::getFloor(m_Property.CurrentLevel);
	}


protected:
	virtual void checkShadowHeight() {
		Float2 point = m_Property.CurrentPoint;
		for (int i = m_Property.CurrentLevel; i >= 0; i--) {
			if (StageManager::getFloor(i)[(int)point.Y][(int)point.X] != 0) {
				m_Property.ShadowHeight = i * Parameter::LevelHeight;
				m_Property.ShadowLevel = i;
				break;
			}
		}
	}

protected:
	GameObject::Property m_Property;
	std::shared_ptr<ObjectManager> m_ObjectManager;
};

#endif // !_GAMEOBJECT_H_
