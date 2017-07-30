#include "ResourceManager.h"
#include "CSVReader.h"
#include <DxLib.h>

#pragma warning(disable : 4996)  

std::unique_ptr< ResourceManager> ResourceManager:: mInstance
			= std::unique_ptr< ResourceManager>(new ResourceManager());

ResourceManager::ResourceManager(){}

ResourceManager::~ResourceManager() {

}

ResourceManager* ResourceManager::getInstance(){
	return mInstance.get();
}

void ResourceManager::loadImage(const std::string& name){
	Images[name] = LoadGraph(name.c_str(), TRUE);
}

void ResourceManager::loadGroupData() {
	LoadDivGraph("Image/mapData.png", Parameter::MapDataCount, Parameter::MapDataMaxCol, Parameter::MapDataMaxRow, Parameter::TileSize, Parameter::TileSize, &mapData[0]);

	StringList test = CSVReader::ReadStrIntCSV("GroupImgs", 1);
	for (int i = 0; i < test.size(); i++) {
		int allNum = atoi(test[i][1].c_str());
		int XNum   = atoi(test[i][2].c_str());
		int YNum   = atoi(test[i][3].c_str());
		int XSize  = atoi(test[i][4].c_str());
		int YSize  = atoi(test[i][5].c_str());

		GroupImgs[test[i][0]] = std::make_unique<int[]>(atoi(test[i][1].c_str()));
		std::string address = "Image/" + test[i][0] + ".png";
		
		LoadDivGraph(address.c_str(), allNum, XNum, YNum, XSize, YSize, &GroupImgs[test[i][0]][0]);
	}
}

int ResourceManager::getImage(const std::string& name){
	return Images["Image/" + name + ".png"];
}

int ResourceManager::getGroupImg(const std::string& name, int num) {
	return GroupImgs[name][num];
}

int ResourceManager::getMapImage(const int num) {
	return mapData[num];
}

void ResourceManager::clear() {
	Images.clear();
}