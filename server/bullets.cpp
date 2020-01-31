#include "bullets.hpp"

Bullet::Bullet(){
	x = 0.0f;
	y = 0.0f;
	startX = 0.0f;
	startY = 0.0f;
	dstX = 0.0f;
	dstY = 0.0f;
	spdX = 0.0f;
	spdY = 0.0f;
	originSpdX = 0.0f;
	originSpdY = 0.0f;
	ttl = 0.0f;
	toRemove = false;
	oL = "";
	damage = 10;
}

Bullet::~Bullet(){

}

void Bullet::update(std::vector <Character> &chars){

	x += originSpdX;
	y += originSpdY;

	dstX += originSpdX;
	dstY += originSpdY;

	startX += originSpdX;
	startY += originSpdY;

	//ROZPOCZECIE UODATE

	float angleRad = atan2(startX - dstX, startY - dstY);

	spdX = -sin(angleRad) * 4;
	spdY = -cos(angleRad) * 4;

	x += spdX;
	y += spdY;

	for (unsigned int i = 0; i < chars.size(); i++){
		if (chars[i].getLogin() == oL){
			if (sqrtf(powf(x - chars[i].getPos().x, 2) + powf(y - chars[i].getPos().y, 2)) > ttl || sqrtf(powf(x - dstX, 2) + powf(y - dstY, 2)) < 5) toRemove = true;
		}
	}
}
 
void Bullet::setStarterInfo(float data1, float data2, Character *origin){
	x = data1;
	y = data2;
	startX = x;
	startY = y;
	dstX = origin->getMousePos().x;
	dstY = origin->getMousePos().y;
	ttl = origin->getRange();
	originSpdX = origin->getSpeedVector().x;
	originSpdY = origin->getSpeedVector().y;
	oL = origin->getLogin();
	if (origin->getAmmoType() == 0){
		damage *= 1;
	}
	else if (origin->getAmmoType() == 1){
		damage *= 1.5; 
	}
}

void Bullet::setRemove(){
	toRemove = true;
}

bool Bullet::checkRemove(){
	return toRemove;
}

int Bullet::getDamage(){
	return damage;
}

std::string Bullet::getOL(){
	return oL;
}

sf::Vector2f Bullet::getPos(){
	sf::Vector2f tmp;
	tmp.x = x;
	tmp.y = y;
	return tmp;
}

sf::Packet& operator <<(sf::Packet& packet, const Bullet& bullet){
	return packet << bullet.x << bullet.y << bullet.startX << bullet.startY << bullet.dstX << bullet.dstY << bullet.originSpdX << bullet.originSpdY;
}

sf::Packet& operator >>(sf::Packet& packet, Bullet& bullet)
{
	return packet >> bullet.x >> bullet.y;
}
