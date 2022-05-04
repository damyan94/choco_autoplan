#ifndef READWRITEFILE_H_
#define READWRITEFILE_H_

//C & C++ system includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Own includes

//Forward declarations

enum WriteMode
{
	OUT,
	APP
};

class ReadWriteFile
{
public:
	ReadWriteFile() = delete;
	~ReadWriteFile() = default;

	static int32_t readFromFile(const std::string& fileName, std::vector<std::string>& readStrings);
	static int32_t writeToFile(const std::string& fileName, const std::string& writeString, WriteMode writeMode);
};

#endif //!READWRITEFILE_H_