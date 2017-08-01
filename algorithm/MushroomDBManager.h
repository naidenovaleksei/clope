#pragma once

#include "stdafx.h"
#include "DBManager.h"
#include "MushroomTransaction.h"

/**
*	MushroomDBManager - ������������� ��������� ��� ������ ��������� CLOPE
*	� ������ ������������� "Mushroom dataset".
*	��������� �� "Mushroom dataset", �������������� ���������� CLOPE_prepareDB.
*	������������ ���������������� ��������� � ����������� ����������� ������� ������ Transaction.
*
*/
class MushroomDBManager: public DBManager
{
public:
	typedef MushroomTransaction Transaction;
public:
	bool isReady() const;
	bool nextTransaction( Transaction& transaction );
	void updateTransaction( Transaction& currentTransaction, int clusterIndex_new );
	void openFile( const std::string& dataFilename );
	void rewind();

private:
	std::string m_dataFilename;
	std::fstream m_dataFStream;
};
