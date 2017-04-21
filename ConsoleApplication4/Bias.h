#pragma once
#include "Neuron.h"

class Network;

class Bias :
	public Neuron
{
public:
	Bias();
	virtual ~Bias();

	virtual void setOutputValue(double outputvalue);
	virtual double getOutputValue();
};

