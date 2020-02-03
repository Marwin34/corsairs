#include "gui.hpp"

Gui::Gui(){
	dY = 0.0f;
	dX = 0.0f;
	status = loginScreen;
	loginFlag = false;
	registerFlag = false;
	restartFlag = false;
	apkShutDown = false;
	inPortRange = false;
	sellFlag = false;
	buyFlag = false;
	repairFlag = false;
	upgradeShip = false;
	lOrR = 0; // LOGIN OR REGISTER
	unactive = 0;
	serverMessageCnt = 0;
	ammoPointerX = 0;
	poleCnt = 0;
	playerShip = 3;
	//SHOP
	shop.activeShip = 3;
	shop.activeGood = 5;
	shop.sellingPrize = 0;
	shop.buyingPrize = 0;
	shop.playerGold = 0;
	shop.visible = false;
	shop.action = 4;
	shop.insertingValue = false;
	shop.goodsWeights[0] = 6;
	shop.goodsWeights[1] = 10;
	shop.goodsWeights[2] = 3;
	shop.goodsWeights[3] = 1;
	shop.goodsWeights[4] = 5;
	shop.unUsedCargo = 0;
	shop.messageCnt = 0;
	shop.displayMessage = false;
}

Gui::~Gui(){

}

void Gui::load(AssetsManager &data){
	windCursor.setOrigin(data["redArrow"].getSize().x / 2, data["redArrow"].getSize().y / 2);
	windCursor.setTexture(data["redArrow"]);
	uiRBC.setTexture(data["uiRBC"]);
	uiM.setTexture(data["uiM"]);
	uiTRC.setTexture(data["uiTRC"]);
	exp.initFont(data.font());
	lvl.initFont(data.font());
	gold.initFont(data.font());
	cargo.initFont(data.font());
	cannobalsCnt.initFont(data.font());
	grenadesCnt.initFont(data.font());
	loginMenu.setOrigin(data["loginMenu"].getSize().x / 2, data["loginMenu"].getSize().y / 2);
	loginMenu.setTexture(data["loginMenu"]);
	registerMenu.setOrigin(data["registerMenu"].getSize().x / 2, data["registerMenu"].getSize().y / 2);
	registerMenu.setTexture(data["registerMenu"]);
	ammoPointer.setTexture(data["border40"]);
	pole0.setTexture(data["pole0"]);
	pole1.setTexture(data["pole1"]);
	pole2.setTexture(data["pole2"]);
	serverMessage.init(data.font());
	serverMessage.setCharSize(14);
	hpIndi.create(data);
	banner.setTexture(data["banner"]);
	banner.setOrigin(data["banner"].getSize().x / 2, data["banner"].getSize().y / 2);
	mainTheme.setTexture(data["mainTheme"]);
	mainTheme.setOrigin(data["mainTheme"].getSize().x / 2, data["mainTheme"].getSize().y / 2);
	
	login.init(data, -80, -58, 150, 0);
	password.init(data, -80, -8, 150, 1);
	restart.init(data, "restart", -50, -30);
	loginB.init(data, "login", -50, 50);
	endB.init(data, "end", 200, 200);
	registerB.init(data, "register", -50, 50);
	portB.init(data, "port", -SCRN_WIDTH / 2 + 10, SCRN_HEIGHT / 2 - 65);
	change1B.init(data, "loginForm", -150, -120);
	change2B.init(data, "registerForm", -50, -120);

	//SHOP INITIALIZATION
	shop.closeShop.init(data, "closeWindow", 310, -240);
	shop.shopBackdrop.setTexture(data["shopBackdrop"]);
	shop.shopBackdrop.setOrigin(data["shopBackdrop"].getSize().x / 2, data["shopBackdrop"].getSize().y / 2);
	shop.shipIcon1.init(data, "shipIcon1", -320, -200);
	shop.shipIcon2.init(data, "shipIcon2", -320, -115);
	shop.shipIcon3.init(data, "shipIcon3", -320, -30);
	shop.buyShip.init(data, "buy", -330, 60);
	shop.goods1.init(data, "goods1", 190, -200);
	shop.goods2.init(data, "goods2", 190, -145);
	shop.goods3.init(data, "goods3", 190, -90);
	shop.goods4.init(data, "goods4", 190, -35);
	shop.goods5.init(data, "goods5", 190, 20);
	shop.buyB.init(data, "buy", 150, 75);
	shop.sellB.init(data, "sell", 250, 75);
	shop.statsShips[0].init(0);
	shop.statsShips[1].init(1);
	shop.statsShips[2].init(2);
	shop.shipsCompare.init(data.font());
	shop.shipsCompare.setCharSize(14);
	shop.shipsCompare.setPositionAndValue(dX - 320, dY + 100, "");
	shop.goodDescription.init(data.font());
	shop.goodDescription.setCharSize(14);
	shop.goodDescription.setPositionAndValue(dX + 190, dY + 110, "");
	shop.valueYesB.init(data, "smallYes", -80, -45);
	shop.valueNoB.init(data, "smallNo", 60, -45);
	shop.repairB.init(data, "repair", -230, 60);

	shop.goodsCount.init(data, 0, 0, 164);
	shop.message.init(data.font());
	shop.message.setCharSize(14);
}

