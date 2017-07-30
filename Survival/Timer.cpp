#include "Timer.h"
#include <DxLib.h>

Timer::Timer() 
	:limitTime(60),
	 currentTime(0)
{}

Timer::Timer(const float& second)
	:limitTime(second * 60),
	 currentTime(0.0f)
{
}

Timer::~Timer() {}

void Timer::SetLimit(const float& second) {
	limitTime = second * 60;
}

void Timer::Initialize() {
	currentTime = 0;
}

void Timer::Update() {
	currentTime++;
}

bool Timer::IsTime() {
	return currentTime >= limitTime;
}

float Timer::GetRate() {
	return (float)currentTime / (float)limitTime;
}