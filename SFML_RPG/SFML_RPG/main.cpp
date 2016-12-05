#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "World.h"
#include "Player.h"
#include "Enemy.h"
#include "NPC.h"
#include "GUIBar.h"
#include "globals.h"
#include <fstream>

using namespace std;
void saveGame();
void loadGame();

#define PIXEL_SIZE 32
#define WIDTH      30*PIXEL_SIZE//Don't change this.
#define HEIGHT     22*PIXEL_SIZE//Don't change this.

using namespace sf;

int main(){
	//create main game window
	RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

	//set frame rate
	window.setFramerateLimit(60);

	World world(window);
	Player mainPlayer("Main Player", "res/Creatures/main.png",world);

	std::vector<Enemy*> currentEnemies;
	std::vector<NPC*> currentNPCs;
	std::vector<Projectile*> currentPlayerBullets;

	theMainPlayer = &mainPlayer;
	GUIBar guibar(window, "res/System/GUIbar.png","res/Fonts/Vecna.otf");
	Sprite gameOverSprite;
	Texture gameOverTexture;
	gameOverTexture.loadFromFile("res/System/GameOver.png");
	gameOverSprite.setTexture(gameOverTexture);
	bool gameOver = false;
	int temp = 0;

	while (window.isOpen()){
		//close window if X is pressed in top right
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}

		//check for a game over
		if (mainPlayer.getCurrentHealth() <= 0) {
			window.clear();
			gameOver = true;
		}

		//get all NPCs in current location
		currentNPCs = world.getLocation(mainPlayer.getCurrentLocation()).getNPCs();

		//get all enemies in current location
		currentEnemies = world.getLocation(mainPlayer.getCurrentLocation()).getEnemies();



		//--------------------------------ALL VECTORS------------------------
		currentNPCs.swap(world.getLocation(mainPlayer.getCurrentLocation()).getNPCs());
		currentEnemies.swap(world.getLocation(mainPlayer.getCurrentLocation()).getEnemies());
		currentPlayerBullets.swap(mainPlayer.getBullets());

		//-------------------------------END VECTORS-----------------------



		//--------------------------------ALL REMOVALS------------------------
		//remove inactive player bullets
		mainPlayer.removeBullets();

		//remove dead enemies
		world.getLocation(mainPlayer.getCurrentLocation()).removeEnemies();

		//remove inactive enemy bullets
		int enemyRemoveCounter = 0;
		for (std::vector<Enemy*>::iterator enemyIntersectIter = currentEnemies.begin(); enemyIntersectIter != currentEnemies.end(); ++enemyIntersectIter){
			Enemy *e = currentEnemies[enemyRemoveCounter];
			e->removeBullets();
			enemyRemoveCounter++;
		}

		//--------------------------------END REMOVALS------------------------



		//--------------------------------ALL THE INTERSECTIONS------------------------
		//player intersect with enemy
		int intersectionCounter = 0;
		for (std::vector<Enemy*>::iterator enemyIntersectIter = currentEnemies.begin(); enemyIntersectIter != currentEnemies.end(); ++enemyIntersectIter){
			if (mainPlayer.getRect().getGlobalBounds().intersects(currentEnemies[intersectionCounter]->getRect().getGlobalBounds())){
				mainPlayer.onEnemyIntersect();
			}
			intersectionCounter++;
		}

		//player intersect with enemy bullet
		intersectionCounter = 0;
		for (std::vector<Enemy*>::iterator enemyIntersectIter = currentEnemies.begin(); enemyIntersectIter != currentEnemies.end(); ++enemyIntersectIter){
			int intersectionCounter2 = 0;
			Enemy *e = currentEnemies[intersectionCounter];
			vector<Projectile*> enemyBullets = e->getBullets();
			for (vector<Projectile*>::iterator bulletIterator = enemyBullets.begin(); bulletIterator != enemyBullets.end(); ++bulletIterator){
				Projectile* p = enemyBullets[intersectionCounter2];
				if (p->getRect().getGlobalBounds().intersects(mainPlayer.getRect().getGlobalBounds())){
					mainPlayer.onEnemyBulletIntersect();
					p->onCollision();
				}
				intersectionCounter2++;
			}
			intersectionCounter++;
		}//end of forloop to check if a player intersects with enemy bullet

		//enemy intersect with player bullet
		intersectionCounter = 0;
		for (std::vector<Enemy*>::iterator enemyIntersectIter = currentEnemies.begin(); enemyIntersectIter != currentEnemies.end(); ++enemyIntersectIter){
			int intersectionCounter2 = 0;
			Enemy *e = currentEnemies[intersectionCounter];
			
			for (vector<Projectile*>::iterator bulletIterator = currentPlayerBullets.begin(); bulletIterator != currentPlayerBullets.end(); ++bulletIterator){
				Projectile* p = currentPlayerBullets[intersectionCounter2];
				if (p->getRect().getGlobalBounds().intersects(e->getRect().getGlobalBounds())){
					e->onPlayerBulletIntersect(mainPlayer.getDamage());
					p->onCollision();
					if (e->getCurrentHealth() <= 0){
						//increase player's xp
						mainPlayer.onIncreaseXPEvent(e->dropExp());
					}
				}
				intersectionCounter2++;
			}
			intersectionCounter++;
		}//end of enemy intersecting with a player's bullet

		//NPC intersect with player bullet
		intersectionCounter = 0;
		for (std::vector<NPC*>::iterator NPCIntersectIter = currentNPCs.begin(); NPCIntersectIter != currentNPCs.end(); ++NPCIntersectIter){
			int intersectionCounter2 = 0;
			NPC *n = currentNPCs[intersectionCounter];

			for (vector<Projectile*>::iterator bulletIterator = currentPlayerBullets.begin(); bulletIterator != currentPlayerBullets.end(); ++bulletIterator){
				Projectile* p = currentPlayerBullets[intersectionCounter2];
				if (p->getRect().getGlobalBounds().intersects(n->getRect().getGlobalBounds())){
					n->onPlayerBulletIntersect();
					p->onCollision();
				}
				intersectionCounter2++;
			}
			intersectionCounter++;
		}
		//NPC intersect with player
		intersectionCounter = 0;
		for (std::vector<NPC*>::iterator NPCIntersectIter = currentNPCs.begin(); NPCIntersectIter != currentNPCs.end(); ++NPCIntersectIter){
			int intersectionCounter2 = 0;
			NPC *n = currentNPCs[intersectionCounter];
			if (n->getRect().getGlobalBounds().intersects(mainPlayer.getRect().getGlobalBounds())){
				n->onPlayerIntersect();
			}
			intersectionCounter++;
		}


		//--------------------------------END INTERSECTIONS-------------------------

		//--------------------------------ALL THE UPDATING--------------------------

		//update player
		mainPlayer.updatePlayer(window);

		//update enemies in current location
		int enemyUpdateCounter = 0;
		for (std::vector<Enemy*>::iterator enemyUpdateIter = currentEnemies.begin(); enemyUpdateIter != currentEnemies.end(); ++enemyUpdateIter) {
			//update enemy
			currentEnemies[enemyUpdateCounter]->updateEnemy( mainPlayer.getRect().getPosition() );
			enemyUpdateCounter++;
		}

		//update NPCs
		int NPCUpdateCounter = 0;
		for (std::vector<NPC*>::iterator NPCUpdateIter = currentNPCs.begin(); NPCUpdateIter != currentNPCs.end(); ++NPCUpdateIter){
			//update NPC
			currentNPCs[NPCUpdateCounter]->updateNPC();
			NPCUpdateCounter++;
		}

		//update player Projectiles
		int playerBulletUpdate = 0;
		for (std::vector<Projectile *>::iterator playerBulletsUpdateIter = currentPlayerBullets.begin(); playerBulletsUpdateIter != currentPlayerBullets.end(); ++playerBulletsUpdateIter) {
			currentPlayerBullets[playerBulletUpdate]->update();
			playerBulletUpdate++;
		}

		//upate enemy projectiles
		int updateCounter = 0;
		for (std::vector<Enemy*>::iterator enemyIntersectIter = currentEnemies.begin(); enemyIntersectIter != currentEnemies.end(); ++enemyIntersectIter){
			int updateCounter2 = 0;
			Enemy *e = currentEnemies[updateCounter];
			vector<Projectile*> enemyBullets = e->getBullets();
			for (vector<Projectile*>::iterator bulletIterator = enemyBullets.begin(); bulletIterator != enemyBullets.end(); ++bulletIterator){
				Projectile* p = enemyBullets[updateCounter2];
				p->update();
				updateCounter2++;
			}
			updateCounter++;
		}
		//---------------------------------END UPDATING---------------------------


		//--------------------------------ALL THE DRAWING-------------------------
		//draw to screen
		if (!gameOver) {
			//draw world and location
			world.drawWorld(window, world.getLocation(mainPlayer.getCurrentLocation()));

			//graph graphic bar
			guibar.drawAll(window, mainPlayer, world);

			//draw main player
			window.draw(mainPlayer.getSprite());

			//draw enemies
			int enemyDrawCounter = 0;
			for (std::vector<Enemy*>::iterator enemyDrawIter = currentEnemies.begin(); enemyDrawIter != currentEnemies.end(); ++enemyDrawIter) {
			
				window.draw(currentEnemies[enemyDrawCounter]->getSprite());
				window.draw(currentEnemies[enemyDrawCounter]->getText());
				enemyDrawCounter++;
			}
			//draw NPS's
			int NPCdrawCounter = 0;
			for (std::vector<NPC*>::iterator NPCDrawIter = currentNPCs.begin(); NPCDrawIter != currentNPCs.end(); ++NPCDrawIter) {
				window.draw(currentNPCs[NPCdrawCounter]->getSprite());
				window.draw(currentNPCs[NPCdrawCounter]->getText());
				NPCdrawCounter++;
			}

			//draw player Projectiles
			int playerBulletCounter = 0;
			for (std::vector<Projectile *>::iterator playerBulletsIter = currentPlayerBullets.begin(); playerBulletsIter != currentPlayerBullets.end(); ++playerBulletsIter) {
				window.draw(currentPlayerBullets[playerBulletCounter]->getSprite());
				playerBulletCounter++;
			}

			//draw enemy projectiles
			int bryonsDrawCounter = 0;
			for (std::vector<Enemy*>::iterator enemyIntersectIter = currentEnemies.begin(); enemyIntersectIter != currentEnemies.end(); ++enemyIntersectIter){
				int bryonsDrawCounter2 = 0;
				Enemy *e = currentEnemies[bryonsDrawCounter];
				vector<Projectile*> enemyBullets = e->getBullets();
				for (vector<Projectile*>::iterator bulletIterator = enemyBullets.begin(); bulletIterator != enemyBullets.end(); ++bulletIterator){
					Projectile* p = enemyBullets[bryonsDrawCounter2];
					window.draw(p->getSprite());
					bryonsDrawCounter2++;
				}
				bryonsDrawCounter++;
			}
		}
		else {
			window.clear();
			window.draw(gameOverSprite);
		}
		//------------------------------------------------------------------------------


		window.display();
		if (temp == 0){
			if (Keyboard::isKeyPressed(Keyboard::RAlt) || Keyboard::isKeyPressed(Keyboard::LAlt)){
				if (Keyboard::isKeyPressed(Keyboard::F2)){
					temp = 20;
					saveGame();
				}
				if (Keyboard::isKeyPressed(Keyboard::F3)){
					temp = 20;
					loadGame();
				}
			}
		}
		if (temp > 0)
		temp--;
	}//end of while window is open loop
	return 0;
}//end of main();