void Gui::update(Character *data, sf::RenderWindow &data2, std::vector<sf::Vector2i> &data3){
	if (shop.displayMessage){
		shop.messageCnt++;
		if (shop.messageCnt > 50){
			shop.messageCnt = 0;
			shop.displayMessage = false;
		}
	}
	if (showServerMessage){
		serverMessageCnt++;
		if (serverMessageCnt > 150){ 
			serverMessageCnt = 0;
			showServerMessage = false;
			messageText = "";
		}
	}

	dX = data->getPos().x;
	dY = data->getPos().y;
	ammoPointerX = data->getAmmoP();
	poleCnt = data->getSails();
	inPortRange = data->getPortingF();
	playerShip = data->getShipId();

	serverMessage.setPositionAndValue(dX - messageText.size()*4,dY + 23,messageText);
	if (shop.displayMessage) shop.message.setPositionAndValue(dX - 20 * 4, dY - 90, "Dokonano transakcji.");

	if (status == loginScreen){
		shopRestart();
		banner.setPosition(dX, dY - SCRN_HEIGHT / 2 + 100);
		mainTheme.setPosition(dX, dY);
		loginMenu.setPosition(dX, dY);
		registerMenu.setPosition(dX, dY);
		login.update(data2, dX, dY);
		password.update(data2, dX, dY);
		endB.posUpdate(dX, dY);
		endB.activeUpdate(data2);
		registerB.posUpdate(dX, dY);
		loginB.posUpdate(dX, dY);
		change1B.posUpdate(dX, dY);
		change2B.posUpdate(dX, dY);

		change1B.activeUpdate(data2);
		change2B.activeUpdate(data2);

		if (change1B.isActive()) lOrR = 0;
		if (change2B.isActive()) lOrR = 1;
		
		if (lOrR < 1)loginB.activeUpdate(data2);
		else registerB.activeUpdate(data2);

		if (loginB.isActive()) loginFlag = true;
		if (registerB.isActive()) registerFlag = true;

		if (endB.isActive()) apkShutDown = true;
		if (unactive > 0) unactive++;
		if (unactive > 2) unactive = 0;
	}
	else if (status == inGame){
		shopUpdate(dX, dY, data2, data3);
		
		lvl.setValue(data->getInfo()[0]);
		exp.setValue(data->getInfo()[1]);
		gold.setValue(data->getInfo()[2]);
		shop.unUsedCargo = data->getInfo()[3] - (data->getInfo()[4] * shop.goodsWeights[0] + data->getInfo()[5] * shop.goodsWeights[1] + data->getInfo()[6] * shop.goodsWeights[2] + data->getInfo()[7] * shop.goodsWeights[3] + data->getInfo()[8] * shop.goodsWeights[4]);
		cargo.setValue(shop.unUsedCargo);
		cannobalsCnt.setValue(data->getInfo()[7]);
		grenadesCnt.setValue(data->getInfo()[8]);

		//PLAYER'S GOODS LOADING
		shop.shopGoods[0] = data->getInfo()[4];
		shop.shopGoods[1] = data->getInfo()[5];
		shop.shopGoods[2] = data->getInfo()[6];
		shop.shopGoods[3] = data->getInfo()[7];
		shop.shopGoods[4] = data->getInfo()[8];
		shop.playerGold = data->getInfo()[2];

		shop.toRepair = shop.statsShips[playerShip].getMaxHp() - data->getInfo()[9];

		windCursor.setPosition(dX + SCRN_WIDTH / 2 - 59, dY + SCRN_HEIGHT / 2 - 60);
		uiRBC.setPosition(dX + SCRN_WIDTH / 2 - 100, dY + SCRN_HEIGHT / 2 - 100);
		uiM.setPosition(dX - 60, dY + 250);
		uiTRC.setPosition(dX + SCRN_WIDTH / 2 - 100, dY - SCRN_HEIGHT /2);
		hpIndi.set_scale((float)data->getInfo()[9] / (float)shop.statsShips[playerShip].getMaxHp());
		hpIndi.setPosition(dX - SCRN_WIDTH / 2 + 20, dY + SCRN_HEIGHT /2 - 120);

		exp.setPosition(uiTRC.getPosition().x + 50, uiTRC.getPosition().y + 4);
		lvl.setPosition(uiTRC.getPosition().x + 50, uiTRC.getPosition().y + 16);
		gold.setPosition(uiTRC.getPosition().x + 50, uiTRC.getPosition().y + 28);
		cargo.setPosition(uiTRC.getPosition().x + 50, uiTRC.getPosition().y + 40);
		cannobalsCnt.setPosition(uiM.getPosition().x + 5, uiM.getPosition().y + 22);
		grenadesCnt.setPosition(uiM.getPosition().x + 45, uiM.getPosition().y + 22);
		ammoPointer.setPosition(uiM.getPosition().x + 40 * ammoPointerX, uiM.getPosition().y);
		pole0.setPosition(uiM.getPosition().x + 80, uiM.getPosition().y);
		pole1.setPosition(uiM.getPosition().x + 80, uiM.getPosition().y);
		pole2.setPosition(uiM.getPosition().x + 80, uiM.getPosition().y);

		if (shop.visible){
			shop.closeShop.activeUpdate(data2);

			if (shop.closeShop.isActive() || !inPortRange){
				shop.visible = false;
				shopRestart();
			}
		}
		else if (inPortRange){
			portB.activeUpdate(data2);

			if (portB.isActive()){
				shop.visible = true;
			}
		}

		if (data->doULive()) {
			restart.setDrawFlag(0);
		}
		else {
			restart.setDrawFlag(1);
			restart.posUpdate(dX, dY);
			restart.activeUpdate(data2);
			if (restart.isActive()) restartFlag = true;
		}

		if (shop.playerGold != shop.lastGold){
			shop.displayMessage = true;
			shop.messageCnt = 0;
		}
	}

	buttonsReset();
	shop.lastGold = shop.playerGold;
}

