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
#ifdef A0S_SCHEMA_CISTA
#	include <boost/asio.hpp>
#	include <boost/process/v2/process.hpp>
#endif // A0S_SCHEMA_CISTA
 
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
	// for `boost::system::error_code::message` language
	setlocale( 0, "" );
#	if ( defined( _WIN32 ) )
	//PostMessage(GetConsoleWindow(),WM_QUIT,0,0);
#	endif // ( defined( _WIN32 ) )
#endif // ( defined( _DEBUG ) ) & ( defined( _WIN32 ) )

	/*
#ifdef A0S_SCHEMA_ICE
	// to support legacy business logic
static_assert( std::is_convertible_v< Acme::SDL_Rect, SDL_Rect >
		, "\n"
		"path to src/schema/ice/sliced/acme.h#88\n"
		"	operator ::SDL_Rect() const {\n"
		"		return ::SDL_Rect{ x, y, w, h };\n"
		"	}\n"
	);
static_assert( std::is_convertible_v< Acme::SDL_Point, SDL_Point >
		, "\n"
		"path to src/schema/ice/sliced/acme.h#118\n"
		"	operator ::SDL_Point() const {\n"
		"		return ::SDL_Point{ x, y };\n"
		"	}\n"
	);
static_assert( std::is_assignable_v< SDL_Point, Acme::SDL_Point >
		, "\n"
		"path to src/schema/ice/sliced/acme.h#118\n"
		"	SDL_Point &operator=(::SDL_Point const& rhs) {\n"
		"		x = ( rhs.x ), y = ( rhs.y );\n"
		"		return *this;\n"
		"	}\n"
	);
#endif // A0S_SCHEMA_ICE
	//*/

	// tmp 
#ifdef A0S_SCHEMA_CISTA
	namespace pb = boost::process::v2;
	boost::asio::io_context ctx;
	auto pathCurrentProcess = std::filesystem::canonical( args[ 0 ] );
	struct jthread : std::thread { using std::thread::thread; ~jthread() { join( ); } };
	std::unique_ptr< jthread > terminateSelfIfParent;
	bool isServer = ( argc > 1 );
	if ( !isServer ) {
		pb::process( ctx, pathCurrentProcess, { std::to_string( pb::current_pid( ) ) } ).detach( );
	} else {
		terminateSelfIfParent = std::make_unique< jthread >( [&ctx, pidParent = pb::pid_type( std::stoi( args[ 1 ] ) )] {
				//__debugbreak( );
				while ( std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) ), true ) 
					try {
						if ( pb::process parent( ctx.get_executor( ), pidParent ); !parent.is_open( ) )
							break;
					} catch (boost::system::system_error const&) {
						break;
					}
				std::exit( 0 );
			} );
	}
#endif // A0S_SCHEMA_CISTA

	// tmp
#ifdef A0S_SCHEMA_ICE
#	ifdef ICE_STATIC_LIBS
    Ice::registerIceSSL( );
    Ice::registerIceWS( );
#	endif
    try {
        Ice::InitializationData initData;
        initData.properties = Ice::createProperties( argc, args );
        const Ice::CommunicatorHolder ich( argc, args, initData );
		//auto communicator1 = ich.communicator( );
		//std::shared_ptr< Ice::Communicator > const& communicator2 = ich.communicator( );
		Ice::CommunicatorPtr const& communicator = ich.communicator( );

		//BaseObject zxc0;
		//Acme::BaseObject qwe0;
		////zxc0 = qwe0;
		////qwe0 = zxc0;
		

#ifdef ICE_CPP11_MAPPING
		//Ice::ValueFactory valueFactory = [](const std::string& type)
		//		{ 
		//			assert(type == Acme::Bullet::ice_staticId());
		//			//return new Acme::Bullet;
		//			::std::shared_ptr< Ice::Value > value;
		//			return value;
		//		};
		//communicator 
		//	->getValueFactoryManager( ) 
		//	->add( valueFactory, Acme::Bullet::ice_staticId( ) );

		Ice::ByteSeq outParams;
		Ice::OutputStream out( communicator );
		out.startEncapsulation();
			auto c = std::make_shared< Acme::Tank >( );
			//auto bulletMix = std::make_shared< Acme::BulletMix >( );
			//auto bulletMix = std::make_shared< Acme::BulletMixI >( );
			//auto asd0 = communicator ->stringToProxy( "::Acme::BulletMix" );
			//auto asd1 = communicator ->stringToProxy( "Acme::BulletMix" );
			//auto asd2 = communicator ->stringToProxy( "Acme::Bullet" );
			auto asd3 = communicator ->stringToProxy( "BulletMix2" );
			//std::shared_ptr< Acme::BulletMix > p = Ice::checkedCast< Acme::BulletMixPrx >( asd3 );
			//auto p = Ice::checkedCast< Acme::BulletMixPrx >( asd3 );

			//auto bulletMixPrx = Ice::uncheckedCast< Acme::BulletMix2 >( asd3 );
			//auto bulletMixPrx = std::make_shared< Acme::BulletMix2 >( );
			Acme::BulletMix2Ptr bulletMixPrx;
			auto zxc0 = bulletMixPrx ->get( );
			__nop( );

			//auto bulletMixPrx = std::make_shared< Acme::BulletMixPrx >( );
			//auto bullet = std::make_shared< Acme::Bullet >( );
			//bullet ->pos_x = 2;
			//bulletMixPrx ->set( bullet );
			//c->bullets.push_back( bulletMix );
			c->bullets.push_back( bulletMixPrx );

			c->pos_x = 1;
			out.write( c );
		out.writePendingValues( );
		out.endEncapsulation( );
		out.finished( outParams );
		auto justBytes = &(*outParams.cbegin( )); (justBytes);
		__nop( );

		Ice::ByteSeq inParams( outParams.cbegin( ), outParams.cend( ) );
		Ice::InputStream in(communicator, inParams);
		in.startEncapsulation( );
		//Acme::BrickPtr b;
		Acme::TankPtr b;
		in.read( b );
		// ?in.endEncapsulation( );
		__nop( );
#endif // ICE_CPP11_MAPPING

    } catch(const std::exception& ex) {
        std::cerr << args[ 0 ] << ": " << ex.what( ) << std::endl;
    }
#endif // A0S_SCHEMA_ICE

	App app;
#ifdef A0S_SCHEMA_CISTA
    app.run( isServer );
#else // A0S_SCHEMA_CISTA
    app.run();
#endif // A0S_SCHEMA_CISTA

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
#endif // GOOGLE_PROTOBUF_VERSION
    return 0;
}
