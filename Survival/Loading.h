#pragma once
#ifndef _LOADING_H_
#define _LOADING_H_

#include <memory>
#include "ResourceLoader.h"
#include "IScene.h"
#include "Timer.h"
#include <string>

class GameDevice;
using StringList = std::vector<std::vector<std::string>>;

class Loading : public IScene {
public:
	Loading(std::shared_ptr<GameDevice> gameDevicePointer);
	~Loading();

	virtual void initialize()override;
	virtual void update()override;
	virtual void draw()override;
	virtual void drawDebug()override;

	virtual bool isEnd()override;
	virtual eScene next()override;

private:
	bool m_IsVisual;
	bool m_EndFlag;
	int m_LoadingHandle;
	Timer m_Timer;

	StringList list;
	ResourceLoader m_ResourceLoader;
};

#endif // !_LOADING_H_
