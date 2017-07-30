#include<functional>

#include "Parameter.h"
#include "GameRunner.h"
#include "GameDevice.h"
#include "InputState.h"
#include "Controller.h"
#include "Loading.h"
#include "Title.h"
#include "GamePlay.h"
#include "YouWin.h"
#include "YouLose.h"
#include "DxLib.h"

GameRunner::GameRunner() :
	endFlag(false), 
	sceneManager(SceneManager()),
	gameDevicePtr(new GameDevice())
{ }

GameRunner::~GameRunner() {
}

void GameRunner::run() {
	initialize();
	//std::shared_ptr<Loading> load = std::make_shared<Loading>(&gameDevice);
	//std::shared_ptr<Loading> load2 = load;//OK
	//std::unique_ptr<Loading> l = std::make_unique<Loading>(&gameDevice);
	//std::unique_ptr<Loading> l2 = std::move(l);//移譲
	//
	////動的配列確保
	//std::unique_ptr<int[]> arrayInt= std::make_unique<int[]>(5);
	//
	////ポインタ取得
	//Loading* pLoading = load.get();//しぇーあど
	//Loading* pLoading2 = l.get();//ユニーク

	////ユニークから配列アクセス
	//int a = arrayInt.get()[0];

	////シェアードポインタの相棒
	////弱参照　laodがdeleteされているか確かめられる
	//std::weak_ptr<Loading> weakL = load;
	//weakL.expired(); // true 不正なポインタ false 有効なポインタ
	//
	////例
	//if (!weakL.expired()) {
	//	//look関数で他のスレッドから守る
	//	weakL.lock()->IsEnd();
	//}

	////関数ポインタ
	//std::function<void()> action = []() {
	//	int a = 0;
	//};

	////関数として使える
	//action();
	////動作を入れ替えられる
	//action = []() {
	//	int a = 10;
	//};

	sceneManager.addScene(eScene::LOADING, new Loading(gameDevicePtr));
	sceneManager.addScene(eScene::TITLE, new Title(gameDevicePtr));
	sceneManager.addScene(eScene::GAMEPLAY, new GamePlay(gameDevicePtr));
	sceneManager.addScene(eScene::YOUWIN, new YouWin(gameDevicePtr));
	sceneManager.addScene(eScene::YOULOSE, new YouLose(gameDevicePtr));

	sceneManager.changeScene(eScene::LOADING);

	while (!isEnd()) {
		ScreenFlip();
		update();
		draw();
		//drawDebug();	//singleモード適用
	}
	finalize();
}

void GameRunner::initialize() {
	ChangeWindowMode(TRUE);
	SetGraphMode(Parameter::ScreenWidth, Parameter::ScreenHeight, 32);
	SetMainWindowText("SurvivalGame");

	DxLib_Init();

	sceneManager.initialize();
}

void GameRunner::update() {
	gameDevicePtr->update();
	sceneManager.update();
}

void GameRunner::draw() {
	ClearDrawScreen();
	sceneManager.draw();
}

void GameRunner::drawDebug() {
	sceneManager.drawDebug();
}

void GameRunner::finalize() {
	DxLib_End();
}

bool GameRunner::isEnd() {
	if (gameDevicePtr->getInputState()->wasKeyDown(KEY_INPUT_ESCAPE)) {
		endFlag = true;
	}
	if (gameDevicePtr->getContrState()->isButtonDown(ePadCode::PAD_BACK, 1)) {
		endFlag = true;
	}
	
	return endFlag;
}