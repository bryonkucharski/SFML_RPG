#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "World.h"

class Player : public Creature
{
public:
	Player(std::string playerName, std::string file, World &world);
	~Player();
	void updatePlayer(RenderWindow &window);
	void onEnemyIntersect();
	void onEnemyBulletIntersect();
	void onIncreaseXPEvent(int amount);
	bool didPlayerLevel();
	void setBulletSpeed(int sp);
	int getBulletSpeed();
	void checkForUpgrades();
	void setBulletPng(string png);
	string getBulletPng();
	void setBulletWidth(int w);
	void setBulletHeight(int h);
	int getBulletWidth();
	int getBulletHeight();

private:
	int running = 5;
	int walking = 2;
	Projectile * newProjectile;
	World wrld;
	int bulletSpeed = 6;
	string bulletPng;
	int bulletWidth = 18;
	int bulletHeight = 18;

};
#endif // !PLAYER_H
