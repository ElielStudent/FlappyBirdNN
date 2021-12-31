#include "AiGame.h"

AiGame::AiGame(string loadFile, string saveFile) {
	this->loadFile = loadFile;
	this->saveFile = saveFile;
	lastBestBird = NULL;
	BestBird = NULL;
	SecondBestBird = NULL;
	ThirdBestBird = NULL;
}

void AiGame::Init() {
	birds = new AiBird * [NumOfAiBirds];

	for (int i = 0; i < NumOfAiBirds; i++) {
		if (loadFile != "0") {
			birds[i] = LoadBird();
		}
		else {
			birds[i] = new AiBird(birdTex, scale);
		}
	}

	while (window->isOpen()) {
		UpdateEvents();
		float deltaTime = clock.restart().asSeconds() * GameSpeed;
		HandlePipes(deltaTime, birds[0]);
		Update(deltaTime);
		Print();
	}
}

void AiGame::Print() {
	window->clear();
	window->draw(backGround);
	for (int i = 0; i < NumOfAiBirds; i++) {
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

void AiGame::Update(float deltaTime) {
	for (int i = 0; i < NumOfAiBirds; i++) {
		if (!birds[i]->Died()) {
			if (!beforePipe.empty())
				birds[i]->Update(deltaTime, &beforePipe.front());
			else
				birds[i]->Update(deltaTime, NULL);

			if (birds[i]->Died()) {
				countDead++;
				if (NumOfAiBirds - countDead == 2) {
					if (ThirdBestBird != NULL)
						delete ThirdBestBird;
					ThirdBestBird = new AiBird(birdTex, scale, birds[i], 0);
				}
				if (NumOfAiBirds - countDead == 1) {
					if (SecondBestBird != NULL)
						delete SecondBestBird;
					SecondBestBird = new AiBird(birdTex, scale, birds[i], 0);
				}
				if (countDead == NumOfAiBirds) {
					if (BestBird != NULL) {
						if (lastBestBird != NULL)
							delete lastBestBird;
						lastBestBird = new AiBird(birdTex, scale, BestBird, 0);
						delete BestBird;
					}
					std::cout << "Gen " << generation <<
						" | Bird: " << (i <= 1 ?
							(i == 0 ? "LBB" : "BB") : std::to_string(i).c_str()) <<
						" | Score: " << score << std::endl;
					BestBird = new AiBird(birdTex, scale, birds[i], 0);
					Restart();
				}
			}
		}
	}
}

void AiGame::Restart() {
	if (lastBestBird == NULL)
		lastBestBird = new AiBird(birdTex, scale, BestBird, 0);

	delete birds[0];
	birds[0] = new AiBird(birdTex, scale, lastBestBird, 0);
	delete birds[1];
	birds[1] = new AiBird(birdTex, scale, BestBird, 0);

	for (int i = 2; i < NumOfAiBirds; i++) {
		delete birds[i];
		int birdChance = rand() % 101;
		if (birdChance <= 5)
			birds[i] = new AiBird(birdTex, scale, ThirdBestBird, MutationPerc);
		else if (birdChance <= 15)
			birds[i] = new AiBird(birdTex, scale, SecondBestBird, MutationPerc);
		else if (birdChance <= 75)
			birds[i] = new AiBird(birdTex, scale, BestBird, MutationPerc);
		else // (birdChance <= 100)
			birds[i] = new AiBird(birdTex, scale, lastBestBird, MutationPerc);
	}

	beforePipe.clear();
	afterPipe.clear();
	timeFromPipes = StartSpawnRate;

	score = 0;
	countDead = 0;
	ScoreTxt.setString("0");
	ScoreTxt.setOrigin(ScoreTxt.getLocalBounds().width / 2, 0);
	generation++;

	SaveBird(BestBird);
}

void AiGame::SaveBird(AiBird* bird) {
	if (saveFile == "0") return;
	bird->SaveBird(saveFile);
}

AiBird* AiGame::LoadBird() {
	AiBird* bird = new AiBird(birdTex, scale, loadFile);
	return bird;
}

