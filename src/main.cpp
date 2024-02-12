/**
 * \mainpage
 * \par Tanks
 * Gra w czołgi wzorowana na Battle City / Tank 1990 umożliwiająca grę przez jednego lub dwóch graczy
 * \author Krystian Kałużny
 * \date 12.05.215
 * \version 1.0
 * \par Kontakt:
 * \a k.kaluzny141@gmail.com
*/

#include "app.h"

int main( int argc, char* args[] )
{
#if ( defined( _DEBUG ) ) & ( defined( _WIN32 ) )
    HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, NULL );
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 1 );
	new char[]{ "Goobay!" };
#endif

    App app;
    app.run();

    return 0;
}