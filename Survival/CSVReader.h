#pragma once
#ifndef _CSVREADER_H_
#define _CSVREADER_H_

#include <string>
#include <vector>

using StringList =  std::vector<std::vector<std::string>>;
using IntList = std::vector<std::vector<int>>;

struct CSVReader{
	static StringList ReadStrIntCSV(std::string name, int offsetY = 0);
	static IntList ReadIntCSV(std::string name);
	static StringList stringList;
	static IntList intList;
};

#endif // !_CSVREADER_H_
