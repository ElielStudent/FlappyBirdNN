#pragma once
#include <SFML/Graphics.hpp>
#include "Pipe.h"
#include "Functions.h"
#include "Constants.h"
class Bird
{
public:
	Bird(sf::Texture& birdTex, float scale);
	void PrintBird(sf::RenderWindow& wind);
	void Update(float deltaTime, Pipe* nextPipe); // pointer because it can be null
	bool IsCollided(Pipe* nextPipe) ;
	bool PassedPipe(Pipe& pipe) ;
	bool Died() { return isDead; }


protected:
	virtual bool IsJumping(Pipe* nextPipe) = 0;
	sf::Sprite birdSprite;
	float velocity;
	float r;
	bool isDead;
};