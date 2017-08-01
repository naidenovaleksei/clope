#pragma once

#include "stdafx.h"
#include "ClusterList.h"

#define NOT_OPEN_DB 1
extern double R;

/**
*	ClopeAlgorithm - класс для работы алгоритма CLOPE.
*	Абстрагирован от конкретной реализации хранения набора транзакций.
*	Использует интерфейс предоставляемый классами DBManager (в том числе Transaction).
*
*/
template <typename DBManager>
class ClopeAlgorithm
{
public:
	bool openFile( const std::string &filename );
	void setRepulsion( const double repulsion );

	int execute();

private:	
	typename DBManager m_DBManager;
	typename DBManager::Transaction currentTransaction;
	ClusterList< typename DBManager::Transaction> clusters;
};


template <typename DBManager>
int ClopeAlgorithm<DBManager>::execute()
{
	int clusterIndex_old;
	int clusterIndex_new;

	if ( !m_DBManager.isReady() ) {
		std::cout << "Can't open file with DB\n";
		exit( NOT_OPEN_DB );
	}

	/* Фаза 1 - Инициализация */	
	while ( m_DBManager.nextTransaction(currentTransaction) )
	{
		clusterIndex_new = clusters.addTransaction( currentTransaction );
		m_DBManager.updateTransaction( currentTransaction, clusterIndex_new );
	}

	/* Фаза 2 - Итерации */
	bool isMoved;
	do {
		m_DBManager.rewind();
		isMoved = false;
		while ( m_DBManager.nextTransaction(currentTransaction) )
		{
			clusterIndex_old = currentTransaction.clusterIndex();
			clusterIndex_new = clusters.replaceTransaction( currentTransaction );

			if ( clusterIndex_old != clusterIndex_new ) {
				m_DBManager.updateTransaction( currentTransaction, clusterIndex_new );
				isMoved = true;
			}
		}
	} while ( isMoved );
	clusters.deleteEmpty();

	return 0;
}


template <typename DBManager>
bool ClopeAlgorithm<DBManager>::openFile( const std::string &filename ) 
{
	m_DBManager.openFile( filename );
	return m_DBManager.isReady();
}


template <typename DBManager>
void ClopeAlgorithm<DBManager>::setRepulsion( const double repulsion )
{
	R = repulsion;
}