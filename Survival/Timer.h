#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

class Timer{
public:
	Timer();
	Timer(const float& second);
	~Timer();

	void SetLimit(const float& second);
	void Initialize();
	void Update();
	bool IsTime();
	float GetRate();

private:
	int limitTime;
	int currentTime;
};

#endif // !_TIMER_H_
