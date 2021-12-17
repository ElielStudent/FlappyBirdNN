#include "Functions.h"

void LoadTex(sf::Texture& tex, string fileName) {
	tex.loadFromFile(fileName);
}

void setTextureByScale(sf::Sprite& sprite, sf::Texture& texture, float scale)
{
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}
