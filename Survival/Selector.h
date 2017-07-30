#pragma once
#ifndef _SELECTOR_H_
#define _SELECTOR_H_

#include <memory>

class GameDevice;
class InputState;
class Controller;

class Selector {
public:
	Selector(std::shared_ptr<GameDevice> _device, int _count, bool _isLoop = true);
	~Selector();

	void update();
	void initialize();

	void setCount(int _max);

	bool isSelected();
	int getSelection();

private:
	void warp();
	void clamp();
	void next();
	void forward();


private:
	std::shared_ptr<InputState> m_InputStatePtr;
	std::shared_ptr<Controller> m_ContrStatePtr;
	bool m_IsSelected;
	bool m_IsLoop;
	int m_SelecteNum;
	int m_selectCount;
};

#endif // !_SELECTOR_H_
