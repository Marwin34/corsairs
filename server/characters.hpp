#include <iostream>
#include <vector>

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#include "ships.hpp"

#pragma once

#define M_PI 3.14159265358979323846

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

class Character{
	struct ShopOrder{
		int action;
		int goodId;
		int shipId;
		int count;
	};

	sf::IpAddress ip;
	std::string login;
	int id;
	int collideDmgCnt;
	int currentAmmo;
	int howMuch;
	float x;
	float y;
	bool up;
	bool right;
	bool down;
	bool left;
	bool lpm;
	bool restart;
	bool isLive;
	bool collide;
	float speed;
	float angle;
	float maxSpeed;
	float acceleration;
	float sails;
	float spdX;
	float spdY;
	float windAngle;
	float wind;
	float canFire;
	int fireCd;
	int windScale;
	sf::Vector2f mousePos;
	Ship ship;
	Stats stats;
	ShopOrder order;
	int ammunition[2];
	friend sf::Packet& operator <<(sf::Packet& packet, const Character& character);
	friend sf::Packet& operator >>(sf::Packet& packet, Character& character);

public:
	Character();
	~Character();
	void init(std::vector <int>);
	void resetBoolka();
	void update(float, float);
	void setId(unsigned int);
	void setLogin(std::string);
	void setIp(sf::IpAddress);
	void positionUpdate();
	void shoot();
	void addDamage(int);
	void reward(Character*);
	void onceAgain();
	void setCollide();
	void dealWithOrder(std::vector<sf::Vector2i>&);
	void provide(int, int, int);
	unsigned int getId();
	std::string getLogin();
	bool willShoot();
	bool doULive();
	bool wantRestart();
	float getMouseAngle();
	float getRange();
	float getAngle();
	float getShipHeight();
	int getLvl();
	int getLife();
	int getAmmoType();
	int getShipId();
	sf::Vector2f getPos();
	sf::Vector2f getMousePos();
	sf::Vector2f getSpeedVector();
	sf::IpAddress getIp();
	std::vector <sf::Vector2f > getBulletsSpawners();
	std::vector <sf::Vector2f > getCollisionsPoints();
	int getRequiredExp(int);
	Stats *getStats();
	std::vector <int> initGoods();
};