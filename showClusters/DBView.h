#pragma once

#include "MushroomDBManager.h"

typedef std::map< int, std::map<char, int> > Map2d;

/**
*	DBView - ��������� �� "Mushroom dataset", �������������� ���������� CLOPE_prepareDB
*	������� ���������� �� � ������� � �������������� ����, ������������ �� ��������� p/e
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

