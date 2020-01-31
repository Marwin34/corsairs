#include "characters.hpp"

float calcDirAng(float mouseAng, float playerAng); // K¥TY

Character::Character(){
	x = 100;
	y = 0;

	collideDmgCnt = 0;
	currentAmmo = 0; // wskazuje ammo
	howMuch = 0; // o ile ujmujemy ammo
	stats.hp = 0;
	stats.lvl = 1;
	stats.exp = 0;
	stats.gold = 0;
	stats.goods1 = 0;
	stats.goods2 = 0;
	stats.goods2 = 0;
	stats.grenades = 0;
	stats.cannonballs = 0;
	stats.shipId = 0;

	angle = 0;
	windAngle = 0.0f;

	maxSpeed = 0.0f; // WYLICZANY W PETLI
	acceleration = 0.1f;
	speed = 0.0f;
	spdX = 0.0f;
	spdY = 0.0f;

	sails = 0.0f;

	wind = 0.0f;
	windScale = 0;

	up = false;
	right = false;
	down = false;
	left = false;
	lpm = false;
	restart = false;
	isLive = true;

	canFire = true;
	collide = false;
	fireCd = 0;

	mousePos.x = 0.0f;
	mousePos.y = 0.0f;

	ip = "";

	ship.init(0);
	ammunition[0] = 0;
	ammunition[1] = 0;

	order.action = 4;
	order.count = 0;
	order.goodId = 6;
}

Character::~Character(){

}

void Character::init(std::vector <int> data){
	if (data.size() > 0){
		x = data[0];
		y = data[1];
		stats.x = (int)x;
		stats.y = (int)y;
		stats.lvl = data[2];
		stats.exp = data[3];
		stats.hp = data[4];
		stats.gold = data[5];
		stats.goods1 = data[6];
		stats.goods2 = data[7];
		stats.goods3 = data[8];
		ammunition[0] = data[9];
		ammunition[1] = data[10];
		stats.cannonballs = ammunition[0];
		stats.grenades = ammunition[1];
		stats.shipId = data[11];
		ship.init(data[11]);
	}
}

void Character::update(float wind, float scale){
	windAngle = wind;
	windScale = scale;
	if (stats.hp < 0) isLive = false;
	if (isLive && ((x < -100 || x > 3100) || (y < -100 || y > 3100))) stats.hp -= 10;

	if (stats.exp >= getRequiredExp(stats.lvl)){
		stats.lvl += 1;
		stats.exp = 0;
	}
	if (!canFire){
		fireCd++;
		if (fireCd >= 100){
			canFire = true;
			fireCd = 0;
		}
	}
	
	ship.calcualteSpawners(angle / 180 * M_PI, x, y);

	stats.cannonballs = ammunition[0];
	stats.grenades = ammunition[1];

	positionUpdate();
	resetBoolka();
}

void Character::shoot(){
	ammunition[currentAmmo]-=howMuch;
	canFire = false;
}

void Character::positionUpdate(){
	if (isLive){
		if (up && sails < 1)	sails += 0.5f;
		if (down && sails > 0)	sails -= 0.5f;

		float windAngleRad = fabs(angle - windAngle) * M_PI / 180;
		wind = floor(cos(windAngleRad) * 10) / 10;

		maxSpeed = sails * (ship.getShipSpeed() + wind * windScale / 4);

		if (speed < maxSpeed){
			speed += acceleration;
		}
		if (speed > maxSpeed){
			speed -= acceleration;
		}
		if (speed < 0.1f) speed = 0.0f;

		if (left) angle += 1;
		if (right) angle -= 1;

		if (angle < -180) angle = 180;
		if (angle > 180) angle = -180;

		float angleRad = angle * M_PI / 180;

		if (collide){
			spdX = 0;
			spdY = 0;
			if (collideDmgCnt++ > 10){
				collideDmgCnt = 0;
				stats.hp -= 5;
			}
		}
		else {
			spdX = -sin(angleRad) * speed;
			spdY = -cos(angleRad) * speed;
		}

		x += spdX;
		y += spdY;

		stats.x = (int)x;
		stats.y = (int)y;
	}
}

void Character::onceAgain(){

	x = 1500;
	y = 1500;
	stats.x = (int)x;
	stats.y = (int)y;
	stats.hp = ship.getMaxHp() ;

	angle = 0;

	speed = 0.0f;
	spdX = 0.0f;
	spdY = 0.0f;

	sails = 0.0f;

	isLive = true;
}

void Character::reward(Character *data){
	stats.exp += data->getLvl() / stats.lvl * 10;
}

