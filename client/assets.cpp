#include "assets.hpp"

AssetsManager::AssetsManager(){
	textures.clear();
}

AssetsManager::~AssetsManager(){

}

void AssetsManager::load(){
	textures["none"].loadFromFile("resources/img/none.png");
	textures["valueInput"].loadFromFile("resources/img/valueInput.png");
	textures["valueInput"].setSmooth(true);
	textures["redArrow"].loadFromFile("resources/img/windArrow.png");
	textures["redArrow"].setSmooth(true);
	textures["testShip"].loadFromFile("resources/img/test_ship.png");
	textures["testShip"].setSmooth(true);
	textures["bullet"].loadFromFile("resources/img/bullet.png");
	textures["bullet"].setSmooth(true);
	textures["hpSmall"].loadFromFile("resources/img/hp.png");
	textures["hpSmall"].setSmooth(true);
	textures["uiLBC"].loadFromFile("resources/img/uiLBC.png"); // RBC - not right bottom corner ui element
	textures["uiLBC"].setSmooth(true);
	textures["uiRBC"].loadFromFile("resources/img/uiRBC.png"); // LBC - not left bottom corner ui element
	textures["uiRBC"].setSmooth(true);
	textures["uiM"].loadFromFile("resources/img/uiM.png");
	textures["uiM"].setSmooth(true);
	textures["level"].loadFromFile("resources/img/map.png");
	textures["level"].setSmooth(true);
	textures["uiTRC"].loadFromFile("resources/img/uiTRC.png");
	textures["uiTRC"].setSmooth(true);
	textures["button"].loadFromFile("resources/img/button.png");
	textures["button"].setSmooth(true);
	textures["buttonH"].loadFromFile("resources/img/buttonH.png");
	textures["buttonH"].setSmooth(true);
	textures["restart"].loadFromFile("resources/img/restart.png");
	textures["restart"].setSmooth(true);
	textures["restartH"].loadFromFile("resources/img/restartH.png");
	textures["restartH"].setSmooth(true);
	textures["login"].loadFromFile("resources/img/login.png");
	textures["login"].setSmooth(true);
	textures["loginH"].loadFromFile("resources/img/loginH.png");
	textures["loginH"].setSmooth(true);
	textures["end"].loadFromFile("resources/img/end.png");
	textures["end"].setSmooth(true);
	textures["endH"].loadFromFile("resources/img/endH.png");
	textures["endH"].setSmooth(true);
	textures["create"].loadFromFile("resources/img/create.png");
	textures["create"].setSmooth(true);
	textures["createH"].loadFromFile("resources/img/createH.png");
	textures["createH"].setSmooth(true);
	textures["change"].loadFromFile("resources/img/change.png");
	textures["change"].setSmooth(true);
	textures["changeLogin"].loadFromFile("resources/img/lscreenB1.png");
	textures["changeLogin"].setSmooth(true);
	textures["changeLoginH"].loadFromFile("resources/img/lscreenB1H.png");
	textures["changeLoginH"].setSmooth(true);
	textures["changeRegister"].loadFromFile("resources/img/lscreenB2.png");
	textures["changeRegister"].setSmooth(true);
	textures["changeRegisterH"].loadFromFile("resources/img/lscreenB2H.png");
	textures["changeRegisterH"].setSmooth(true);
	textures["loginMenu"].loadFromFile("resources/img/loginMenu.png");
	textures["loginMenu"].setSmooth(true);
	textures["registerMenu"].loadFromFile("resources/img/registerMenu.png");
	textures["registerMenu"].setSmooth(true);
	textures["backdrop"].loadFromFile("resources/img/tlo.png");
	textures["backdrop"].setSmooth(true);
	textures["island"].loadFromFile("resources/img/island.png");
	textures["island"].setSmooth(true);
	textures["border40"].loadFromFile("resources/img/border40.png");
	textures["border40"].setSmooth(true);
	textures["pole0"].loadFromFile("resources/img/pole0.png");
	textures["pole0"].setSmooth(true);
	textures["pole1"].loadFromFile("resources/img/pole1.png");
	textures["pole1"].setSmooth(true);
	textures["pole2"].loadFromFile("resources/img/pole2.png");
	textures["pole2"].setSmooth(true);
	textures["port"].loadFromFile("resources/img/port.png");
	textures["port"].setSmooth(true);
	textures["portH"].loadFromFile("resources/img/portH.png");
	textures["portH"].setSmooth(true);
	textures["shopBackdrop"].loadFromFile("resources/img/shopBackdrop.png");
	textures["shopBackdrop"].setSmooth(true);
	textures["shipIcon1"].loadFromFile("resources/img/shipIcon1.png");
	textures["shipIcon1"].setSmooth(true);
	textures["shipIcon1H"].loadFromFile("resources/img/shipIcon1H.png");
	textures["shipIcon1H"].setSmooth(true);
	textures["shipIcon2"].loadFromFile("resources/img/shipIcon2.png");
	textures["shipIcon2"].setSmooth(true);
	textures["shipIcon2H"].loadFromFile("resources/img/shipIcon2H.png");
	textures["shipIcon2H"].setSmooth(true);
	textures["shipIcon3"].loadFromFile("resources/img/shipIcon3.png");
	textures["shipIcon3"].setSmooth(true);
	textures["shipIcon3H"].loadFromFile("resources/img/shipIcon3H.png");
	textures["shipIcon3H"].setSmooth(true);
	textures["closeWindow"].loadFromFile("resources/img/closeWindow.png");
	textures["closeWindow"].setSmooth(true);
	textures["closeWindowH"].loadFromFile("resources/img/closeWindowH.png");
	textures["closeWindowH"].setSmooth(true);
	textures["goods1"].loadFromFile("resources/img/goods1.png");
	textures["goods1"].setSmooth(true);
	textures["goods1H"].loadFromFile("resources/img/goods1H.png");
	textures["goods1H"].setSmooth(true);
	textures["goods2"].loadFromFile("resources/img/goods2.png");
	textures["goods2"].setSmooth(true);
	textures["goods2H"].loadFromFile("resources/img/goods2H.png");
	textures["goods2H"].setSmooth(true);
	textures["goods3"].loadFromFile("resources/img/goods3.png");
	textures["goods3"].setSmooth(true);
	textures["goods3H"].loadFromFile("resources/img/goods3H.png");
	textures["goods3H"].setSmooth(true);
	textures["goods4"].loadFromFile("resources/img/goods4.png");
	textures["goods4"].setSmooth(true);
	textures["goods4H"].loadFromFile("resources/img/goods4H.png");
	textures["goods4H"].setSmooth(true);
	textures["goods5"].loadFromFile("resources/img/goods5.png");
	textures["goods5"].setSmooth(true);
	textures["goods5H"].loadFromFile("resources/img/goods5H.png");
	textures["goods5H"].setSmooth(true);
	textures["sellB"].loadFromFile("resources/img/sell.png");
	textures["sellB"].setSmooth(true);
	textures["sellBH"].loadFromFile("resources/img/sellH.png");
	textures["sellBH"].setSmooth(true);
	textures["buyB"].loadFromFile("resources/img/buy.png");
	textures["buyB"].setSmooth(true);
	textures["buyBH"].loadFromFile("resources/img/buyH.png");
	textures["buyBH"].setSmooth(true);
	textures["smallYes"].loadFromFile("resources/img/smallYes.png");
	textures["smallYes"].setSmooth(true);
	textures["smallYesH"].loadFromFile("resources/img/smallYesH.png");
	textures["smallYesH"].setSmooth(true);
	textures["smallNo"].loadFromFile("resources/img/smallNo.png");
	textures["smallNo"].setSmooth(true);
	textures["smallNoH"].loadFromFile("resources/img/smallNoH.png");
	textures["smallNoH"].setSmooth(true);
	textures["repair"].loadFromFile("resources/img/repair.png");
	textures["repair"].setSmooth(true);
	textures["repairH"].loadFromFile("resources/img/repairH.png");
	textures["repairH"].setSmooth(true);
	textures["valuePointer"].loadFromFile("resources/img/valuePointer.png");
	textures["valuePointer"].setSmooth(true);
	textures["Karakana"].loadFromFile("resources/img/karakana.png");
	textures["Karakana"].setSmooth(true);
	textures["Slup"].loadFromFile("resources/img/slup.png");
	textures["Slup"].setSmooth(true);
	textures["obrys"].loadFromFile("resources/img/obrys.png");
	textures["obrys"].setSmooth(true);
	textures["wnetrze"].loadFromFile("resources/img/wn2.png");
	textures["wnetrze"].setSmooth(true);
	textures["banner"].loadFromFile("resources/img/banner.png");
	textures["banner"].setSmooth(true);
	textures["mainTheme"].loadFromFile("resources/img/mainTheme.png");
	textures["mainTheme"].setSmooth(true);
	textures["newOcean"].loadFromFile("resources/img/newOcean.png");
	textures["newOcean"].setSmooth(true);
	textures["floatingGoods"].loadFromFile("resources/img/floatingGoods.png");
	textures["floatingGoods"].setSmooth(true);

	//FONTS
	mainFont.loadFromFile("resources/font/Anonymous_Pro.ttf");
}

sf::Font* AssetsManager::font(){
	return &mainFont;
}

sf::Texture& AssetsManager::operator[](std::string data){
	if (textures.count(data) > 0){
		return textures[data];
	}
	else return textures["none"];
}