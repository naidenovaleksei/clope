#include "MushroomDBManager.h"

bool MushroomDBManager::isReady() const
{
	return m_dataFStream.is_open();
}


void MushroomDBManager::openFile( const string& dataFilename )
{
	m_dataFilename = dataFilename;
	if ( m_dataFStream.is_open() ) m_dataFStream.close();
	m_dataFStream.open( m_dataFilename );
}


bool MushroomDBManager::nextTransaction( Transaction& transaction )
{
	std::string line;
	std::getline( m_dataFStream, line );

	if ( !line.empty() ) {
		transaction.setData( line );
		return true;
	} else return false;
}


void MushroomDBManager::updateTransaction( Transaction& transaction, int clusterIndex_new )
{
	std::streamoff pos_old;
	char line[6];

	// Перезаписывает только значение номера кластера, которое расположено 
	// в определенном месте в записи транзакции, а именно последние 4 байта строки
	sprintf_s( line, "%.4d\n", clusterIndex_new + 1 );

	pos_old = m_dataFStream.tellg();
	m_dataFStream.seekp(-6, std::ios_base::cur);
	m_dataFStream.write( line, 5);
	m_dataFStream.seekg(pos_old, std::ios_base::beg);
}


void MushroomDBManager::rewind()
{
	openFile(m_dataFilename);
}
