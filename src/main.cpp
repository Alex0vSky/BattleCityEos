/**
 * \mainpage
 * \par Tanks
 * Gra w czołgi wzorowana na Battle City / Tank 1990 umożliwiająca grę przez jednego lub dwóch graczy
 * \author Krystian Kałużny
 * \date 12.05.215
 * \version 1.0
 * \par Kontakt:
 * \a k.kaluzny141@gmail.com
 * TODO(alex): writeme
*/

#include "app.h"

int main( int argc, char* args[] )
{
#if ( defined( _DEBUG ) ) & ( defined( _WIN32 ) )
    HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, NULL );
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 1895 );
#	ifdef new
#		error `new` has been redefined
#	endif
	new char[]{ "Goobay!" };
#endif

    App app;
    app.run();

#ifdef GOOGLE_PROTOBUF_VERSION
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	google::protobuf::ShutdownProtobufLibrary( );
#endif // PROTOBUF_VERSION
    return 0;
}
