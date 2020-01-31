#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Network.hpp>

#include <iostream>
#include <vector>
#include <ctime>

#include "characters.hpp"
#include "bullets.hpp"
#include "islands.hpp"
#include "drop.hpp"
#include "TxTDB\txtDb.hpp"

//using namespace tmx;

#define FRAME_RATE_LIMIT 100
#define SCRN_WIDTH 800
#define SCRN_HEIGHT 608

class Game{
	sf::Clock mainClock;
	sf::Time mainTimer; 
	sf::UdpSocket socket;
	sf::Packet packet; 
	float windAngle;
	int windScale;
	int windResetTick;
	int dbUpdateCnt;
	std::vector<std::string> messages;
	std::vector<std::string> pings;

	DatabaseManager database;

	std::vector <Character> logOffQueue;

	//sf::Window window;

	bool run;

	std::vector <Character> playersOnline;
	std::vector <Bullet> bullets;
	std::vector <Island> archipelag;
	std::vector <Drop> floatingGoods;

public:
	Game();
	~Game();
	void start();
	void sendData();
	void receiveData();
	void checkCollisions(Character*, Bullet*);
	void obstacleCollisions(Character*);
	void checkGathering(Character*, Drop*);
	Island nearestIsland(int);
};