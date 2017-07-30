#pragma once
#ifndef _INPUTSTATE_H_
#define _INPUTSTATE_H_

class InputState {
public:
	InputState();
	~InputState();

	void updateKey();
	bool wasKeyDown(int keycode);
	bool wasKeyUp(int keycode);
	bool isKeyDown(int keycode);


private:
	char m_Currentkeys[256];
	char m_Previouskeys[256];
};
#endif // !_INPUTSTATE_H_

