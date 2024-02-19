// src\protobufProxy.h - proxies for protobuf generated classes, support assignments stuff for data members
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)

/**
 * @brief
 * Base class for std trait detection
 */
template<typename O>
class ProxyBase {
protected:
	std::reference_wrapper<O *> m_object;

public:
	ProxyBase(std::reference_wrapper<O *> object) : 
		m_object( object ) 
	{}
};

/**
 * @brief
 * The class for wrap of simple pb T
 */
template<typename O, typename T, auto SETTER, auto GETTER>
class ProxyXetter : public ProxyBase< O > {
public:
	ProxyXetter &operator=(T rhs) {
		return (m_object->*SETTER)( rhs ), *this;
	}
	ProxyXetter &operator+=(T rhs) {
		return (m_object->*SETTER)( rhs + (m_object->*GETTER)( ) ), *this;
	}
	// Post-increment for integers
	template<typename T>
	std::enable_if_t< ( true 
			&& std::is_integral_v< typename T >
			&& !std::is_same_v< typename T, bool > 
		), ProxyXetter & >
	operator++(T) {
		return (m_object->*SETTER)( (m_object->*GETTER)( ) + 1 ), *this;
	}
	ProxyXetter &operator=(ProxyXetter &rhs) {
		return m_object = rhs.m_object, *this;
	}
	operator T() {
		return (m_object->*GETTER)( );
	}
	// Disallow implicit cast to `bool` type
	template<
			typename DISALLOW
			, typename = std::enable_if_t< ( true 
					&& std::is_same_v< typename T, bool > 
					&& !std::is_base_of_v< ProxyBase< O >, typename DISALLOW > 
				) >
		>
	ProxyXetter &operator=(DISALLOW) = delete;
};

/**
 * @brief
 * The class for wrap of SDL_Rect data for PbObject
 */
template<auto PTMF>
class ProxySdlRect : public ProxyBase< A0S_proto::PbObject > {
	using SdlRect_t = A0S_proto::PbSdlRect;
	SdlRect_t *m_rect;
	/**
	 * @brief
	 * The class is responsible for getter/setter SDL_Rect data.
	 */
	template<auto SETTER, auto GETTER>
	class RectXetter {
		SdlRect_t *m_rect;

	public:
		RectXetter() = default;
		RectXetter(SdlRect_t *rect) : m_rect( rect ) {}
		RectXetter &operator=(int32_t v) {
			return (m_rect ->*SETTER)( v ), *this;
		}
		operator int32_t() {
			return (m_rect ->*GETTER)( );
		}
	};

public:
	RectXetter< &SdlRect_t::set_x, &SdlRect_t::x > x;
	RectXetter< &SdlRect_t::set_y, &SdlRect_t::y > y;
	RectXetter< &SdlRect_t::set_w, &SdlRect_t::w > w;
	RectXetter< &SdlRect_t::set_h, &SdlRect_t::h > h;
	ProxySdlRect(A0S_proto::PbObject *object) : 
		ProxyBase( object )
		, m_rect{ (object->*PTMF)( ) } 
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
 * The class for wrap of SDL_Point data
 */
template<typename O, auto PTMF>
class ProxySdlPoint : public ProxyBase< O > {
	using SdlPoint_t = A0S_proto::PbSdlPoint;
	SdlPoint_t *m_point;
	/**
	 * @brief
	 * The class is responsible for getter/setter SDL_Point data.
	 */
	template<auto SETTER, auto GETTER>
	class PointXetter {
		SdlPoint_t *m_point;

	public:
		PointXetter() = default;
		PointXetter(SdlPoint_t *rect) : m_point( rect ) {}
		PointXetter &operator=(int32_t v) {
			return (m_point ->*SETTER)( v ), *this;
		}
		operator int32_t() {
			return (m_point ->*GETTER)( );
		}
	};

public:
	PointXetter< &SdlPoint_t::set_x, &SdlPoint_t::x > x;
	PointXetter< &SdlPoint_t::set_y, &SdlPoint_t::y > y;
	ProxySdlPoint(O *object) : 
		ProxyBase( object )
		, m_point{ (object->*PTMF)( ) } 
		, x{ m_point } 
		, y{ m_point } 
	{}
	ProxySdlPoint &operator=(::SDL_Point const& rhs) {
		m_point ->set_x( rhs.x );
		m_point ->set_y( rhs.y );
		return *this;
	}
	operator ::SDL_Point() {
		return { m_point ->x( ), m_point ->y( ) };
	}
};

/**
 * @brief
 * The class for wrap of enum pb T
 */
template<typename O, typename OUTER, typename INNER, auto SETTER, auto GETTER>
class ProxyEnum : public ProxyBase< O > {
public:
	ProxyEnum &operator=(OUTER rhs) {
		auto direction = static_cast< INNER >( rhs );
		return (m_object->*SETTER)( direction ), *this;
	}
	operator OUTER() const {
		return static_cast< OUTER >( (m_object->*GETTER)( ) );
	}
};

template<typename T>
using pb_data_t = std::shared_ptr< T >;

// tmp, for clearing inher
struct FakeObject {
	void draw() 
	{}
};

