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
	
private:
	int running = 5;
	int walking = 2;
	Projectile * newProjectile;
	World wrld;
};
#endif // !PLAYER_H
