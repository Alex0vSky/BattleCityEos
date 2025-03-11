// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net.h"
#include "net/tx/DataExchanger.h"
#include "net/tx/EventExchanger.h"
#include "cista/typeHash.h"
#include "cista/xerialize.h"
//#include "../ThirdParty/Hexdump.hpp"
        
#define GETFULLMAP
//#define GETPLAYER
//#ifdef DUMMY
//#endif // DUMMY
namespace net {

template<typename T1, typename T2>
void assignment(T1& lhs, T2 const& rhs) {
	lhs.reserve( rhs.size( ) );
	std::transform(
		rhs.begin( ), rhs.end( ), std::back_inserter( lhs )
		, [](T2::value_type const& element) { 
				typename T1::value_type row;
				row.reserve( element.size( ) );
				std::copy( element.begin( ), element.end( ), std::back_inserter( row ) );
				return row;
			}
	);
}

NetGame::NetGame(int players_count) :
	Game( 1 )
	, m_txEmmiter{ std::make_unique< tx::DataExchanger >( ) }
	, m_txEventer{ std::make_unique< tx::EventExchanger >( ) }
{
//*
	//auto tmp0 = cista::type_hash< net::NetPlayer >( );
	// clear generating level for client, from `void Game::clearLevel()`
	if ( NetworkApplicationType::Client == AppConfig::appType ) {
		for ( auto &row : Game::m_level ) {
			for ( auto &item : row ) {
				if ( item != nullptr ) 
					delete item;
				// to '. = empty field'
				item = nullptr;
			}
		}
	}
 
	using Command = tx::DataExchanger::Command;
#ifdef GETFULLMAP
	m_txEmmiter ->setCommandHandler< Command::GetFullMap >( 
			[this](tx::Buffer const& data) mutable ->void
			{
				Level level = *deserialize_< Level >( data );
				std::copy( level.begin( ), level.end( ), NetGame::m_level.begin( ) );
				forEachParentLevel_( [this](int i, int j, Object *&object) {
						if ( nullptr == object )
							__nop( );
						auto &ref = NetGame::m_level[ i ][ j ];
						if ( auto* pval = std::get_if< Object >( &ref ) )
							object = pval;
						if ( auto* pval = std::get_if< Brick >( &ref ) )
							object = pval;
					} );
				//std::vector< std::vector< element_t > > level1_;
				//assignment( level1_, NetGame::m_level ); // tmp check
				//__nop( );
			}
			, [this](void) mutable ->tx::Buffer 
			{
				if ( m_fullMap ) 
					return { };
				m_fullMap = true;
				// for `Game::m_level`
				forEachParentLevel_( [this](int i, int j, Object *&object) {
						if ( nullptr == object )
							return;
						auto &ref = NetGame::m_level[ i ][ j ];
						if ( Brick* brick = dynamic_cast< Brick* >( object ) ) 
							ref = *brick;
						else 
							ref = *object;
					} );
				////std::vector< std::vector< element_t > > level_;
				////assignment( level_, NetGame::m_level ); // tmp check
				////__nop( );

				//if ( !m_playerPtr ->m_isDurty )
				//	co_return;
				//m_playerPtr ->m_isDurty = false;

				////printf( "[server] ptr: %p\n", m_playerPtr ); //
				//printf( "[server] pos_y: %d\n", (int)m_playerPtr ->pos_y ); //
				////printf( "[server] m_flags: %d\n", (int)m_playerPtr ->m_flags ); //
				//printf( "[server] m_current_frame: %d\n", (int)m_playerPtr ->m_current_frame ); //

				//// trace
				//auto trace = ( std::stringstream( )<< Hexdump( data.data( ), std::min( size_t{ 16 }, data.size( ) ) ) ).str( );
				//printf( "[m_txEmmiter::serverSide] %s", trace.c_str( ) );

				return serialize_( NetGame::m_level );
			}
		);
#endif // GETFULLMAP

#ifdef GETPLAYER
	m_txEmmiter ->setCommandHandler< Command::Player >( 
			[this](tx::Buffer const& data) mutable ->void
			{
				//// trace
				//auto trace = ( std::stringstream( )<< Hexdump( data.data( ), std::min( size_t{ 16 }, data.size( ) ) ) ).str( );
				//printf( "[m_txEmmiter::clientSide] %s", trace.c_str( ) );

				//auto buffer1 = data;
				//if ( !deserialize_< NetPlayer >( buffer1 ) ->m_shots.empty( ) )
				//	__nop( );
				//auto playerTmp = *deserialize_< NetPlayer >( data );
				// *m_playerPtr = playerTmp;

				NetPlayer netPlayer = *m_playerPtr;
				netPlayer = *deserialize_< NetPlayer >( data );
				*m_playerPtr = netPlayer;
				//printf( "[client] ptr: %p\n", m_playerPtr ); //
				//printf( "[client] pos_y: %d\n", (int)m_playerPtr ->pos_y ); //
				//printf( "[client] m_flags: %d\n", (int)m_playerPtr ->m_flags ); //
				//printf( "[client] m_current_frame: %d\n", (int)m_playerPtr ->m_current_frame ); //
				__nop( );
			}
			, [this](void) mutable ->tx::Buffer 
			{
				if ( !m_playerPtr ->m_isDurty )
					return { };
				m_playerPtr ->m_isDurty = false;

				return serialize_( *m_playerPtr );
			}
		);
#endif // GETPLAYER

	using EventName = tx::EventExchanger::Eventer::EventName;
	using EventData = tx::EventExchanger::Eventer::EventData;
	using EventShotOwner = tx::EventExchanger::EventData::Shot::Owner;
	m_txEventer ->setCommandHandler< EventName::ClientShot >( 
			[this](void) mutable ->tx::Buffer 
			{
				Bullet bullet;
				if ( !m_playerPtr ->getBulletOfShot( &bullet ) ) 
					return { };
				EventData::Shot eventData{ EventShotOwner::Player, bullet };
				return serialize_( eventData );
			}
			, [this](tx::Buffer const& data) mutable ->void
			{
				auto shot = *deserialize_< EventData::Shot >( data );
				Bullet bullet = shot.bullet;
				printf( "[server] bullet, pos_x/pos_y: %f/%f\n", bullet.pos_x, bullet.pos_y ); //
				// ...
				return;
			}
		);
	m_txEventer ->setCommandHandler< EventName::ClientMovement >( 
			[this](void) mutable ->tx::Buffer 
			{
				if ( !m_playerPtr ->m_isDurty ) 
					return { };
				m_playerPtr ->m_isDurty = false;
				EventData::Movement eventData{ m_playerPtr ->pos_x, m_playerPtr ->pos_y, m_playerPtr ->direction, m_playerPtr ->stop };
				return serialize_( eventData );
			}
			, [this](tx::Buffer const& data) mutable ->void
			{
				auto movement = *deserialize_< EventData::Movement >( data );
				printf( "[server] movement, pos_x/pos_y: %f/%f\n", movement.pos_x, movement.pos_y ); //
				m_playerPtr ->pos_x = movement.pos_x;
				m_playerPtr ->pos_y = movement.pos_y;
				//m_playerPtr ->stop = movement.stop;
				m_playerPtr ->setDirection( movement.direction );
				return;
			}
		);
//*/
}
} // namespace net
    