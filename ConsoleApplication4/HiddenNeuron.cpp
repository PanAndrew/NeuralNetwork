#include "stdafx.h"
#include "Network.h"
#include "HiddenNeuron.h"


HiddenNeuron::HiddenNeuron(double stepvalue, double betavalue, int numberOfPrevLayer)
{
	this->betaValue = betavalue;
	this->stepValue = stepvalue;

	for (unsigned int i = 0; i < numberOfPrevLayer; i++)
	{
		weights.push_back(weightGenerator());
		inputValues.push_back(0);
		lastDeltaValues.push_back(0);
	}

	std::cout << "Utworzylem sie: ukryty" << std::endl;
}


HiddenNeuron::~HiddenNeuron()
{
}

void HiddenNeuron::setInputValue(int it, double value)
{
	this->inputValues.at(it) = value;
}

std::vector<double> HiddenNeuron::getInputValues()
{
	return inputValues;
}

void HiddenNeuron::setOutputValue()
{
	setWeightedSum();
	this->outputValue = activationFunction();
}

double HiddenNeuron::getErrorValue()
{
	return this->errorValue;
}

void HiddenNeuron::setErrorValue(double errorValue)
{
	this->errorValue = errorValue;
}

double HiddenNeuron::getStepValue()
{
	return this->stepValue;
}

void HiddenNeuron::setWeight(int it, double newWeight)
{
	this->weights.at(it) = newWeight;
}

std::vector<double> HiddenNeuron::getWeights()
{
	return this->weights;
}

double HiddenNeuron::activationFunction()
{
	double result = 0.0;
	result = 1.0 /( 1.0 + exp((-1.0*(this->betaValue))*this->weightedSum));
	return result; //result
}

double HiddenNeuron::derivativeActiFunc()
{
	if (betaValue == 1.0)
	{
		return activationFunction()*(1.0 - activationFunction()); //activationFunction()*(1.0 - activationFunction())
	}
	else
	{
		double ebs = exp(betaValue*weightedSum);
		return (betaValue*ebs) / (pow((ebs + 1.0), 2.0));
	}
}

double HiddenNeuron::weightGenerator()
{
	double value=0;
	do
	{
		value = (((double(rand()) / double(RAND_MAX)) * (0.5 + 0.5)) - 0.5);
	} while (value == 0);
	return value;
}

void HiddenNeuron::setWeightedSum()
{
	double result = 0;
	for (int i = 0; i < inputValues.size(); i++)
	{
		result += inputValues.at(i) * weights.at(i);
	}
	this->weightedSum = result;
}

double HiddenNeuron::getWeightedSum()
{
	return this->weightedSum;
}

std::vector<double> HiddenNeuron::getLastDeltaValues()
{
	return this->lastDeltaValues;
}

void HiddenNeuron::setLastDeltaValues(int i, double value)
{
	this->lastDeltaValues.at(i) = value;
}