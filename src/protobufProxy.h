// src\protobufProxy.h - proxies for protobuf generated classes, support assignment for data members
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)

/**
 * @brief
 * The class for wrap of simple pb T
 */
template<typename T, auto SETTER, auto GETTER>
class ProxyXetter {
	A0S_proto::Object &m_object;

public:
	ProxyXetter(A0S_proto::Object &o) : m_object( o ) {}
	ProxyXetter &operator=(T b) {
		return (m_object.*SETTER)( b ), *this;
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
/**
 * @brief
 * The class for wrap of pb SDL_Rect and SDL_Rect data
 */
template<auto PTMF>
class ProxySdlRect {
	using SdlRect_t = A0S_proto::SDL_Rect;
	SdlRect_t *m_rect;

public:
	ProxySdlRectXetter< &SdlRect_t::set_x, &SdlRect_t::x > x;
	ProxySdlRectXetter< &SdlRect_t::set_y, &SdlRect_t::y > y;
	ProxySdlRectXetter< &SdlRect_t::set_w, &SdlRect_t::w > w;
	ProxySdlRectXetter< &SdlRect_t::set_h, &SdlRect_t::h > h;
	ProxySdlRect(A0S_proto::Object &o) : 
		m_rect{ (o.*PTMF)( ) } 
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
