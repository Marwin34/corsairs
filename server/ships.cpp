#include "ships.hpp"

Ship::Ship(){
	id = 0;
	cannonRange = 0;
	shipSpeed = 0;
	cargoSpace = 0;
	height = 0;
	prize = 0;
	maxHp = 0;

	cannonsT.resize(0);
	cannonsR.resize(0);
	cannonsD.resize(0);
	cannonsL.resize(0);
}

Ship::~Ship(){

}

void Ship::init(int data){
	if (data == 0){
		prize = 100;
		id = 1;
		shipSpeed = 2.5f;
		cannonRange = 180.0f;
		cargoSpace = 800;
		maxHp = 100;
		height = 30;

		cannonsT.resize(1);
		cannonsR.resize(1);
		cannonsD.resize(1);
		cannonsL.resize(1);
	}
	if (data == 1){
		prize = 200;
		id = 2;
		shipSpeed = 2.9f;
		cannonRange = 200.0f;
		cargoSpace = 1600;
		maxHp = 250;
		height = 35;

		cannonsT.resize(1);
		cannonsR.resize(2);
		cannonsD.resize(1);
		cannonsL.resize(2);
	}
	if (data == 2){
		prize = 1001;
		id = 3;
		shipSpeed = 2.4f;
		cannonRange = 250.0f;
		cargoSpace = 5000;
		maxHp = 500;
		height = 40;

		cannonsT.resize(1);
		cannonsR.resize(3);
		cannonsD.resize(2);
		cannonsL.resize(3);
	}
}

void Ship::calcualteSpawners(float angle, float x, float y){
	//SET CANNONS POSITION
	if (id == 1){
		//FRONT CANNONS
		cannonsT[0].x = x + cos(-(angle + (M_PI / 2))) * 20;
		cannonsT[0].y = y + sin(-(angle + (M_PI / 2))) * 20;

		//RIGHT CANNONS
		cannonsR[0].x = x + cos(-(angle + (0))) * 20;
		cannonsR[0].y = y + sin(-(angle + (0))) * 20;

		//REAR CANNONS
		cannonsD[0].x = x + cos(-(angle + (M_PI / 2) * 3)) * 20;
		cannonsD[0].y = y + sin(-(angle + (M_PI / 2) * 3)) * 20;

		//LEFT CANNONS
		cannonsL[0].x = x + cos(-(angle + (M_PI))) * 20; 
		cannonsL[0].y = y + sin(-(angle + (M_PI))) * 20;

	}
	else if (id == 2){
		//FRONT CANNONS
		cannonsT[0].x = x + cos(-(angle + (M_PI / 2))) * 20;
		cannonsT[0].y = y + sin(-(angle + (M_PI / 2))) * 20;

		//RIGHT CANNONS
		cannonsR[0].x = x + cos(-(angle) + M_PI / 4) * 20;
		cannonsR[0].y = y + sin(-(angle) + M_PI / 4) * 20;

		cannonsR[1].x = x + cos(-(angle) - M_PI / 4) * 20;
		cannonsR[1].y = y + sin(-(angle) - M_PI / 4) * 20;

		//REAR CANNONS
		cannonsD[0].x = x + cos(-(angle + (M_PI / 2) * 3)) * 20;
		cannonsD[0].y = y + sin(-(angle + (M_PI / 2) * 3)) * 20;

		//LEFT CANNONS
		cannonsL[0].x = x + cos(-(angle + (M_PI)) + M_PI / 4) * 20;
		cannonsL[0].y = y + sin(-(angle + (M_PI)) + M_PI / 4) * 20;

		cannonsL[1].x = x + cos(-(angle + (M_PI)) - M_PI / 4) * 20;
		cannonsL[1].y = y + sin(-(angle + (M_PI)) - M_PI / 4) * 20;
	}
	else if (id == 3){
		//FRONT CANNONS
		cannonsT[0].x = x + cos(-(angle + (M_PI / 2))) * 20;
		cannonsT[0].y = y + sin(-(angle + (M_PI / 2))) * 20;

		//RIGHT CANNONS
		cannonsR[0].x = x + cos(-(angle + (M_PI / 4))) * 25;
		cannonsR[0].y = y + sin(-(angle + (M_PI / 4))) * 25;

		cannonsR[1].x = x + cos(-(angle)) * 20;
		cannonsR[1].y = y + sin(-(angle)) * 20;

		cannonsR[2].x = x + cos(-(angle - (M_PI / 4))) * 25;
		cannonsR[2].y = y + sin(-(angle - (M_PI / 4))) * 25;

		//REAR CANNONS
		cannonsD[0].x = x + cos(-(angle + (M_PI / 2)*3) + M_PI / 6) * 20;
		cannonsD[0].y = y + sin(-(angle + (M_PI / 2) * 3) + M_PI / 6) * 20;

		cannonsD[1].x = x + cos(-(angle + (M_PI / 2) * 3) - M_PI / 6) * 20;
		cannonsD[1].y = y + sin(-(angle + (M_PI / 2) * 3) - M_PI / 6) * 20;

		//LEFT CANNONS
		cannonsL[0].x = x + cos(-(angle + (M_PI / 4) * 3)) * 25;
		cannonsL[0].y = y + sin(-(angle + (M_PI / 4) * 3)) * 25;

		cannonsL[1].x = x + cos(-(angle + (M_PI))) * 20;
		cannonsL[1].y = y + sin(-(angle + (M_PI))) * 20;

		cannonsL[2].x = x + cos(-(angle + (M_PI / 4) * 5)) * 25;
		cannonsL[2].y = y + sin(-(angle + (M_PI / 4) * 5)) * 25;
	}
}

