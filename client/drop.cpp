#include "drop.hpp"

Drop::Drop(){
	x = 0.0f;
	y = 0.0f;
}

Drop::~Drop(){

}

void Drop::createTexture(sf::Texture &data){
	sprite.setTexture(data);
	sprite.setOrigin(data.getSize().x / 2, data.getSize().y / 2);
	sprite.setPosition(x, y);
}


void Drop::update(){
	sprite.setPosition(x, y);
}

void Drop::draw(sf::RenderWindow *win){
	win->draw(sprite);
}

sf::Packet& operator <<(sf::Packet& packet, const Drop& drop){
	return packet << drop.x << drop.y;
}

sf::Packet& operator >>(sf::Packet& packet, Drop& drop)
{
	return packet >> drop.x >> drop.y;
}
