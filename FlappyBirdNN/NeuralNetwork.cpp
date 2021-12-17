#include "NeuralNetwork.h"

double inline getRand() {
	return (rand() % 2001 - 1000.0) / 1000.0;
}

void RandMat(int n, int m, double* matrix) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i * n + j] = getRand();
		}
	}
}

double activationFunc(double x) {
	return max(x, 0.0);					//Relu
	//return x / (1 + abs(x));			//Fast sigmoid
}

NeuralNetwork::NeuralNetwork()
{
	layers[0].resize(NumOfNodesInInput);
	layers[NumOfHiddenLayers + 1].resize(NumOfNodesInOutput);
	bias[NumOfHiddenLayers].resize(NumOfNodesInOutput);
	for (int i = 1; i <= NumOfHiddenLayers; i++) {
		layers[i].resize(NumOfNodesInHidden);
		bias[i - 1].resize(NumOfNodesInHidden);
	}
	RandMat(NumOfNodesInHidden, NumOfNodesInInput, *inputW);
	RandMat(NumOfNodesInOutput, NumOfNodesInHidden, *outputW);
	for (int i = 0; i < NumOfHiddenLayers - 1; i++) {
		RandMat(NumOfNodesInHidden, NumOfNodesInHidden, *(hiddenWs[i]));
	}
	for (int i = 0; i < NumOfHiddenLayers + 1; i++) {
		for (auto& b : bias[i]) {
			b = getRand();
		}
	}
}

NeuralNetwork::NeuralNetwork(NeuralNetwork* base, int mPer) {

}

bool NeuralNetwork::Calculate(double* input)
{
	for (int i = 0; i < NumOfNodesInInput; i++) {
		layers[0][i] = input[i];							//get input inside the input layer
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {			//Calculate the first layer from input
		layers[1][i] = bias[0][i];							//add bias to the hidden layer
		for (int j = 0; j < NumOfNodesInInput; j++) {
			layers[1][i] += layers[0][j] * inputW[i][j];	//node in first hidden plus all inputs times the input weight
		}
		layers[1][i] = activationFunc(layers[1][i]);
	}

	for (int k = 2; k < NumOfHiddenLayers + 1; k++) {						//for every hidden layer (starting from 2nd hidden layer)
		for (int i = 0; i < NumOfNodesInHidden; i++) {						//for every node in the hidden layer
			layers[k][i] = bias[k - 1][i];									//start the 2nd layer as bias from the layer from before
			for (int j = 0; j < NumOfNodesInHidden; j++) {					//for every node in the hidden layer
				layers[k][i] += layers[k - 1][j] * hiddenWs[k - 2][i][j];	//layer k equals the layer from before times the weight of the hidden layers (-2 cause it starts at 0)
			}
			layers[k][i] = activationFunc(layers[k][i]);					//use the activation function on the layer
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {													//Calculate the last layer to output
		layers[NumOfHiddenLayers + 1][i] = bias[NumOfHiddenLayers][i];								//add bias to the output layer
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			layers[NumOfHiddenLayers + 1][i] += layers[NumOfHiddenLayers][j] * outputW[i][j];		//node in output all nodes in last hidden times the output weight
		}
		layers[NumOfHiddenLayers + 1][i] = activationFunc(layers[NumOfHiddenLayers + 1][i]);		//use the activation function on the layer
	}

	return layers[NumOfHiddenLayers + 1][0] > layers[NumOfHiddenLayers + 1][1];	
}
