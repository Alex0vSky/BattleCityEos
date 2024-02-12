#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "iappstate.h"
#include "objects/player.h"
#include "appconfig.h"
#include "engine/renderer.h"
#include "app_state/game.h"

/**
 * @brief
 * Game mode selection class: 1 player or 2 players or outputs. The class is the first state of the application, it appears immediately after starting the program and allows you to switch to the game state (Game class).
 */
class Menu : public IAppState {
    /**
     * A base offset by x
     */
	const int c_xBase = 80;
    /**
     * A container storing all the subtitles that appear in the menu.
     */
	std::vector<std::string> m_menu_texts{ 
			{ "1 Player" }
			, { "2 Players (HotSeat)" }
			, { "2 Players (Online, EOS)" }
			, { "Exit" }
		};
    /**
     * Index of the selected menu item.
     */
    int m_menu_index = 0;
    /**
     * Variable responsible for the tank indicator.
     */
    Player* m_tank_pointer;
    /**
     * The variable stores information whether to exit the current game state and go to the game or disable the application.
     */
    bool m_finished = false;

public:
    Menu() {
		m_tank_pointer = new Player(0, 0 , ST_PLAYER_1, TankStateFlag::TSF_MENU);
		m_tank_pointer->direction = D_RIGHT;
		m_tank_pointer->pos_x = c_xBase;
		m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 112;
		m_tank_pointer->setFlag(TankStateFlag::TSF_LIFE);
		m_tank_pointer->update(0);
		m_tank_pointer->clearFlag(TankStateFlag::TSF_LIFE);
		m_tank_pointer->clearFlag(TankStateFlag::TSF_SHIELD);
		m_tank_pointer->setFlag(TankStateFlag::TSF_MENU);
		Engine::getEngine( ).getAudio( ) ->stopAllSounds( );
	}
    ~Menu() {
		delete m_tank_pointer;
	}
    /**
     * The function draws the game logo, menu subtitles and the selected item indicator in the shape of a tank.
     */
    void draw() {
		Renderer* renderer = Engine::getEngine().getRenderer();
		renderer->clear();

		renderer->drawRect(&AppConfig::map_rect, {0, 0, 0, 255}, true);
		renderer->drawRect(&AppConfig::status_rect, {0, 0, 0, 255}, true);

		//LOGO
		const SpriteData* logo = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_TANKS_LOGO);
		SDL_Rect dst = {(AppConfig::map_rect.w + AppConfig::status_rect.w - logo->rect.w)/2, 50, logo->rect.w, logo->rect.h};
		renderer->drawObject(&logo->rect, &dst);

		int i = 0;
		SDL_Point text_start;
		for(auto text : m_menu_texts)
		{
			text_start = { ( c_xBase + 36 ), (i + 1) * 32 + 120};
			i++;
			renderer->drawText(&text_start, text, {255, 255, 255, 255}, 2);
		}

		m_tank_pointer->draw();

		renderer->flush();
	}
    /**
     * The function is responsible for animating the indicator in the form of a tank.
     * @param dt - time since the last animation
     * @see Tank::update(Uint32 dt)
     */
    void update(Uint32 dt) {
		m_tank_pointer->speed = m_tank_pointer->default_speed;
		m_tank_pointer->stop = true;
		m_tank_pointer->update(dt);
	}
    /**
     * The function responds to keystrokes:
     * @li Up and down arrow - change the selected menu item
     * @li Enter and Space - confirms the current menu item
     * @li Esc - exit the program
     * @param ev - pointer to the SDL_Event union storing the type and parameters of various events
     */
    void eventProcess(SDL_Event* ev) {
		if(ev->type == SDL_KEYDOWN)
		{
			if(ev->key.keysym.sym == SDLK_UP)
			{
				m_menu_index--;
				if(m_menu_index < 0)
					m_menu_index = m_menu_texts.size() - 1;

				m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 110;
			}
			else if(ev->key.keysym.sym == SDLK_DOWN)
			{
				m_menu_index++;
				if(static_cast<size_t>(m_menu_index) >= m_menu_texts.size())
					m_menu_index = 0;

				m_tank_pointer->pos_y = (m_menu_index + 1) * 32 + 110;
			}
			else if(ev->key.keysym.sym == SDLK_SPACE || ev->key.keysym.sym == SDLK_RETURN)
			{
				m_finished = true;
			}
			else if(ev->key.keysym.sym == SDLK_ESCAPE)
			{
				m_menu_index = -1;
				m_finished = true;
			}
		}
	}
    /**
     * A function that checks whether you should exit the menu and move to the next game state.
     * @return @a true if any menu option was selected or the Esc key was pressed, @a false otherwise
     */
    bool finished() const {
		return m_finished;
	}
    /**
     * Go to the game in the selected mode or exit the application.
     * @return @a nullptr if "Exit" is selected or Esc is pressed, otherwise the function returns a pointer to Game
     */
    IAppState* nextState() {
		if(m_menu_index == m_menu_texts.size() - 1)
			return nullptr;
		else if(m_menu_index == 0)
		{
			Game* g = new Game(1);
			return g;
		}
		else if(m_menu_index == 1)
		{
			Game* g = new Game(2);
			return g;
		}
		else if(m_menu_index == 2)
		{
			std::cout << "TODO(alex): makeme" << std::endl;
		}
		return nullptr;
	}
};
