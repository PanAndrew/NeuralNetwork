#pragma once
#include "Neuron.h"

class Network;

class OutputNeuron :
	public Neuron
{
private:
	std::vector<double> inputValues;
	std::vector<double> weights;
	double errorValue;
	double stepValue;
	double betaValue;
	double weightedSum;
	std::vector<double> lastDeltaValues;

public:
	OutputNeuron(double stepvalue, double betavalue, int numberOfPrevLayer);
	virtual ~OutputNeuron();

	void setInputValue(int it, double value);
	std::vector<double> getInputValues();
	void setOutputValue();

	double getErrorValue();
	void setErrorValue(double errorValue);

	double getStepValue();

	void setWeight(int it, double newWeight);
	std::vector<double> getWeights();

	double activationFunction();

	double derivativeActiFunc();

	double weightGenerator();

	void setWeightedSum();

	double getWeightedSum();

	std::vector<double> getLastDeltaValues();
	void setLastDeltaValues(int i, double value);
};

