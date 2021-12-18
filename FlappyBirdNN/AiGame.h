#pragma once
#include "Game.h"
#include "AiBird.h"

class AiGame : public Game {
public:
	AiGame(string loadFile = "0",string saveFile = "0");
	void Init();
	void Print();
	void Update(float deltaTime);
	void Restart();
	void SaveBird(AiBird* bird);
	AiBird* LoadBird();
private:
	AiBird* lastBestBird;
	AiBird* BestBird;
	AiBird* SecondBestBird;
	AiBird* ThirdBestBird;
	AiBird** birds;
	int countDead = 0;
	int generation = 0;
	string loadFile,saveFile;
};

