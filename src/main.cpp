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
#	if ( defined( _WIN32 ) )
	PostMessage(GetConsoleWindow(),WM_QUIT,0,0);
#	endif // ( defined( _WIN32 ) )
#endif // ( defined( _DEBUG ) ) & ( defined( _WIN32 ) )

	if ( false )
	{
// TODO(alex): test here protobuf::set_allocated_object()
// +all_erase_if
// ?push_back
    Engine::getEngine().initModules( );
    Engine::getEngine().getSpriteConfig()->getSpriteData( SpriteType::ST_PLAYER_1 );
A0S_proto::PbObject *mutable_object1 = nullptr;
A0S_proto::PbObject *mutable_object2 = nullptr;
	// all_erase_if
{
	//Tank tank1( 0, 0, ST_PLAYER_1 );
	Bullet bullet1( 1, 1 );
	mutable_object1 = bullet1.dataOffline( ) ->mutable_object( );
	std::unique_ptr< Bullet > value;
	value = std::make_unique< Bullet >( 
			3, 3 
		);
	//value ->dataOffline( ) ->unsafe_arena_set_allocated_object( mutable_object1 );

	A0S_proto::PbObject *advanced = nullptr;
	advanced = value ->dataOffline( ) ->object( ).New( );
	*advanced = *mutable_object1; // PbObject::CopyFrom()
	//value ->dataOffline( ) ->set_allocated_object( advanced );
	value ->dataOffline( ) ->unsafe_arena_set_allocated_object( advanced );
	__nop( );
}

	// push_back
{
	Bullet bullet2( 2, 2 );
	mutable_object2 = bullet2.dataOffline( ) ->mutable_object( );
	google::protobuf::RepeatedPtrField< A0S_proto::PbBullet > m_original_;
	google::protobuf::RepeatedPtrField< A0S_proto::PbBullet >* m_original = &m_original_;
	Bullet *value = &bullet2;
	A0S_proto::PbBullet store;
	{
		A0S_proto::PbObject *advanced = nullptr;
		advanced = value ->dataOffline( ) ->object( ).New( );
		*advanced = *mutable_object2; // PbObject::CopyFrom()
		store.set_allocated_object( advanced );
		m_original ->Add( std::move( store ) );
		for ( auto it = m_original ->begin( ); it != m_original ->end( ); ++it) {
			auto pos_x = it ->object( ).pos_x( );
			auto pos_y = it ->object( ).pos_y( );
			__nop( );
		}
		__nop( );
	}
}
	}

	App app;
    app.run();

#ifdef GOOGLE_PROTOBUF_VERSION
#	if ( defined( _DEBUG ) ) & ( defined( _WIN32 ) )
	// Avoid MSVC 2019 incrementalLinking bug: vector deleting destructor was previously strong but is now weak; performing full link
	delete[] new A0S_proto::PbObject[ 1 ];
	delete[] new A0S_proto::PbBonus[ 1 ];
	delete[] new A0S_proto::PbTank[ 1 ];
	delete[] new A0S_proto::PbPlayer[ 1 ];
	delete[] new A0S_proto::PbBrick[ 1 ];
	delete[] new A0S_proto::PbEnemy[ 1 ];
	delete[] new A0S_proto::PbBullet[ 1 ];
#endif // ( defined( _DEBUG ) ) & ( defined( _WIN32 ) )
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
