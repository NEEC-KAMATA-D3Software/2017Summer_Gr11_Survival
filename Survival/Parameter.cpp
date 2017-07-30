#include "Parameter.h"
#include "Matrix2.h"


const float Parameter::AnimSpeed = 0.15f;
const float Parameter::PlayerMoveSpeed = 2.0f;
const float Parameter::BallSpeed = 9.0f;

const Float2 Parameter::ScreenCenter 
			= Float2(Parameter::ScreenWidth, Parameter::ScreenHeight) / 2;

const Float2 Parameter::HalfTile
			= Float2(Parameter::TileWidth, Parameter::TileHeight) / 2;

//eDirectionP順(8方向登録)
//描画タイルとあたり判定タイルのサイズの比を常数にした
const std::array<Float2, 9> Parameter::SquareVelocitys{
	Matrix2::Rotate(Float2::Up() , -atan(1)),
	Float2::Up(),
	Matrix2::Rotate(Float2::Right() * 0.8f, -atan(1)),
	Float2::Right(),
	Matrix2::Rotate(Float2::Down() , -atan(1)),
	Float2::Down(),
	Matrix2::Rotate(Float2::Left() * 0.8f, -atan(1)),
	Float2::Left(),
	Float2::Zero()
};
const std::array<Float2, 9> Parameter::RhombVelocitys{
	Float2::Up() * 0.6275f,
	Matrix2::Rotate(Float2::Up(), atan(2)),
	Float2::Right() * 0.8f * 1.2549f,
	Matrix2::Rotate(Float2::Right(), atan(0.5f)),
	Float2::Down() * 0.6275f,
	Matrix2::Rotate(Float2::Down(), atan(2)),
	Float2::Left() * 0.8f * 1.2549f,
	Matrix2::Rotate(Float2::Left(), atan(0.5f)),
	Float2::Zero()
};

