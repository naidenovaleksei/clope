#include "ConsoleManager.h"


ConsoleManager::ConsoleManager()
{

}


ConsoleManager::ConsoleManager( const std::string description )
	:m_description( description )
{

}



std::string ConsoleManager::attribute( int argc, char* argv[], const std::string &attrName )
{
	std::string attrValue = "";
	if ( argc < 2 || argv == NULL ) return attrValue;

	for ( int i=1; i < argc-1; i++ )
	{
		if ( !attrName.compare(argv[i]) ) {
			attrValue = std::string( argv[i+1] );
			break;
		}
	}
	
	return attrValue;
}

void ConsoleManager::exit()
{
	std::cout << m_description;
	::exit( 1 );
}