void Gui::eventUpdate(sf::Event *event){
	if (status == loginScreen){
		login.eventHandler(event);
		password.eventHandler(event);
		loginB.eventHandler(event);
		registerB.eventHandler(event);
		endB.eventHandler(event);
		change1B.eventHandler(event);
		change2B.eventHandler(event);
	}
	else if (status == inGame){
		if(shop.insertingValue) shop.goodsCount.eventHandler(event);

		restart.eventHandler(event);
		portB.eventHandler(event);

		shop.closeShop.eventHandler(event);
		shop.shipIcon1.eventHandler(event);
		shop.shipIcon2.eventHandler(event);
		shop.shipIcon3.eventHandler(event);
		shop.buyShip.eventHandler(event);
		shop.goods1.eventHandler(event);
		shop.goods2.eventHandler(event);
		shop.goods3.eventHandler(event);
		shop.goods4.eventHandler(event);
		shop.goods5.eventHandler(event);
		shop.buyB.eventHandler(event);
		shop.sellB.eventHandler(event);
		shop.valueYesB.eventHandler(event);
		shop.valueNoB.eventHandler(event);
		shop.repairB.eventHandler(event);
	}
}

void Gui::setWindCursorR(float data){
	windCursor.setRotation(data);
}

void Gui::draw(sf::RenderWindow *win){
	if (status == loginScreen){
		win->draw(mainTheme); 
		if (lOrR < 1){
			win->draw(loginMenu);
			loginB.draw(win);
		}
		else {
			win->draw(registerMenu);
			registerB.draw(win);
		}
		login.draw(win);
		password.draw(win);
		endB.draw(win);
		change1B.draw(win);
		change2B.draw(win);
		serverMessage.draw(win);
		win->draw(banner);
	}
	else if (status == inGame){
		win->draw(uiM);
		win->draw(uiRBC);
		win->draw(uiTRC);
		win->draw(windCursor);
		//hpIndi.draw_ind(win);
		lvl.draw(win);
		exp.draw(win);
		gold.draw(win);
		cargo.draw(win);
		cannobalsCnt.draw(win);
		grenadesCnt.draw(win);
		win->draw(ammoPointer);
		if (poleCnt == 0) win->draw(pole0);
		else if (poleCnt == 0.5) win->draw(pole1);
		else if (poleCnt == 1) win->draw(pole2);

		if (!shop.visible && inPortRange) portB.draw(win);

		if (shop.visible) shopDraw(win);

		if (restart.getDrawFlag()) restart.draw(win);
	} 
}

