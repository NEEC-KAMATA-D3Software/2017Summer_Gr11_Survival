#pragma once
#ifndef _RANGE_H_
#define _RANGE_H_

#include "Timer.h"
#include "Parameter.h"

class Range {
public:
	Range(bool _isLoop = true);
	Range(int _min, int _max, bool _isLoop = true);
	Range::Range(int _min, int _max, float _timer, bool _isLoop);
	~Range();

	void initialize();
	void setLoop(bool _isLoop);
	void setRange(int _min, int _max);
	void setTimer(const float& second);
	int getCursorTri();
	int getCursor();
	void update();
	bool IsLast();

private:
	void warp();
	void clamp();

private:
	int m_Min;
	int m_Max;
	int m_Cursor;
	bool m_IsLoop;
	Timer m_Timer;
};

#endif // !_RANGE_H_
