#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

#pragma once

#define COUNTER_SIZE 12
#define TEXT_SIZE 35

class Counter{

    sf::Text text;
    sf::Color color;

    char numberChar[5];

public:

	Counter(int = 255, int = 255, int = 255, int = COUNTER_SIZE);
	void initFont(sf::Font*);
    void setCharSize(int);
    void setColor(int,int,int);
    void setPosition(float,float);
    void setValue(int);
    void draw(sf::RenderWindow*);

};


class Text{

    sf::Text text;
    sf::Color color;

public:

	Text(int = 255, int = 255, int = 255, int = TEXT_SIZE);
	void init(sf::Font*);
    void setCharSize(int);
    void setColor(int,int,int);
    void setPositionAndValue(float,float,std::string);
    void draw(sf::RenderWindow*);

};

