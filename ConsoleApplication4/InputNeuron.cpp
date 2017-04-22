#include "stdafx.h"
#include "InputNeuron.h"

InputNeuron::InputNeuron()
{
	std::cout << "Utworzylem sie: wejscie" << std::endl;
}

InputNeuron::~InputNeuron()
{
}

void InputNeuron::setOutputValue(double outputvalue)
{
	this->outputValue = outputvalue;
}