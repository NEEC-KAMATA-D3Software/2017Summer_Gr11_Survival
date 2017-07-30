#pragma once
#ifndef _GAMERUNNER_H_
#define _GAMERUNNER_H_

#include <memory>
#include "SceneManager.h"

class GameDevice;

class GameRunner {
public:
	GameRunner();
	~GameRunner();

	void run();

private:
	void initialize();
	void update();
	void draw();
	void drawDebug();
	void finalize();
	bool isEnd();

private:
	bool endFlag;
	SceneManager sceneManager;
	std::shared_ptr<GameDevice> gameDevicePtr;
};

#endif // !_GAMERUNNER_H_
