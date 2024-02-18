// src\protobufProxy.h - proxies for protobuf generated classes, support assignments stuff for data members
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)

/**
 * @brief
 * The class for wrap of simple pb T
 */
template<typename O, typename T, auto SETTER, auto GETTER>
class ProxyXetter {
	O &m_object;

public:
	ProxyXetter(O &object) : m_object( object ) {}
	ProxyXetter &operator=(T rhs) {
		return (m_object.*SETTER)( rhs ), *this;
	}
	ProxyXetter &operator+=(T rhs) {
		return (m_object.*SETTER)( rhs + (m_object.*GETTER)( ) ), *this;
	}
	ProxyXetter &operator=(ProxyXetter &rhs) {
		return m_object = rhs.m_object, *this;
	}
	operator T() {
		return (m_object.*GETTER)( );
	}
	// Disallow implicit cast to `bool` type
	template<
			typename TDELETED
			, typename = std::enable_if_t< std::is_same_v< typename T, bool > >
		>
	ProxyXetter &operator=(TDELETED) = delete;
};

/**
 * @brief
 * The class for wrap of pb SDL_Rect and SDL_Rect data
 */
template<auto PTMF>
class ProxySdlRect {
	using SdlRect_t = A0S_proto::SDL_Rect;
	SdlRect_t *m_rect;
	/**
	 * @brief
	 * The class is responsible for getter/setter SDL_Rect data.
	 */
	template<auto SETTER, auto GETTER>
	class ProxySdlRectXetter {
		A0S_proto::SDL_Rect *m_rect;
	public:
		ProxySdlRectXetter(A0S_proto::SDL_Rect *rect) : m_rect( rect ) {}
		ProxySdlRectXetter &operator=(int32_t v) {
			return (m_rect ->*SETTER)( v ), *this;
		}
		operator int32_t() {
			return (m_rect ->*GETTER)( );
		}
	};

public:
	ProxySdlRectXetter< &SdlRect_t::set_x, &SdlRect_t::x > x;
	ProxySdlRectXetter< &SdlRect_t::set_y, &SdlRect_t::y > y;
	ProxySdlRectXetter< &SdlRect_t::set_w, &SdlRect_t::w > w;
	ProxySdlRectXetter< &SdlRect_t::set_h, &SdlRect_t::h > h;
	ProxySdlRect(A0S_proto::Object &object) : 
		m_rect{ (object.*PTMF)( ) } 
		, x{ m_rect } 
		, y{ m_rect } 
		, w{ m_rect } 
		, h{ m_rect } 
	{}
	ProxySdlRect &operator=(::SDL_Rect const& rhs) {
		m_rect ->set_x( rhs.x );
		m_rect ->set_y( rhs.y );
		m_rect ->set_w( rhs.w );
		m_rect ->set_h( rhs.h );
		return *this;
	}
	operator ::SDL_Rect() {
		return { m_rect ->x( ), m_rect ->y( ), m_rect ->w( ), m_rect ->h( ) };
	}
};

/**
 * @brief
 * The class for wrap of enum pb T
 */
template<typename O, typename OUTER, typename INNER, auto SETTER, auto GETTER>
class ProxyEnum {
	O &m_object;

public:
	ProxyEnum(O &object) : m_object( object ) {}
	ProxyEnum &operator=(OUTER rhs) {
		auto direction = static_cast< INNER >( rhs );
		return (m_object.*SETTER)( direction ), *this;
	}
	operator OUTER() const {
		return static_cast< OUTER >( (m_object.*GETTER)( ) );
	}
};

// tmp, for clearing inher
struct FakeObject {
	void draw() 
	{}
};
