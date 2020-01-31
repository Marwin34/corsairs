#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#pragma once

class Ship{
	std::string shipName;
	std::string cannonsSet;
	int oX;
	int oY;
	int cargoSpace;
	int cost;
	int maxHp;
	enum side {
		topSide,
		rightSide,
		downSide,
		leftSide,
	};
	std::vector < std::vector <float > > cannons;
	

public:
	Ship();
	~Ship();
	void init(int);
	int getCargoSpace();
	int getPrize();
	int getMaxHp();
	std::string getShipName();
	sf::Vector2i getOriginC();
	std::vector<std::string> getStats();
};