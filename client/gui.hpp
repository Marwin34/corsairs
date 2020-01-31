#include <iostream>
#include <sstream>

#include <SFML\Graphics.hpp>

#include "assets.hpp"
#include "cnt_txt_lib/cnt_txt.hpp"
#include "characters.hpp"
#include "buttons.hpp"
#include "inputs.hpp"
#include "ships.hpp"

#define SCRN_WIDTH 1024
#define SCRN_HEIGHT 768

class Indicator:public sf::Drawable, public sf::Transformable{
	sf::VertexArray i_vertices;
	sf::VertexArray obr_vertices;
	sf::Texture i_tileset;
	sf::Texture i_tileset2;

	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;

public:

	void create(AssetsManager&);
	void set_scale(float);
	void draw_ind(sf::RenderWindow *);
};

class Gui{

	enum {
		loginScreen,
		inGame,
	};

	struct ShopMenu {
		int activeShip;
		int activeGood;
		int shopGoods[5];
		int goodsWeights[5];
		int action;
		int sellingPrize;
		int buyingPrize;
		int playerGold;
		int lastGold;
		int unUsedCargo;
		int toRepair;
		int messageCnt;
		bool visible;
		bool insertingValue;
		bool displayMessage;
		sf::Sprite shopBackdrop;
		Button shipIcon1;
		Button shipIcon2;
		Button shipIcon3;
		Button buyShip;
		Button closeShop;
		Button goods1;
		Button goods2;
		Button goods3;
		Button goods4;
		Button goods5;
		Button buyB;
		Button sellB;
		Button valueYesB;
		Button valueNoB;
		Button repairB;
		SliderInput goodsCount;
		SliderInput repairCount;
		Ship statsShips[3];
		Text shipsCompare;
		Text goodDescription;
		Text message;
	};

	float dX;
	float dY;
	float poleCnt;
	int unactive;
	int lOrR;
	int serverMessageCnt;
	int ammoPointerX;
	int status;
	int playerShip;
	sf::Font* font;
	sf::Sprite windCursor;
	sf::Sprite uiRBC;
	sf::Sprite uiM;
	sf::Sprite uiTRC;
	sf::Sprite loginMenu;
	sf::Sprite registerMenu;
	sf::Sprite ammoPointer;
	sf::Sprite pole0;
	sf::Sprite pole1;
	sf::Sprite pole2;
	sf::Sprite banner;
	sf::Sprite mainTheme;
	std::string messageText;
	Counter exp;
	Counter lvl;
	Counter gold;
	Counter cargo;
	Counter cannobalsCnt;
	Counter grenadesCnt;
	Text serverMessage;
	Button restart;
	Button loginB;
	Button endB;
	Button registerB;
	Button portB;
	Button change1B;
	Button  change2B;
	Input login;
	Input password;
	bool loginFlag;
	bool registerFlag;
	bool restartFlag;
	bool apkShutDown;
	bool showServerMessage;
	bool inPortRange;
	bool buyFlag;
	bool sellFlag;
	bool repairFlag;
	bool upgradeShip;
	ShopMenu shop;
	Indicator hpIndi;

public:
	Gui();
	~Gui();
	void draw(sf::RenderWindow*);
	void load(AssetsManager&);
	void update(Character*, sf::RenderWindow&, std::vector<sf::Vector2i>&);
	void updateStatus(int);
	void setWindCursorR(float);
	void eventUpdate(sf::Event*);
	void setMessage(std::string);
	void shopUpdate(float, float, sf::RenderWindow&, std::vector<sf::Vector2i>&);
	void shopPosUpdate(float, float);
	void shopDraw(sf::RenderWindow*);
	void shopRestart();
	void buttonsReset();
	bool restartMessage();
	bool sendLogin();
	bool terminateWindow();
	bool busy();
	std::vector <int> shopOrder();
	std::vector <std::string> loginMessage();
	std::vector <std::string> guiMessage();
};