void Gui::updateStatus(int data){
	status = data;
}

void Gui::setMessage(std::string data){
	showServerMessage = true;
	serverMessageCnt = 0;
	if (data == "0") messageText = "Blêdne dane logowania!";
	if (data == "1") messageText = "Utworzono nowe konto!";
	if (data == "2") messageText = "Login zajêty!";
	if (data == "3") messageText = "Za krótkie haslo!";
	if (data == "4") messageText = "Brak polaczenia sprawdz ip lub lacze!";
}

void Gui::shopUpdate(float dX, float dY, sf::RenderWindow &win, std::vector<sf::Vector2i> &data1){
	shop.shopBackdrop.setPosition(dX, dY);
	//shop.valueBackdrop.setPosition(dX, dY);
	portB.posUpdate(dX, dY);
	shop.closeShop.posUpdate(dX, dY);
	shop.shipIcon1.posUpdate(dX, dY);
	shop.shipIcon2.posUpdate(dX, dY);
	shop.shipIcon3.posUpdate(dX, dY);
	shop.buyShip.posUpdate(dX, dY);
	shop.goods1.posUpdate(dX, dY);
	shop.goods2.posUpdate(dX, dY);
	shop.goods3.posUpdate(dX, dY);
	shop.goods4.posUpdate(dX, dY);
	shop.goods5.posUpdate(dX, dY);
	shop.buyB.posUpdate(dX, dY);
	shop.sellB.posUpdate(dX, dY);
	shop.valueNoB.posUpdate(dX, dY);
	shop.valueYesB.posUpdate(dX, dY);
	shop.repairB.posUpdate(dX, dY);
	
	if (shop.activeShip >= 0 && shop.activeShip < 3) {
		std::string textValue;
		textValue = "Nazwa: " + shop.statsShips[shop.activeShip].getStats()[0] +
			"\nLadownia: " + shop.statsShips[shop.activeShip].getStats()[1] +
			"\nZycie:" + shop.statsShips[shop.activeShip].getStats()[3] +
			"\nArmaty:" + shop.statsShips[shop.activeShip].getStats()[4] +
			"\nKoszt: " + shop.statsShips[shop.activeShip].getStats()[2];
			
		shop.shipsCompare.setPositionAndValue(dX - 320, dY + 100, textValue);
	}
	else shop.shipsCompare.setPositionAndValue(dX - 320, dY + 100, "");

	if (shop.activeGood >= 0 && shop.activeGood < 5) { 
		std::string textValue;

		if (shop.activeGood == 0) textValue = "Nazwa: Kawa\n";
		else if (shop.activeGood == 1) textValue = "Nazwa: Przyprawy\n";
		else if (shop.activeGood == 2) textValue = "Nazwa: Rum\n";
		else if (shop.activeGood == 3) textValue = "Nazwa: Kule armatnie\n";
		else if (shop.activeGood == 4) textValue = "Nazwa: Granaty armatnie\n";

		std::ostringstream a; 

		a << "Ilosc: "
			<< shop.shopGoods[shop.activeGood]
			<< "\nCena sprzedazy: "
			<< data1[shop.activeGood].y
			<< "\nCena zakupu: "
			<< data1[shop.activeGood].x
			<< "\nZajmowane miesjce:"
			<< shop.goodsWeights[shop.activeGood]
			<< "\n";

		textValue += a.str();

		shop.goodDescription.setPositionAndValue(dX + 155, dY + 110, textValue);

		shop.buyingPrize = data1[shop.activeGood].x;
		shop.sellingPrize = data1[shop.activeGood].y;
	}
	else shop.goodDescription.setPositionAndValue(dX + 155, dY + 110, "");

	if (shop.visible){
		shop.shipIcon1.activeUpdate(win);
		shop.shipIcon2.activeUpdate(win);
		shop.shipIcon3.activeUpdate(win);
		shop.buyShip.activeUpdate(win);
		shop.goods1.activeUpdate(win);
		shop.goods2.activeUpdate(win);
		shop.goods3.activeUpdate(win);
		shop.goods4.activeUpdate(win);
		shop.goods5.activeUpdate(win);
		shop.buyB.activeUpdate(win);
		shop.sellB.activeUpdate(win);
		shop.valueYesB.activeUpdate(win);
		shop.valueNoB.activeUpdate(win);
		shop.repairB.activeUpdate(win);

		if (!shop.insertingValue){
			if (shop.shipIcon1.isActive()) shop.activeShip = 0;
			if (shop.shipIcon2.isActive()) shop.activeShip = 1;
			if (shop.shipIcon3.isActive()) shop.activeShip = 2;

			if (shop.activeShip >= 0 
				&& shop.activeShip < 3
				&& shop.statsShips[shop.activeShip].getPrize() <= shop.playerGold 
				&& shop.statsShips[shop.activeShip].getCargoSpace() >= shop.statsShips[playerShip].getCargoSpace() - shop.unUsedCargo){

				if (shop.buyShip.isActive()){
					shop.action = 2;
					upgradeShip = true;
				}
			}

			if (shop.goods1.isActive()) shop.activeGood = 0;
			if (shop.goods2.isActive()) shop.activeGood = 1;
			if (shop.goods3.isActive()) shop.activeGood = 2;
			if (shop.goods4.isActive()) shop.activeGood = 3;
			if (shop.goods5.isActive()) shop.activeGood = 4;

			if (shop.sellB.isActive() && shop.activeGood >= 0 && shop.activeGood < 5){
				shop.action = 0;
				shop.insertingValue = true;
				shop.goodsCount.setMaxValue(shop.shopGoods[shop.activeGood]);
			}
			if (shop.buyB.isActive() && shop.activeGood >= 0 && shop.activeGood < 5){
				shop.action = 1;
				shop.insertingValue = true;
				int tmpInt = shop.unUsedCargo / shop.goodsWeights[shop.activeGood];
				if (tmpInt > shop.playerGold / shop.buyingPrize){
					shop.goodsCount.setMaxValue(shop.playerGold / shop.buyingPrize);
				}
				else shop.goodsCount.setMaxValue(tmpInt);
				
			}

			if (shop.repairB.isActive()){
				if (shop.toRepair > shop.playerGold / 2){
					shop.toRepair = shop.playerGold / 2;
				}
				repairFlag = true;
				shop.action = 3;
			}

		}
		else {
			//shop.goodsCount.update(win, dX, dY);
			shop.goodsCount.update(win, dX, dY);

			if (shop.valueYesB.isActive()){
				shop.insertingValue = false;
				if (shop.action == 0) sellFlag = true;
				if (shop.action == 1) buyFlag = true;
			}
			if (shop.valueNoB.isActive()){
				shop.insertingValue = false;
				shop.goodsCount.clear();
			}
		}
	}
}

