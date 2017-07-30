#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

#include "IScene.h"
#include "Timer.h"
#include <memory>

class GameDevice;
class InputState;
class Controller;
class Selector;

class Title : public IScene {
public:
	Title(std::shared_ptr<GameDevice> gameDevicePtr);
	~Title();

	virtual void initialize()override;
	virtual void update()override;
	virtual void draw()override;
	virtual void drawDebug()override;

	virtual bool isEnd()override;
	virtual eScene next()override;

private:
	int m_TitleImg;
	int m_SingleImg;
	int m_MultyPlayImg;
	int m_CooperateImg;
	int m_MaskImg;

	bool m_IsVisual;
	Timer m_Timer;
	std::vector<int> m_Selection;

	bool m_EndFlag;
	std::shared_ptr<InputState> m_InputStatePtr;
	std::shared_ptr<Controller> m_ContrStatePtr;
	std::shared_ptr<Selector> m_SelectManagerPtr;
};

#endif // !_TITLE_H_
