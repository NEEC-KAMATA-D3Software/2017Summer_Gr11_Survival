#include "GameRunner.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	GameRunner game;
	game.run();
	return 0;
}