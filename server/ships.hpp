#include <iostream>
#include <vector>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#define M_PI 3.14159265358979323846

class Ship{
	int id;
	int prize;
	int maxHp;
	float shipSpeed;
	float cannonRange; 
	float height; 
	int cargoSpace;
	enum side {
		topSide,
		rightSide,
		downSide,
		leftSide,
	};
	std::vector <sf::Vector2f> cannonsT;
	std::vector <sf::Vector2f> cannonsR;
	std::vector <sf::Vector2f> cannonsD;
	std::vector <sf::Vector2f> cannonsL;

public:
	Ship();
	~Ship();
	void init(int);
	void calcualteSpawners(float, float, float);
	int getCargoSpace();
	int getPrize();
	int getMaxHp();
	int getMaxCargo();
	float getCannonRange();
	float getShipSpeed();
	float getHeight();
	std::vector <sf::Vector2f> getCannonsSpawner(int);
	std::vector <sf::Vector2f> getCollisinonsPoints(float, float, float);
};