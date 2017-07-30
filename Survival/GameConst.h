#pragma once
#ifndef _GAMECONST_H_
#define _GAMECONST_H_

enum class eGameMode {
	SINGLE,
	MULTIPLAY,
	COOPERATE,
};

struct GameConst
{
	static int Winner;
	static eGameMode GameMode;

	static void setMode(eGameMode mode);
	static void setWinner(int winner);
};

#endif // !_GAMECONST_H_
