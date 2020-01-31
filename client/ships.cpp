#include "ships.hpp"

Ship::Ship(){
	shipName = "undefined";
	cannonsSet = "";
	oX = 0;
	oY = 0;
	cargoSpace = 0;
	cost = 0;
	maxHp = 0;
}

Ship::~Ship(){

}

void Ship::init(int date){
	if (date == 0){
		shipName = "Karakana";
		oX = 21;
		oY = 36;
		cargoSpace = 800;
		cost = 100;
		maxHp = 100;
		cannonsSet = "1:1:1:1";
	}
	if (date == 1){
		shipName = "Slup";
		oX = 20;
		oY = 50;
		cargoSpace = 1600;
		cost = 250;
		maxHp = 250;
		cannonsSet = "1:2:1:2";
	}
	if (date == 2){
		shipName = "Bryg";
		oX = 30;
		oY = 60;
		cargoSpace = 5000;
		cost = 1001;
		maxHp = 500;
		cannonsSet = "1:3:2:3";
	}
}

int Ship::getCargoSpace(){
	return cargoSpace;
}

int Ship::getPrize(){
	return cost;
}

int Ship::getMaxHp(){
	return maxHp;
}

std::string Ship::getShipName(){
	return shipName;
}

sf::Vector2i Ship::getOriginC(){
	sf::Vector2i tmp;
	tmp.x = oX;
	tmp.y = oY;
	return tmp;
}

std::vector<std::string> Ship::getStats(){
	std::vector<std::string> tmp;
	std::ostringstream a;

	tmp.resize(0);

	tmp.push_back(shipName);

	a << cargoSpace;
	tmp.push_back(a.str());

	a.str("");

	a << cost;
	tmp.push_back(a.str());

	a.str("");
	a << maxHp;

	tmp.push_back(a.str());

	tmp.push_back(cannonsSet);

	return tmp;
}