#include "MushroomTransaction.h"

#define CLUSTER_NO_LENGTH 4	// ���������� �������� � ������ ������ �������� � ������ "p,[22 �������],XXXX"
#define CLUSTER_NO_POS 46	// ������� ������ ������ �������� � ������ "p,[22 �������],XXXX"
#define ELEM_LENGTH 2		// ���������� �������� ����� �������� �������� ��������

// ���������� �������� ������ ��������, ������� ����������� 
// � ������������ ����� � ������ ����������, � ������ ��������� 4 ����� ������ (�������� CLUSTER_NO_POS)
const int MushroomTransaction::clusterIndex() const 
{
	char number[ CLUSTER_NO_LENGTH + 1 ];
	m_line.copy( number, CLUSTER_NO_LENGTH, CLUSTER_NO_POS );
	number[ CLUSTER_NO_LENGTH ] = '\n';
	return atoi( number ) - 1;
}


// ����������� ������ ���������� � ������ ���������, ���
//	������ ������� - ���������� ����� ��������� ����������
//	���������� �������� - �������� ��������� ���������� ('a'..'z', '?' - �� ����������)
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