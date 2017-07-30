#pragma once
#ifndef _STAGEMANAGER_H_
#define _STAGEMANAGER_H_

#include "CSVReader.h"

struct StageManager {
	static void initialize(int stageNo);
	static IntList& getFloor(int level);
	static void clear();

	static IntList m_MapData0;
	static IntList m_MapData1;
	static IntList m_MapData2;
	static IntList m_MapData3;
	static IntList m_MapData4;
	static int MaxX;
	static int MaxY;
};

#endif // !_STAGEMANAGER_H_
