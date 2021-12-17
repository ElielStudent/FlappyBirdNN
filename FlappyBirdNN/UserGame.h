#pragma once
#include "Game.h"
#include "UserBird.h"
class UserGame :
    public Game
{
public:
    UserGame();
    void Init();
    void Print();
    void Update(float deltaTime);
    void Restart();
private:
    Bird* bird;
};

