#include "GameConst.h"

int GameConst::Winner = 0;
eGameMode GameConst::GameMode = eGameMode::SINGLE;

void GameConst::setMode(eGameMode mode) {
	GameMode = mode;
}

void GameConst::setWinner(int winner) {
	Winner = winner;
}

