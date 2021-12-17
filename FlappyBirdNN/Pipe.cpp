#include "Pipe.h"

Pipe::Pipe(sf::Texture& pipeDownTex, sf::Texture& pipeUpTex, float scale, float dis)
{
	pipeDis = dis * scale;
	height = std::rand() % (int)((ScreenH / 4) * 3 - pipeDis - 40 * scale) + pipeDis + 20 * scale + 10;

	position = ScreenW;
	setTextureByScale(pipeUp, pipeUpTex, scale);
	setTextureByScale(pipeDown, pipeDownTex, scale);
	pipeDown.setOrigin(0, pipeDownTex.getSize().y);

	pipeUp.setPosition(position, height);
	pipeDown.setPosition(position, height - pipeDis);
}

void Pipe::Update(float deltaTime, float speed)
{
	position -= speed * deltaTime * pipeDown.getScale().x;
	pipeUp.setPosition(position, pipeUp.getPosition().y);
	pipeDown.setPosition(position, pipeDown.getPosition().y);
}

void Pipe::PrintPipe(sf::RenderWindow& wind) {
	wind.draw(pipeDown);
	wind.draw(pipeUp);
}