void Character::dealWithOrder(std::vector<sf::Vector2i> &data1){
	if (data1.size() == 5){
		if (order.action == 0){ // sprzedaz
			if (stats.gold + data1[order.goodId].y * order.count >= 9997){
				stats.gold = 9998;
			}
			else stats.gold += data1[order.goodId].y * order.count;
			
			if(order.goodId < 5){
				if (order.goodId == 0) stats.goods1 -= order.count;
				if (order.goodId == 1) stats.goods2 -= order.count;
				if (order.goodId == 2) stats.goods3 -= order.count;
				if (order.goodId == 3){
					stats.cannonballs -= order.count;
					ammunition[0] -= order.count;
				}
				if (order.goodId == 4) {
					stats.grenades -= order.count;
					ammunition[1] -= order.count;
				}
			}
			order.action = 4; // a takie zabezpiecznie ...
			order.count = 0;
			order.goodId = 6;
		}
		else if (order.action == 1){ // kupno
			stats.gold -= data1[order.goodId].x * order.count;
			if (order.goodId < 5) {
				if (order.goodId == 0) stats.goods1 += order.count;
				if (order.goodId == 1) stats.goods2 += order.count;
				if (order.goodId == 2) stats.goods3 += order.count;
				if (order.goodId == 3){
					stats.cannonballs += order.count;
					ammunition[0] += order.count;
				}
				if (order.goodId == 4) {
					stats.grenades += order.count;
					ammunition[1] += order.count;
				}
			}
			order.action = 4; // a takie zabezpiecznie ...
			order.count = 0;
			order.goodId = 6;
		}
		else if (order.action == 2){
			
			if (order.shipId < 3){
				Ship tmp;
				tmp.init(order.shipId);
				stats.gold -= tmp.getPrize(); 
				ship = tmp;
				stats.shipId = order.shipId;
				stats.hp = tmp.getMaxHp();
			}

			order.action = 4; // a takie zabezpiecznie ...
			order.count = 0;
			order.shipId = 4;
		}
		else if (order.action == 3){

			stats.hp += order.count;
			stats.gold -= order.count * 2;

			order.action = 4; // a takie zabezpiecznie ...
			order.count = 0;
			order.shipId = 4;
		}
	}
}

void Character::resetBoolka(){
	up = false;
	right = false;
	down = false;
	left = false;
	collide = false;
}

void Character::setId(unsigned int size){
	id = size;
}

void Character::setLogin(std::string data){
	login = data;
}

void Character::setIp(sf::IpAddress data){
	ip = data;
}

void Character::addDamage(int data){
	stats.hp -= data;
}

void Character::setCollide(){
	collide = true;
}

void Character::provide(int data1, int data2, int data3){
	if (data1 + data2 + data3 < ship.getMaxCargo() - stats.goods1 + stats.goods2 + stats.goods3 + stats.cannonballs + stats.grenades){
		stats.goods1 += data1;
		stats.goods2 += data2;
		stats.goods3 += data3;
	}
}

unsigned int Character::getId(){
	return id;
}

std::string Character::getLogin(){
	return login;
}

bool Character::willShoot(){
	if (lpm && canFire){
		float mouseAngle = atan2(x - mousePos.x, y - mousePos.y) * 180 / M_PI;

		if (calcDirAng(mouseAngle, angle) >= -18 && calcDirAng(mouseAngle, angle) <= 18) {
			if(ship.getCannonsSpawner(0).size() < ammunition[currentAmmo] ) return true;
		}
		if (calcDirAng(mouseAngle, angle) >= -135 && calcDirAng(mouseAngle, angle) <= -45) {
			if (ship.getCannonsSpawner(1).size() < ammunition[currentAmmo]) return true;
		}
		if (calcDirAng(mouseAngle, angle) >= 168 || calcDirAng(mouseAngle, angle) <= -168) {
			if (ship.getCannonsSpawner(2).size() < ammunition[currentAmmo]) return true;
		}
		if (calcDirAng(mouseAngle, angle) >= 45 && calcDirAng(mouseAngle, angle) <= 135) {
			if (ship.getCannonsSpawner(3).size() < ammunition[currentAmmo]) return true;
		}
	}
	return false;
}

bool Character::doULive(){
	return isLive;
}

bool Character::wantRestart(){
	return restart;
}

float Character::getRange(){
	return ship.getCannonRange();
}

float Character::getAngle(){
	return angle;
}

float Character::getShipHeight(){
	return ship.getHeight();
}

int Character::getRequiredExp(int data){
	if (data == 1) return 50;
	if (data == 2) return 100;
	if (data == 3) return 200;
	return 0;
}

