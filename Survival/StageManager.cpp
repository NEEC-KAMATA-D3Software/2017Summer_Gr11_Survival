#include "StageManager.h"

IntList StageManager::m_MapData0 = IntList();
IntList StageManager::m_MapData1 = IntList();
IntList StageManager::m_MapData2 = IntList();
IntList StageManager::m_MapData3 = IntList();
IntList StageManager::m_MapData4 = IntList();
int StageManager::MaxX = 0;
int StageManager::MaxY = 0;

void StageManager::initialize(int stageNo) {
	m_MapData0 = CSVReader::ReadIntCSV("floor" + std::to_string(stageNo) + "_" + std::to_string(0));
	m_MapData1 = CSVReader::ReadIntCSV("floor" + std::to_string(stageNo) + "_" + std::to_string(1));
	m_MapData2 = CSVReader::ReadIntCSV("floor" + std::to_string(stageNo) + "_" + std::to_string(2));
	m_MapData3 = CSVReader::ReadIntCSV("floor" + std::to_string(stageNo) + "_" + std::to_string(3));
	m_MapData4 = CSVReader::ReadIntCSV("floor" + std::to_string(stageNo) + "_" + std::to_string(4));
	MaxX = m_MapData0[0].size();
	MaxY = m_MapData0.size();
}

IntList& StageManager::getFloor(int level) {
	switch (level){
		case 0: return m_MapData0; break;
		case 1: return m_MapData1; break;
		case 2: return m_MapData2; break;
		case 3: return m_MapData3; break;
		case 4: return m_MapData4; break;
		default: 
			return m_MapData4;
			break;
	}
}

void StageManager::clear() {
	m_MapData0.clear();
	m_MapData1.clear();
	m_MapData2.clear();
	m_MapData3.clear();
}
