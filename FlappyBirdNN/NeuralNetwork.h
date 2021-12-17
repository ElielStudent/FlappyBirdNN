#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define NumOfHiddenLayers 2
#define NumOfNodesInHidden 8
#define NumOfNodesInInput 5
#define NumOfNodesInOutput 2			//How much the bird wants to jump vs not

typedef double HiddenW[NumOfNodesInHidden][NumOfNodesInHidden];

class NeuralNetwork {
public:
	NeuralNetwork();
	NeuralNetwork(NeuralNetwork* base, int mPer);
	bool Calculate(double* input);

private:
	vector<double> layers[NumOfHiddenLayers + 2];
	vector<double> bias[NumOfHiddenLayers + 1];
	double inputW[NumOfNodesInHidden][NumOfNodesInInput];
	double outputW[NumOfNodesInOutput][NumOfNodesInHidden];
	HiddenW hiddenWs[NumOfHiddenLayers - 1];
};

