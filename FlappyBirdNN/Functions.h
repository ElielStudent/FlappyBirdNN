#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

void LoadTex(sf::Texture& tex, string fileName);

void setTextureByScale(sf::Sprite& sprite, sf::Texture& texture, float scale);