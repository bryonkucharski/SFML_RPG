#include "World.h"

#define PIXEL_SIZE 32

World::World(RenderWindow &window) {
	this->setupHome(window);
}
Location & World::getLocation(int requested) {
	switch (requested) {
		case 0:
			return home;
		case 1:
			return town1;
	};
}

void World::drawWorld(RenderWindow &window, Location &toDraw) {

	window.draw(toDraw.getSprite());

	//draw all obstacles
	int counter = 0;
	for (std::vector<RectangleShape>::iterator obsIter = toDraw.getObstacles().begin(); obsIter != toDraw.getObstacles().end(); ++obsIter)
	{
		window.draw(toDraw.getObstacles()[counter]);
		counter++;
	}
	
}
void World::setHome(Location& h) {
	this->home = h;
}
Location& World::getHome() {
	return home;
}
void World::setupHome(RenderWindow &window) {

	RectangleShape house(Vector2f(6 * PIXEL_SIZE, 4 * PIXEL_SIZE));
	house.setPosition(Vector2f(32, 0));
	house.setFillColor(Color::Transparent);

	RectangleShape trees(Vector2f(10 * PIXEL_SIZE, 5 * PIXEL_SIZE));
	trees.setPosition(Vector2f(PIXEL_SIZE * 19, 0));
	trees.setFillColor(Color::Transparent);

	//Building the big house MH
	RectangleShape bigHouse1(Vector2f(5 * PIXEL_SIZE, 9 * PIXEL_SIZE));
	bigHouse1.setPosition(Vector2f(PIXEL_SIZE * 11, PIXEL_SIZE * 9));
	bigHouse1.setFillColor(Color::Transparent);
	RectangleShape bigHouse2(Vector2f(1 * PIXEL_SIZE, 7 * PIXEL_SIZE));
	bigHouse2.setPosition(Vector2f(PIXEL_SIZE * 16, PIXEL_SIZE * 9));
	bigHouse2.setFillColor(Color::Transparent);
	RectangleShape bigHouse3(Vector2f(1 * PIXEL_SIZE, 6 * PIXEL_SIZE));
	bigHouse3.setPosition(Vector2f(PIXEL_SIZE * 17, PIXEL_SIZE * 9));
	bigHouse3.setFillColor(Color::Transparent);
	RectangleShape bigHouse4(Vector2f(1 * PIXEL_SIZE, 7 * PIXEL_SIZE));
	bigHouse4.setPosition(Vector2f(PIXEL_SIZE * 18, PIXEL_SIZE * 9));
	bigHouse4.setFillColor(Color::Transparent);
	RectangleShape bigHouse5(Vector2f(5 * PIXEL_SIZE, 9 * PIXEL_SIZE));
	bigHouse5.setPosition(Vector2f(PIXEL_SIZE * 19, PIXEL_SIZE * 9));
	bigHouse5.setFillColor(Color::Transparent);
	

	//Add the shape to the obstacle list
	home.addToObstacles(house);
	home.addToObstacles(trees);
	home.addToObstacles(bigHouse1);
	home.addToObstacles(bigHouse2);
	home.addToObstacles(bigHouse3);
	home.addToObstacles(bigHouse4);
	home.addToObstacles(bigHouse5);
	
}