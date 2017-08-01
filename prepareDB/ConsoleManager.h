#pragma once
#include "stdafx.h"

/**
*	ConsoleManager - отвечает за получение аргументов из командной строки и вывод описани€ программы
*
*/
class ConsoleManager
{
public:
	ConsoleManager();
	ConsoleManager( const std::string description );

	// ѕолучение значени€ параметра с идентификатором attrName
	std::string attribute( int argc, char* argv[], const std::string &attrName );
	// ¬ыход из программы с выводом содержимого строки m_description
	void exit();

private:
	std::string m_description;
};
