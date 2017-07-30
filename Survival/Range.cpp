#include "Range.h"

Range::Range(bool _isLoop):
	Range(0, 0, _isLoop)
{ }

Range::Range(int _min, int _max, bool _isLoop):
	Range(_min, _max, Parameter::AnimSpeed, _isLoop)
{ }

Range::Range(int _min, int _max, float _timer, bool _isLoop) :
	m_Min(_min),
	m_Max(_max + 1),
	m_Cursor(m_Min),
	m_IsLoop(_isLoop),
	m_Timer(Timer(_timer))
{ }

Range::~Range() {}

void Range::initialize() {
	m_Cursor = m_Min;
}

int Range::getCursorTri() {
	if (m_Cursor == m_Max) { return m_Cursor - 2; }
	return m_Cursor;
}

int Range::getCursor() {
	return m_Cursor;
}

void Range::setLoop(bool _isLoop) {
	m_IsLoop = _isLoop;
}

void Range::setRange(int _min, int _max) {
	m_Min = _min;
	m_Max = _max + 1;
	m_Cursor = m_Min;
}

void Range::setTimer(const float& second) {
	m_Timer.SetLimit(second);
}

void Range::warp() {
	if (m_Cursor > m_Max) {
		m_Cursor = m_Min;
	}
}

void Range::clamp() {
	if (m_Cursor > m_Max) {
		m_Cursor = m_Max;
	}
}

void Range::update() {
	m_Timer.Update();
	if (m_Timer.IsTime()) {
		m_Timer.Initialize();
		m_Cursor++;
		if (m_IsLoop) {
			warp();
		}else {
			clamp();
		}
	}
}

bool Range::IsLast() {
	return 	m_Cursor >= m_Max;
}