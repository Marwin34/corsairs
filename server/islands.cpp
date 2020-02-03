#include "islands.hpp"

Island::Island(){
	x = 0;
	y = 0;
	collideR = 0;
	name = "";
	goodsValues.resize(0);
}

Island::~Island(){

}

void Island::init(std::string data){
	if (data == "Conceicao"){
		name = "Conceicao";
		x = 500;
		y = 500;
		collideR = 150;
		width = 400;
		height = 400;

		//PRICES
		goodsValues.resize(5);
		goodsValues[0].x = 5;
		goodsValues[0].y = 3;
		goodsValues[1].x = 13;
		goodsValues[1].y = 12;
		goodsValues[2].x = 15;
		goodsValues[2].y = 8;
		goodsValues[3].x = 1;
		goodsValues[3].y = 1;
		goodsValues[4].x = 3;
		goodsValues[4].y = 2;
	}
	else if (data == "Dowsen"){
		name = "Dowsen";
		x = 2500;
		y = 2500;
		collideR = 150;
		width = 400;
		height = 400;

		//PRICES
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

float Island::getR(){
	return collideR;
}

std::vector<sf::Vector2i> &Island::getGoodsValues(){
	return goodsValues;
}