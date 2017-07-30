#include "SceneManager.h"
#include <assert.h>
#include "DxLib.h"
#include "Parameter.h"

typedef std::unordered_map<eScene, IScene*>::iterator SceneMapIter;
typedef std::unordered_map<eScene, IScene*> SceneMap;

SceneManager::SceneManager() :
	scenes(SceneMap()),
	nowScene(eScene::NONE),
	m_IsFade(false),
	m_FadeX(Parameter::ScreenWidth)
{ }

SceneManager::~SceneManager() {
	scenes.clear();
}

void SceneManager::addScene(eScene sceneType, IScene* scene) {
	//assert入れないと事故る
	assert(scenes.find(sceneType) == scenes.end() && "すでにキーが登録されています");
	//scenes.find(sceneType) はキーがあるか確かめるための関数
	//戻り値はイテレータ　もし見つからなければscenes.end()(最終イテレータ)が返ってくる
	scenes[sceneType] = scene;
}

void SceneManager::initialize() {
	if (nowScene == eScene::NONE) { return; }
	scenes[nowScene]->initialize();
}

void SceneManager::update() {
	if (m_IsFade) {
		if (m_FadeX == -Parameter::ScreenWidth) {
			changeScene(scenes[nowScene]->next());
		}
		else if (m_FadeX <= Parameter::ScreenWidth * -3) {
			m_IsFade = false;
			m_FadeX = Parameter::ScreenWidth;
			return;
		}
		m_FadeX -= 25;
		return;
	}
	if (nowScene == eScene::NONE) { return; }
	scenes[nowScene]->update();
	if (scenes[nowScene]->isEnd()) {
		if (scenes[nowScene]->next() == eScene::GAMEPLAY) {
			m_FadeImg = LoadGraph("Image/ReadyGo.png", TRUE);
		}
		else {
			m_FadeImg = LoadGraph("Image/FadeImg.png", TRUE);
		}
		m_IsFade = true;
	}
}

void SceneManager::draw() {
	if (nowScene == eScene::NONE) { return; }
	scenes[nowScene]->draw();

	DrawGraph(m_FadeX, 0, m_FadeImg, TRUE);
}

void SceneManager::drawDebug() {
	scenes[nowScene]->drawDebug();
}

void SceneManager::changeScene(eScene next) {
	//もしscenesにnextが登録されていなくてもあんおーだマップが
	//勝手になんか作っちゃうのでエラーがよくわからない
	assert(scenes.find(next) != scenes.end() && "キーが登録されていません");
	scenes[next]->initialize();
	nowScene = next;
}