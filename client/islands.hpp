#include <iostream>
#include <vector>

#include <SFML\Graphics.hpp>
#include "assets.hpp"

class Island {
	float x;
	float y;
	float collideR;
	float width;
	float height;
	float pX;
	float pY;
	float portR;
	std::string name;
	sf::Sprite sprite;
	std::vector<sf::Vector2i> goodsValues;

public:
	Island();
	~Island();
	void init(std::string, AssetsManager&);
	void draw(sf::RenderWindow*);
	sf::Vector2f getPos();
	sf::Vector2f getSize();
	float getR();
	float getPortR();
	sf::Vector2f getPortCords();
	std::vector<sf::Vector2i> &getGoodsValues();
	std::string getName();
};