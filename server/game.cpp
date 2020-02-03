#include "game.hpp"

Game::Game(){
	mainClock.restart();
	mainTimer = sf::Time::Zero; 
	std::srand(std::time(0));

	run = true;

	socket.bind(50001);
	socket.setBlocking(false); 

	playersOnline.resize(0);
	bullets.resize(0);
	logOffQueue.resize(0);
	floatingGoods.resize(0);

	windResetTick = 0;
	windAngle = (std::rand() % 360) + 0;
	windAngle -= 180;
	windScale = (std::rand() % 3) + 1;
	dbUpdateCnt = 0;
	messages.resize(0);
	pings.resize(0);
	archipelag.resize(2);
	archipelag[0].init("Conceicao");
	archipelag[1].init("Dowsen");
}

Game::~Game(){

}

void Game::start(){
	std::cout << "Serwer started" << std::endl;

	while (run){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) run = false;
		receiveData();
		mainTimer = mainClock.getElapsedTime();

		if (mainTimer.asMilliseconds() > 20){
			if (windResetTick > 6000){
				windAngle = (std::rand() % 360) + 0;
				windAngle -= 180;
				windScale = (std::rand() % 3) + 1;
				windResetTick = 0;
			}
			if (dbUpdateCnt > 3000){
				for (unsigned int i = 0; i < playersOnline.size(); i++){
					database.update(playersOnline[i].getStats(), playersOnline[i].getLogin());
				}
				dbUpdateCnt = 0;
			}

			std::cout << "Liczba graczy online: " << playersOnline.size() << std::endl;

			for (unsigned int i = 0; i < bullets.size(); i++){
				if (bullets[i].checkRemove()) bullets.erase(bullets.begin() + i);
			}

			for (unsigned int i = 0; i < bullets.size(); i++){
				bullets[i].update(playersOnline);
			}

			for (unsigned int i = 0; i < floatingGoods.size(); i++){
				if (floatingGoods[i].checkRemove()) floatingGoods.erase(floatingGoods.begin() + i);
			}

			for (unsigned int i = 0; i < playersOnline.size(); i++){
				obstacleCollisions(&playersOnline[i]);
				playersOnline[i].update(windAngle, windScale);
				playersOnline[i].dealWithOrder(nearestIsland(i).getGoodsValues());
				if (playersOnline[i].wantRestart() && !playersOnline[i].doULive()) playersOnline[i].onceAgain();
				std::vector <sf::Vector2f> tmpV;
				tmpV = playersOnline[i].getBulletsSpawners();
				if (tmpV.size() > 0 && playersOnline[i].doULive()){
					playersOnline[i].shoot();
					for (unsigned int j = 0; j < tmpV.size(); j++){
						Bullet tmp;
						tmp.setStarterInfo(tmpV[j].x, tmpV[j].y, &playersOnline[i]);
						bullets.push_back(tmp);
					}
				}
			}

			for (unsigned int i = 0; i < playersOnline.size(); i++){
				if (!playersOnline[i].doULive()) continue;
				for (unsigned int j = 0; j < floatingGoods.size(); j++){
					checkGathering(&playersOnline[i], &floatingGoods[j]);
				}
			}

			for (unsigned int i = 0; i < playersOnline.size(); i++){
				if (!playersOnline[i].doULive()) continue;
				for (unsigned int j = 0; j < bullets.size(); j++){
					checkCollisions(&playersOnline[i], &bullets[j]);
				}
			}

			sendData();
			mainClock.restart();
			windResetTick++;
			dbUpdateCnt++;
		}
	}
}

