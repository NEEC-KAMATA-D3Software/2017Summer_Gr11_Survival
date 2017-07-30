#pragma once
#ifndef _METHORD_H_
#define _METHORD_H_

#include "Vector2.h"
#include "Parameter.h"
#include "GameObject.h"
#include <memory>

static class Methord{
public:
	//for内forのまとめ
	//static void MyForeach(Action<int, int> action, Vector2 xy) {
	//	for (int y = 0; y < xy.y; y++) {
	//		for (int x = 0; x < xy.x; x++) {
	//			action(x, y);
	//		}
	//	}
	//}

	//object当たり判定(所在pointと高さ判定)
	static bool Collition(std::shared_ptr<GameObject> objP_1, std::shared_ptr<GameObject> objP_2) {
		bool sameArea = objP_1->getProperty().CurrentPoint == objP_2->getProperty().CurrentPoint;
		bool sameHeight = abs(objP_1->getProperty().CurrentHeight - objP_2->getProperty().CurrentHeight) <= 20;
		return sameArea && sameHeight;
	}

	//object当たり判定(円の当たり判定)
	static bool CollitionCircle(std::shared_ptr<GameObject> objP_1, std::shared_ptr<GameObject> objP_2) {
		float distanceX = Float2::Length(objP_1->getProperty().BeforeP - objP_2->getProperty().BeforeP);
		float distanceY = abs(objP_1->getProperty().CurrentHeight - objP_2->getProperty().CurrentHeight);
		bool sameArea = distanceX < (objP_1->getProperty().CollitionRadius + objP_2->getProperty().CollitionRadius);
		bool sameHeight = distanceY <= 20;
		return sameArea && sameHeight;
	}




	//点の四角い内判定（外積法）--　正方形
	static bool IsInScale(Float2 position, Float2 leftBottom, Float2 scaleXY) {
		bool isIn1 = Vector2Cross(Float2(-scaleXY.X, 0), position - Float2(leftBottom.X + scaleXY.X, leftBottom.Y)) < 0;
		bool isIn2 = Vector2Cross(Float2(scaleXY.X, 0), position - Float2(leftBottom.X, leftBottom.Y + scaleXY.Y)) < 0;
		bool isIn3 = Vector2Cross(Float2(0, -scaleXY.Y), position - Float2(leftBottom.X + scaleXY.X, leftBottom.Y + scaleXY.Y)) < 0;
		bool isIn4 = Vector2Cross(Float2(0, scaleXY.Y), position - leftBottom) < 0;
		return isIn1 && isIn2 && isIn3 && isIn4;
	}


	//点の四角い内判定（外積法）--　任意形	--　未完成
	static bool IsInScale(Float2 _thisP, Float2 checkP1, Float2 checkP2, Float2 checkP3, Float2 checkP4) {
		bool isIn1 = Vector2Cross(_thisP - checkP1, checkP2 - checkP1) < 0;
		bool isIn2 = Vector2Cross(_thisP - checkP2, checkP3 - checkP2) < 0;
		bool isIn3 = Vector2Cross(_thisP - checkP3, checkP4 - checkP3) < 0;
		bool isIn4 = Vector2Cross(_thisP - checkP4, checkP1 - checkP4) < 0;
		return isIn1 && isIn2 && isIn3 && isIn4;
	}

	//二次元外積
	static float Vector2Cross(Float2 v1, Float2 v2) {
		return v1.X * v2.Y - v1.Y * v2.X;
	}

	//二次元内積
	static float Vector2Dot(Float2 v1, Float2 v2) {
		return v1.X * v2.X + v1.Y * v2.Y;
	}

	//四捨五入(Map内位置調整)  ---- 未完成
	static Float2 NomalizePosition(Float2 position) {
		float x = position.X / Parameter::TileHeight;
		float y = position.Y / Parameter::TileHeight;

		//x = Mathf.Round(x) * Parameter::TileHeight;
		//y = Mathf.Round(y) * Parameter::TileHeight;

		return Float2(x, y);
	}


	//当たり判定用
	static void GetCorner(Float2& _startP, int _scale, Float2 corner[4]) {
		Float2 Scale = Float2(Parameter::HalfTileWidth, Parameter::HalfTileHeight) * _scale;

		Float2 check1 = _startP + Float2(Parameter::HalfTileWidth, 0);
		Float2 check2 = check1 + Scale;
		Float2 check3 = check2 + Float2(-Scale.X, Scale.Y);
		Float2 check4 = check3 - Scale;

		corner[0] = check1;
		corner[1] = check2;
		corner[2] = check3;
		corner[3] = check4;
	}

};

#endif // !_METHORD_H_
