#pragma once
#include "Game.h"
#include "AiBird.h"

class AiGame : public Game {
public:
	AiGame(string baseFile = "0",string saveFile = "0");
	void Init();
	void Print();
	void Update(float deltaTime);
private:
	AiBird** birds;
	int countDead = 0;
	string baseFile,saveFile;

};

