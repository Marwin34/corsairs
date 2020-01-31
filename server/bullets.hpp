#include <iostream>
#include <vector>

#include "characters.hpp"

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#define M_PI 3.14159265358979323846

class Bullet{
	int damage;
	float x;
	float y;
	float spdX;
	float spdY;
	float originSpdX;
	float originSpdY;
	float startX;
	float startY;
	float dstX;
	float dstY;
	float ttl;
	int cnt;
	bool toRemove;
	std::string oL;

	friend sf::Packet& operator <<(sf::Packet& packet, const Bullet& bullet);
	friend sf::Packet& operator >>(sf::Packet& packet, Bullet& bullet);

public:
	Bullet();
	~Bullet();
	void update(std::vector <Character>&);
	void setStarterInfo(float, float, Character*);
	void setRemove();
	bool checkRemove();
	int getDamage();
	std::string getOL();
	sf::Vector2f getPos();
};