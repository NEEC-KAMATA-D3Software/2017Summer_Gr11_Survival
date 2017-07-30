#pragma once
#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include "Vector2.h"
#include <array>

struct Parameter {
	static const int ScreenWidth = 800;
	static const int ScreenHeight = 600;
	static const int MaxFloor = 5;

	static const int BeforeSize = 36;

	static const int TileSize = 64;
	static const int CharaSize = 56;

	static const int TileWidth = 64;
	static const int TileHeight = 32;
	static const int HalfTileWidth = 32;
	static const int HalfTileHeight = 16;

	static const int MapDataCount = 16;
	static const int MapDataMaxCol = 8;
	static const int MapDataMaxRow = 2;

	static const int PlayerImgMaxCol = 6;
	static const int PlayerImgMaxRow = 4;
	static const int PlayerImgCount = PlayerImgMaxCol * PlayerImgMaxRow;
	static const int PlayerJumpSpeed = 1;
	static const int PlayerJumpPower = 10;

	static const int CollitionRadius_Player = 15;	//‰æ‘œ”¼Œa + 1
	static const int CollitionRadius_Ball = 6;		//‰æ‘œ”¼Œa

	static const int LevelHeight = 32;

	static const float AnimSpeed;
	static const float PlayerMoveSpeed;
	static const float BallSpeed;

	static const Float2 ScreenCenter;
	static const Float2 HalfTile;


	static const std::array<Float2, 9> SquareVelocitys;
	static const std::array<Float2, 9> RhombVelocitys;
};

#endif // !_PARAMETER_H_
