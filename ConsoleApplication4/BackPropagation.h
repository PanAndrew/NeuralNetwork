#pragma once
#include "Network.h"
#include "Neuron.h"
#include "HiddenNeuron.h"
#include "OutputNeuron.h"
#include "InputNeuron.h"

class Network;

class BackPropagation
{
private:
	std::vector<InputNeuron*> *inputLayer;
	std::vector<std::vector<HiddenNeuron*>> *hiddenLayer;
	std::vector<OutputNeuron*> *outputLayer;
	double momentum;

public:
	BackPropagation(Network* network, double momentum);
	virtual ~BackPropagation();

	void errorOutput();
	void errorHidden();
	void weightCorrection();
};