void Game::receiveData(){

	packet.clear();

	sf::IpAddress sender;
	unsigned short port;
	std::string type = "";

	if (socket.receive(packet, sender, port) == sf::Socket::Done)
	{
		packet >> type;

		if (type == "ping"){

			std::string buffor;
			packet >> buffor;

			pings.push_back(sender.toString());
			std::cout << sender << std::endl;
		}
		else if (type == "register"){
			
			std::string lBuffor;
			std::string pBuffor;
			packet >> lBuffor >> pBuffor;

			messages.push_back(sender.toString());
			messages.push_back(database.registerNewObject(lBuffor, pBuffor));

		}
		else if (type == "login"){

			bool notLogged = true;
			std::string lBuffor;
			std::string pBuffor;
			packet >> lBuffor >> pBuffor;

			for (unsigned int i = 0; i < playersOnline.size(); i++){
				if (playersOnline[i].getLogin() == lBuffor) notLogged = false;
			}
			if (notLogged){
				std::vector <int> st = database.login(lBuffor, pBuffor);
				if (st.size() > 1){
					Character tmp;
					tmp.setLogin(lBuffor);
					tmp.setIp(sender);
					tmp.init(st);
					playersOnline.push_back(tmp);
				}
				else {
					messages.push_back(sender.toString());
					messages.push_back("0"); 
				}
			}
		}
		else if (type == "data"){
			std::string login;
			packet >> login;
			for (unsigned int i = 0; i < playersOnline.size(); i++){
				if (playersOnline[i].getLogin() == login) packet >> playersOnline[i];
			}
		}
		else if (type == "logoff"){
			std::string buffor;
			packet >> buffor;
			for (unsigned int j = 0; j < playersOnline.size(); j++){
				if (playersOnline[j].getLogin() == buffor){
					logOffQueue.push_back(playersOnline[j]);
					database.update(playersOnline[j].getStats(), playersOnline[j].getLogin());
					playersOnline.erase(playersOnline.begin() + j);
				}
			}
		}
	}
}

void Game::sendData(){

	packet.clear();

	unsigned short port = 50000;
	std::string type = "data";

	packet << type << windAngle << windScale << playersOnline.size();
	for (unsigned int i = 0; i < playersOnline.size(); i++){
		packet << playersOnline[i];
	}
	packet << bullets.size();

	for (unsigned int i = 0; i < bullets.size(); i++){
		packet << bullets[i];
	}

	packet << floatingGoods.size();

	for (unsigned int i = 0; i < floatingGoods.size(); i++){
		packet << floatingGoods[i];
	}

	for (unsigned int i = 0; i < playersOnline.size(); i++){
		if (socket.send(packet, playersOnline[i].getIp(), port) != sf::Socket::Done)
		{
			std::cout << "Blad wysylania" << std::endl;
		}
	}

	for (unsigned int i = 0; i < logOffQueue.size(); i++){
		if (socket.send(packet, logOffQueue[i].getIp(), port) != sf::Socket::Done)
		{
			std::cout << "Blad wysylania" << std::endl;
		}
	}
	logOffQueue.resize(0);

	for (unsigned int i = 0; i < messages.size(); i+=2){
		packet.clear();
		type = "message";
		packet << type << messages[i + 1];
		if (socket.send(packet, messages[i], port) != sf::Socket::Done)
		{
			std::cout << "Blad wysylania" << std::endl;
		}
	}
	messages.resize(0);

	for (unsigned int i = 0; i < pings.size(); i += 2){
		packet.clear();
		type = "pong";
		packet << type;
		if (socket.send(packet, pings[i], port) != sf::Socket::Done)
		{
			std::cout << "Blad wysylania" << std::endl;
		}
	}
	pings.resize(0);
}

