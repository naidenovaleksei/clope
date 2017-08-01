#pragma once
#include "stdafx.h"
#include "Transaction.h"

/**
*	MushroomTransaction - предоставляет интерфейс для работы с транзакциями в алгоритме CLOPE 
*	в случае использования "Mushroom dataset".
*
*/
class MushroomTransaction: public Transaction
{
private:
	static const int ITEMCOUNT = 22;
public:
	typedef std::pair<int, char> itemType;
	struct hashItem;

public:
	inline itemType item( int i ) const;
	inline const int size() const;
	inline const char getType() const;
	inline bool isCorrectValue( int i ) const;

	const int clusterIndex() const;
	void setData( const std::string& line );

private:
	std::array< char, ITEMCOUNT > m_items;
	std::string m_line;
};


struct MushroomTransaction::hashItem {
	size_t operator()(const itemType &item ) const
	{
		return item.first*26 + item.second;
	}
};


const int MushroomTransaction::size() const 
{ 
	return m_items.size(); 
}


const char MushroomTransaction::getType() const
{ 
	return m_line[0]; 
}


MushroomTransaction::itemType MushroomTransaction::item( int i ) const 
{ 
	return itemType( i, m_items[i] ); 
}


bool MushroomTransaction::isCorrectValue( int i ) const 
{
	return m_items[i] >= 'a' && m_items[i] <= 'z';
}