int Character::getLvl(){
	return stats.lvl;
}

int Character::getLife(){
	return stats.hp;
}

int Character::getAmmoType(){
	return currentAmmo;
}

int Character::getShipId(){
	return stats.shipId;
}

sf::Vector2f Character::getPos(){
	sf::Vector2f pos;
	pos.x = x;
	pos.y = y;
	return pos;
}


sf::Vector2f Character::getMousePos(){
	sf::Vector2f mpos;
	mpos.x = mousePos.x;
	mpos.y = mousePos.y;
	return mpos;
}

sf::Vector2f Character::getSpeedVector(){
	sf::Vector2f speed;
	speed.x = spdX;
	speed.y = spdY;
	return speed;
}

sf::IpAddress Character::getIp(){
	return ip;
}

std::vector <sf::Vector2f > Character::getBulletsSpawners(){
	std::vector <sf::Vector2f > spawners;
	spawners.resize(0);
	if (lpm && canFire){
		float mouseAngle = atan2(x - mousePos.x, y - mousePos.y) * 180 / M_PI;

		if (calcDirAng(mouseAngle, angle) >= -18 && calcDirAng(mouseAngle, angle) <= 18) {
			if (ship.getCannonsSpawner(0).size() <= ammunition[currentAmmo]){
				spawners = ship.getCannonsSpawner(0);
				howMuch = spawners.size();
			}
		}
		if (calcDirAng(mouseAngle, angle) >= -135 && calcDirAng(mouseAngle, angle) <= -45) {
			if (ship.getCannonsSpawner(1).size() <= ammunition[currentAmmo]){
				spawners = ship.getCannonsSpawner(1);
				howMuch = spawners.size();
			}
		}
		if (calcDirAng(mouseAngle, angle) >= 168 || calcDirAng(mouseAngle, angle) <= -168) {
			if (ship.getCannonsSpawner(2).size() <= ammunition[currentAmmo]){
				spawners = ship.getCannonsSpawner(2);
				howMuch = spawners.size();
			}
		}
		if (calcDirAng(mouseAngle, angle) >= 45 && calcDirAng(mouseAngle, angle) <= 135) {
			if (ship.getCannonsSpawner(3).size() <= ammunition[currentAmmo]){
				spawners = ship.getCannonsSpawner(3);
				howMuch = spawners.size();
			}
		}
	}
	return spawners;
}

std::vector <sf::Vector2f > Character::getCollisionsPoints(){
	return ship.getCollisinonsPoints(angle, x, y);
}

Stats *Character::getStats(){
	return &stats;
}

std::vector <int> Character::initGoods(){
	std::vector<int> tmp;
	tmp.push_back(stats.goods1 / 4);
	stats.goods1 -= stats.goods1 / 4;
	tmp.push_back(stats.goods2 / 4);
	stats.goods2 -= stats.goods2 / 4;
	tmp.push_back(stats.goods3 / 4);
	stats.goods3 -= stats.goods3 / 4;
	return tmp;
}

sf::Packet& operator <<(sf::Packet& packet, const Character& character){ // OPERATOR WYSY£ANIA
	return packet	<< character.login
					<< character.x 
					<< character.y 
					<< character.spdX 
					<< character.spdY 
					<< character.angle 
					<< character.sails
					<< character.speed
					<< character.maxSpeed
					<< character.stats.shipId
					<< character.stats.hp 
					<< character.stats.lvl 
					<< character.stats.exp 
					<< character.stats.gold 
					<< character.stats.goods1
					<< character.stats.goods2
					<< character.stats.goods3
					<< character.stats.cannonballs
					<< character.stats.grenades
					<< character.isLive
					<< character.collide;
}

sf::Packet& operator >>(sf::Packet& packet, Character& character){ // OPERATOR ODBIERANIA
	return packet   >> character.restart
					>> character.up
					>> character.right
					>> character.down
					>> character.left
					>> character.lpm
					>> character.currentAmmo
					>> character.order.action
					>> character.order.goodId
					>> character.order.shipId
					>> character.order.count
					>> character.mousePos.x
					>> character.mousePos.y;
}

float calcDirAng(float mouseAng, float playerAng){
	float dirAng = 0;

	if ((mouseAng - playerAng) > 180) dirAng = ((mouseAng - playerAng) - 180) - 180;
	else if ((mouseAng - playerAng) < -180) dirAng = 180 + (180 + (mouseAng - playerAng));
	else dirAng = mouseAng - playerAng;

	return dirAng;
}