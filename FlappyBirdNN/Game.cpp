#include "Game.h"

Game::Game() {
	window = new sf::RenderWindow(sf::VideoMode(ScreenW, ScreenH), "Flippy bard");
}

void Game::Start()
{
	LoadData();
	LoadBackGround();

	srand((unsigned)time(NULL));

	clock.restart();
	window->setFramerateLimit(BaseFrameLimit);

	timeFromPipes = StartSpawnRate;
	timeToSpawn = 0;

	Init();
}

void Game::LoadData()
{
	LoadTex(groundTex, GroundPic);
	LoadTex(backGroundTex, BackGroundPic);
	LoadTex(birdTex, BirdPic);
	LoadTex(pipeUpTex, PipeUpPic);
	LoadTex(pipeDownTex, PipeDownPic);
	font.loadFromFile(FontPath);
}

void Game::LoadBackGround() {
	scale = ScreenH / (float)backGroundTex.getSize().y;
	setTextureByScale(backGround, backGroundTex, scale);
	setTextureByScale(ground, groundTex, scale);
	ground.setPosition(0, scale * (backGroundTex.getSize().y - groundTex.getSize().y));
	ScoreTxt.setPosition(ScreenW / 2, ScreenH / 15);
	ScoreTxt.setFont(font);
	ScoreTxt.setScale(scale, scale);
	ScoreTxt.setString("0");
	ScoreTxt.setOrigin(ScoreTxt.getLocalBounds().width / 2, 0);
}

int Game::UpdateEvents() {
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyReleased)
			if (event.key.code == sf::Keyboard::Space)
				return 1;
	}
}

void Game::HandlePipes(float deltaTime, Bird* bird)
{
	timeToSpawn -= deltaTime;

	if (timeToSpawn <= 0) {
		beforePipe.push_back(Pipe(pipeDownTex, pipeUpTex, scale, PipeDis));
		timeToSpawn = timeFromPipes;
		timeFromPipes -= PipeSpawnRateInc;
		timeFromPipes = max(timeFromPipes, MinSpawnRate);
	}

	for (auto& i : beforePipe) {
		i.Update(deltaTime, BaseSpeed);
	}

	for (auto& i : afterPipe) {
		i.Update(deltaTime, BaseSpeed);
	}

	if (beforePipe.begin() != beforePipe.end() && bird->PassedPipe(beforePipe.front())) {
		afterPipe.push_back(*beforePipe.begin());
		beforePipe.pop_front();
		score++;
		ScoreTxt.setString(std::to_string(score));
		ScoreTxt.setOrigin(ScoreTxt.getLocalBounds().width / 2, 0);
	}

	if (afterPipe.begin() != afterPipe.end() && afterPipe.front().GetEndPosition() < 0)
		afterPipe.pop_front();
}
