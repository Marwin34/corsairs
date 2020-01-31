#include <iostream>
#include <vector>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#define M_PI 3.14159265358979323846

class Bullet{
	float x;
	float y;
	float realX;
	float realY;
	float spdX;
	float spdY;
	float originSpdX;
	float originSpdY;
	float startX;
	float startY;
	float dstX;
	float dstY;
	sf::Sprite sprite;

	friend sf::Packet& operator <<(sf::Packet& packet, const Bullet& bullet);
	friend sf::Packet& operator >>(sf::Packet& packet, Bullet& bullet);

public:
	Bullet();
	~Bullet();
	void update();
	void checkPosition();
	void createTexture(sf::Texture&);
	void draw(sf::RenderWindow*);
};