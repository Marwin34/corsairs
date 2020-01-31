#include "characters.hpp"

float calcDirAng(float mouseAng, float playerAng);
Character::Character(){

	x = 0;
	y = 0;

	mExp = 0;

	statistics.hp = 1;
	statistics.exp = 0;
	
	statistics.lvl = 0;
	statistics.gold = 0;
	statistics.goods1 = 0;
	statistics.goods2 = 0;
	statistics.goods3 = 0;
	statistics.cannonballs = 0;
	statistics.grenades = 0;
	currentAmmo = 0;
	
	up = false;
	right = false;
	down = false;
	left = false;
	lpm = false;
	restart = false;
	isLive = true;
	collide = false;
	lpmPressed = false;

	angle = 0;
	spdX = 0.0f;
	spdY = 0.0f;
	realSpdX = 0.0f;
	realSpdY = 0.0f;
	sails = 0.0f;
	speed = 0.0f;
	maxSpeed = 0.0f;

	model.init(0);
	cCargoSpace = model.getCargoSpace();
	dLogin.setCharSize(12);
	
	order.action = 4;
	order.count = 0;
	order.goodId = 6;
	order.shipId = 4;
}

Character::~Character(){

}

void Character::draw(sf::RenderWindow *win){
	if (isLive){
		models[statistics.shipId].setOrigin(model.getOriginC().x, model.getOriginC().y);
		win->draw(models[statistics.shipId]);
		win->draw(hpBar);
		dLogin.draw(win);
	}
}

void Character::update(){
	if (isLive){
		model.init(statistics.shipId);
		spdX = realSpdX;
		spdY = realSpdY;

		checkPosition();
		if(!collide)movingUpdate();

		sprite.setRotation(360 - angle);
		sprite.setPosition(x, y);

		models[0].setRotation(360 - angle);
		models[0].setPosition(x, y);
		models[1].setRotation(360 - angle);
		models[1].setPosition(x, y);
		models[2].setRotation(360 - angle);
		models[2].setPosition(x, y);

		//UPDATE HP BARA
		float hpPr = static_cast<float>(statistics.hp) / model.getMaxHp();
		hpBar.setScale(hpPr, 1);
		hpBar.setPosition(x, y - 60);

		dLogin.setPositionAndValue(x - (login.size() * 3.5), y - 80, login);
	}
}

void Character::movingUpdate(){
	//std::cout << x << " , " << y << std::endl;
	x += spdX;
	y += spdY;
}

void Character::checkPosition(){
	if (fabs(x - realX) > 0.1){
		//std::cout << " from " << x << " to " << realX << std::endl;
		x = realX;
	}
	if (fabs(y - realY) > 0.1){
		//std::cout << " from " << y << " to " << realY << std::endl;
		y = realY;
	}
}

void Character::eventHanlder(sf::Event *event){

	if (event->type == sf::Event::KeyReleased){
		if (event->key.code == sf::Keyboard::W) up = true;
		if (event->key.code == sf::Keyboard::S) down = true;
		if (event->key.code == sf::Keyboard::Num1) currentAmmo = 0;
		if (event->key.code == sf::Keyboard::Num2) currentAmmo = 1;
	}

	if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left) lpmPressed = true;
}

void Character::steer(float data1, float data2){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) right = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) left = true;

	if (lpmPressed){
		float mouseAngle = atan2(x - data1, y - data2) * 180 / M_PI;

		if ((calcDirAng(mouseAngle, angle) >= -18 && calcDirAng(mouseAngle, angle) <= 18) ||
			(calcDirAng(mouseAngle, angle) >= 45 && calcDirAng(mouseAngle, angle) <= 135) ||
			(calcDirAng(mouseAngle, angle) >= -135 && calcDirAng(mouseAngle, angle) <= -45) ||
			(calcDirAng(mouseAngle, angle) >= 162 || calcDirAng(mouseAngle, angle) <= -162)) lpm = true;
	}
}

void Character::resetBoolka(){
	up = false;
	right = false;
	down = false;
	left = false;
	lpm = false;
	lpmPressed = false;
}

void Character::porting(float data1, float data2, float data3){
	if (sqrtf(powf(data1 - x, 2) + powf(data2 - y, 2)) < data3) portingF = true;
	else portingF = false;
}

