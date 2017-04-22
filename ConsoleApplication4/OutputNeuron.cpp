#include "stdafx.h"
#include "Network.h"
#include "OutputNeuron.h"


OutputNeuron::OutputNeuron(double stepvalue, double betavalue, int numberOfPrevLayer)
{
	this->betaValue = betavalue;
	this->stepValue = stepvalue;

	for (unsigned int i = 0; i < numberOfPrevLayer; i++)
	{
		weights.push_back(weightGenerator());
		inputValues.push_back(0);
		lastDeltaValues.push_back(0);
	}

	std::cout << "Utworzylem sie: wyjscie" << std::endl;
}


OutputNeuron::~OutputNeuron()
{
}

void OutputNeuron::setInputValue(int it, double value)
{
	this->inputValues.at(it) = value;
}

std::vector<double> OutputNeuron::getInputValues()
{
	return inputValues;
}

void OutputNeuron::setOutputValue()
{
	setWeightedSum();
	this->outputValue = activationFunction();
}

double OutputNeuron::getErrorValue()
{
	return this->errorValue;
}

void OutputNeuron::setErrorValue(double errorValue)
{
	this->errorValue = errorValue;
}

double OutputNeuron::getStepValue()
{
	return this->stepValue;
}

void OutputNeuron::setWeight(int it, double newWeight)
{
	this->weights.at(it) = newWeight;
}

std::vector<double> OutputNeuron::getWeights()
{
	return this->weights;
}

double OutputNeuron::activationFunction()
{
	double result = 0.0;
	result = 1.0 /( 1.0 + exp((-1.0*(this->betaValue))*(this->weightedSum)));
	return result;
}

double OutputNeuron::derivativeActiFunc()
{
	if (betaValue == 1.0)
	{
		return activationFunction()*(1.0 - activationFunction());
	}
	else
	{
		double ebs = exp(betaValue*weightedSum);
		return (betaValue*ebs) / (pow((ebs + 1.0), 2.0));
	}
}

double OutputNeuron::weightGenerator()
{
	double value = 0;
	do
	{
		value = (((double(rand()) / double(RAND_MAX)) * (0.5 + 0.5)) - 0.5);
	} while (value == 0);
	return value;
}

void OutputNeuron::setWeightedSum()
{
	double result = 0;
	for (int i = 0; i < inputValues.size(); i++)
	{
		result += inputValues.at(i) * weights.at(i);
	}
	this->weightedSum = result;
}

double OutputNeuron::getWeightedSum()
{
	return this->weightedSum;
}

std::vector<double> OutputNeuron::getLastDeltaValues()
{
	return this->lastDeltaValues;
}

void OutputNeuron::setLastDeltaValues(int i, double value)
{
	this->lastDeltaValues.at(i) = value;
}