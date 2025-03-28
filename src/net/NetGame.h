// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "game.h"
#include "net/type.h"

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

namespace net {
namespace tx { class DataExchanger; class EventExchanger; } // namespace tx 
class NetGame : public ::Game {
	// TODO(alex): get from network
	static constexpr auto c_MODE = cista::mode::NONE
			| cista::mode::WITH_VERSION
			| cista::mode::WITH_INTEGRITY
			| cista::mode::DEEP_CHECK
		;

public:
    /**
     * Allows multi-player
     */
	NetGame(int players_count);
	~NetGame();

	void draw() override;
	void update(Uint32 dt) override;

private:
	virtual void generateEnemy() override;
	bool m_fullMap = false;

	// TODO(alex): uglyAndFast, omitt `static`, delete in App::run
	inline static std::shared_ptr< NetPlayer > m_playerPtr;

	std::unique_ptr< tx::DataExchanger > m_txEmmiter;
	std::unique_ptr< tx::EventExchanger > m_txEventer;
	Level m_level;
	void emmiter_();
	void eventer_();

	template <typename... Args>
	static constexpr auto serialize_(Args&&... args) {
		return cista::serialize< c_MODE >( std::forward< Args >( args )... );
	}
	template <typename T>
	static constexpr auto deserialize_(cista::byte_buf const& data) {
		return cista::deserialize< T, c_MODE >( data );
	}

	using func_t = std::function< void(int i, int j, Object *&object) >;
	void forEachParentLevel_(func_t cb) {
		std::for_each( Game::m_level.begin( ), Game::m_level.end( ), [this, cb](std::vector<Object *> &element) {
				int i = &element - &Game::m_level[ 0 ];
				int j = -1;
				for ( Object *&object : element ) {
					++j;
					//if ( !object ) 
					//	continue;
					cb( i, j, object );
				}
			} );
	}
};
} // namespace net
