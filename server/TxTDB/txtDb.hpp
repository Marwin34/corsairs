#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include "../characters.hpp"

#pragma once


class DatabaseManager{
	struct DBStats{
		int hp;
		int x;
		int y;
		int lvl;
		int pd;
		int gold;
		int shipId;
		int goods1;
		int goods2;
		int goods3;
		int cannonballC;
		int grenadesC;
	};

	struct dbObject{
		int id;
		std::string login;
		std::string password;
		DBStats pStats;
	};

	std::vector <dbObject> dbObjects;
public:
	DatabaseManager();
	~DatabaseManager();
	void load(std::string);
	void save(std::string);
	void update(Stats*, std::string);
	void drop();
	std::string registerNewObject(std::string, std::string);
	std::vector <int> login(std::string, std::string );
};
