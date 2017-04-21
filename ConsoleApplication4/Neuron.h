#pragma once

class Network;

class Neuron
{
protected:
	double outputValue;

public:
	Neuron();
	virtual ~Neuron();

	double getOutputValue();

};

