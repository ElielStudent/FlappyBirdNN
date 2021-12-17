#include "Bird.h"

Bird::Bird(sf::Texture& birdTex, float scale) {
	setTextureByScale(birdSprite, birdTex, scale);
	birdSprite.setOrigin(birdTex.getSize().x / 2, birdTex.getSize().y / 2);
	birdSprite.setPosition(ScreenW / 4, ScreenH / 2);
	velocity = 0;
	r = birdTex.getSize().x * scale / 2;
	isDead = false;
}

void Bird::PrintBird(sf::RenderWindow& wind)
{
	wind.draw(birdSprite);
}

void Bird::Update(float deltaTime, Pipe* nextPipe)
{
	if (IsJumping(nextPipe))
		velocity = JumpSpeed;
	else
		velocity -= Gravity * deltaTime;

	if (velocity > 0)
		birdSprite.setRotation(UpRotation);
	else
		birdSprite.setRotation(birdSprite.getRotation() + 1);

	birdSprite.setPosition(birdSprite.getPosition().x,
		birdSprite.getPosition().y - velocity * deltaTime * birdSprite.getScale().y);

	if (IsCollided(nextPipe))
		isDead = true;
}

bool Bird::IsCollided(Pipe* nextPipe)
{
	sf::Vector2f pos = birdSprite.getPosition();
	if (nextPipe && pos.x + r > nextPipe->GetStartPosition() 
		&& nextPipe->GetEndPosition() >= pos.x - r) {
		return pos.y + r * 0.7 > nextPipe->getH() ||
			pos.y - r * 0.7 < nextPipe->getH() - nextPipe->GetDis();
	}
	return pos.y > GroundY* birdSprite.getScale().x;

}

bool Bird::PassedPipe(Pipe& pipe)
{
	return pipe.GetEndPosition() < birdSprite.getPosition().x - r;
}
