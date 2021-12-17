#include "AiGame.h"

AiGame::AiGame(string baseFile, string saveFile){
	this->baseFile = baseFile;
	this->saveFile = saveFile;
}

void AiGame::Init(){
	birds = new AiBird*[NumOfAiBirds];

	for (int i = 0; i < NumOfAiBirds; i++) {
		if (baseFile != "0") {
			//load from file
		}
		else {
			birds[i] = new AiBird(birdTex, scale);
		}
	}

	while (window->isOpen())
	{
		UpdateEvents();
		float deltaTime = clock.restart().asSeconds();
		HandlePipes(deltaTime, birds[0]);
		Update(deltaTime);
		Print();
	}
}

void AiGame::Print(){
	window->clear();
	window->draw(backGround);
	for (int i = 0; i < NumOfAiBirds; i++){
		if (!birds[i]->Died())
			birds[i]->PrintBird(*window);
	}
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

void AiGame::Update(float deltaTime){
	for (int i = 0; i < NumOfAiBirds; i++) {
		if (!birds[i]->Died()) {
			if (!beforePipe.empty())
				birds[i]->Update(deltaTime,&beforePipe.front());
			else
				birds[i]->Update(deltaTime, NULL);

			if (birds[i]->Died()) {
				countDead++;
				if (countDead == NumOfAiBirds) {
					//mutate
					//restart
					for (int i = 0; i < NumOfAiBirds; i++) {
						delete birds[i];
						birds[i] = new AiBird(birdTex,scale);
					}
					beforePipe.clear();
					afterPipe.clear();
					timeFromPipes = StartSpawnRate;
					score = 0;
					ScoreTxt.setString("0");
					ScoreTxt.setOrigin(ScoreTxt.getLocalBounds().width / 2, 0);
					countDead = 0;

				}
			}
		}
	}
}