void Character::createTexture(AssetsManager &container){
	models[0].setTexture(container["Karakana"]);
	models[0].setOrigin(container["Karakana"].getSize().x / 2, container["Karakana"].getSize().y / 2);
	models[1].setTexture(container["Slup"]);
	models[1].setOrigin(container["Slup"].getSize().x / 2, container["Slup"].getSize().y / 2);
	models[2].setTexture(container["testShip"]);
	models[2].setOrigin(container["testShip"].getSize().x / 2, container["testShip"].getSize().y / 2);
	sprite.setTexture(container[model.getShipName()]);
	sprite.setOrigin(model.getOriginC().x, model.getOriginC().y);
	hpBar.setTexture(container["hpSmall"]);
	hpBar.setOrigin(container["hpSmall"].getSize().x / 2, container["hpSmall"].getSize().y / 2);
	dLogin.init(container.font());
}

void Character::updateShopOrder(std::vector<int> data1){
	if (data1.size() < 3){
		order.action = 4;
		order.count = 0;
		order.goodId = 6;
		order.shipId = 4;
	}
	else if (data1.size() == 3){

		order.action = data1[0];

		if (order.action == 0 || order.action == 1){
			order.goodId = data1[1];
			order.count = data1[2];
		}
		else if (order.action == 2){
			order.shipId = data1[1];
			order.count = data1[2];
		}
		else if (order.action == 3){
			order.shipId = data1[1];
			order.count = data1[2];
		}

	}
}

int Character::getAmmoP(){
	return currentAmmo;
}
int Character::getShipId(){
	return statistics.shipId;
}

bool Character::getUp(){
	return up;
}

bool Character::getRight(){
	return right;
}

bool Character::getDown(){
	return down;
}

bool Character::getLeft(){
	return left;
}

bool Character::doULive(){
	return isLive;
}

bool Character::getPortingF(){
	return portingF;
}

float Character::getAngle(){
	return angle;
}

float Character::getSails(){
	return sails;
}

std::string Character::getLogin(){
	return login;
}

std::string Character::getTextureName(){
	return model.getShipName();
}

sf::Vector2f Character::getPos(){
	sf::Vector2f pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

std::vector<int> Character::getInfo(){
	std::vector<int> table;
	table.push_back(statistics.exp);
	table.push_back(statistics.lvl);
	table.push_back(statistics.gold);
	table.push_back(model.getCargoSpace());
	table.push_back(statistics.goods1);
	table.push_back(statistics.goods2);
	table.push_back(statistics.goods3);
	table.push_back(statistics.cannonballs);
	table.push_back(statistics.grenades);
	table.push_back(statistics.hp);
	return table;
}

sf::Packet& operator <<(sf::Packet& packet, const Character& character){// OPERATOR WYSY£ANIA
	return packet	<< character.up 
					<< character.right 
					<< character.down 
					<< character.left 
					<< character.lpm
					<< character.currentAmmo
					<< character.order.action
					<< character.order.goodId
					<< character.order.shipId
					<< character.order.count;
}

sf::Packet& operator >>(sf::Packet& packet, Character& character){// OPERATOR ODBIERANIA
	return packet	>> character.login
					>> character.realX 
					>> character.realY 
					>> character.realSpdX 
					>> character.realSpdY 
					>> character.angle 
					>> character.sails
					>> character.speed
					>> character.maxSpeed
					>> character.statistics.shipId
					>> character.statistics.hp
					>> character.statistics.lvl
					>> character.statistics.exp
					>> character.statistics.gold
					>> character.statistics.goods1
					>> character.statistics.goods2
					>> character.statistics.goods3
					>> character.statistics.cannonballs
					>> character.statistics.grenades
					>> character.isLive
					>> character.collide;
}

float calcDirAng(float mouseAng, float playerAng){
	float dirAng = 0;

	if ((mouseAng - playerAng) > 180) dirAng = ((mouseAng - playerAng) - 180) - 180;
	else if ((mouseAng - playerAng) < -180) dirAng = 180 + (180 + (mouseAng - playerAng));
	else dirAng = mouseAng - playerAng;

	return dirAng;
}