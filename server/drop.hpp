#include <iostream>
#include <vector>

#include "characters.hpp"

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#define M_PI 3.14159265358979323846

class Drop{
	float x;
	float y;
	float ttl;
	bool toRemove;
	int goods1;
	int goods2;
	int goods3;

	friend sf::Packet& operator <<(sf::Packet& packet, const Drop& drop);
	friend sf::Packet& operator >>(sf::Packet& packet, Drop& drop);

public:
	Drop();
	~Drop();
	void update(std::vector <Character>&);
	void setStarterInfo(float, float, Character*);
	void setRemove();
	bool checkRemove();
	std::string getOL();
	sf::Vector2f getPos();
	std::vector <int> getPackage();
};