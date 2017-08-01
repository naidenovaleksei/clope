#include "DataReader.h"

bool MushroomDBManager::isReady() const
{
	return m_dataFStream.is_open();
}

/* setDataFilename = openFile*/
void MushroomDBManager::setDataFilename( const string& dataFilename )
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

	sprintf_s( line, "%.4d\n", clusterIndex_new+1 );

	pos_old = m_dataFStream.tellg();
	m_dataFStream.seekp(-6, std::ios_base::cur);
	m_dataFStream.write( line, 5);
	m_dataFStream.seekg(pos_old, std::ios_base::beg);
}

void MushroomDBManager::rewind()
{
	setDataFilename(m_dataFilename);
}

MushroomDBManager::Transaction::Transaction() 
{
	//m_items.resize(ITEMCOUNT);
}


int MushroomDBManager::Transaction::size() const 
{ 
	return m_items.size(); 
}


int MushroomDBManager::Transaction::clusterIndex() const 
{
	char number[5];
	/* - magic numbers!!!*/
	m_line.copy(number, 4, 46);
	number[4] = '\n';
	return atoi( number )-1;
}

char MushroomDBManager::Transaction::getType() const
{ 
	return m_line[0]; 
}


MushroomDBManager::Transaction::itemType MushroomDBManager::Transaction::item( int i ) const 
{ 
	return itemType( i, m_items[i] ); 
}


bool MushroomDBManager::Transaction::isCorrectValue( int i ) const 
{
	return m_items[i] >= 'a' && m_items[i] <= 'z';
}


void MushroomDBManager::Transaction::setData( const std::string& line )
{
	m_line = line;
	char value;
	/* пожалуйста, пробелы */
	for (int index = 0; index<ITEMCOUNT; index++)
	{
		value = m_line[index*2+2];
		if ( value == '?' ||  (value >= 'a' && value <= 'z') ) {
			m_items[index] = value;
		} else {
			std::cout << "DataBase must consist of only items [a..z] and '?'.\n";
			exit(3);
		}
	}
}