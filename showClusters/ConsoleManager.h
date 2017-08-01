#pragma once
#include "stdafx.h"

/**
*	ConsoleManager - �������� �� ��������� ���������� �� ��������� ������ � ����� �������� ���������
*
*/
class ConsoleManager
{
public:
	ConsoleManager();
	ConsoleManager( const std::string description );

	// ��������� �������� ��������� � ��������������� attrName
	std::string attribute( int argc, char* argv[], const std::string &attrName );
	// ����� �� ��������� � ������� ����������� ������ m_description
	void exit();

private:
	std::string m_description;
};
