#include <iostream>
#include <sstream>

#include <SFML\Graphics.hpp>

#include "assets.hpp"
#include "cnt_txt_lib/cnt_txt.hpp"

#define SCRN_WIDTH 1024
#define SCRN_HEIGHT 768

class Input{
	float x;
	float y;
	int width;
	int height;
	int animationCnt;
	std::string string;
	std::string sText;
	Text text;
	bool active;
	int type;
public:
	Input();
	~Input();
	void init(AssetsManager&, float, float, int, int);
	void update(sf::RenderWindow&, float, float);
	void eventHandler(sf::Event*);
	void draw(sf::RenderWindow*);
	void clear();
	std::string value();
};

class SliderInput{
	float x;
	float y;
	float mX;
	float stepLenght;
	int width;
	int height;
	int maxValue;
	int cValue;
	bool active;
	bool hoovered;
	sf::Sprite backdrop;
	sf::Sprite sliderPointer;
	Text showingValue;
public:
	SliderInput();
	~SliderInput();
	void init(AssetsManager&, float, float, int);
	void update(sf::RenderWindow&, float, float);
	void eventHandler(sf::Event*);
	void draw(sf::RenderWindow*);
	void clear();
	void setMaxValue(int);
	int value();
};