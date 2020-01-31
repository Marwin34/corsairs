#include <iostream>

#include <SFML\Graphics.hpp>

#include "assets.hpp"
#include "cnt_txt_lib/cnt_txt.hpp"

#define SCRN_WIDTH 1024
#define SCRN_HEIGHT 768

class Button{
	sf::Sprite sprite;
	sf::Sprite spriteHoovered;
	float dX;
	float dY;
	float x;
	float y;
	int width;
	int height;
	bool hoovered;
	std::string string;
	Text text;
	bool active;
	bool drawF;
public:
	Button();
	~Button();
	void init(AssetsManager&, std::string, float, float);
	void posUpdate(float, float);
	void activeUpdate(sf::RenderWindow&);
	void checkHoover(float, float);
	void draw(sf::RenderWindow*);
	void setDrawFlag(bool);
	void eventHandler(sf::Event*);
	void activeReset();
	bool getDrawFlag();
	bool isActive();
};