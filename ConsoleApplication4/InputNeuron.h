#pragma once
#include "Neuron.h"
class InputNeuron :
	public Neuron
{
public:
	InputNeuron();
	virtual ~InputNeuron();

	void setOutputValue(double outputvalue);
};