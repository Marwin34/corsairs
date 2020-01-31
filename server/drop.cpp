#include "drop.hpp"

Drop::Drop(){
	x = 0.0f;
	y = 0.0f;
	ttl = 0.0f;
	toRemove = false;
	goods1 = 0;
	goods2 = 0;
	goods3 = 0;
}

Drop::~Drop(){

}

void Drop::update(std::vector <Character> &chars){
	//ROZPOCZECIE UODATE

}

void Drop::setStarterInfo(float data1, float data2, Character *origin){
	x = data1;
	y = data2;
	ttl = origin->getRange();
	std::vector <int > tmp;
	tmp = origin->initGoods();
	if (tmp.size() >= 3){
		goods1 = tmp[0];
		goods2 = tmp[1];
		goods3 = tmp[2];
	}
}

void Drop::setRemove(){
	toRemove = true;
}

bool Drop::checkRemove(){
	return toRemove;
}

sf::Vector2f Drop::getPos(){
	sf::Vector2f tmp;
	tmp.x = x;
	tmp.y = y;
	return tmp;
}

std::vector <int> Drop::getPackage(){
	std::vector<int> tmp;
	tmp.push_back(goods1);
	tmp.push_back(goods2);
	tmp.push_back(goods3);
	return tmp;
}

sf::Packet& operator <<(sf::Packet& packet, const Drop& drop){
	return packet << drop.x << drop.y;
}

sf::Packet& operator >>(sf::Packet& packet, Drop& drop)
{
	return packet >> drop.x >> drop.y;
}
