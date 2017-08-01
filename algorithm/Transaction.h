#pragma once

#include "stdafx.h"

/**
*	Transaction - предоставляет интерфейс для работы с транзакциями в алгоритме CLOPE.
*	При использовании другого набора транзакций наследовать DBManager и Transaction.
*
*/
class Transaction
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
