#pragma once
#include "stdafx.h"
#include "Transaction.h"

/**
*	DBManager - предоставляет интерфейс для работы алгоритма CLOPE.
*	Обеспечивает последовательное обращение к транзакциям посредством объекта класса Transaction.
*	При использовании другого набора транзакций наследовать DBManager и Transaction.
*
*/
class DBManager 
{
public:
	typedef Transaction Transaction;
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
