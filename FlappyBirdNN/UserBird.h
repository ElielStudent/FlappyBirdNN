#pragma once
#include "Bird.h"
class UserBird :
    public Bird
{
public:
    UserBird(sf::Texture& birdTex, float scale);
private:
    bool IsJumping(Pipe* nextPipe);
    bool jumpLastFrame;
};