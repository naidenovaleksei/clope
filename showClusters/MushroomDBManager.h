#pragma once

#include "stdafx.h"
#include "MushroomTransaction.h"

/**
*	MushroomDBManager - ������������� ��������� ��� ������ ��������� CLOPE
*	� ������ ������������� "Mushroom dataset".
*	��������� �� "Mushroom dataset", �������������� ���������� CLOPE_prepareDB.
*	������������ ���������������� ��������� � ����������� ����������� ������� ������ Transaction.
*	��� ������������� ������� ������ ���������� �������� MushroomDBManager � MushroomTransaction 
*	������ �������� � ��� �� ������������.
*
*/
class MushroomDBManager 
{
public:
	typedef MushroomTransaction Transaction;
public:
	bool isReady() const;
	bool nextTransaction( Transaction& transaction );
	void updateTransaction( Transaction& currentTransaction, int clusterIndex_new );
	void openFile( const string& dataFilename );
	void rewind();

private:
	std::string m_dataFilename;
	std::fstream m_dataFStream;
};
