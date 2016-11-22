#include "Location.h"

Location::Location(){
	//nothing
}
Location::Location(std::string locationName, std::string file, int locationID, int next1, int next2, int next3, Vector2f nextPos1, Vector2f nextPos2, Vector2f nextPos3){
	
	this->setFileName(file);
	this->setName(locationName);
	this->getTexture().loadFromFile(fileName);
	this->getSprite().setTexture(this->getTexture());
	this->getSprite().setPosition(Vector2f(0, 0));

	this->setLocationID(locationID);

	this->setLocation1(next1);
	this->setLocation2(next2);
	this->setLocation3(next3);

	this->setNext1Position(nextPos1);
	this->setNext2Position(nextPos2);
	this->setNext3Position(nextPos3);
		
}
void Location::setup() {
	this->getTexture().loadFromFile(fileName);
	this->getSprite().setTexture(this->getTexture());
	this->getSprite().setPosition(Vector2f(0, 0));
}
Location::~Location() {}

std::string Location::getName() {
	return name;
}
std::string Location::getFileName() {
	return fileName;
}

int Location::getLocationID() {
	return locationID;
}
void Location::setFileName(std::string name) {
	this->fileName = name;
}
void Location::setLocationID(int ID) {
	this->locationID = ID;
}
void Location::setName(std::string name) {
	this->name = name;
}

void Location::setEnemies() {

}
void Location::addToObstacles(RectangleShape &rectanlgeToAdd) {
	obstacles.push_back(rectanlgeToAdd);
}
std::vector<RectangleShape>& Location::getObstacles() {
	return obstacles;
}

void Location::setLocation1(int locationNum) {
	this->nextLocation1 = locationNum;

}
void Location::setLocation2(int locationNum) {
	this->nextLocation2 = locationNum;
}
void Location::setLocation3(int locationNum) {
	this->nextLocation3 = locationNum;
}

int Location::getLocation1() {
	return nextLocation1;
}
int Location::getLocation2() {
	return nextLocation2;
}
int Location::getLocation3() {
	return nextLocation3;
}
Vector2f Location::getNext1Position() {
	return next1Position;
}
Vector2f Location::getNext2Position() {
	return next2Position;
}
Vector2f Location::getNext3Position() {
	return next3Position;
}
void Location::setNext1Position(Vector2f pos) {
	this->next1Position = pos;
}
void Location::setNext2Position(Vector2f pos) {
	this->next2Position = pos;
}
void Location::setNext3Position(Vector2f pos) {
	this->next3Position = pos;
}
void Location::addToLocationChanges(RectangleShape& rectanlgeToAdd) {
	this->locationChanges.push_back(rectanlgeToAdd);
}

std::vector<RectangleShape>& Location::getLocationChanges() {
	return locationChanges;
}