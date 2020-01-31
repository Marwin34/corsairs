#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Network.hpp>

#include <iostream>
#include <vector>
#include <fstream>

#include "assets.hpp"
#include "gui.hpp"
#include "characters.hpp"
#include "bullets.hpp"
#include "islands.hpp"
#include "drop.hpp"

//using namespace tmx;

#define FRAME_RATE_LIMIT 100
#define SCRN_WIDTH 1024
#define SCRN_HEIGHT 768

struct Background {
	sf::Sprite sprite;
	float x, y;
};

class Game{
	sf::Clock mainClock;
	sf::Time mainTimer;
	sf::Time pingTime;
	sf::UdpSocket socket;
	sf::Packet packet;
	sf::IpAddress serwer;
	sf::RenderWindow window;
	sf::View view;
	sf::Vector2i mousePos;
	sf::Vector2f mousePosRelevant;

	std::string login;
	std::string password;

	enum state{
		loginScreen,
		inGame,
	};
	int status;
	int connectCnt;

	float wAngle;
	int wScale;
	unsigned int myPlayerIndex;

	bool run;
	bool logged;
	bool wantToLogOff;
	bool canLogOff;
	bool connectionOk;

	std::vector <Character> players;
	std::vector <Bullet> bullets; 
	std::vector <Island> archipelag;
	std::vector <Drop> floatingGoods;

	AssetsManager assets;

	Gui ui;
	Background image;

public:
	Game();
	~Game();
	void start();
	void receiveData();
	void sendData();
	void ping();
	void sendLogOff();
	void loadSerwerIp();
	void draw();
	void viewStatus();
	void imageUpdate();
	void sendGuiMessages();
	Island nearestIsland();
};