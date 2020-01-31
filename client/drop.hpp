#include <iostream>
#include <vector>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#define M_PI 3.14159265358979323846

class Drop{
	float x;
	float y;
	sf::Sprite sprite;

	friend sf::Packet& operator <<(sf::Packet& packet, const Drop& drop);
	friend sf::Packet& operator >>(sf::Packet& packet, Drop& drop);

public:
	Drop();
	~Drop();
	void update();
	void createTexture(sf::Texture&);
	void draw(sf::RenderWindow*);
};