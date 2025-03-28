// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/NetGame.h"
#include "xerialization.h"
//#include "../ThirdParty/Hexdump.hpp"

/*
template <typename Ctx>
void serialize(Ctx & context, net::Level const* el, cista::offset_t const offset) {
	for ( auto &row : *el )
		for ( auto &col: row ) {
			
			if ( auto *pval = std::get_if< Object >( &col ) ) {
				cista::serialize( context, *pval );
			}
			if ( auto* pval = std::get_if< Brick >( &col ) ) {
				cista::serialize( context, *pval );
			}

			__nop( );
		}
}
//*/

#define GETFULLMAP
//#define GETPLAYER
//#ifdef DUMMY
//#endif // DUMMY
namespace net {

void NetGame::emmiter_()
{
//*
	//auto tmp0 = cista::type_hash< net::NetPlayer >( );
	using Command = tx::DataExchanger::Command;
#ifdef GETFULLMAP
	m_txEmmiter ->setCommandHandler< Command::GetFullMap >( 
			[this](tx::Buffer const& data) mutable ->void
			{
				//Level level = *deserialize_< Level >( data );
				Level level; ::deserialize( data, &level );
				std::copy( level.begin( ), level.end( ), NetGame::m_level.begin( ) );
				forEachParentLevel_( [this](int i, int j, Object *&object) {
						auto &ref = NetGame::m_level[ i ][ j ];
						if ( auto* pval = cista::get_if< Object >( ref ) )
							object = new Object( *pval );
						if ( auto* pval = cista::get_if< Brick >( ref ) )
							object = new Brick( *pval );
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

				//return serialize_( NetGame::m_level );
				return ::serialize( NetGame::m_level );
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

				//return serialize_( *m_playerPtr );
				return ::serialize( *m_playerPtr );
			}
		);
#endif // GETPLAYER
//*/
}
} // namespace net
    