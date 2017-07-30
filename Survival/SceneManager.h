#pragma once
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include <unordered_map>
#include "IScene.h"

class SceneManager {
public:
	SceneManager();
	~SceneManager();

	void addScene(eScene sceneType, IScene* scene);
	void initialize();
	void update();
	void draw();
	void drawDebug();

	void changeScene(eScene next);

private:
	//sharedPtr�ɕύX
	std::unordered_map<eScene, IScene*> scenes;
	eScene nowScene;
	bool m_IsFade;
	int m_FadeImg;
	int m_FadeX;
};

#endif // !_SCENEMANAGER_H_
