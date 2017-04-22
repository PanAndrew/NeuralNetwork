#pragma once
#include "Neuron.h"
#include "InputNeuron.h"
#include "HiddenNeuron.h"
#include "OutputNeuron.h"
#include "Bias.h"
#include "BackPropagation.h"
#include "FileOperation.h"

class Neuron;

class InputNeuron;
class HiddenNeuron;
class OutputNeuron;
class Bias;
class BackPropagation;
class FileOperation;

class Network
{
private:
	std::vector<InputNeuron*> inputLayer;
	std::vector<std::vector<HiddenNeuron*>> hiddenLayer;
	std::vector<OutputNeuron*> outputLayer;

	int row;
	bool bias;
	int epochCounter;
	int iterationCounter;
	double iterationsMediumSquareError;
	std::vector<double> epochMediumSquareError;

	//void addBias(std::vector<int> anatomy);
	void createNetworkStructure(std::vector<int> anatomy, bool bias, double stepValue, double betaValue);

	BackPropagation *backprop;
	FileOperation *file;

public:
	Network(std::vector<int> anatomy, bool bias, double momentum, double stepValue, double betaValue, int iterationsPerEpoch);
	virtual ~Network();

	std::vector<InputNeuron*> *getInputLayer();
	std::vector<std::vector<HiddenNeuron*>> *getHiddenLayer();
	std::vector<OutputNeuron*> *getOutputLayer();

	FileOperation *getFile();
	BackPropagation *getBackPropagation();

	void loadInputValues();

	void forwardPropagation();

	void backPropagation();

	void printOutputs();

	void printInputs();

	void printHiddenInputs();

	void epochsAndMidSquareError();

	void mediumSquareError();

	std::vector<double> getVectorOfMediumSquareError();

	double getMediumSquareError();

	void displayInfo();

	int getEpochCounter();

	std::vector<std::vector<double>> test;

	void printInfoAboutNeurons();

	void printMSEToFile();
};

