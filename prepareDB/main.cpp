// CLOPE_prepareDB.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConsoleManager.h"

#define NOT_OPEN_DB 1

const std::string description = 
"\n\
Command format: CLOPE_prepareDB.exe -i  \n\
\n\
-i - original mushroom dataset file \n\
-o - modified mushroom dataset file \n\
\n\
Program use mushroom dataset which is \"*.txt\" file.\n\
Program create modified mushroom dataset which is \"*.txt\" file for CLOPE_algorithm.exe. \n\
Modified mushroom dataset is added 5 empty bytes like \",0000\" \n\
to store cluster-value for each transaction.\n\
\n\
Author: Naidenov Aleksei";

int modifyDB( const std::string infilename, const std::string outfilename );
int main(int argc, char* argv[])
{	
	ConsoleManager console( description );

	const std::string infilename = console.attribute( argc, argv, "-i" );
	const std::string outfilename = console.attribute( argc, argv, "-o" );

	if ( infilename.empty() || outfilename.empty() )
		console.exit();

	return modifyDB( infilename, outfilename );
}


int modifyDB( const std::string infilename, const std::string outfilename )
{
	std::ifstream inFStream;
	inFStream.open( infilename );

	std::ofstream outFStream;
	outFStream.open( outfilename, std::ios_base::trunc );

	if ( !inFStream.is_open() || !outFStream.is_open() ) {
		std::cout << "Can't open file with DB\n";
		exit( NOT_OPEN_DB );
	}

	std::string line;
	inFStream >> line;
	while ( !line.empty() )
	{
		line.append( ",   -\n" );
		outFStream << line;
		line.clear();
		inFStream >> line;
	}
	return 0;
}
