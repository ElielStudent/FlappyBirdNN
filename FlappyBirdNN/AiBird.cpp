#include "AiBird.h"

AiBird::~AiBird(){
	delete network;
}

AiBird::AiBird(sf::Texture& birdTex, float scale) :Bird(birdTex, scale) {
	network = new NeuralNetwork();
}

AiBird::AiBird(sf::Texture& birdTex, float scale, AiBird* base, int mPer) : Bird(birdTex, scale) {
	this->network = new NeuralNetwork(base->network, mPer);
}

bool AiBird::IsJumping(Pipe* nextPipe) {
	float scale = birdSprite.getScale().y;
	if (nextPipe) {
		//Height of bird,velocity of bird,height of lower pipe,height of higher pipe,distance from pipe
		double AiInput[] = { birdSprite.getPosition().y / scale, velocity,
			nextPipe->getH() / scale,
			(nextPipe->getH() - nextPipe->GetDis()) / scale,
			(nextPipe->GetEndPosition() - birdSprite.getPosition().x) / scale };
		return network->Calculate(AiInput);
	}
	//Give values of a pipe in the middle/end of the screen
	double AiInput[] = { birdSprite.getPosition().y / scale, velocity,
		(ScreenH / 2) / scale,
		((ScreenH / 2) - PipeDis) / scale,
		(ScreenW - birdSprite.getPosition().x) / scale };
	return network->Calculate(AiInput);

}
