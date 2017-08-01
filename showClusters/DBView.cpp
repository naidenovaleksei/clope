#include "DBView.h"


void DBView::openFile ( const std::string &filename )
{
	m_dbManager.openFile( filename );
	if ( !m_dbManager.isReady() ) {
		printf( "Can't open file with DB: %s\n", filename.c_str() );
		exit( 1 );
	}

	MushroomDBManager::Transaction currentTransaction;
	while ( m_dbManager.nextTransaction(currentTransaction) )
	{
		char pe = currentTransaction.getType();
		int clusterIndex = currentTransaction.clusterIndex();
		m_checkList[clusterIndex][pe]++;
	}
}


void DBView::showDB()
{
	printf( "Cluster\t| p\t| e\n" );
	printf( "--------|-------|----\n" );

	int index = 0;
	for ( auto cluster = m_checkList.begin(); cluster != m_checkList.end(); ++cluster )
	{
		++index;

		auto itP = cluster->second.find('p');
		int p = itP != cluster->second.end()? itP->second: 0;

		auto itE = cluster->second.find('e');
		int e = itE != cluster->second.end()? itE->second: 0;

		printf( "%3d \t| %3d \t| %3d\n", index, p, e );
	}
}
