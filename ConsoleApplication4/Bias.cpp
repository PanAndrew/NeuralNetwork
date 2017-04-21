#include "stdafx.h"
#include "Bias.h"
#include "Network.h"


Bias::Bias()
{
	this->outputValue = 1;

	std::cout << "Utworzylem sie: BIAS" << std::endl;
}

Bias::~Bias()
{
}

void Bias::setOutputValue(double outputvalue)
{
	this->outputValue = outputValue;
}

double Bias::getOutputValue()
{
	return this->outputValue;
}
