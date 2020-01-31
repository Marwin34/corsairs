#include "game.hpp"

Game::Game(){
	mainClock.restart();
	mainTimer = sf::Time::Zero;

	run = true;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Client", sf::Style::Default, settings);
	view.setSize(SCRN_WIDTH, SCRN_HEIGHT);
	window.setFramerateLimit(60);

	socket.bind(50000);
	socket.setBlocking(false);

	players.resize(0);
	bullets.resize(0);
	floatingGoods.resize(0);

	logged = false;
	wantToLogOff = false;
	connectionOk = false;

	status = loginScreen;

	wAngle = 0;
	wScale = 0;

	mousePos.x = 0;
	mousePos.y = 0;
	mousePosRelevant.x = 0.0f;
	mousePosRelevant.y = 0.0f;

	assets.load();
	ui.load(assets);

	image.sprite.setTexture(assets["newOcean"]);
	image.x = 0;
	image.y = 0;
	image.sprite.setPosition(image.x, image.y);

	connectCnt = 0;
	archipelag.resize(2);
	archipelag[0].init("Conceicao", assets);
	archipelag[1].init("Dowsen", assets);
}

Game::~Game(){

}

void Game::start(){
	std::cout << "Client started" << std::endl;
	loadSerwerIp();
	ping();

	while (window.isOpen())
	{
		receiveData(); // odbiór danych z serwera
		if (connectCnt >= 50000){
			ui.setMessage("4");
			connectCnt = 1;
		}

		if (!logged){
			ui.updateStatus(loginScreen); // zmiana stanu gui
			wantToLogOff = false;
		}
		if (logged) ui.updateStatus(inGame);

		sf::Event event;
		while (window.pollEvent(event))
		{
			ui.eventUpdate(&event);

			if (logged && !ui.busy()){ // jeœli nie jestesmy w ui to player obs³u¿y event

				players[myPlayerIndex].eventHanlder(&event);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if(logged) wantToLogOff = true;
		}

		if (wantToLogOff) {
			sendLogOff();
		}

		mainTimer = mainClock.getElapsedTime();

		if (mainTimer.asMilliseconds() > 50 && !logged){
			Character tmp;
			ui.update(&tmp, window, archipelag[0].getGoodsValues());
			if (ui.terminateWindow()) window.close(); //wyjscie z gry

			view.move(tmp.getPos().x - view.getCenter().x, tmp.getPos().y - view.getCenter().y);
			
			draw();
			mainClock.restart();
			sendData();
		}
		else if (mainTimer.asMilliseconds() > 20 && logged){ 
			mousePos = sf::Mouse::getPosition(window);

			ui.setWindCursorR(360 - wAngle);

			mousePosRelevant.x = (float)mousePos.x + players[myPlayerIndex].getPos().x - (float)(SCRN_WIDTH / 2);
			mousePosRelevant.y = (float)mousePos.y + players[myPlayerIndex].getPos().y - (float)(SCRN_HEIGHT / 2);
			players[myPlayerIndex].steer(mousePosRelevant.x, mousePosRelevant.y);
			players[myPlayerIndex].updateShopOrder(ui.shopOrder());
			players[myPlayerIndex].porting(nearestIsland().getPortCords().x, nearestIsland().getPortCords().y, nearestIsland().getPortR());


			for (unsigned int i = 0; i < players.size(); i++){
				players[i].update();
			}

			for (unsigned int i = 0; i < bullets.size(); i++){
				bullets[i].update();
			}

			imageUpdate();
			ui.update(&players[myPlayerIndex], window, nearestIsland().getGoodsValues()); //aktualizacja ui
			view.move(players[myPlayerIndex].getPos().x - view.getCenter().x, players[myPlayerIndex].getPos().y - view.getCenter().y);

			draw();
			//std::cout << players[myPlayerIndex].getPos().x << " , " << players[myPlayerIndex].getPos().y << std::endl;
			mainClock.restart();
			sendData();
		}
	}
}

void Game::draw(){
	if (!logged){
		window.clear(sf::Color::Cyan);
		window.setView(view);
		ui.draw(&window);
		window.display();
	}
	else if (logged){
		window.clear(sf::Color::White);

		window.setView(view);

		window.draw(image.sprite);
		for (unsigned int i = 0; i < archipelag.size(); i++){
			archipelag[i].draw(&window);
		}

		for (unsigned int i = 0; i < floatingGoods.size(); i++){
			floatingGoods[i].draw(&window);
		}

		for (unsigned int i = 0; i < bullets.size(); i++){
			bullets[i].draw(&window);
		}

		for (unsigned int i = 0; i < players.size(); i++){
			players[i].draw(&window);
		}

		ui.draw(&window);
		window.display();
	}

}

void Game::receiveData(){

	packet.clear();
	 
	sf::IpAddress sender;
	unsigned short port;
	std::string type;

	if (socket.receive(packet, sender, port) == sf::Socket::Done){
		logged = false;
		packet >> type;

		if (type == "pong"){
			connectCnt = 0;
		}
		else if (type == "message"){
			std::string buffor;
			packet >> buffor;
			ui.setMessage(buffor);
		}
		else if (type == "data"){
			unsigned int size;
			packet >> wAngle >> wScale >> size;

			players.resize(size);

			for (unsigned int i = 0; i < size; i++){
				players[i].createTexture(assets);
				packet >> players[i];
				if (players[i].getLogin() == login){
					logged = true;
					myPlayerIndex = i;
				}
			}

			packet >> size;
			bullets.resize(size);

			for (unsigned int i = 0; i < size; i++){
				packet >> bullets[i];
				bullets[i].createTexture(assets["bullet"]);
			}

			packet >> size;
			floatingGoods.resize(size);

			for (unsigned int i = 0; i < size; i++){
				packet >> floatingGoods[i];
				floatingGoods[i].createTexture(assets["floatingGoods"]);
			}
		}
		
	}
	else if(connectCnt > 0)connectCnt++;
}

void Game::sendData(){

	packet.clear();
	unsigned short port = 50001;
	if (!logged){
		std::vector <std::string> tmp = ui.guiMessage();
		if (tmp.size() > 1){
			std::string type = tmp[0];

			login = tmp[1];
			password = tmp[2];

			packet << type << login << password;

			if (socket.send(packet, serwer, port) != sf::Socket::Done)
			{
				std::cout << "Blad wysylania" << std::endl;
			}
		}
	}
	else if(logged){
		std::string type = "data";

		packet << type << login;

		packet << ui.restartMessage() << players[myPlayerIndex] << mousePosRelevant.x << mousePosRelevant.y;

		if (socket.send(packet, serwer, port) != sf::Socket::Done)
		{
			std::cout << "Blad wysylania" << std::endl;
		}
		players[myPlayerIndex].resetBoolka(); // wyczyszczenie flag kalwiszy i lpma dla gracza
	}
}

void Game::ping(){

	packet.clear();
	unsigned short port = 50001;
	std::string type = "ping";

	packet << type << "1";
	connectCnt = 1;

	if (socket.send(packet, serwer, port) != sf::Socket::Done)
	{
		std::cout << "Blad wysylania" << std::endl;
	}
}

void Game::sendLogOff(){

	packet.clear();
	unsigned short port = 50001;
	std::string type = "logoff";

	packet << type << login;

	if (socket.send(packet, serwer, port) != sf::Socket::Done)
	{
		std::cout << "Blad wysylania" << std::endl;
	}
}

void Game::loadSerwerIp(){
	std::fstream file("resources/ip.txt", std::ios::in);
	if (file.is_open()){
		std::string str;
		file >> str;
		serwer = str;
	}
	file.close();

	std::cout << "Server ip: " << serwer << std::endl;
}

Island Game::nearestIsland(){
	if (sqrt(pow(players[myPlayerIndex].getPos().x - archipelag[0].getPos().x, 2) + pow(players[myPlayerIndex].getPos().y - archipelag[0].getPos().y, 2)) >
		sqrt(pow(players[myPlayerIndex].getPos().x - archipelag[1].getPos().x, 2) + pow(players[myPlayerIndex].getPos().y - archipelag[1].getPos().y, 2))){
		return archipelag[1];
	}
	else return archipelag[0];
}

void Game::viewStatus(){
	if (players[myPlayerIndex].getPos().x != view.getCenter().x) std::cout << " dif x = " << players[myPlayerIndex].getPos().x - view.getCenter().x;
	if (players[myPlayerIndex].getPos().y != view.getCenter().y) std::cout << " dif y = " << players[myPlayerIndex].getPos().y - view.getCenter().y;
}

void Game::imageUpdate(){
	image.x = players[myPlayerIndex].getPos().x / 2;
	image.y = players[myPlayerIndex].getPos().y / 2;
	//image.sprite.setPosition(image.x, image.y);
}