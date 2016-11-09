#include "Player.h"

Player::~Player() {

}
void Player::updatePlayer(RenderWindow &window) {

	this->getSprite().setPosition(this->getRect().getPosition());

	this->setCurrentPosition(this->getRect().getPosition());

	std::cout << this->getCurrentPosition().x << " " << this->getCurrentPosition().y << std::endl;

	std::cout << this->getRect().getGlobalBounds().height << " " << this->getRect().getGlobalBounds().width << "\n";

	std::vector<RectangleShape> obstacles = this->getCurrentLocation().getObstacles();

	this->setWalkingCounter(this->getWalkingCounter() + 1);

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->setDirection(1);
		this->getSprite().setTextureRect(IntRect(this->getWalkingCounter() * 32, 96, 32, 32));
		this->getRect().move(-this->getSpeed(), 0);		
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->setDirection(2);
		this->getSprite().setTextureRect(IntRect(this->getWalkingCounter() * 32, 32, 32, 32));
		this->getRect().move(this->getSpeed(), 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		this->setDirection(3);
		this->getSprite().setTextureRect(IntRect(this->getWalkingCounter() * 32, 64, 32, 32));

		int counter = 0;
		for (std::vector<RectangleShape>::iterator obsIter = obstacles.begin(); obsIter != obstacles.end(); ++obsIter) {
			if (this->getRect().getGlobalBounds().intersects(obstacles[counter].getGlobalBounds())) {
				std::cout << "YES\n";
			}
			else
			{
				std::cout << "NO\n";
			}
		}
		this->getRect().move(0, -this->getSpeed());
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		this->setDirection(4);
		this->getSprite().setTextureRect(IntRect(this->getWalkingCounter() * 32, 0, 32, 32));
		this->getRect().move(0, this->getSpeed());
	}

	if (this->getWalkingCounter() == 2){
		setWalkingCounter(0);
	}

	this->drawCreature(window);
}