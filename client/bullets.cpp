#include "bullets.hpp"

Bullet::Bullet(){
	x = 0.0f;
	y = 0.0f;
	realX = 0.0f;
	realY = 0.0f;
	startX = 0.0f;
	startY = 0.0f;
	originSpdX = 0.0f;
	originSpdY = 0.0f;
	dstX = 0.0f;
	dstY = 0.0f;
	spdX = 0.0f;
	spdY = 0.0f;
}

Bullet::~Bullet(){

}

void Bullet::createTexture(sf::Texture &data){
	sprite.setTexture(data);
	sprite.setOrigin(data.getSize().x / 2, data.getSize().y / 2);
	sprite.setPosition(x, y);
}


void Bullet::update(){
	checkPosition();

	x += originSpdX;
	y += originSpdY;

	dstX += originSpdX;
	dstY += originSpdY;

	startX += originSpdX;
	startY += originSpdY;

	float angleRad = atan2(startX - dstX, startY - dstY);

	spdX = -sin(angleRad) * 4;
	spdY = -cos(angleRad) * 4;

	x += spdX;
	y += spdY;

	sprite.setPosition(x, y);
}

void Bullet::checkPosition(){
	if (x != realX) x = realX;
	if (y != realY) y = realY;
}

void Bullet::draw(sf::RenderWindow *win){
	win->draw(sprite);
}

sf::Packet& operator <<(sf::Packet& packet, const Bullet& bullet){ // NIE UWZYWANY
	return packet << bullet.x << bullet.y << bullet.startX << bullet.startX << bullet.dstX << bullet.dstY;
}

sf::Packet& operator >>(sf::Packet& packet, Bullet& bullet)
{
	return packet >> bullet.realX >> bullet.realY >> bullet.startX >> bullet.startY >> bullet.dstX >> bullet.dstY >> bullet.originSpdX >> bullet.originSpdY;
}
