#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
/**
 * @brief
 * The class is responsible for drawing objects on the screen.
 */
class Renderer {
    /**
     * Pointer to an object associated with the window buffer.
     */
    SDL_Renderer* m_renderer = nullptr;
    /**
     * Pointer to a texture containing all visible game elements.
     */
    SDL_Texture* m_texture = nullptr;
    /**
     * Pointer to an auxiliary texture when drawing text on the screen.
     */
    SDL_Texture* m_text_texture = nullptr;
    /**
     * Font size 28.
     */
    TTF_Font* m_font1 = nullptr;
    /**
     * Font size 14.
     */
    TTF_Font* m_font2 = nullptr;
    /**
     * Font size 10.
     */
    TTF_Font* m_font3 = nullptr;

public:
    ~Renderer() {
		if(m_renderer != nullptr)
			SDL_DestroyRenderer(m_renderer);
		if(m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
		if(m_text_texture != nullptr)
			SDL_DestroyTexture(m_text_texture);
		if(m_font1 != nullptr)
			TTF_CloseFont(m_font1);
		if(m_font2 != nullptr)
			TTF_CloseFont(m_font2);
		if(m_font3 != nullptr)
			TTF_CloseFont(m_font3);
	}
    /**
     * Loading a texture from a file and creating a renderer related to the application window.
     * @param window - pointer to the application window content object
     */
    void loadTexture(SDL_Window* window) {
		SDL_Surface* surface = nullptr;
		m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		int freesrcYes = 1;
		SDL_RWops *RWops = SDL_RWFromConstMem( s_texture, sizeof( s_texture ) );
		surface = IMG_Load_RW( RWops, freesrcYes );

		//load surface
		if(surface != nullptr && m_renderer != nullptr)
			m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);

		SDL_FreeSurface(surface);
	}
    /**
     * Font loading in three different sizes.
     */
    void loadFont() {
		SDL_RWops *RWops = nullptr;
		// Not working flag if zero
		int freesrcYes = 1;
		RWops = SDL_RWFromConstMem( s_prstartk, sizeof( s_prstartk ) );
		m_font1 = TTF_OpenFontRW( RWops, freesrcYes, 28 );
		RWops = SDL_RWFromConstMem( s_prstartk, sizeof( s_prstartk ) );
		m_font2 = TTF_OpenFontRW( RWops, freesrcYes, 14 );
		RWops = SDL_RWFromConstMem( s_prstartk, sizeof( s_prstartk ) );
		m_font3 = TTF_OpenFontRW( RWops, freesrcYes, 10 );
	}

    /**
     * Clearing the screen buffer.
     */
    void clear() {
		SDL_SetRenderDrawColor(m_renderer, 110, 110, 110, 255);
		SDL_RenderClear(m_renderer); //clear the back buffer
	}

    /**
     * Screen buffer presentation.
     */
    void flush() {
		SDL_RenderPresent(m_renderer); //swap buffers
	}

    /**
     * Redrawing a fragment of the texture onto a fragment of the screen buffer.
     * @param texture_src - source texture rectangle
     * @param window_dest - target rectangle on the screen buffer
     */
	void drawObject(rect_t const& texture_src, rect_t const& window_dest) {
		::SDL_Rect texture_src_{ texture_src.x, texture_src.y, texture_src.w, texture_src.h };
		::SDL_Rect window_dest_{ window_dest.x, window_dest.y, window_dest.w, window_dest.h };
		SDL_RenderCopy( m_renderer, m_texture, &texture_src_, &window_dest_ ); //draw on the back buffer
	}

    /**
     * Setting the scale of the displayed buffer so that it maintains the board proportions and is located in the center of the application window.
     * @param xs - horizontal scale as the ratio of the window width to the map width
     * @param ys - vertical scale as the ratio of the window height to the map height
     * @see AppConfig::map_rect
     */
    void setScale(float xs, float ys) {
		float scale = std::min(xs, ys);
		if(scale < 0.1) return;

		rect_t viewport;
		viewport.x = ((float)AppConfig::windows_rect.w / scale - (AppConfig::map_rect.w + AppConfig::status_rect.w)) / 2.0;
		viewport.y = ((float)AppConfig::windows_rect.h / scale - AppConfig::map_rect.h) / 2.0;
		if(viewport.x < 0) viewport.x = 0;
		if(viewport.y < 0) viewport.y = 0;
		viewport.w = AppConfig::map_rect.w + AppConfig::status_rect.w;
		viewport.h = AppConfig::map_rect.h;

		SDL_RenderSetScale(m_renderer, scale, scale);
		::SDL_Rect viewport_{ viewport.x, viewport.y, viewport.w, viewport.h };
		SDL_RenderSetViewport(m_renderer, &viewport_);
	}

    /**
     * Draw text in the window buffer at the selected starting position.
     * @param start - location of the starting point of the drawn text; a negative value of any of the coordinates results in the text being centered on that axis
     * @param text - drawn text
     * @param text_color - colors of the drawn text
     * @param font_size - font number with which the text will be drawn; three values available: 1, 2, 3
     */
    void drawText(const point_t* start, std::string text, SDL_Color text_color, int font_size = 1) {
		if(m_font1 == nullptr || m_font2 == nullptr || m_font3 == nullptr) return;
		if(m_text_texture != nullptr)
			SDL_DestroyTexture(m_text_texture);

		SDL_Surface* text_surface = nullptr;
		if(font_size == 2) text_surface = TTF_RenderText_Solid(m_font2, text.c_str(), text_color);
		else if(font_size == 3) text_surface = TTF_RenderText_Solid(m_font3, text.c_str(), text_color);
		else text_surface = TTF_RenderText_Solid(m_font1, text.c_str(), text_color);

		if(text_surface == nullptr) return;

		m_text_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);
		if(m_text_texture == nullptr) return;

		rect_t window_dest;
		if(start == nullptr)
		{
			window_dest.x = (AppConfig::map_rect.w + AppConfig::status_rect.w - text_surface->w)/2;
			window_dest.y = (AppConfig::map_rect.h - text_surface->h)/2;
		}
		else
		{
			if(start->x < 0) window_dest.x = (AppConfig::map_rect.w + AppConfig::status_rect.w - text_surface->w)/2;
			else window_dest.x = start->x;

			if(start->y < 0) window_dest.y = (AppConfig::map_rect.h - text_surface->h)/2;
			else window_dest.y = start->y;
		}
		window_dest.w = text_surface->w;
		window_dest.h = text_surface->h;

		::SDL_Rect window_dest_{ window_dest.x, window_dest.y, window_dest.w, window_dest.h };
		SDL_RenderCopy(m_renderer, m_text_texture, NULL, &window_dest_);
	}

    /**
     * Function that draws a rectangle in the window buffer.
     * @param rect - position of the rectangle on the board
     * @param rect_color - color of the rectangle
     * @param fill - a variable that tells whether the rectangle should be filled
     */
    void drawRect(const rect_t* rect, SDL_Color rect_color, bool fill = false) {
		SDL_SetRenderDrawColor(m_renderer, rect_color.r, rect_color.g, rect_color.b, rect_color.a);

		::SDL_Rect rect_{ rect ->x, rect ->y, rect ->w, rect ->h };
		if(fill)
			SDL_RenderFillRect(m_renderer, &rect_);
		else
			SDL_RenderDrawRects(m_renderer, &rect_, 1);
	}
};
