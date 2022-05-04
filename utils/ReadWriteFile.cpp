//Coresponding header
#include "../utils/ReadWriteFile.h"

//C & C++ system includes
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

//Own includes

int32_t ReadWriteFile::readFromFile(const std::string& fileName,
	std::vector<std::string>& readStrings)
{
	std::ifstream inStream(fileName, std::ios::in);
	if (!inStream.is_open())
	{
		std::cerr << "Error, unable to open file: " << fileName << std::endl;
		return EXIT_FAILURE;
	}

	std::string readLine;
	while (std::getline(inStream, readLine))
		if (readLine[0] != '#' || readLine.size() <= 0) //The '#' symbol will indicate a commented line in the input file
			readStrings.push_back(readLine);

	inStream.close();

	return EXIT_SUCCESS;
}

int32_t ReadWriteFile::writeToFile(const std::string& fileName,
	const std::string& writeString, WriteMode writeMode)
{
	std::ofstream outStream;

	if (writeMode == WriteMode::OUT)
		outStream.open(fileName, std::ios::out);

	else if (writeMode == WriteMode::APP)
		outStream.open(fileName, std::ios::app);

	if (!outStream.is_open())
	{
		std::cerr << "Error, unable to open file: " << fileName << std::endl;
		return EXIT_FAILURE;
	}

	outStream << writeString;

	outStream.close();

	return EXIT_SUCCESS;
}