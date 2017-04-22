#include "stdafx.h"
#include "Network.h"

Network::Network(std::vector<int> anatomy, bool bias, double momentum, double stepValue, double betaValue, int iterationsPerEpoch)
{
	this->bias = bias;
	createNetworkStructure(anatomy, bias, stepValue, betaValue);
	this->backprop = new BackPropagation(this, momentum);
	this->file = new FileOperation(iterationsPerEpoch);

	this->row = 0;

	epochCounter = 0;
	iterationCounter = 0;
	//epochMediumSquareError.push_back(1);

	///////////TESTY//////////////
	//WEJSCIA
	//inputLayer.at(0)->setOutputValue(1);
	//inputLayer.at(1)->setOutputValue(2);
	//inputLayer.at(2)->setOutputValue(3);
	//inputLayer.at(3)->setOutputValue(4);

	////WARSTWA UKRYTA
	//hiddenLayer.at(0).at(0)->setWeight(0,-2);
	//hiddenLayer.at(0).at(0)->setWeight(1, 1);
	//hiddenLayer.at(0).at(0)->setWeight(2, 3);
	//hiddenLayer.at(0).at(0)->setWeight(3, -3);

	//hiddenLayer.at(0).at(1)->setWeight(0, 2);
	//hiddenLayer.at(0).at(1)->setWeight(1, 3);
	//hiddenLayer.at(0).at(1)->setWeight(2, -1);
	//hiddenLayer.at(0).at(1)->setWeight(3, -2);

	//hiddenLayer.at(0).at(2)->setWeight(0, -1);
	//hiddenLayer.at(0).at(2)->setWeight(1, -2);
	//hiddenLayer.at(0).at(2)->setWeight(2, 3);
	//hiddenLayer.at(0).at(2)->setWeight(3, -2);

	////WARSTWA WYJSCIOWA
	//outputLayer.at(0)->setWeight(0, -3);
	//outputLayer.at(0)->setWeight(1, -1);
	//outputLayer.at(0)->setWeight(2, 3);

	//outputLayer.at(1)->setWeight(0, -1);
	//outputLayer.at(1)->setWeight(1, 2);
	//outputLayer.at(1)->setWeight(2, 4);

	//outputLayer.at(2)->setWeight(0, 2);
	//outputLayer.at(2)->setWeight(1, 3);
	//outputLayer.at(2)->setWeight(2, -4);

	//outputLayer.at(3)->setWeight(0, -3);
	//outputLayer.at(3)->setWeight(1, 1);
	//outputLayer.at(3)->setWeight(2, 2);

	//if (bias == true)
		//addBias(anatomy);
}

Network::~Network()
{
}

std::vector<InputNeuron*> *Network::getInputLayer()
{
	return &(this->inputLayer);
}

std::vector<std::vector<HiddenNeuron*>> *Network::getHiddenLayer()
{
	return &(this->hiddenLayer);
}

std::vector<OutputNeuron*> *Network::getOutputLayer()
{
	return &(this->outputLayer);
}

void Network::createNetworkStructure(std::vector<int> anatomy, bool bias, double stepValue, double betaValue)
{
	for (int j = 0; j < *anatomy.begin(); j++)
	{
		InputNeuron* inputNeuron = new InputNeuron();
		inputLayer.push_back(inputNeuron);
	}

	for (auto it = anatomy.begin() + 1; it != anatomy.end() - 1; it++)
	{
		std::vector<HiddenNeuron*> layer;
		for (int i = 0; i < *it; i++)
		{
			HiddenNeuron *hiddenNeuron;
			if (it == anatomy.begin() + 1)
			{
				if(bias == true)
					hiddenNeuron = new HiddenNeuron(stepValue, betaValue, inputLayer.size()+1);
				else
					hiddenNeuron = new HiddenNeuron(stepValue, betaValue, inputLayer.size());
			}
			else
			{
				if(bias == true)
					hiddenNeuron = new HiddenNeuron(stepValue, betaValue, hiddenLayer.back().size() + 1);
				else
					hiddenNeuron = new HiddenNeuron(stepValue, betaValue, hiddenLayer.back().size());
			}

			layer.push_back(hiddenNeuron);
		}
		hiddenLayer.push_back(layer);
	}

	for (int k = 0; k < anatomy.back(); k++)
	{
		OutputNeuron *outputNeuron;
		if(bias == true)
			outputNeuron = new OutputNeuron(stepValue, betaValue, hiddenLayer.back().size()+1);
		else
			outputNeuron = new OutputNeuron(stepValue, betaValue, hiddenLayer.back().size());

		outputLayer.push_back(outputNeuron);
	}

}

//void Network::addBias(std::vector<int> anatomy)
//{
//	for (unsigned int i = 0; i<anatomy.size() - 1; i++)
//	{
//		Neuron *bias = new Bias(this);
//		network[i].push_back(bias);
//	}
//}

FileOperation *Network::getFile()
{
	return this->file;
}

BackPropagation *Network::getBackPropagation()
{
	return this->backprop;
}

void Network::loadInputValues()
{
	int i = 0;
	std::vector<double> value = file->getRandedRow();
	//test.push_back(value);
	//row++;
	//if (row > 3)
	//	row = 0;
	for (auto &it : inputLayer)
	{
		it->setOutputValue(value.at(i));
		i++;
	}
}

