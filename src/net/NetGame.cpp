// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net.h"
#include "net/tx/DataExchanger.h"
#include "net/tx/EventExchanger.h"
   
namespace net {

NetGame::~NetGame()
{
//*
	//Game::m_players.clear( );
	//m_playerPtr.reset( );
	forEachParentLevel_( [this](int i, int j, Object *&object) {
			if ( nullptr == object )
				return;
			delete object;
			object = nullptr;
		} );
	Game::m_level.clear( );
	m_txEmmiter.reset( );
	m_txEventer.reset( );
//*/
}

void NetGame::generateEnemy() {
//*
	// dont generate ememies for client
	if ( NetworkApplicationType::Server == AppConfig::appType )
		Game::generateEnemy( );
//*/
}
void NetGame::update(Uint32 dt) {
//*
	// Initial rewrite
	if ( !m_playerPtr ) {
		for ( auto player : Game::m_players ) 
			delete player;
		Game::m_players.clear( );

		unsigned playerIndex = 0;
		m_playerPtr = std::make_shared< NetPlayer > ( 
				AppConfig::player_starting_point.at( playerIndex ).x
				, AppConfig::player_starting_point.at( playerIndex ).y
				, sprite_t::ST_PLAYER_1
			);
		m_playerPtr ->player_keys = AppConfig::player_keys.at( playerIndex );
		++playerIndex;
		Game::m_players.push_back( m_playerPtr.get( ) );

		NetGame::m_level.resize( Game::m_level.size( ) );
		std::for_each( Game::m_level.begin( ), Game::m_level.end( ), [this](std::vector<Object *> &element) {
			    int i = &element - &Game::m_level[ 0 ];
				NetGame::m_level[ i ].resize( element.size( ) );
			} );

		//std::vector< std::vector< element_t > > level_;
		//assignment( level_, NetGame::m_level ); // tmp check
		//__nop( );

		//// tmp
		//m_playerPtr ->setFlag( TankStateFlag::TSF_LIFE );
		//Bullet* bullet = m_playerPtr ->fire( );
		//m_playerPtr ->clearFlag( TankStateFlag::TSF_LIFE );
		//m_playerPtr ->m_shots.push_back( *bullet );
		////auto buffer0 = serialize_( m_playerPtr ->m_shots );
		////auto asd0 = *deserialize_< net::NetPlayer::shoots_t >( buffer0 );
		//auto buffer1 = serialize_( *m_playerPtr );
		//auto asd1 = *deserialize_< net::NetPlayer >( buffer1 );
		__nop( );
	}

	if ( NetworkApplicationType::IntraProcess != AppConfig::appType || !m_playerPtr ->m_isDurty ) {
		Game::update( dt );
		//printf( "[NetGam] m_flags: %d\n", (int)m_playerPtr ->m_flags ); //
		//printf( "[NetGam] m_current_frame: %d\n", (int)m_playerPtr ->m_current_frame ); //
		//printf( "[NetGam] pos_y: %d\n", (int)m_playerPtr ->pos_y ); //
		//m_playerPtr ->m_isDurty = true;
	}

	if ( m_txEmmiter ) m_txEmmiter ->update( ); // Eventer check, commented
	if ( m_txEventer ) m_txEventer ->update( ); // Eventer check, uncommented
//*/
}
void NetGame::draw() {
//*
    Engine& engine = Engine::getEngine();
    Renderer* renderer = engine.getRenderer();
    renderer->clear();

    if(m_level_start_screen)
    {
        std::string level_name = "STAGE " + Engine::intToString(m_current_level);
        renderer->drawText(nullptr, level_name, {255, 255, 255, 255}, 1);
    }
    else
    {
        renderer->drawRect(&AppConfig::map_rect, {0, 0, 0, 0}, true);
        for(auto row : Game::m_level)
            for(auto item : row)
                if(item != nullptr) item->draw();

        for(auto player : m_players) player->draw();
		// tmp comment
        for(auto enemy : m_enemies) enemy->draw();
        for(auto bush : m_bushes) bush->draw();
        for(auto bonus : m_bonuses) bonus->draw();
        m_eagle->draw();

        if(m_game_over)
        {
            point_t pos;
            pos.x = -1;
            pos.y = m_game_over_position;
            renderer->drawText(&pos, AppConfig::game_over_text.data( ), {255, 10, 10, 255});
			Engine::getEngine( ).getAudio( ) ->playSound( ) ->gameover( );
        }

        //=============Game Status=============
        rect_t src = engine.getSpriteConfig()->getSpriteData(sprite_t::ST_LEFT_ENEMY)->rect;
        rect_t dst;
        point_t p_dst;
        //enemies to kill
        for(int i = 0; i < static_cast<int>(m_enemy_to_kill); i++)
        {
            dst = {AppConfig::status_rect.x + 8 + src.w * (i % 2), 5 + src.h * (i / 2), src.w, src.h};
            renderer->drawObject(src, dst);
        }
        //player lives
        int i = 0;
        for(auto player : m_players)
        {
            dst = {AppConfig::status_rect.x + 5, i * 18 + 180, 16, 16};
            p_dst = {dst.x + dst.w + 2, dst.y + 3};
            i++;
            renderer ->drawObject( player->src_rect, dst );
            renderer->drawText(&p_dst, Engine::intToString(player->lives_count), {0, 0, 0, 255}, 3);
        }
        //map number
        src = engine.getSpriteConfig()->getSpriteData(sprite_t::ST_STAGE_STATUS)->rect;
        dst = {AppConfig::status_rect.x + 8, static_cast<int>(185 + (m_players.size() + m_killed_players.size()) * 18), src.w, src.h};
        p_dst = {dst.x + 10, dst.y + 26};
        renderer->drawObject(src, dst);
        renderer->drawText(&p_dst, Engine::intToString(m_current_level), {0, 0, 0, 255}, 2);

        if(m_pause)
            renderer->drawText(nullptr, std::string("PAUSE"), {200, 0, 0, 255}, 1);
    }

    renderer->flush();
//*/
}
} // namespace net
    