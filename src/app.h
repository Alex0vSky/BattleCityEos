#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "app_state/iappstate.h"
#include "appconfig.h"
#include "app_state/menu.h"

/**
 * @brief
 * Application main class. Its operation is equivalent to that of the application.
 */
class App {
    /**
     * A variable that keeps the main program loop running.
     */
    bool is_running;
    /**
     * Current application status.
     */
    IAppState* m_app_state;
    /**
     * Application window object.
     */
    SDL_Window* m_window = nullptr;

public:
    ~App() {
		delete m_app_state;
	}
    /**
     * The function includes initialization of the SDL2 library, game engine, loading of textures and fonts.
     * After correct initialization, the program enters the main loop, which in turn: reacts to the event,
     * updates the current state of the application, draws objects on the screen.
     */
#ifdef A0S_SCHEMA_CISTA
    void run(bool isServer = false) {
#else // A0S_SCHEMA_CISTA
    void run() {
#endif // A0S_SCHEMA_CISTA
		is_running = true;
		//initialize SDL and create windows

		if(SDL_Init( SDL_INIT_VIDEO|SDL_INIT_AUDIO ) == 0)
		{
#ifdef A0S_SCHEMA_CISTA
			m_window = SDL_CreateWindow( ( isServer ?"TANKS - server" :"TANKS - client" ), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										AppConfig::windows_rect.w, AppConfig::windows_rect.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
#else // A0S_SCHEMA_CISTA
			m_window = SDL_CreateWindow("TANKS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										AppConfig::windows_rect.w, AppConfig::windows_rect.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
#endif // A0S_SCHEMA_CISTA

			if(m_window == nullptr) return;

			if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return;
			if(TTF_Init() == -1) return;
			if ( 0 != Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 1536) ) return;

			srand(time(NULL)); //initializing the pseudorandom generator

			Engine& engine = Engine::getEngine();
			engine.initModules();
			engine.getRenderer()->loadTexture(m_window);
			engine.getRenderer()->loadFont();
			engine.getAudio( ) ->loadSound( );

			m_app_state = new Menu;
#ifdef A0S_SCHEMA_CISTA
			m_app_state ->setServer( isServer );
#endif // A0S_SCHEMA_CISTA

			double FPS;
			Uint32 time1, time2, dt, fps_time = 0, fps_count = 0, delay = 15;
			time1 = SDL_GetTicks();
			while(is_running)
			{
				time2 = SDL_GetTicks();
				dt = time2 - time1;
				time1 = time2;

				if(m_app_state->finished())
				{
					IAppState* new_state = m_app_state->nextState();
					delete m_app_state;
					m_app_state = new_state;
				}
				if(m_app_state == nullptr) break;

				eventProcess();

				m_app_state->update(dt);
				m_app_state->draw();

				SDL_Delay(delay);

				//FPS
				fps_time += dt; fps_count++;
				if(fps_time > 200)
				{
					FPS = (double)fps_count / fps_time * 1000;
					if(FPS > 60) delay++;
					else if(delay > 0) delay--;
					fps_time = 0; fps_count = 0;
				}
			}

			engine.destroyModules();
		}

		SDL_DestroyWindow(m_window);
		m_window = nullptr;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
    /**
     * Function handling queued events.
     */
    void eventProcess() {
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				is_running = false;
			}
			else if(event.type == SDL_WINDOWEVENT)
			{
				if(event.window.event == SDL_WINDOWEVENT_RESIZED ||
				   event.window.event == SDL_WINDOWEVENT_MAXIMIZED ||
				   event.window.event == SDL_WINDOWEVENT_RESTORED ||
				   event.window.event == SDL_WINDOWEVENT_SHOWN)
				{

					AppConfig::windows_rect.w = event.window.data1;
					AppConfig::windows_rect.h = event.window.data2;
					Engine::getEngine().getRenderer()->setScale((float)AppConfig::windows_rect.w / (AppConfig::map_rect.w + AppConfig::status_rect.w),
																(float)AppConfig::windows_rect.h / AppConfig::map_rect.h);
				}
			}

			m_app_state->eventProcess(&event);
		}
	}
};
