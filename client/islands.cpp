#include "islands.hpp"

Island::Island(){
	x = 0;
	y = 0;
	collideR = 0;
	pX = 0;
	pY = 0;
	portR = 0;
	name = "";
	goodsValues.resize(0);
}

Island::~Island(){

}

void Island::init(std::string data1, AssetsManager &data2){
	if (data1 == "Conceicao"){
		name = "Conceicao";
		x = 500;
		y = 500;
		pX = 440;
		pY = 180;
		portR = 100;
		collideR = 150;
		width = 400;
		height = 400;
		sprite.setTexture(data2["island"]);
		sprite.setPosition(x - width, y - height);

		//ceny towarów
		goodsValues.resize(5);
		goodsValues[0].x = 5; // x cena kupna 
		goodsValues[0].y = 3; // y cena sprzedazy
		goodsValues[1].x = 13;
		goodsValues[1].y = 12;
		goodsValues[2].x = 15;
		goodsValues[2].y = 8;
		goodsValues[3].x = 1;
		goodsValues[3].y = 1;
		goodsValues[4].x = 3;
		goodsValues[4].y = 2;
	}
	if (data1 == "Dowsen"){
		name = "Dowsen";
		x = 2500;
		y = 2500;
		pX = 2440;
		pY = 2180;
		portR = 100;
		collideR = 150;
		width = 400;
		height = 400;
		sprite.setTexture(data2["island"]);
		sprite.setPosition(x - width, y - height);

		//ceny towarów
		goodsValues.resize(5);
		goodsValues[0].x = 15;
		goodsValues[0].y = 13;
		goodsValues[1].x = 3;
		goodsValues[1].y = 2;
		goodsValues[2].x = 15;
		goodsValues[2].y = 8;
		goodsValues[3].x = 1;
		goodsValues[3].y = 1;
		goodsValues[4].x = 3;
		goodsValues[4].y = 2;
	}
}

void Island::draw(sf::RenderWindow *win){
	win->draw(sprite);
}

sf::Vector2f Island::getPos(){
	sf::Vector2f tmp;
	tmp.x = x;
	tmp.y = y;
	return tmp;
}

sf::Vector2f Island::getSize(){
	sf::Vector2f tmp;
	tmp.x = width;
	tmp.y = height;
	return tmp;
}

sf::Vector2f Island::getPortCords(){
	sf::Vector2f tmp;
	tmp.x = pX;
	tmp.y = pY;
	return tmp;
}

float Island::getR(){
	return collideR;
}

float Island::getPortR(){
	return portR;
}

std::vector<sf::Vector2i> &Island::getGoodsValues(){
	return goodsValues;
}

std::string Island::getName(){
	return name;
}