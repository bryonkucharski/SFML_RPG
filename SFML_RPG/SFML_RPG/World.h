#ifndef WORLD_H
#define WORLD_H

#include <vector>
using namespace std;

#include "Location.h"

class World
{
	public:
		World();
		World(RenderWindow &window);
		void drawWorld(RenderWindow &window,Location &toDraw);

		void setupHome(RenderWindow &window);
		void setupBigHouse();
		void setupForest();
		void setupTown();

		Location &getLocation(int requested);
		string getLocationString(int requested);

	private:
		//used to draw obstacles/location changers
		void createObstacleRectangle(RectangleShape &rectangle, Vector2f rectSize, Vector2f rectPosition, Color rectColor, Location &loc);
		void createLocationRectangle(RectangleShape &rectangle, Vector2f rectSize, Vector2f rectPosition, Color rectColor, Location &loc);

		Location home;
		Location town1;
		Location bigHouseInterior;
		Location forest;
		Location graveyard;
		Location dungeon;
		Location beach;
		Location ghostShed;
		Location market;
		Location port;
		Location pub;
		Location waterfall; // WF = waterfall.
		Location WFbossRoom;// This is the water fall boss room.
		Location WFcorridor;// This is the staircase that goes down from waterfall.


};

#endif // !WORLD_H
