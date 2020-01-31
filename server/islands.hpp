#include <iostream>
#include <vector>

#include <SFML\Network.hpp>

class Island {
	float x;
	float y;
	float collideR;
	float width;
	float height;
	std::string name;
	std::vector<sf::Vector2i> goodsValues;

public:
	Island();
	~Island();
	void init(std::string);
	sf::Vector2f getPos();
	sf::Vector2f getSize();
	float getR();
	std::vector<sf::Vector2i> &getGoodsValues();
};