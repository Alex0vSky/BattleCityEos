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

int main(int argc, char* args[])
{
#if ( defined( _DEBUG ) ) & ( defined( _WIN32 ) )
    HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, NULL );
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 161 );
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
	// still memory leaks in dynamic_init_dummy_acme_2eproto...btree_set, not in google::protobuf::DescriptorPool::generated_pool( ); / google::protobuf::DescriptorPool::internal_generated_pool( ); / google::protobuf::DescriptorPool::internal_generated_database( );
//{163} normal block at 0x011AF750, 8 bytes long.
// Data: <P       > 50 F7 1A 01 00 00 00 01 
//{161} normal block at 0x011AF718, 8 bytes long.
// Data: <        > 18 F7 1A 01 00 00 00 01 
//{159} normal block at 0x011AF6A8, 8 bytes long.
// Data: <        > A8 F6 1A 01 00 00 00 01 
#endif // PROTOBUF_VERSION
    return 0;
}
