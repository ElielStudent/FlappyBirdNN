#pragma once
#include "Bird.h"                          
#include "NeuralNetwork.h"
class AiBird : public Bird{
public:
    ~AiBird();
    AiBird(sf::Texture& birdTex, float scale);
    AiBird(sf::Texture& birdTex, float scale,AiBird* base,int mPer);
    AiBird(sf::Texture& birdTex, float scale, string loadFile);
    void SaveBird(string saveFile);
private:
    bool IsJumping(Pipe* nextPipe);
    NeuralNetwork* network;
};

