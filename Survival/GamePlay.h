#pragma once
#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include <memory>
#include <array>
#include "IScene.h"

class GameDevice;
class InputState;
class ObjectManager;

class GamePlay : public IScene {
public:
	GamePlay(std::shared_ptr<GameDevice> gameDevicePtr);
	~GamePlay();

	virtual void initialize()override;
	virtual void update()override;
	virtual void draw()override;
	virtual void drawDebug()override;

	virtual bool isEnd()override;
	virtual eScene next()override;

private:
	void drawMap();
	void drawFloor(int floorNo);

private:
	bool m_EndFlag = false;
	int m_GamePlayHandle;
	int m_StageNo;
	eScene m_Next;
	std::shared_ptr<InputState> m_InputStatePtr;
	std::shared_ptr<GameDevice> m_GameDevicePtr;
	std::shared_ptr<ObjectManager> m_ObjectManagerPtr;
};

#endif // !_GAMEPLAY_H_
