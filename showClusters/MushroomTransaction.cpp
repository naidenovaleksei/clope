#include "MushroomTransaction.h"

#define CLUSTER_NO_LENGTH 4	// количество символов в записи номера кластера в строке "p,[22 объекта],XXXX"
#define CLUSTER_NO_POS 46	// позиция записи номера кластера в строке "p,[22 объекта],XXXX"
#define ELEM_LENGTH 2		// количество символов между записями соседних объектов

// Возвращает значение номера кластера, которое расположено 
// в определенном месте в записи транзакции, а именно последние 4 байта строки (смещение CLUSTER_NO_POS)
const int MushroomTransaction::clusterIndex() const 
{
	char number[ CLUSTER_NO_LENGTH + 1 ];
	m_line.copy( number, CLUSTER_NO_LENGTH, CLUSTER_NO_POS );
	number[ CLUSTER_NO_LENGTH ] = '\n';
	return atoi( number ) - 1;
}


// Преобразует строку транзакции в массив элементов, где
//	индекс массива - порядковый номер параметра транзакции
//	содержимое элемента - значение параметра транзакции ('a'..'z', '?' - не определено)
void MushroomTransaction::setData( const std::string& line )
{
	char value;
	m_line = line;

	for ( int index = 0; index < ITEMCOUNT; ++index )
	{
		value = m_line[ (index + 1)*ELEM_LENGTH ];
		if ( value == '?' ||  (value >= 'a' && value <= 'z') ) {
			m_items[index] = value;
		} else {
			std::cout << "DataBase must consist of only items [a..z] and '?'.\n";
			exit(3);
		}
	}
}