#include "inputs.hpp"


Input::Input(){
	x = 0;
	y = 0;
	width = 0;
	height = 24;
	string = "";
	sText = "";
	active = false;
	type = 0;
	animationCnt = 0;
}

Input::~Input(){

}

void Input::init(AssetsManager& data1, float data2, float data3, int data4, int data5){
	text.init(data1.font());
	text.setCharSize(14);
	text.setPositionAndValue(data2 + 1, data2, string);
	text.setColor(0,0,0);
	x = data2;
	y = data3;
	width = data4;
	type = data5;
}

void Input::update(sf::RenderWindow &win, float dX, float dY){
	float mPosX = (float)sf::Mouse::getPosition(win).x + dX - float(SCRN_WIDTH / 2);
	float mPosY = (float)sf::Mouse::getPosition(win).y + dY - float(SCRN_HEIGHT / 2);

	if (mPosX > dX + x && mPosX < dX + x + width && mPosY > dY + y && mPosY < dY + y + height){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) active = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) active = false;

	std::string toShow;
	toShow = sText;
	animationCnt++;
	if (animationCnt > 40) animationCnt = 0;
	if (active && animationCnt < 20) toShow += "|";
	text.setPositionAndValue(dX + x, dY + y, toShow);
}

void Input::eventHandler(sf::Event *event){
	if (active){
		if (event->type == sf::Event::TextEntered){
			animationCnt = 0; // ALWAYS SHOW CURSOR WHEN TYPING
			if (event->text.unicode == 8){ //BACKSPACE
				if (string.size()>0)
					string.erase(string.size() - 1, 1);
			}
			else if (event->text.unicode < 128 && event->text.unicode != 13)
			string += (char)event->text.unicode;

			std::string tmp = "";

			if (type == 0){
				if (string.size()>round(width / 7.5)){ // 7.5 = SYMBOL HEIGHT
					tmp = string.substr((string.size() - round(width / 7.5)));
				}
				else tmp = string;
			}
			else if (type == 1){
				for (unsigned int i = 0; i < string.size(); i++){
					if (i >= round(width / 7.5)) break;
					tmp += "*";
				}
			}
			sText = "";
			sText = tmp;
		}
	}
}

void Input::draw(sf::RenderWindow *win){
	text.draw(win);
}

void Input::clear(){
	string = "";
	sText = "";
}

std::string Input::value(){
	return string;
}

SliderInput::SliderInput(){
	x = 0;
	y = 0;
	width = 0;
	height = 24;
	maxValue = 0;
	cValue = 0;
	stepLenght = 0.0f;
	active = false;
	hoovered = false;
}

SliderInput::~SliderInput(){

}

void SliderInput::init(AssetsManager& data1, float data2, float data3, int data4){
	backdrop.setTexture(data1["valueInput"]);
	backdrop.setOrigin(data1["valueInput"].getSize().x / 2, data1["valueInput"].getSize().y / 2);
	sliderPointer.setTexture(data1["valuePointer"]);
	sliderPointer.setOrigin(data1["valuePointer"].getSize().x / 2, data1["valuePointer"].getSize().y / 2);
	showingValue.init(data1.font());
	showingValue.setCharSize(16);
	x = data2;
	y = data3;
	width = data4;
}

void SliderInput::update(sf::RenderWindow &win, float dX, float dY){
	float mPosX = (float)sf::Mouse::getPosition(win).x + dX - float(SCRN_WIDTH / 2);
	float mPosY = (float)sf::Mouse::getPosition(win).y + dY - float(SCRN_HEIGHT / 2);

	
	if (mPosX > dX + x - width / 2 && mPosX < dX + x + width / 2 && mPosY > dY + y - 17 && mPosY <= dY + y + height / 2 ){ 
		hoovered = true;
		mX = (float)sf::Mouse::getPosition(win).x - float(SCRN_WIDTH / 2) + float(width) / 2 + 1; 
	}
	else hoovered = false;

	stepLenght = (float)width / (float)maxValue;

	std::ostringstream a;
	a << cValue;
	if (cValue == 1) a << " sztuka.";
	else if (cValue >= 2 && cValue <= 3) a << " sztuki.";
	else a << " sztuk.";

	backdrop.setPosition(dX + x, dY + y);
	sliderPointer.setPosition(dX + x - width / 2 +  stepLenght * cValue, dY + y-5);
	showingValue.setPositionAndValue(dX + x - a.str().size() * 4.3, dY + y + 20, a.str());
}

void SliderInput::eventHandler(sf::Event *event){
	if (hoovered && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		cValue = mX / stepLenght;
	}
}

void SliderInput::draw(sf::RenderWindow *win){
	win->draw(backdrop);
	win->draw(sliderPointer);
	showingValue.draw(win);
}

void SliderInput::clear(){
	cValue = 0;
}

void SliderInput::setMaxValue(int data1){
	maxValue = data1;
}

int SliderInput::value(){
	return cValue;
}