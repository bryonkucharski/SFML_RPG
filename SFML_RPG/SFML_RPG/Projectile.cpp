#include "Projectile.h"

Projectile::Projectile(std::string file,Vector2f pos,Vector2f size,int dir, int speed) {
	
	texture.loadFromFile(file);
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(IntRect(0, 0, 18,18));
	this->rect.setPosition(pos);

	this->rect.setSize(size);


	this->setDirection(dir);
	this->setSpeed(speed);
	this->setActive(true);

	this->setAnimationCounter(0);

}
Projectile::~Projectile() {}
void Projectile::update() {

	this->sprite.setPosition(this->rect.getPosition());

	/*
	time = clock.getElapsedTime();
	if (time.asSeconds() > 1) {
		setActive(false);
	}*/

	//update spritesheet every .5 seconds
	animationTime = animationClock.getElapsedTime();
	if (animationTime.asSeconds() > .5) {
		this->updateAnimation();
	}

	if (this->isActive())
	{
		if (direction == 1){
			this->rect.move(-speed, 0);
		}
		if (direction == 2) {
			this->rect.move(speed, 0);
		}
		if (direction == 3) {
			this->rect.move(0, -speed);
		}
		if (direction == 4){
			this->rect.move(0, speed);
		}
	}
}
void Projectile::setActive(bool state) {
	this->active = state;
}

void Projectile::setDirection(int d) {
	this->direction = d;
}
void Projectile::setSpeed(float s){
	this->speed = s;
}

int Projectile::getDirection() {
	return direction;
}
int Projectile::getSpeed() {
	return speed;
}
bool Projectile::isActive() {
	return active;
}
void Projectile::setAnimationCounter(int a) {
	this->animationCounter = a;
}
int Projectile::getAnimationCounter() {
	return this->animationCounter;
}
void Projectile::updateAnimation() {
	//increment counter
	this->setAnimationCounter(this->getAnimationCounter() + 1);
	
	//reset counter if 3
	if (this->getAnimationCounter() == 3) {
		this->setAnimationCounter(0);
	}
	//set the texture
	this->sprite.setTextureRect( IntRect(0,0,18,18) );
}
