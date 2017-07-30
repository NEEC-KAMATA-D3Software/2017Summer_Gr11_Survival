#pragma once
#ifndef _YOULOSE_H_
#define _YOULOSE_H_

#include <memory>
#include "IScene.h"
#include "Timer.h"

class GameDevice;
class InputState;
class Controller;

class YouLose : public IScene {
public:
	YouLose(std::shared_ptr<GameDevice> gameDevicePointer);
	~YouLose();

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

	std::shared_ptr<InputState> m_InputStatePtr;
	std::shared_ptr<Controller> m_ContrStatePtr;
};

#endif // !_YOULOSE_H_