void Network::forwardPropagation()
{
	for (auto it = hiddenLayer.begin(); it != hiddenLayer.end(); it++)
	{
		for (auto iter = it->begin(); iter != it->end(); iter++) //Hidden neurons
		{
			if (it == hiddenLayer.begin())
			{
				for (auto iterator = inputLayer.begin(); iterator != inputLayer.end(); iterator++) // Input neurons
				{
					(*iter)->setInputValue(std::distance(inputLayer.begin(), iterator), (*iterator)->getOutputValue());
				}
			}
			else if(hiddenLayer.size() > 1)
			{
				for (auto iterator = (it-1)->begin(); iterator != (it-1)->end(); iterator++)
				{
					(*iter)->setInputValue(std::distance((it-1)->begin(), iterator), (*iterator)->getOutputValue());
				}
			}

			if (bias == true)
			{
				if(it==hiddenLayer.begin())
					(*iter)->setInputValue(inputLayer.size(), 1);
				else
					(*iter)->setInputValue((it - 1)->size(), 1);
			}


			(*iter)->setOutputValue();
		}
	}

	for (auto it = outputLayer.begin(); it != outputLayer.end(); it++) // Output neurons
	{
		for (auto iterator = hiddenLayer.back().begin(); iterator != hiddenLayer.back().end(); iterator++)
		{
			(*it)->setInputValue(std::distance(hiddenLayer.back().begin(), iterator), (*iterator)->getOutputValue());
		}

		if (bias == true)
		{
				(*it)->setInputValue(hiddenLayer.back().size(), 1);
		}

		(*it)->setOutputValue();
	}
}

void Network::backPropagation()
{
	backprop->errorOutput();
	backprop->errorHidden();
	backprop->weightCorrection();
}

void Network::printOutputs()
{
	for (auto it = outputLayer.begin(); it != outputLayer.end(); it++)
	{
		std::cout << (*it)->getOutputValue() << " ";
	}
}

void Network::printInputs()
{
	for (auto it = inputLayer.begin(); it != inputLayer.end(); it++)
	{
		std::cout << (*it)->getOutputValue() << " ";
	}
}

void Network::printHiddenInputs()
{
	for (auto &it : hiddenLayer.at(0))
	{
		std::cout << "Neuron ukryty ";
		for (int j = 0; j < it->getInputValues().size(); j++)
		{
			std::cout << it->getInputValues().at(j);
		}
		std::cout << std::endl;
	}
}

void Network::epochsAndMidSquareError()
{
	iterationCounter++;
	if (iterationCounter % file->getVectors().size() == 0 && iterationCounter != 0)
	{
		epochCounter++;
		double mse = iterationsMediumSquareError / file->getVectors().size();
		epochMediumSquareError.push_back(mse);
		iterationsMediumSquareError = 0;
	}

	mediumSquareError();
}

void Network::mediumSquareError()
{
	auto input_iter = inputLayer.begin();
	for (auto & it : outputLayer)
	{
		iterationsMediumSquareError += pow(((*input_iter)->getOutputValue() - it->getOutputValue()), 2) / outputLayer.size() ;
		input_iter++;
	}
}

std::vector<double> Network::getVectorOfMediumSquareError()
{
	return epochMediumSquareError;
}

double Network::getMediumSquareError()
{
	return epochMediumSquareError.back();
}


void Network::displayInfo()
{
	std::cout << "Liczba iteracji: " << iterationCounter << std::endl;
	std::cout << "Liczba epok: " << epochMediumSquareError.size() << std::endl;
	std::cout << "Ostatni blad sredniokwadratowy: " << epochMediumSquareError.back() << std::endl;
}

int Network::getEpochCounter()
{
	return epochCounter;
}

void Network::printInfoAboutNeurons()
{
	//Ukryta
	int i = 0;
	for (auto & it : hiddenLayer.at(0))
	{
		std::cout << "Neuron ukryty "<< i << " wagi: " << std::endl;
		for (auto &iter : it->getWeights())
			std::cout << iter << " ";

		std::cout << std::endl;
		std::cout << "Suma wazona: " <<it->getWeightedSum();
		std::cout << std::endl << std::endl;
		i++;
	}

	std::cout << std::endl << std::endl;

	i = 0;
	//Wyjsciowa
	for (auto &it : outputLayer)
	{
		std::cout << "Neuron wyjsciowy " << i << " wagi: " << std::endl;
		for (auto &iter : it->getWeights())
			std::cout << iter << " ";

		std::cout << std::endl;
		std::cout << "Suma wazona: " << it->getWeightedSum();
		std::cout << std::endl << std::endl;
		i++;
	}
}

void Network::printMSEToFile()
{
	std::vector<std::string> tempMSEVec;
	std::string temp;
	for (auto &it : epochMediumSquareError)
	{
		temp = std::to_string(it);
		std::replace(temp.begin(), temp.end(), '.', ',');
		tempMSEVec.push_back(temp);
	}

	std::ofstream outputFile("..\\mse.txt", std::ios::out);
	
	if (outputFile.good())
	{
		for (auto &it : tempMSEVec)
		{
			outputFile << it << std::endl;
		}
		outputFile.close();
	}
	else
		std::cout << "Nie udalo sie odczytac pliku" << std::endl;
}
