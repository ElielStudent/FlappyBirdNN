#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Functions.h"

class Pipe
{
public:
	Pipe(sf::Texture& pipeDownTex, sf::Texture& pipeUpTex, float scale,float dis);
	void Update(float deltaTime, float speed);
	void PrintPipe(sf::RenderWindow& wind);
	float GetEndPosition() { return position + 
		pipeDown.getTexture()->getSize().x * pipeDown.getScale().x; };
	float GetStartPosition() { return position; };
	float getH() { return height; };
	float GetDis() { return pipeDis; };

private:
	float position;
	float height;
	float pipeDis;
	sf::Sprite pipeDown;
	sf::Sprite pipeUp;

};

