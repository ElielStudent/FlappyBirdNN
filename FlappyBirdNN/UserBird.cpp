#include "UserBird.h"

UserBird::UserBird(sf::Texture& birdTex, float scale) :Bird(birdTex, scale)
{
	jumpLastFrame = false;
}

bool UserBird::IsJumping(Pipe* nextPipe)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (jumpLastFrame)
			return false;
		return (jumpLastFrame = true);
	}
	else
		jumpLastFrame = false;
	return false;
}