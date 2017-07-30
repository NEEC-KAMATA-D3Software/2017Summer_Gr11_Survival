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
	//std::unique_ptr<Loading> l2 = std::move(l);//�ڏ�
	//
	////���I�z��m��
	//std::unique_ptr<int[]> arrayInt= std::make_unique<int[]>(5);
	//
	////�|�C���^�擾
	//Loading* pLoading = load.get();//�����[����
	//Loading* pLoading2 = l.get();//���j�[�N

	////���j�[�N����z��A�N�Z�X
	//int a = arrayInt.get()[0];

	////�V�F�A�[�h�|�C���^�̑��_
	////��Q�Ɓ@laod��delete����Ă��邩�m���߂���
	//std::weak_ptr<Loading> weakL = load;
	//weakL.expired(); // true �s���ȃ|�C���^ false �L���ȃ|�C���^
	//
	////��
	//if (!weakL.expired()) {
	//	//look�֐��ő��̃X���b�h������
	//	weakL.lock()->IsEnd();
	//}

	////�֐��|�C���^
	//std::function<void()> action = []() {
	//	int a = 0;
	//};

	////�֐��Ƃ��Ďg����
	//action();
	////��������ւ�����
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
		//drawDebug();	//single���[�h�K�p
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