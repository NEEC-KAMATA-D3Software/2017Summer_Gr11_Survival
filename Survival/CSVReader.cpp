#include "CSVReader.h"
#include <sstream>
#include <fstream>
#include <memory>
#include <DxLib.h>

StringList CSVReader::stringList = StringList();
IntList CSVReader::intList = IntList();

IntList CSVReader::ReadIntCSV(std::string name) {
	name = "CSV/" + name + ".csv";
	intList.clear();
	std::ifstream ifs(name);	//input file stream
	if (!ifs) {
		printfDx("Read Resource Fail\n");
	}
	std::string str;
	while (std::getline(ifs, str)) {
		std::string token;
		std::vector<int> ints;
		std::istringstream stream(str);
		while (std::getline(stream, token, ',')) {
			ints.push_back(atoi(token.c_str()));
		}
		intList.push_back(ints);
	}
	ifs.close();
	return intList;
}


StringList CSVReader::ReadStrIntCSV(std::string name, int offsetY) {
	name = "CSV/" + name + ".csv";
	stringList.clear();
	std::ifstream ifs(name);	//input file stream
	if (!ifs) {
		printfDx("Read GroupResource Fail\n");
	}
	std::string str;
	for (int i = 0; i < offsetY; i++) {
		std::getline(ifs, str);
	}

	while (std::getline(ifs, str)) {
		std::string token;
		std::vector<std::string> strings;
		std::istringstream stream(str);
		while (std::getline(stream, token, ',')) {
			strings.push_back(token);
		}
		stringList.push_back(strings);
	}
	ifs.close();
	return stringList;
}
