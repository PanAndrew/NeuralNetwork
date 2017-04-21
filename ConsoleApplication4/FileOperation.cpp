#include "stdafx.h"
#include "FileOperation.h"


FileOperation::FileOperation()
{
	noOfIter = 4;
}


FileOperation::~FileOperation()
{
}

void FileOperation::loadFile(std::string file)
{
	std::ifstream inputFile(file);
	std::string buffor;

	if (inputFile.good())
	{
		while (std::getline(inputFile, buffor))
		{
			std::istringstream inputStream(buffor);
			std::vector<double> row((std::istream_iterator<double>(inputStream)), std::istream_iterator<double>());
			this->vectors.push_back(row);
		}
	}
	else
		std::cout << "Nie udalo sie odczytac pliku" << std::endl;
}

std::vector<std::vector<double>> FileOperation::getVectors()
{
	return this->vectors;
}

std::vector<double> FileOperation::getRandedRow()
{
	if (rowNumbers.size() == 0) randNumbers();
	int i = rowNumbers.back();
	rowNumbers.pop_back();
	return this->vectors.at(i);
}

std::vector<double> FileOperation::getSpecifiedRow(int row)
{
	return this->vectors.at(row);
}

void FileOperation::printVectors()
{
	for (auto it = vectors.begin(); it != vectors.end(); it++)
	{
		for (auto iter = it->begin(); iter != it->end() ; iter++)
		{
			std::cout << *iter;
		}
		std::cout << std::endl;
	}
}

void FileOperation::printRandedRow()
{
	srand(time(NULL));
	int randomLine = rand() % this->vectors.size();
	
	for (auto it = vectors.at(randomLine).begin(); it != vectors.at(randomLine).end(); it++)
	{
		std::cout << *it;
	}
}

void FileOperation::printSpecifiedRow(int row)
{
	for (auto it = vectors.at(row).begin(); it != vectors.at(row).end(); it++)
	{
		std::cout << *it;
	}
}

void FileOperation::randNumbers()
{
	std::vector<int> tempNumbers;
	for (int i = 0; i < vectors.size(); i++)
	{
		tempNumbers.push_back(i);
	}
	for (int i = 0; i < noOfIter; i++)
	{
		int temp = rand() % tempNumbers.size();
		rowNumbers.push_back(tempNumbers.at(temp));
		tempNumbers.erase(tempNumbers.begin() + temp);
	}
}