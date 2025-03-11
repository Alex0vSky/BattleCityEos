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
#define BOOST_PROCESS_USE_STD_FS
#include <boost/optional.hpp>
#include <boost/process/v2/process.hpp>
 
int main(int argc, char* args[])
{
#if ( defined( _DEBUG ) ) & ( defined( _WIN32 ) )
    HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, NULL );
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 161 );
#	ifdef new
#		error `new` has been redefined
#	endif
	new char[]{ "Goobye!" };
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

#ifdef A0S_SCHEMA_CISTA
	namespace pb = boost::process::v2;
	boost::asio::io_context ctx;
	const auto pathCurrentProcess = std::filesystem::canonical( args[ 0 ] );
	struct jthread : std::thread { using std::thread::thread; ~jthread() { join( ); } };
	std::unique_ptr< jthread > runningChild, runningParent, focusWindow;
	const auto argsChild = { std::to_string( pb::current_pid( ) ) };
	std::unique_ptr< pb::process > child;
	std::atomic_bool stop = false;
	//AppConfig::appType = NetworkApplicationType::IntraProcess; // commentme if real Client and Server
	const bool isServer = ( argc == 1 ); if ( isServer ) { 
		if ( NetworkApplicationType::Initial == AppConfig::appType ) {
			AppConfig::appType = NetworkApplicationType::Server;
			child = std::make_unique< pb::process >( ctx, pathCurrentProcess, argsChild );
			//while( true ) std::this_thread::sleep_for( std::chrono::milliseconds{ 300 } ); // run client only
			runningChild = std::make_unique< jthread >( [&child, &stop] {
					while( !stop ) {
						bool running = false;
						try {
							running = child ->running( );
						} catch (boost::system::system_error const&) {
						}
						if ( !running ) {
							printf( "[~] std::quick_exit( 0 )\n" );
							std::quick_exit( 0 );
						}
						std::this_thread::sleep_for( std::chrono::milliseconds{ 300 } );
					}
					__nop( );
				} );
		}
	} else {
		if ( NetworkApplicationType::Initial == AppConfig::appType ) { 
			//__debugbreak( ); // to debug child/client
		}
		AppConfig::appType = NetworkApplicationType::Client;
		focusWindow = std::make_unique< jthread >( [&args] {
#if ( defined( _DEBUG ) ) & ( defined( _WIN32 ) )
				std::this_thread::sleep_for( std::chrono::milliseconds{ 2 *1000 } );
				// only captureless lambdas are convertible to function pointers
				auto func = [](HWND hwnd, LPARAM server_pid) ->BOOL {
					DWORD window_pid{ 0u }; ::GetWindowThreadProcessId( hwnd, &window_pid );
					if ( pb::current_pid( ) == window_pid ) {
						printf( "[~] focus client window\n" );
					//if ( server_pid == window_pid ) {
					//	printf( "[~] focus server window\n" );

						::SetFocus( hwnd );
						//::SetActiveWindow( hwnd );
						//::SetForegroundWindow( hwnd );
					}
					return TRUE;
				};
				::EnumWindows( static_cast< WNDENUMPROC >(func), std::stoi( args[ 1 ] ) );
#endif // ( defined( _DEBUG ) ) & ( defined( _WIN32 ) )
			} );
		// stop waiting on exit from GUI
		runningParent = std::make_unique< jthread >( [&ctx, pidParent = pb::pid_type( std::stoi( args[ 1 ] ) )] {
				try {
					pb::native_exit_code_type exit_status;
					pb::process( ctx.get_executor( ), pidParent ).handle( ).wait( exit_status );
				} catch (boost::system::system_error const& ex) {
					printf( "[~] catch: %s\n", ex.what( ) );
					__nop( );
				}
				printf( "[~] 1 std::quick_exit( 0 )\n" );
				std::quick_exit( 0 );
			} );
	}
#endif // A0S_SCHEMA_CISTA

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
    app.run( );
#ifdef A0S_SCHEMA_CISTA
	stop = true;
	if ( runningParent ) {
		printf( "[~] 3 std::quick_exit( 0 )\n" );
		std::quick_exit( 0 );
	}
	ctx.reset( );
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
