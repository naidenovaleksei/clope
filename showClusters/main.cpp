#include "stdafx.h"
#include "ConsoleManager.h"
#include "DBView.h"

const std::string description = 
"\n\
Command format: CLOPE_showClusters.exe -i  \n\
\n\
-i - modified mushroom dataset file \n\
\n\
Program use modified mushroom dataset which is \"*.txt\" file in result of CLOPE_algorithm.exe. \n\
Program output is the mushroom dataset table in like-console view. \n\
\n\
Top view:\n\
    Cluster | p     | e  \n\
    --------|-------|----\n\
       1    | ...   | ...\n\
       2    | ...   | ...\n\
\n\
Author: Naidenov Aleksei";

int main(int argc, char* argv[])
{	
	ConsoleManager console( description );
	const std::string infilename = console.attribute( argc, argv, "-i" );
	if ( infilename.empty() )
		console.exit();

	DBView view;
	view.openFile( infilename );
	view.showDB();

	return 0;
}

