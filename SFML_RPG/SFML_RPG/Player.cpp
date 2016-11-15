#include "Player.h"

Player::~Player() {

}
//handles player movements. called every frame in main.
void Player::updatePlayer(RenderWindow &window) {

	//implement spriting by holding shift, MH
	int speedMod = 0;
	if (Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RControl)) {
		speedMod = 5;
	}

	//allow player to walk at the start of every frame. 
	this->setAllWalk(true);

	//map the player's sprite to the player's rect
	this->getSprite().setPosition(this->getRect().getPosition());

	//get the current x and y of the player every frame
	this->setCurrentPosition(this->getRect().getPosition());

	//holds all rectangles that the player is not allowed to insersect with
	std::vector<RectangleShape> obstacles = this->getCurrentLocation().getObstacles();

	//increment walking counter for animation 
	this->setWalkingCounter(this->getWalkingCounter() + 1);

	//added WASD support MH
	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
	{
		this->setDirection(1);

		animationTime = animationClock.getElapsedTime();
		if (animationTime.asSeconds() > animationCounter)
		{
			this->getSprite().setTextureRect(IntRect(this->getWalkingCounter() * 32, 32, 32, 32));
			animationClock.restart();
		}

		this->getRect().move(-this->getSpeed() - speedMod, 0);
	
		while(this->checkForIntersect(obstacles, this->getRect())){
			this->getRect().move(this->getSpeed() + speedMod, 0);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
	{
		this->setDirection(2);

		animationTime = animationClock.getElapsedTime();
		if (animationTime.asSeconds() > animationCounter)
		{
			this->getSprite().setTextureRect(IntRect(this->getWalkingCounter() * 32, 32 * 2, 32, 32));
			animationClock.restart();
		}

		this->getRect().move(this->getSpeed() + speedMod, 0);

		while (this->checkForIntersect(obstacles, this->getRect())) {
			this->getRect().move(-this->getSpeed() - speedMod, 0);
		}
		
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
	{
		this->setDirection(3);

		animationTime = animationClock.getElapsedTime();
		if (animationTime.asSeconds() > animationCounter)
		{
			this->getSprite().setTextureRect(IntRect(this->getWalkingCounter() * 32, 96, 32, 32));
			animationClock.restart();
		}

		this->getRect().move(0, -this->getSpeed() - speedMod);

		while(this->checkForIntersect(obstacles, this->getRect())) {
				this->getRect().move(0, this->getSpeed() + speedMod);
		}
			
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
	{
		this->setDirection(4);

		animationTime = animationClock.getElapsedTime();
		if (animationTime.asSeconds() > animationCounter)
		{
			this->getSprite().setTextureRect(IntRect(this->getWalkingCounter() * 32, 0, 32, 32));			
			animationClock.restart();
		}

		this->getRect().move(0, this->getSpeed() + speedMod);

		while(this->checkForIntersect(obstacles, this->getRect())){
			this->getRect().move(0, -this->getSpeed() - speedMod);
		}
	}

	if (this->getWalkingCounter() == 2){
		setWalkingCounter(0);
	}

	//draw create to the screen
	this->drawCreature(window);
}