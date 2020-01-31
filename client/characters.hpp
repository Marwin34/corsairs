#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#include "ships.hpp"
#include "assets.hpp"
#include "cnt_txt_lib\cnt_txt.hpp"

#define SCRN_WIDTH 1024
#define SCRN_HEIGHT 768

#pragma once

//#define M_PI 3.14159265358979323846

class Character{
	struct ShopOrder{
		int action;
		int goodId;
		int shipId;
		int count;
	};

	struct Stats {
		int hp;
		int x;
		int y;
		int lvl;
		int exp;
		int gold;
		int shipId;
		int goods1;
		int goods2;
		int goods3;
		int cannonballs;
		int grenades;
	};

	std::string login;
	sf::Sprite sprite;
	sf::Sprite hpBar;
	bool up;
	bool right;
	bool down;
	bool left;
	bool lpm;
	bool restart;
	bool isLive;
	bool collide;
	bool portingF;
	bool lpmPressed;
	float x;
	float y;
	float realX;
	float realY;
	float angle;
	float spdX;
	float spdY;
	float realSpdX;
	float realSpdY;
	float sails;
	float speed;
	float maxSpeed;
	int mExp;
	int cCargoSpace;
	int currentAmmo; // okresla urzywane obecnie ammo
	friend sf::Packet& operator <<(sf::Packet& packet, const Character& character);
	friend sf::Packet& operator >>(sf::Packet& packet, Character& character);
	Ship model;
	Text dLogin;
	Stats statistics;
	ShopOrder order;
	sf::Sprite models[3];

public:
	Character();
	~Character();
	void draw(sf::RenderWindow*);
	void resetBoolka();
	void update();
	void eventHanlder(sf::Event*);
	void steer(float, float);
	void setWindAngle(float);
	void setWindScale(int);
	void movingUpdate();
	void checkPosition();
	void createTexture(AssetsManager&);
	void porting(float, float, float);
	void updateShopOrder(std::vector<int>);
	int getAmmoP();
	int getShipId();
	bool getUp();
	bool getRight();
	bool getDown();
	bool getLeft();
	bool doULive();
	bool getPortingF();
	float getAngle();
	float getSails();
	std::string getLogin();
	std::string getTextureName();
	sf::Vector2f getPos();
	std::vector<int> getInfo();
};