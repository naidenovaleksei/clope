#pragma once

#include "MushroomDBManager.h"

typedef std::map< int, std::map<char, int> > Map2d;

/**
*	DBView - считывает БД "Mushroom dataset", подготовленную программой CLOPE_prepareDB
*	выводит содержимое БД в консоль в табулированном виде, сгруппировав по параметру p/e
*
*/
class DBView
{
public:
	void openFile( const std::string &filename );
	void showDB();
private:
	Map2d m_checkList;
	MushroomDBManager m_dbManager;
};

