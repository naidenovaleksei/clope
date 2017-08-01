#pragma once

#include "stdafx.h"
#include <array> 


class MushroomDBManager 
{
private:
	static const int ITEMCOUNT = 22;
public:
	/* typedef MyTransaction Transaction; вместо чуши внизу */
	/* Андрей очень плаксиво просит убрать вложенные классы (зло, говорит) */
	class Transaction
	{
	public:
		typedef std::pair<int, char> itemType;
		struct hash_name {
			size_t operator()(const itemType &item ) const
			{
				return item.first*26 + item.second;
			}
		};

	public:
		Transaction();
		itemType item( int i ) const;
		int size() const;
		int clusterIndex() const;
		char getType() const;
		bool isCorrectValue( int i ) const;
		void setData( const std::string& line );

	private:
		std::array< char, ITEMCOUNT > m_items;
		std::string m_line;
	};

public:
	bool isReady() const;
	bool nextTransaction( Transaction& transaction );
	void updateTransaction( Transaction& currentTransaction, int clusterIndex_new );
	void setDataFilename( const string& dataFilename );
	void rewind();

private:
	std::string m_dataFilename;
	std::fstream m_dataFStream;
};
