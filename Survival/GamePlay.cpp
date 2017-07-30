#include "GamePlay.h"

#include "ResourceManager.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "GameConst.h"

#include "GameDevice.h"
#include "InputState.h"

#include "Vector2.h"
#include "DxLib.h"

#include "Player.h"

GamePlay::GamePlay(std::shared_ptr<GameDevice> gameDevicePtr) :
	m_EndFlag(false),
	m_StageNo(1),
	m_Next(eScene::TITLE),
	m_ObjectManagerPtr(new ObjectManager()),
	m_GameDevicePtr(gameDevicePtr),
	m_InputStatePtr(gameDevicePtr->getInputState())
{ }

GamePlay::~GamePlay() {
	m_ObjectManagerPtr->~ObjectManager();
}

void GamePlay::initialize() {
	m_GamePlayHandle = ResourceManager::getInstance()->getImage("gameplay");
	m_EndFlag = false;
	StageManager::clear();
	StageManager::initialize(1);
	PlayMusic("Sound/BackBGM1.mid", DX_PLAYTYPE_LOOP);
	m_ObjectManagerPtr->clearObjects();
	m_ObjectManagerPtr->addObject(std::make_shared<Player>(m_GameDevicePtr, m_ObjectManagerPtr, 1));
	if (GameConst::GameMode != eGameMode::SINGLE) {
		m_ObjectManagerPtr->addObject(std::make_shared<Player>(m_GameDevicePtr, m_ObjectManagerPtr, 2));
	}
	m_ObjectManagerPtr->initialize();
	GameConst::setWinner(0);
}

void GamePlay::update() {
	m_EndFlag = m_InputStatePtr->wasKeyDown(KEY_INPUT_RETURN);
	m_ObjectManagerPtr->update();

	int currentPlayer = m_ObjectManagerPtr->getPlayerCount();
	if (currentPlayer == 0) { 
		m_Next = eScene::YOULOSE; 
		m_EndFlag = true;
	}
	else if (currentPlayer == 1 && GameConst::GameMode != eGameMode::SINGLE) {
		m_Next = eScene::YOUWIN; 
		GameConst::setWinner(m_ObjectManagerPtr->getPlayerID());
		m_EndFlag = true;
	}
}

void GamePlay::draw() {
	DrawGraph(280, 20, m_GamePlayHandle, TRUE);
	drawMap();	
}

void GamePlay::drawMap() {
	for (int i = 0; i < Parameter::MaxFloor; i++) {
		drawFloor(i);
	}
}

void GamePlay::drawFloor(int floorNo) {
	Float2 halfTile = Parameter::HalfTile;
	Float2 screenCenter = Parameter::ScreenCenter;
	IntList floorData = StageManager::getFloor(floorNo);
	float halfStageY = floorData.size() * Parameter::HalfTileHeight;
	

	Float2 offset = screenCenter - Float2(0, halfStageY + Parameter::LevelHeight * floorNo) - halfTile;

	for (int y = 0; y < floorData.size(); y++) {
		for (int x = 0; x < floorData[y].size(); x++) {
			Float2 position = Float2(x, y) * halfTile + Float2(0, x * halfTile.Y) + offset;
			int imgHandle = ResourceManager::getInstance()->getMapImage(floorData[y][x]);
			
			DrawGraph(position.X, position.Y, imgHandle, TRUE);
			m_ObjectManagerPtr->drawBody(x, y, floorNo - 1);
			m_ObjectManagerPtr->drawShadow(x, y, floorNo - 1);
		}
		offset.X -= Parameter::HalfTileWidth;
	}
}

void GamePlay::drawDebug() {
	m_ObjectManagerPtr->drawDebug();
}

eScene GamePlay::next() {

	return m_Next;
}

bool GamePlay::isEnd() {
	return m_EndFlag;
}