void Gui::shopDraw(sf::RenderWindow *win){
	win->draw(shop.shopBackdrop);
	shop.shipIcon1.draw(win);
	shop.shipIcon2.draw(win);
	shop.shipIcon3.draw(win);
	shop.buyShip.draw(win);
	shop.shipsCompare.draw(win);
	shop.goods1.draw(win);
	shop.goods2.draw(win);
	shop.goods3.draw(win);
	shop.goods4.draw(win);
	shop.goods5.draw(win);
	shop.buyB.draw(win);
	shop.sellB.draw(win);
	shop.goodDescription.draw(win);
	shop.repairB.draw(win);
	shop.closeShop.draw(win);
	if (shop.insertingValue){
		shop.goodsCount.draw(win);
		shop.valueYesB.draw(win);
		shop.valueNoB.draw(win);
	}
	if (shop.displayMessage) shop.message.draw(win);
}

void Gui::buttonsReset(){
	loginB.activeReset();
	endB.activeReset();
	restart.activeReset();
	registerB.activeReset();
	portB.activeReset();
	change1B.activeReset();
	change2B.activeReset();

	shop.closeShop.activeReset();
	shop.shipIcon1.activeReset();
	shop.shipIcon2.activeReset();
	shop.shipIcon3.activeReset();
	shop.buyShip.activeReset();
	shop.goods1.activeReset();
	shop.goods2.activeReset();
	shop.goods3.activeReset();
	shop.goods4.activeReset();
	shop.goods5.activeReset();
	shop.buyB.activeReset();
	shop.sellB.activeReset();
	shop.repairB.activeReset();
}

