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

		surface = IMG_Load( AppConfig::texture_path.data( ) );
		//std::filesystem::path path = SDL_GetBasePath( );
		//path /= AppConfig::texture_path;
		//std::filesystem::path canonicalPath = std::filesystem::weakly_canonical( path );
		//std::string npath = canonicalPath.make_preferred( ).string( );
		//surface = IMG_Load( npath.c_str( ) );

		//load surface
		if(surface != nullptr && m_renderer != nullptr)
			m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);

		SDL_FreeSurface(surface);
	}
    /**
     * Font loading in three different sizes.
     */
    void loadFont() {
		m_font1 = TTF_OpenFont(AppConfig::font_name.data( ), 28);
		m_font2 = TTF_OpenFont(AppConfig::font_name.data( ), 14);
		m_font3 = TTF_OpenFont(AppConfig::font_name.data( ), 10);
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
    void drawObject(const SDL_Rect *texture_src, const SDL_Rect *window_dest) {
		SDL_RenderCopy(m_renderer, m_texture, texture_src, window_dest); //draw on the back buffer
	}
	void drawObject(SDL_Rect const& texture_src, SDL_Rect const& window_dest) {
		SDL_RenderCopy( m_renderer, m_texture, &texture_src, &window_dest ); //draw on the back buffer
	}
#ifdef A0S_SCHEMA_ICE
	void drawObject(Acme::SDL_Rect const& texture_src, Acme::SDL_Rect const& window_dest) {
		::SDL_Rect texture_src_ = texture_src, window_dest_ = window_dest;
		SDL_RenderCopy( m_renderer, m_texture, &texture_src_, &window_dest_ ); //draw on the back buffer
	}
#endif // A0S_SCHEMA_ICE

    /**
     * Setting the scale of the displayed buffer so that it maintains the board proportions and is located in the center of the application window.
     * @param xs - horizontal scale as the ratio of the window width to the map width
     * @param ys - vertical scale as the ratio of the window height to the map height
     * @see AppConfig::map_rect
     */
    void setScale(float xs, float ys) {
		float scale = std::min(xs, ys);
		if(scale < 0.1) return;

		SDL_Rect viewport;
		viewport.x = ((float)AppConfig::windows_rect.w / scale - (AppConfig::map_rect.w + AppConfig::status_rect.w)) / 2.0;
		viewport.y = ((float)AppConfig::windows_rect.h / scale - AppConfig::map_rect.h) / 2.0;
		if(viewport.x < 0) viewport.x = 0;
		if(viewport.y < 0) viewport.y = 0;
		viewport.w = AppConfig::map_rect.w + AppConfig::status_rect.w;
		viewport.h = AppConfig::map_rect.h;

		SDL_RenderSetScale(m_renderer, scale, scale);
		SDL_RenderSetViewport(m_renderer, &viewport);
	}

    /**
     * Draw text in the window buffer at the selected starting position.
     * @param start - location of the starting point of the drawn text; a negative value of any of the coordinates results in the text being centered on that axis
     * @param text - drawn text
     * @param text_color - colors of the drawn text
     * @param font_size - font number with which the text will be drawn; three values available: 1, 2, 3
     */
    void drawText(const SDL_Point* start, std::string text, SDL_Color text_color, int font_size = 1) {
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

		SDL_Rect window_dest;
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

		SDL_RenderCopy(m_renderer, m_text_texture, NULL, &window_dest);
	}

    /**
     * Function that draws a rectangle in the window buffer.
     * @param rect - position of the rectangle on the board
     * @param rect_color - color of the rectangle
     * @param fill - a variable that tells whether the rectangle should be filled
     */
    void drawRect(const SDL_Rect* rect, SDL_Color rect_color, bool fill = false) {
		SDL_SetRenderDrawColor(m_renderer, rect_color.r, rect_color.g, rect_color.b, rect_color.a);

		if(fill)
			SDL_RenderFillRect(m_renderer, rect);
		else
			SDL_RenderDrawRects(m_renderer, rect, 1);
	}
};
