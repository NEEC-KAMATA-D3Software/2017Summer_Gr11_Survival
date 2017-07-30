#pragma once
#ifndef _YOUWIN_H_
#define _YOUWIN_H_

#include <memory>
#include "IScene.h"
#include "Timer.h"

class GameDevice;
class InputState;
class Controller;
class Selector;

class YouWin : public IScene {
public:
	YouWin(std::shared_ptr<GameDevice> gameDevicePointer);
	~YouWin();

	virtual void initialize()override;
	virtual void update()override;
	virtual void draw()override;
	virtual void drawDebug()override;

	virtual bool isEnd()override;
	virtual eScene next()override;

private:
	bool m_EndFlag;
	int m_ImgHandle;
	int m_PromptHandle;

	bool m_IsVisual;
	Timer m_Timer;
	eScene nextScene;

	std::shared_ptr<InputState> m_InputStatePtr;
	std::shared_ptr<Controller> m_ContrStatePtr;
	std::shared_ptr<Selector> m_SelectManagerPtr;
};

#endif // !_YOUWIN_H_