void saveGame(){
	//save the file
	ofstream theFile;
	theFile.open("saveFile.txt", ios::out);
	//write stuff
	/*
	position
	location
	total experience
	level
	damage
	current health
	max health
	*/
	if (theFile.is_open()){
		theFile << theMainPlayer->getCurrentPosition().x << "\n" <<
		theMainPlayer->getCurrentPosition().y << "\n" <<
		theMainPlayer->getCurrentLocation() << "\n" <<
		theMainPlayer->getTotalExperience() << "\n" <<
		theMainPlayer->getLevel() << "\n" <<
		theMainPlayer->getDamage() << "\n" <<
		theMainPlayer->getCurrentHealth() << "\n" <<
		theMainPlayer->getMaxHealth();
	}
	theFile.close();
	cout << "save command pressed\n";
}


void loadGame(){
	cout << "load command pressed\n";
	ifstream theFile;
	string line;
	theFile.open("saveFile.txt", ios::in);
	float positionx = 0;//0
	float positiony = 0;//1
	int location = 0;//2
	int xp = 2003;//3
	int level = 0;//4
	int damage = 0;//5
	int currentHealth = 0;//6
	int maxHealth = 0;//7
	int counter = 0;
	if (theFile.is_open()){
		while (getline(theFile, line)){
			//cout << line << '\n';
			switch (counter){
			case 0:
				positionx = stof(line);
				break;
			case 1:
				positiony = stof(line);
				break;
			case 2:
				location = stoi(line);
				break;
			case 3:
				xp = stoi(line);
				break;
			case 4:
				level = stoi(line);
				break;
			case 5:
				damage = stoi(line);
				break;
			case 6:
				currentHealth = stoi(line);
				break;
			case 7:
				maxHealth = stoi(line);
				break;
			}
			counter++;
		}
		theFile.close();
		//write values to player
		theMainPlayer->setCurrentPosition(Vector2f(positionx, positiony));
		theMainPlayer->getRect().setPosition(Vector2f(positionx, positiony));
		theMainPlayer->setCurrentLocation(location);
		theMainPlayer->setTotalExperience(xp);
		theMainPlayer->setLevel(level);
		theMainPlayer->setDamage(damage);
		theMainPlayer->setCurrentHealth(currentHealth);
		theMainPlayer->setMaxHealth(maxHealth);
	}
}//end of loadGame()