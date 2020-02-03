#include "txtDb.hpp"

DatabaseManager::DatabaseManager(){
	dbObjects.resize(0); 
}

DatabaseManager::~DatabaseManager(){

}


void DatabaseManager::load(std::string name){
	std::ifstream file(name, std::ios::app);

	int id, hp, x, y, lvl, pd, gold, shipId, goods1, goods2, goods3, cannonballC, grenadesC;
	std::string login, password;

	while (file >> id >> login >> password >> x >> y >> hp >> lvl >> pd >> gold >> shipId >> goods1 >> goods2 >> goods3 >> cannonballC >> grenadesC){
		dbObject tmp;
		tmp.id = id;
		tmp.login = login;
		tmp.password = password;
		tmp.pStats.x = x;
		tmp.pStats.y = y;
		tmp.pStats.hp = hp;
		tmp.pStats.lvl = lvl;
		tmp.pStats.pd = pd;
		tmp.pStats.gold = gold;
		tmp.pStats.shipId = shipId;
		tmp.pStats.goods1 = goods1;
		tmp.pStats.goods2 = goods2;
		tmp.pStats.goods3 = goods3;
		tmp.pStats.cannonballC = cannonballC;
		tmp.pStats.grenadesC = grenadesC;

		dbObjects.push_back(tmp);
	}

	file.close();
}

void DatabaseManager::save(std::string name){
	std::ofstream file("resources/schowek.txt", std::ios::app);

	for (unsigned int i = 0; i < dbObjects.size(); i++){
		file << dbObjects[i].id << " " << dbObjects[i].login << " " << dbObjects[i].password << " "
			 << dbObjects[i].pStats.x << " " << dbObjects[i].pStats.y << " " << dbObjects[i].pStats.hp << " "
			 << dbObjects[i].pStats.lvl << " " << dbObjects[i].pStats.pd << " " << dbObjects[i].pStats.gold << " "
			 << dbObjects[i].pStats.shipId << " " << dbObjects[i].pStats.goods1 << " " << dbObjects[i].pStats.goods2 << " " 
			 << dbObjects[i].pStats.goods3 << " " << dbObjects[i].pStats.cannonballC << " " << dbObjects[i].pStats.grenadesC << std::endl;
	}
	file.close();

	remove(name.c_str());
	rename("resources/schowek.txt", name.c_str());

	std::cout << "SAVE!" << std::endl;

	drop();
}

std::string DatabaseManager::registerNewObject(std::string login, std::string password){
	load("resources/database.txt");
	int cnt = 0;
	for (unsigned int i = 0; i < dbObjects.size(); i++){
		if (dbObjects[i].login == login) return "2";
	}
	if (password.size() <= 3) return "3";
	else{
		dbObject tmp;

		tmp.id = dbObjects.size();
		tmp.login = login;
		tmp.password = password;
		tmp.pStats.x = 0;
		tmp.pStats.y = 0;
		tmp.pStats.hp = 100;
		tmp.pStats.lvl = 1;
		tmp.pStats.pd = 0;
		tmp.pStats.shipId = 0;
		tmp.pStats.gold = 1000;
		tmp.pStats.grenadesC = 5;
		tmp.pStats.cannonballC = 50;
		tmp.pStats.goods1 = 0;
		tmp.pStats.goods2 = 0;
		tmp.pStats.goods3 = 1;

		dbObjects.push_back(tmp);
		save("resources/database.txt");
		return "1";
	}
	drop();
}

std::vector <int> DatabaseManager::login(std::string data1, std::string data2){
	std::vector <int> tmp;
	tmp.resize(0);

	load("resources/database.txt");

	for (unsigned int i = 0; i < dbObjects.size(); i++){
		if (dbObjects[i].login == data1 && dbObjects[i].password == data2){
			tmp.push_back(dbObjects[i].pStats.x);
			tmp.push_back(dbObjects[i].pStats.y);
			tmp.push_back(dbObjects[i].pStats.lvl);
			tmp.push_back(dbObjects[i].pStats.pd);
			tmp.push_back(dbObjects[i].pStats.hp);
			tmp.push_back(dbObjects[i].pStats.gold);
			tmp.push_back(dbObjects[i].pStats.goods1);
			tmp.push_back(dbObjects[i].pStats.goods2);
			tmp.push_back(dbObjects[i].pStats.goods3);
			tmp.push_back(dbObjects[i].pStats.cannonballC);
			tmp.push_back(dbObjects[i].pStats.grenadesC);
			tmp.push_back(dbObjects[i].pStats.shipId);
			drop();
			return tmp;
		}
	}
	drop();
	return tmp;
}

void DatabaseManager::update(Stats *data1, std::string data2){ 
	load("resources/database.txt");
	for (unsigned int i = 0; i < dbObjects.size(); i++){
		if (dbObjects[i].login == data2){
			std::cout << data1->x << " , " << data1->y << std::endl;
			dbObjects[i].pStats.x = data1->x;
			dbObjects[i].pStats.y = data1->y;
			dbObjects[i].pStats.hp = data1->hp;
			dbObjects[i].pStats.lvl = data1->lvl;
			dbObjects[i].pStats.pd = data1->exp;
			dbObjects[i].pStats.gold = data1->gold;
			dbObjects[i].pStats.shipId = data1->shipId;
			dbObjects[i].pStats.goods1 = data1->goods1;
			dbObjects[i].pStats.goods2 = data1->goods2;
			dbObjects[i].pStats.goods3 = data1->goods3;
			dbObjects[i].pStats.cannonballC = data1->cannonballs;
			dbObjects[i].pStats.grenadesC = data1->grenades;
			break;
		}
	}
	save("resources/database.txt");
}

void DatabaseManager::drop(){
	dbObjects.resize(0);
}