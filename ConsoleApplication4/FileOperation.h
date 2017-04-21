#pragma once

class FileOperation
{
private:
	int noOfIter; // number of iterations
	std::vector<std::vector<double>> vectors;
	//int randomLine;
	std::vector<int> rowNumbers;

public:
	FileOperation();
	virtual ~FileOperation();

	void loadFile(std::string file);

	std::vector<std::vector<double>> getVectors();
	std::vector<double> getRandedRow();
	std::vector<double> getSpecifiedRow(int row);

	void printVectors();
	void printRandedRow();
	void printSpecifiedRow(int row);

	void randNumbers();
};