#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
extern const uint8_t s_sound_backgroundIdle[16966];
extern const uint8_t s_sound_backgroundMovement[5569];
extern const uint8_t s_sound_bonus[8315];
extern const uint8_t s_sound_explosion[6625];
extern const uint8_t s_sound_fire[5539];
extern const uint8_t s_sound_gameover[15170];
extern const uint8_t s_sound_gamestart[31478];
/**
 * @brief The class combines elements related to the sound playing.
 */
class Audio {
	// @insp SO 45001462/sdl-mixer-is-playing-single-chunk-over-itself-possible
	// @insp SO 55786004/play-one-sound-after-another-with-sdl-mixer
	class Play {
		// Custom deleter
		using chunk_t = std::unique_ptr< Mix_Chunk, decltype(&Mix_FreeChunk) >;
		template<unsigned int N>
 		chunk_t load_(const uint8_t (&data)[N]) {
			int freesrcYes = 1;
			Mix_Chunk *p = Mix_LoadWAV_RW( SDL_RWFromConstMem( data, sizeof( data ) ), freesrcYes );
			return { p, &Mix_FreeChunk };
		}
		chunk_t m_gamestart, m_gameover, m_fire, m_explosion, m_bonus, m_backgroundMovement, m_backgroundIdle;
	public:
		Play() :
			m_gamestart( load_( s_sound_gamestart ) )
			, m_gameover( load_( s_sound_gameover ) )
			, m_fire( load_( s_sound_fire ) )
			, m_explosion( load_( s_sound_explosion ) )
			, m_bonus( load_( s_sound_bonus ) )
			, m_backgroundMovement( load_( s_sound_backgroundMovement ) )
			, m_backgroundIdle( load_( s_sound_backgroundIdle ) )
		{}
		// TODO(alex): to single call(c, *p,loop=0 { Mix_HaltChannel(c), Mix_PlayChannel(c, p, loop) }
		void gamestart() {
			Mix_HaltChannel(0), Mix_PlayChannel(0, m_gamestart.get( ), 0);
		}
		void gameover() {
			Mix_HaltChannel(1), Mix_PlayChannel(1, m_gameover.get( ), 0);
		}
		void fire() {
			Mix_HaltChannel(2), Mix_PlayChannel(2, m_fire.get( ), 0);
		}
		void explosion() {
			Mix_HaltChannel(3), Mix_PlayChannel(3, m_explosion.get( ), 0);
		}
		void bonus() {
			Mix_HaltChannel(4), Mix_PlayChannel(4, m_bonus.get( ), 0);
		}
		void die() {
			Mix_HaltChannel(5), Mix_HaltChannel(3);
			Mix_PlayChannel(5, m_explosion.get( ), 0);
			Mix_HaltChannel(6), Mix_HaltChannel(7);
		}
		void backgroundMovement() {
			Mix_HaltChannel(7);
			//if ( Mix_Playing( 6 ) ) return;
			Mix_HaltChannel(6), Mix_PlayChannel(6, m_backgroundMovement.get( ), -1);
		}
		void backgroundIdle() {
			Mix_HaltChannel(6);
			Mix_HaltChannel(7), Mix_PlayChannel(7, m_backgroundIdle.get( ), -1);
		}
	};
	std::shared_ptr< Play > m_play;

public:
    /**
     * @return a sound player
     */
	[[nodiscard]] Play *playSound() {
		return m_play.get( );
	}
    /**
     * Stop playing all sounds
     */
	void stopAllSounds() {
		for(int i=0; i<=7; ++i)
			Mix_HaltChannel(i);
	}
    /**
     * Sound files loading.
     */
	void loadSound() {
		m_play = std::make_shared< Play >( );
		// set default sound channels volumes
		const auto volume = MIX_MAX_VOLUME/5;
		Mix_Volume(0,volume/2);
		Mix_Volume(1,volume/2);
		Mix_Volume(2,volume/2);
		Mix_Volume(3,volume/4);
		Mix_Volume(4,volume/2);
		Mix_Volume(5,volume/2);
		Mix_Volume(6,volume);
		Mix_Volume(7,volume/4);
	}
};
