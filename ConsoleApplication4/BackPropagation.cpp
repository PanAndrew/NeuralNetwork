#include "stdafx.h"
#include "BackPropagation.h"



BackPropagation::BackPropagation(Network* network, double momentum)
{
	this->inputLayer = network->getInputLayer();
	this->hiddenLayer = network->getHiddenLayer();
	this->outputLayer = network->getOutputLayer();
	this->momentum = momentum;
}


BackPropagation::~BackPropagation()
{
}

void BackPropagation::errorOutput()
{
	auto input_it = inputLayer->begin();
	for (auto it = outputLayer->begin(); it != outputLayer->end(); it++)
	{
		double errorValue = (*it)->derivativeActiFunc() * ((*input_it)->getOutputValue() - (*it)->getOutputValue());
		
		input_it++;
		(*it)->setErrorValue(errorValue);
	}
}

void BackPropagation::errorHidden()
{
	int i;
	double errorValue;

	for (auto vector_it = hiddenLayer->end(); vector_it != hiddenLayer->begin(); vector_it--) //warstwa warstw
	{
		i = 0;
		for (auto it = (vector_it-1)->begin(); it != (vector_it-1)->end(); it++) // warstwa neuronow ukrytych
		{
			errorValue = 0.0;
			
			if ((*(vector_it-1)) == hiddenLayer->back())
			{
				for (auto iter = outputLayer->begin(); iter != outputLayer->end(); iter++) // warstwa wyjsciowa
				{
					double value = (*iter)->getWeights().at(i);
					errorValue += (*iter)->getErrorValue() * value;
				}
			}
			else if(hiddenLayer->size() > 1)
			{
				for (auto iter = (vector_it)->begin(); iter != (vector_it)->end(); iter++) //(vector_it + 1)->begin() //(vector_it + 1)->end() 
				{
					double value = (*iter)->getWeights().at(i);
					errorValue += (*iter)->getErrorValue() * value;
				}
			}
			
			errorValue *= (*it)->derivativeActiFunc();
			(*it)->setErrorValue(errorValue);
			i++;
		}
	}
}

void BackPropagation::weightCorrection()
{
	for (auto it = hiddenLayer->begin(); it != hiddenLayer->end(); it++)
	{
		for (auto iter = it->begin(); iter != it->end(); iter++)
		{
			for (unsigned int i = 0; i < (*iter)->getWeights().size(); i++)
			{
				double deltaValue = ((*iter)->getStepValue()*(*iter)->getErrorValue() * (*iter)->getInputValues().at(i));
				double newWeight = (*iter)->getWeights().at(i) + deltaValue;
				newWeight += momentum * (*iter)->getLastDeltaValues().at(i);
				(*iter)->setWeight(i, newWeight);
				(*iter)->setLastDeltaValues(i, deltaValue);
			}
		}
	}

	for (auto iter = outputLayer->begin(); iter != outputLayer->end(); iter++)
	{
		for (unsigned int i = 0; i < (*iter)->getWeights().size(); i++)
		{
			double deltaValue = ((*iter)->getStepValue()*(*iter)->getErrorValue() * (*iter)->getInputValues().at(i));
			double newWeight = (*iter)->getWeights().at(i) + deltaValue;
			newWeight += momentum * (*iter)->getLastDeltaValues().at(i);
			(*iter)->setWeight(i, newWeight);
			(*iter)->setLastDeltaValues(i, deltaValue);
		}
	}
}