int Ship::getCargoSpace(){
	return cargoSpace;
}

int Ship::getPrize(){
	return prize;
}

int Ship::getMaxHp(){
	return maxHp;
}

int Ship::getMaxCargo(){
	if(id == 1){
		return 800;
	}
	else if (id == 2){
		return 1600;
	}
	else if (id == 3){
		return 5000;
	}
	else return 0;
}

float Ship::getCannonRange(){
	return cannonRange;
}

float Ship::getShipSpeed(){
	return shipSpeed;
}

float Ship::getHeight(){
	return height;
}

std::vector < sf::Vector2f > Ship::getCannonsSpawner(int data){
	if (data == 0){
		return cannonsT;
	}
	if (data == 1){
		return cannonsR;
	}
	if (data == 2){
		return cannonsD;
	}
	if (data == 3){
		return cannonsL;
	}
	std::vector < sf::Vector2f > a;
	return a;
}

std::vector < sf::Vector2f > Ship::getCollisinonsPoints(float angle, float x, float y){
	std::vector < sf::Vector2f > a;
	a.resize(2);

	float mainAngle = angle / 180 * M_PI;

	if (id == 1){
		a[0].x = x + cos(-(mainAngle + (M_PI / 2))) * 15;
		a[0].y = y + sin(-(mainAngle + (M_PI / 2))) * 15;

		a[1].x = x + cos(-(mainAngle + 3 * (M_PI / 2))) * 15;
		a[1].y = y + sin(-(mainAngle + 3 * (M_PI / 2))) * 15;
	}
	else if (id == 2){
		a[0].x = x + cos(-(mainAngle + (M_PI / 2))) * 20;
		a[0].y = y + sin(-(mainAngle + (M_PI / 2))) * 20;

		a[1].x = x + cos(-(mainAngle + 3 * (M_PI / 2))) * 15;
		a[1].y = y + sin(-(mainAngle + 3 * (M_PI / 2))) * 15;
	}
	else if (id == 3){
		a[0].x = x + cos(-(mainAngle + (M_PI / 2))) * 20;
		a[0].y = y + sin(-(mainAngle + (M_PI / 2))) * 20;

		a[1].x = x + cos(-(mainAngle + 3 * (M_PI / 2))) * 17;
		a[1].y = y + sin(-(mainAngle + 3 * (M_PI / 2))) * 17;
	}

	return a;
}