void Gui::shopRestart(){
	shop.visible = false;
	shop.activeShip = 3;
	shop.activeGood = 5;
	shop.action = 4;
	shop.insertingValue = false;
}

bool Gui::restartMessage(){
	if (restartFlag) {
		restartFlag = false;
		return true;
	}
	else return false;
}

bool Gui::sendLogin(){
	if (loginB.isActive()){
		return true;
	}
	else return false;
}

bool Gui::terminateWindow(){
	return apkShutDown;
}

bool Gui::busy(){
	if (shop.visible) return true;
	else return false;
}

std::vector <int> Gui::shopOrder(){
	std::vector <int> tmp;
	tmp.resize(0);

	if ((shop.action == 0 && sellFlag) || (shop.action == 1 && buyFlag)){ 
		tmp.push_back(shop.action);
		tmp.push_back(shop.activeGood);
		tmp.push_back(shop.goodsCount.value());
		shop.goodsCount.clear();
		sellFlag = false;
		buyFlag = false;
	}
	if (shop.action == 2 && upgradeShip){
		tmp.push_back(shop.action);
		tmp.push_back(shop.activeShip);
		tmp.push_back(1);
		upgradeShip = false;
	}
	if (shop.action == 3 && repairFlag){
		tmp.push_back(shop.action);
		tmp.push_back(shop.activeShip);
		tmp.push_back(shop.toRepair);
		repairFlag = false;
	}

	return tmp;
}

std::vector <std::string> Gui::loginMessage(){
	std::vector <std::string> tmp;
	tmp.resize(2);
	tmp[0] = login.value();
	tmp[1] = password.value();
	return tmp;
}

std::vector <std::string> Gui::guiMessage(){
	std::vector <std::string> tmp;
	tmp.resize(0);
	if (status == loginScreen){
		if (loginFlag){
			loginFlag = false;
			tmp.resize(3);
			tmp[0] = "login";
			tmp[1] = login.value();
			tmp[2] = password.value();
		}
		if (registerFlag){
			registerFlag = false;
			tmp.resize(3);
			tmp[0] = "register";
			tmp[1] = login.value();
			tmp[2] = password.value();
		}
	}
	return tmp;
}

void Indicator::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    states.transform *= getTransform();
	states.texture = &i_tileset;
	target.draw(i_vertices, states);
}

void Indicator::create(AssetsManager &container){
	i_tileset = container["wnetrze"];
	i_tileset2 = container["obrys"];

	i_vertices.setPrimitiveType(sf::Quads);
	i_vertices.resize(4);

	i_vertices[0].position = sf::Vector2f(1, 1);
	i_vertices[1].position = sf::Vector2f(1, 49);
	i_vertices[2].position = sf::Vector2f(30, 49);
	i_vertices[3].position = sf::Vector2f(30, 1);

	i_vertices[0].texCoords = sf::Vector2f(0, 0);
	i_vertices[1].texCoords = sf::Vector2f(0, 48);
	i_vertices[2].texCoords = sf::Vector2f(29, 48);
	i_vertices[3].texCoords = sf::Vector2f(29, 0);

	obr_vertices.setPrimitiveType(sf::Quads);
	obr_vertices.resize(4);

	obr_vertices[0].position = sf::Vector2f(0, 0);
	obr_vertices[1].position = sf::Vector2f(0, 50);
	obr_vertices[2].position = sf::Vector2f(31, 50);
	obr_vertices[3].position = sf::Vector2f(31, 0);

	obr_vertices[0].texCoords = sf::Vector2f(0, 0);
	obr_vertices[1].texCoords = sf::Vector2f(0, 50);
	obr_vertices[2].texCoords = sf::Vector2f(31, 50);
	obr_vertices[3].texCoords = sf::Vector2f(31, 0);
}

void Indicator::set_scale(float procent){
	float y = 50 - (49 * procent);
	float y_t = 48 - (48 * procent);

	i_vertices[0].position = sf::Vector2f(1, y);
	i_vertices[3].position = sf::Vector2f(30, y);

	i_vertices[0].texCoords = sf::Vector2f(0, y_t);
	i_vertices[3].texCoords = sf::Vector2f(29, y_t);

}

void Indicator::draw_ind(sf::RenderWindow *win){
	sf::RenderStates states;
	states.transform *= getTransform();
	states.texture = &i_tileset;
	sf::RenderStates states2;
	states2.transform *= getTransform();
	states2.texture = &i_tileset2;
	win->draw(obr_vertices, states2);
	win->draw(i_vertices, states);
}