void Game::checkCollisions(Character *data1, Bullet *data2){
	if (data1->getLogin() != data2->getOL()){
		if (data1->getShipId() == 0){
			if (sqrtf(powf(data1->getPos().x - data2->getPos().x, 2) + powf(data1->getPos().y - data2->getPos().y, 2)) < 18 ||
				sqrtf(powf(data1->getCollisionsPoints()[0].x - data2->getPos().x, 2) + powf(data1->getCollisionsPoints()[0].y - data2->getPos().y, 2)) < 18 ||
				sqrtf(powf(data1->getCollisionsPoints()[1].x - data2->getPos().x, 2) + powf(data1->getCollisionsPoints()[1].y - data2->getPos().y, 2)) < 18){
				data1->addDamage(data2->getDamage());
				if (data1->getLife() < 0){

					Drop tmp;
					tmp.setStarterInfo(data1->getPos().x, data1->getPos().y, data1);
					floatingGoods.push_back(tmp);

					for (unsigned int i = 0; i < playersOnline.size(); i++){
						if (playersOnline[i].getLogin() == data2->getOL())playersOnline[i].reward(data1);
					}
				}
				data2->setRemove();
			}
		}
		else if (data1->getShipId() == 1){
			if (sqrtf(powf(data1->getPos().x - data2->getPos().x, 2) + powf(data1->getPos().y - data2->getPos().y, 2)) < 20 ||
				sqrtf(powf(data1->getCollisionsPoints()[0].x - data2->getPos().x, 2) + powf(data1->getCollisionsPoints()[0].y - data2->getPos().y, 2)) < 20 ||
				sqrtf(powf(data1->getCollisionsPoints()[1].x - data2->getPos().x, 2) + powf(data1->getCollisionsPoints()[1].y - data2->getPos().y, 2)) < 20){
				data1->addDamage(data2->getDamage());
				if (data1->getLife() < 0){
					for (unsigned int i = 0; i < playersOnline.size(); i++){
						if (playersOnline[i].getLogin() == data2->getOL())playersOnline[i].reward(data1);
					}
				}
				data2->setRemove();
			}
		}
		else if (data1->getShipId() == 2){
			if (sqrtf(powf(data1->getPos().x - data2->getPos().x, 2) + powf(data1->getPos().y - data2->getPos().y, 2)) < 32 ||
				sqrtf(powf(data1->getCollisionsPoints()[0].x - data2->getPos().x, 2) + powf(data1->getCollisionsPoints()[0].y - data2->getPos().y, 2)) < 25 ||
				sqrtf(powf(data1->getCollisionsPoints()[1].x - data2->getPos().x, 2) + powf(data1->getCollisionsPoints()[1].y - data2->getPos().y, 2)) < 25){
				data1->addDamage(data2->getDamage());
				if (data1->getLife() < 0){
					for (unsigned int i = 0; i < playersOnline.size(); i++){
						if (playersOnline[i].getLogin() == data2->getOL())playersOnline[i].reward(data1);
					}
				}
				data2->setRemove();
			}
		}
	}
}

void Game::obstacleCollisions(Character *data){
	float x;
	float y;
	for (unsigned int i = 0; i < archipelag.size(); i++){
		x = archipelag[i].getPos().x - archipelag[i].getSize().x / 2;
		y = archipelag[i].getPos().y - archipelag[i].getSize().y / 2;
		float a = atan2(x - data->getPos().x, y - data->getPos().y);

		if (sqrtf(powf(data->getPos().x - x, 2) + powf(data->getPos().y - y, 2)) < archipelag[i].getR() + data->getShipHeight() && cos(a - data->getAngle() / 180 * M_PI) < 0){
			data->setCollide();
		}
	}

}

void Game::checkGathering(Character *data1, Drop *data2){
	if (data1->doULive()){
		if (sqrtf(powf(data1->getPos().x - data2->getPos().x, 2) + powf(data1->getPos().y - data2->getPos().y, 2)) < 40){
			data2->setRemove();
			if (data2->getPackage().size() >= 2)data1->provide(data2->getPackage()[0], data2->getPackage()[1], data2->getPackage()[2]);
		}
	}
}

Island Game::nearestIsland(int index){
	if (sqrt(pow(playersOnline[index].getPos().x - archipelag[0].getPos().x, 2) + pow(playersOnline[index].getPos().y - archipelag[0].getPos().y, 2)) >
		sqrt(pow(playersOnline[index].getPos().x - archipelag[1].getPos().x, 2) + pow(playersOnline[index].getPos().y - archipelag[1].getPos().y, 2))){
		return archipelag[1];
	}
	else return archipelag[0];
}