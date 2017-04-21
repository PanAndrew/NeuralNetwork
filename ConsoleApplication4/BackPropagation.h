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

public:
	BackPropagation(Network* network);
	virtual ~BackPropagation();

	void errorOutput();
	void errorHidden();
	void weightCorrection();
};

