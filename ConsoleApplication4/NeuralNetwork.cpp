//NeuralNetwork.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include "Network.h"

//#include "FileOperation.h"

int main()
{
	srand(time(NULL));

	std::vector<std::vector<int>> array;
	std::vector<int> col;

	//////////TESTY SIECI NEURONOWEJ

	//USTALENIE KONFIGURACJI
	std::cout << "KONFIGURACJA:" << std::endl;
	std::vector<int> anatomy = { 4,6,4 };

	for (auto it = anatomy.begin(); it != anatomy.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	//USTALENIE ILOSCI ITERACJI
	int iterationsPerEpoch = 4;
	std::cout << std::endl << "Liczba iteracji na epoke: " << iterationsPerEpoch << std::endl;

	std::cout << std::endl << "Lista neuronow (zglaszajcie sie):" << std::endl;

	//UTWORZENIE SIECI
	Network network(anatomy, true, 0.5, 0.6, 1.0, iterationsPerEpoch);

	//ZALADOWANIE PLIKU
	network.getFile()->loadFile("transformation.txt");
	std::cout << std::endl;
	
	//PIERWSZE INFO O SIECI
	//std::cout << std::endl << std::endl;
	std::cout << "Informacje o sieci:" << std::endl;
	network.printInfoAboutNeurons();

	//for (int i = 0; i < iterations; i++)
	//{
	//	network.loadInputValues();
	//	network.forwardPropagation();
	//	network.backPropagation();
	//	network.epochsAndMidSquareError();

	//	if (i % 100000 == 0 && i != 0)
	//		std::cout << "10000" << std::endl;
	//}

	int i;
	do
	{
		for (i = 0; i < iterationsPerEpoch; i++)
		{
			network.loadInputValues();
			network.forwardPropagation();
			network.backPropagation();
			network.epochsAndMidSquareError();
		}
	} while (network.getMediumSquareError() > 0.001);


	//TEST SIECI
	std::cout << std::endl << "Test sieci na podstawie losowego zestawu wzorcow:" << std::endl;

	for (int k = 0; k < 4; k++)
	{
		network.loadInputValues();
		std::cout << std::endl;
		network.printInputs();
		network.forwardPropagation();
		std::cout << std::endl;
		network.printOutputs();
		std::cout << std::endl;
	}

	//WYPISANIE WYJSC Z OSTATNIEJ WARSTWY
	std::cout << std::endl << "Wartosci z ostatniej warstwy podczas ostatniej iteracji:" << std::endl;
	network.printOutputs();
	std::cout << std::endl;

	std::cout << "Ostatnie wejscie" << std::endl;
	network.printInputs();
	std::cout << std::endl << std::endl;
	
	std::cout << "Informacje o sieci:" << std::endl;
	network.displayInfo();
	std::cout << std::endl << std::endl;
	//network.printInfoAboutNeurons();

	network.printMSEToFile();

	//network.printHiddenInputs();

	//WYPISANIE WSZYSTKICH WZORCOW TESTOWYCH
	//for (auto &it : network.test)
	//{
	//	for (auto &iter : it)
	//	{
	//		std::cout << iter;
	//	}
	//	std:: cout << std::endl;
	//}

	std::cout << std::endl << "DZIALA HAHAHA :)" << std::endl << std::endl;
	//std::system("PAUSE");
    return 0;
}

