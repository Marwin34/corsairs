#include "cnt_txt.hpp"


Counter::Counter(int red, int green, int blue, int charSize){
    text.setString("0");
    text.setCharacterSize(charSize);
    color.r=red;
    color.g=green;
    color.b=blue;
    text.setFillColor(color);

}

void Counter::initFont(sf::Font *font){
	text.setFont(*font);
}

void Counter::setCharSize(int charSize){
    text.setCharacterSize(charSize);
}

void Counter::setColor(int red, int green, int blue){
    color.r=red;
    color.g=green;
    color.b=blue;
    text.setFillColor(color);
}

void Counter::setPosition(float x, float y){
    text.setPosition(x,y);
}
void Counter::setValue(int value){
    _itoa_s(value,numberChar,10);
    text.setString(numberChar);
}

void Counter::draw(sf::RenderWindow* win){
    win->draw(text);
}

Text::Text(int red, int green, int blue, int charSize){
    text.setString("NONE");
    //text.setFont(font);
    text.setCharacterSize(charSize);
    color.r=red;
    color.g=green;
    color.b=blue;
    text.setFillColor(color);
}

void Text::init(sf::Font *font){
	text.setFont(*font);
}

void Text::setCharSize(int charSize){
    text.setCharacterSize(charSize);
}

void Text::setColor(int red, int green, int blue){
    color.r=red;
    color.g=green;
    color.b=blue;
    text.setFillColor(color);
}

void Text::setPositionAndValue(float x, float y, std::string textString){
    text.setPosition(x,y);
    text.setString(textString);
}

void Text::draw(sf::RenderWindow* win){
    win->draw(text);
}
