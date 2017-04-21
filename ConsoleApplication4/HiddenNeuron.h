#pragma once
#include "Neuron.h"

class Network;

class HiddenNeuron :
	public Neuron
{
private:
	std::vector<double> inputValues;
	std::vector<double> weights;
	double errorValue;
	double stepValue;
	double betaValue;
	double weightedSum;

public:
	HiddenNeuron(double stepvalue, double betavalue, int numberOfPrevLayer);
	virtual ~HiddenNeuron();

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
};

