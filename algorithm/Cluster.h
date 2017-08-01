#pragma once
#include "stdafx.h"


template <typename Transaction>
class Cluster
{
public:
	Cluster();
	Cluster( const Transaction &transaction );

	bool empty() const;
	bool isContain( const typename Transaction::itemType &item ) const;
	const double deltaAdd ( const Transaction &transaction ) const;
	void add( const Transaction &transaction ) ;
	void remove( const Transaction &transaction ) ;

private:
	int m_transNum;
	int m_width;
	int m_size;
	std::unordered_map< typename Transaction::itemType, int, typename Transaction::hashItem > m_occ;
};


template <typename Transaction>
Cluster<Transaction>::Cluster()
	:m_transNum(0), m_width(0), m_size(0)
{

}


template <typename Transaction>
Cluster<Transaction>::Cluster( const Transaction &transaction )
	:m_transNum(0), m_width(0), m_size(0)
{
	add( transaction );
}


template <typename Transaction>
bool Cluster<Transaction>::empty() const
{ 
	return m_transNum == 0; 
}


template <typename Transaction>
bool::Cluster<Transaction>::isContain( const typename Transaction::itemType &item ) const 
{ 
	return m_occ.find( item ) != m_occ.end(); 
}


template <typename Transaction>
const double Cluster<Transaction>::deltaAdd ( const Transaction &transaction ) const 
{
	int size_new = m_size;
	int width_new = m_width;

	for ( int i = 0; i < transaction.size(); ++i )
	{
		if ( transaction.isCorrectValue(i) ) {
			auto item = transaction.item(i);
			if ( !isContain(item) )
				++width_new;
			++size_new;
		}
	}

	if ( m_transNum ) {
		return size_new*(m_transNum + 1)/pow(width_new, R) - m_size*m_transNum/pow(m_width, R);
	} else {
		return size_new / pow(width_new, R);
	}
}


template <typename Transaction>
void Cluster<Transaction>::add( const Transaction &transaction ) 
{
	++m_transNum;

	for ( int i = 0; i < transaction.size(); ++i )
	{
		if ( transaction.isCorrectValue(i) ) {
			auto item = transaction.item(i);
			if ( !isContain(item) ) 
				++m_width;
			++m_occ[item];
			++m_size;
		}
	}
}

template <typename Transaction>
void Cluster<Transaction>::remove( const Transaction &transaction ) 
{
	--m_transNum;

	for ( int i = 0; i < transaction.size(); ++i )
	{
		if ( transaction.isCorrectValue(i) ) {
			auto item = transaction.item(i);
			if ( m_occ[ item ] == 0 ) {
				m_occ.erase( item );
				--m_width;
			}
			--m_occ[ item ];
			--m_size;
		}
	}

}