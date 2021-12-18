#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Bird.h"
#include "Constants.h"
#include "Pipe.h"
#include "Functions.h"

using namespace std;

// game is virual because it has virtual funcs
class Game
{
public:
	Game();
	void Start();
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Print() = 0;
	void LoadData();
	void LoadBackGround();
	int UpdateEvents();
	void HandlePipes(float deltaTime, Bird* bird);

protected:

	float scale;

	sf::RenderWindow* window;

	sf::Texture backGroundTex;
	sf::Texture groundTex;
	sf::Texture birdTex;
	sf::Texture pipeUpTex;
	sf::Texture pipeDownTex;
	sf::Font font;

	sf::Sprite backGround;
	sf::Sprite ground;

	sf::Clock clock;

	list<Pipe> beforePipe;
	list<Pipe> afterPipe;

	float timeFromPipes;
	float timeToSpawn;

	int score;
	sf::Text ScoreTxt;
};


