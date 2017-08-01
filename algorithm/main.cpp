#include "stdafx.h"

#include "ConsoleManager.h"
#include "ClopeAlgorithm.h"
#include "MushroomDBManager.h"

const std::string description = 
"\n\
Command format: CLOPE_algorithm.exe -i  -r\n\
\n\
-i - modified mushroom dataset file \n\
-r - repulsion value \n\
\n\
Program use modified mushroom dataset which is \"*.txt\" file in result of CLOPE_prepareDB.exe. \n\
Program distribute transactions by clusters and update cluster-value\n\
of transaction in modified mushroom dataset file\n\
\n\
Author: Naidenov Aleksei";

int main(int argc, char* argv[])
{
	ConsoleManager console( description );
	ClopeAlgorithm <MushroomDBManager> clopeAlgorithm;

	const std::string DBfilename = console.attribute( argc, argv, "-i" );
	const std::string repulsion = console.attribute( argc, argv, "-r" );	

	if ( DBfilename.empty() || repulsion.empty() )
		console.exit();

	clopeAlgorithm.setRepulsion( std::stod(repulsion) );
	if ( !clopeAlgorithm.openFile( DBfilename ) ) {
		std::cout << "Can't open file with DB: " << DBfilename<< "\n";
		exit( NOT_OPEN_DB );
	}

	return clopeAlgorithm.execute();
}

