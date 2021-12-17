#include "UserGame.h"

UserGame::UserGame() :Game()
{

}

void UserGame::Init(){
	bird = new UserBird(birdTex, scale);

	while (window->isOpen()){
		UpdateEvents();
		float deltaTime = clock.restart().asSeconds();
		HandlePipes(deltaTime, bird);
		Update(deltaTime);
		Print();
	}
}

void UserGame::Print()
{
	window->clear();
	window->draw(backGround);
	bird->PrintBird(*window);
	for (auto& bp : beforePipe) {
		bp.PrintPipe(*window);
	}
	for (auto& ap : afterPipe) {
		ap.PrintPipe(*window);
	}
	window->draw(ground);
	window->draw(ScoreTxt);
	window->display();
}

void UserGame::Update(float deltaTime)
{
	if (!beforePipe.empty())
		bird->Update(deltaTime, &beforePipe.front());
	else
		bird->Update(deltaTime, NULL);


	if (bird->Died()) 
		Restart();
	
}

void UserGame::Restart() {
	delete bird;
	bird = new UserBird(birdTex,scale);
	beforePipe.clear();
	afterPipe.clear();
	score = 0;
	ScoreTxt.setString("0");
	ScoreTxt.setOrigin(ScoreTxt.getLocalBounds().width / 2, 0);
	timeFromPipes = StartSpawnRate;
}
