#include "buttons.hpp"

Button::Button(){
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	hoovered = false;
	drawF = true;
	active = false;
}

Button::~Button(){

}

void Button::init(AssetsManager &data1, std::string data2, float data3, float data4){
	if (data2 == "restart"){
		sprite.setTexture(data1["restart"]);
		spriteHoovered.setTexture(data1["restartH"]);
		width = data1["restart"].getSize().x;
		height = data1["restart"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "login"){
		sprite.setTexture(data1["login"]);
		spriteHoovered.setTexture(data1["loginH"]);
		width = data1["login"].getSize().x;
		height = data1["login"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "end"){
		sprite.setTexture(data1["end"]);
		spriteHoovered.setTexture(data1["endH"]);
		width = data1["end"].getSize().x;
		height = data1["end"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "register"){
		sprite.setTexture(data1["create"]);
		spriteHoovered.setTexture(data1["createH"]);
		width = data1["create"].getSize().x;
		height = data1["create"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "change"){
		sprite.setTexture(data1["change"]);
		spriteHoovered.setTexture(data1["change"]);
		width = data1["change"].getSize().x;
		height = data1["change"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "port"){
		sprite.setTexture(data1["port"]);
		spriteHoovered.setTexture(data1["portH"]);
		width = data1["port"].getSize().x;
		height = data1["port"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "shipIcon1"){
		sprite.setTexture(data1["shipIcon1"]);
		spriteHoovered.setTexture(data1["shipIcon1H"]);
		width = data1["shipIcon1"].getSize().x;
		height = data1["shipIcon1"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "shipIcon2"){
		sprite.setTexture(data1["shipIcon2"]);
		spriteHoovered.setTexture(data1["shipIcon2H"]);
		width = data1["shipIcon2"].getSize().x;
		height = data1["shipIcon2"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "shipIcon3"){
		sprite.setTexture(data1["shipIcon3"]);
		spriteHoovered.setTexture(data1["shipIcon3H"]);
		width = data1["shipIcon3"].getSize().x;
		height = data1["shipIcon3"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "goods1"){
		sprite.setTexture(data1["goods1"]);
		spriteHoovered.setTexture(data1["goods1H"]);
		width = data1["goods1"].getSize().x;
		height = data1["goods1"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "goods2"){
		sprite.setTexture(data1["goods2"]);
		spriteHoovered.setTexture(data1["goods2H"]);
		width = data1["goods2"].getSize().x;
		height = data1["goods2"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "goods3"){
		sprite.setTexture(data1["goods3"]);
		spriteHoovered.setTexture(data1["goods3H"]);
		width = data1["goods3"].getSize().x;
		height = data1["goods3"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "goods4"){
		sprite.setTexture(data1["goods4"]);
		spriteHoovered.setTexture(data1["goods4H"]);
		width = data1["goods4"].getSize().x;
		height = data1["goods4"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "goods5"){
		sprite.setTexture(data1["goods5"]);
		spriteHoovered.setTexture(data1["goods5H"]);
		width = data1["goods5"].getSize().x;
		height = data1["goods5"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "buy"){
		sprite.setTexture(data1["buyB"]);
		spriteHoovered.setTexture(data1["buyBH"]);
		width = data1["buyB"].getSize().x;
		height = data1["buyB"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "sell"){
		sprite.setTexture(data1["sellB"]);
		spriteHoovered.setTexture(data1["sellBH"]);
		width = data1["sellB"].getSize().x;
		height = data1["sellB"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "closeWindow"){
		sprite.setTexture(data1["closeWindow"]);
		spriteHoovered.setTexture(data1["closeWindowH"]);
		width = data1["closeWindow"].getSize().x;
		height = data1["closeWindow"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "smallYes"){
		sprite.setTexture(data1["smallYes"]);
		spriteHoovered.setTexture(data1["smallYesH"]);
		width = data1["smallYes"].getSize().x;
		height = data1["smallYes"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "smallNo"){
		sprite.setTexture(data1["smallNo"]);
		spriteHoovered.setTexture(data1["smallNoH"]);
		width = data1["smallNo"].getSize().x;
		height = data1["smallNo"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "repair"){
		sprite.setTexture(data1["repair"]);
		spriteHoovered.setTexture(data1["repairH"]);
		width = data1["repair"].getSize().x;
		height = data1["repair"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "loginForm"){
		sprite.setTexture(data1["changeLogin"]);
		spriteHoovered.setTexture(data1["changeLoginH"]);
		width = data1["changeLogin"].getSize().x;
		height = data1["changeLogin"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
	else if (data2 == "registerForm"){
		sprite.setTexture(data1["changeRegister"]);
		spriteHoovered.setTexture(data1["changeRegisterH"]);
		width = data1["changeRegister"].getSize().x;
		height = data1["changeRegister"].getSize().y;
		x = data3;
		y = data4;
		string = data2;
	}
}

void Button::posUpdate(float data1, float data2){
	dX = data1;
	dY = data2;

	sprite.setPosition(dX + x, dY + y);
	spriteHoovered.setPosition(dX + x, dY + y);
	text.setPositionAndValue(x + dX + (string.size() * 3.5), y + dY + 5, string);
}

void Button::activeUpdate(sf::RenderWindow &win){

	float mPosX = (float)sf::Mouse::getPosition(win).x + dX - float(SCRN_WIDTH / 2);
	float mPosY = (float)sf::Mouse::getPosition(win).y + dY - float(SCRN_HEIGHT / 2);

	if (mPosX > dX + x && mPosX < dX + x + width && mPosY > dY + y && mPosY < dY + y + height)
		hoovered = true;
	else hoovered = false;
}


void Button::setDrawFlag(bool data){
	if (data == 0) drawF = false;
	else if (data == 1) drawF = true;
}

void Button::draw(sf::RenderWindow *win){
	if (drawF){
		if (!hoovered) win->draw(sprite);
		else win->draw(spriteHoovered);
		text.draw(win);
	}
}

void Button::eventHandler(sf::Event *event){

	if (hoovered && event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left) {
		active = true;
	}
	else active = false;
}

void Button::activeReset(){
	active = false;
}

bool Button::getDrawFlag(){
	return drawF;
}

bool Button::isActive(){
	return active;
}