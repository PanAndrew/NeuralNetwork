#pragma once

class FileOperation
{
private:
	std::vector<std::vector<double>> vectors;
	//int randomLine;

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

};