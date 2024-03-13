//
// Copyright (c) ZeroC, Inc. All rights reserved.
//
//
// Ice version 3.7.10
//
// <auto-generated>
//
// Generated from file `acme.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __acme_h__
#define __acme_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Comparable.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/GCObject.h>
#include <Ice/Value.h>
#include <Ice/Incoming.h>
#include <Ice/FactoryTableInit.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/Optional.h>
#include <IceUtil/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 307
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 >= 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 10
#       error Ice patch level mismatch!
#   endif
#endif

#ifdef ICE_CPP11_MAPPING // C++11 mapping

namespace Acme
{

class BaseObject;
class Brick;

}

namespace Acme
{

/**
 * A rectangle, with the origin at the upper left (integer).
 *
 * \sa SDL_RectEmpty
 * \sa SDL_RectEquals
 * \sa SDL_HasIntersection
 * \sa SDL_IntersectRect
 * \sa SDL_IntersectRectAndLine
 * \sa SDL_UnionRect
 * \sa SDL_EnclosePoints
 */
struct SDL_Rect
{
    int x;
    int y;
    int w;
    int h;

    /**
     * Obtains a tuple containing all of the struct's data members.
     * @return The data members in a tuple.
     */
    std::tuple<const int&, const int&, const int&, const int&> ice_tuple() const
    {
        return std::tie(x, y, w, h);
    }
	operator ::SDL_Rect() const {
		return ::SDL_Rect{ x, y, w, h };
	}
};

enum class SpriteType : unsigned char
{
    ST_TANK_A,
    ST_TANK_B,
    ST_TANK_C,
    ST_TANK_D,
    ST_PLAYER_1,
    ST_PLAYER_2,
    ST_BRICK_WALL,
    ST_STONE_WALL,
    ST_WATER,
    ST_BUSH,
    ST_ICE,
    ST_BONUS_GRENADE,
    ST_BONUS_HELMET,
    ST_BONUS_CLOCK,
    ST_BONUS_SHOVEL,
    ST_BONUS_TANK,
    ST_BONUS_STAR,
    ST_BONUS_GUN,
    ST_BONUS_BOAT,
    ST_SHIELD,
    ST_CREATE,
    ST_DESTROY_TANK,
    ST_DESTROY_BULLET,
    ST_BOAT_P1,
    ST_BOAT_P2,
    ST_EAGLE,
    ST_DESTROY_EAGLE,
    ST_FLAG,
    ST_BULLET,
    ST_LEFT_ENEMY,
    ST_STAGE_STATUS,
    ST_TANKS_LOGO,
    ST_NONE
};

using Ice::operator<;
using Ice::operator<=;
using Ice::operator>;
using Ice::operator>=;
using Ice::operator==;
using Ice::operator!=;

}

namespace Acme
{

/**
 * @brief Base class for game objects
 */
class BaseObject : public ::Ice::ValueHelper<BaseObject, ::Ice::Value>
{
public:

    virtual ~BaseObject();

    BaseObject() = default;

    BaseObject(const BaseObject&) = default;
    BaseObject(BaseObject&&) = default;
    BaseObject& operator=(const BaseObject&) = default;
    BaseObject& operator=(BaseObject&&) = default;

    /**
     * One-shot constructor to initialize all data members.
     * @param m_frame_display_time Display time of the current animation frame.
     * @param m_current_frame Number of the current animation frame.
     * @param to_erase The variable says whether the object should be deleted.
     * @param collision_rect Collision rectangle; may be smaller than the dimensions of dest_rect.
     * @param dest_rect The target position of the object on the screen.
     * @param src_rect Position on the texture of the currently displayed frame.
     * @param type BaseObject type.
     * @param pos_x Accurate horizontal position of the object.
     * @param pos_y Accurate vertical position of the object.
     */
    BaseObject(int m_frame_display_time, int m_current_frame, bool to_erase, const ::Acme::SDL_Rect& collision_rect, const ::Acme::SDL_Rect& dest_rect, const ::Acme::SDL_Rect& src_rect, ::Acme::SpriteType type, double pos_x, double pos_y) :
        m_frame_display_time(m_frame_display_time),
        m_current_frame(m_current_frame),
        to_erase(to_erase),
        collision_rect(collision_rect),
        dest_rect(dest_rect),
        src_rect(src_rect),
        type(type),
        pos_x(pos_x),
        pos_y(pos_y)
    {
    }

    /**
     * Obtains a tuple containing all of the value's data members.
     * @return The data members in a tuple.
     */
    std::tuple<const int&, const int&, const bool&, const ::Acme::SDL_Rect&, const ::Acme::SDL_Rect&, const ::Acme::SDL_Rect&, const ::Acme::SpriteType&, const double&, const double&> ice_tuple() const
    {
        return std::tie(m_frame_display_time, m_current_frame, to_erase, collision_rect, dest_rect, src_rect, type, pos_x, pos_y);
    }

    /**
     * Obtains the Slice type ID of this value.
     * @return The fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

protected:

    /**
     * Display time of the current animation frame.
     */
    int m_frame_display_time;
    /**
     * Number of the current animation frame.
     */
    int m_current_frame;

public:

    /**
     * The variable says whether the object should be deleted. If change is equal to @a true, no updating and drawing of the object is skipped.
     */
    bool to_erase;
    /**
     * Collision rectangle; may be smaller than the dimensions of dest_rect.
     */
    ::Acme::SDL_Rect collision_rect;
    /**
     * The target position of the object on the screen.
     */
    ::Acme::SDL_Rect dest_rect;
    /**
     * Position on the texture of the currently displayed frame.
     */
    ::Acme::SDL_Rect src_rect;
    /**
     * BaseObject type.
     */
    ::Acme::SpriteType type;
    /**
     * Accurate horizontal position of the object.
     */
    double pos_x;
    /**
     * Accurate vertical position of the object.
     */
    double pos_y;

protected:

    template<typename T, typename S>
    friend struct Ice::StreamWriter;
    template<typename T, typename S>
    friend struct Ice::StreamReader;
};

/// \cond INTERNAL
static BaseObject _iceS_BaseObject_init;
/// \endcond

/**
 * @brief Class responsible for a single piece of wall.
 * @see BaseObject
 */
class Brick : public ::Ice::ValueHelper<Brick, BaseObject>
{
public:

    virtual ~Brick();

    Brick() = default;

    Brick(const Brick&) = default;
    Brick(Brick&&) = default;
    Brick& operator=(const Brick&) = default;
    Brick& operator=(Brick&&) = default;

    /**
     * One-shot constructor to initialize all data members.
     * @param m_frame_display_time Display time of the current animation frame.
     * @param m_current_frame Number of the current animation frame.
     * @param to_erase The variable says whether the object should be deleted.
     * @param collision_rect Collision rectangle; may be smaller than the dimensions of dest_rect.
     * @param dest_rect The target position of the object on the screen.
     * @param src_rect Position on the texture of the currently displayed frame.
     * @param type BaseObject type.
     * @param pos_x Accurate horizontal position of the object.
     * @param pos_y Accurate vertical position of the object.
     * @param m_collision_count Number of times the bullets hit the wall.
     */
    Brick(int m_frame_display_time, int m_current_frame, bool to_erase, const ::Acme::SDL_Rect& collision_rect, const ::Acme::SDL_Rect& dest_rect, const ::Acme::SDL_Rect& src_rect, ::Acme::SpriteType type, double pos_x, double pos_y, int m_collision_count) :
        Ice::ValueHelper<Brick, BaseObject>(m_frame_display_time, m_current_frame, to_erase, collision_rect, dest_rect, src_rect, type, pos_x, pos_y),
        m_collision_count(m_collision_count)
    {
    }

    /**
     * Obtains a tuple containing all of the value's data members.
     * @return The data members in a tuple.
     */
    std::tuple<const int&, const int&, const bool&, const ::Acme::SDL_Rect&, const ::Acme::SDL_Rect&, const ::Acme::SDL_Rect&, const ::Acme::SpriteType&, const double&, const double&, const int&> ice_tuple() const
    {
        return std::tie(m_frame_display_time, m_current_frame, to_erase, collision_rect, dest_rect, src_rect, type, pos_x, pos_y, m_collision_count);
    }

    /**
     * Obtains the Slice type ID of this value.
     * @return The fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    /**
     * Number of times the bullets hit the wall.
     */
    int m_collision_count;
};

}

namespace Acme
{

}

/// \cond STREAM
namespace Ice
{

template<>
struct StreamableTraits<::Acme::SDL_Rect>
{
    static const StreamHelperCategory helper = StreamHelperCategoryStruct;
    static const int minWireSize = 16;
    static const bool fixedLength = true;
};

template<typename S>
struct StreamReader<::Acme::SDL_Rect, S>
{
    static void read(S* istr, ::Acme::SDL_Rect& v)
    {
        istr->readAll(v.x, v.y, v.w, v.h);
    }
};

template<>
struct StreamableTraits< ::Acme::SpriteType>
{
    static const StreamHelperCategory helper = StreamHelperCategoryEnum;
    static const int minValue = 0;
    static const int maxValue = 32;
    static const int minWireSize = 1;
    static const bool fixedLength = false;
};

template<typename S>
struct StreamReader<::Acme::BaseObject, S>
{
    static void read(S* istr, ::Acme::BaseObject& v)
    {
        istr->readAll(v.m_frame_display_time, v.m_current_frame, v.to_erase, v.collision_rect, v.dest_rect, v.src_rect, v.type, v.pos_x, v.pos_y);
    }
};

template<typename S>
struct StreamWriter<::Acme::Brick, S>
{
    static void write(S* ostr, const ::Acme::Brick& v)
    {
        ostr->writeAll(v.m_collision_count);
    }
};

template<typename S>
struct StreamReader<::Acme::Brick, S>
{
    static void read(S* istr, ::Acme::Brick& v)
    {
        istr->readAll(v.m_collision_count);
    }
};

}
/// \endcond

/// \cond INTERNAL
namespace Acme
{

using BaseObjectPtr = ::std::shared_ptr<BaseObject>;

using BrickPtr = ::std::shared_ptr<Brick>;

}
/// \endcond

#else // C++98 mapping

namespace IceProxy
{

namespace Acme
{

class BaseObject;
/// \cond INTERNAL
void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< BaseObject>&);
::IceProxy::Ice::Object* upCast(BaseObject*);
/// \endcond

class Brick;
/// \cond INTERNAL
void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< Brick>&);
::IceProxy::Ice::Object* upCast(Brick*);
/// \endcond

}

}

namespace Acme
{

class BaseObject;
/// \cond INTERNAL
::Ice::Object* upCast(BaseObject*);
/// \endcond
typedef ::IceInternal::Handle< BaseObject> BaseObjectPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Acme::BaseObject> BaseObjectPrx;
typedef BaseObjectPrx BaseObjectPrxPtr;
/// \cond INTERNAL
void _icePatchObjectPtr(BaseObjectPtr&, const ::Ice::ObjectPtr&);
/// \endcond

class Brick;
/// \cond INTERNAL
::Ice::Object* upCast(Brick*);
/// \endcond
typedef ::IceInternal::Handle< Brick> BrickPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::Acme::Brick> BrickPrx;
typedef BrickPrx BrickPrxPtr;
/// \cond INTERNAL
void _icePatchObjectPtr(BrickPtr&, const ::Ice::ObjectPtr&);
/// \endcond

}

namespace Acme
{

/**
 * A rectangle, with the origin at the upper left (integer).
 *
 * \sa SDL_RectEmpty
 * \sa SDL_RectEquals
 * \sa SDL_HasIntersection
 * \sa SDL_IntersectRect
 * \sa SDL_IntersectRectAndLine
 * \sa SDL_UnionRect
 * \sa SDL_EnclosePoints
 */
struct SDL_Rect
{
    ::Ice::Int x;
    ::Ice::Int y;
    ::Ice::Int w;
    ::Ice::Int h;

    bool operator==(const SDL_Rect& rhs_) const
    {
        if(this == &rhs_)
        {
            return true;
        }
        if(x != rhs_.x)
        {
            return false;
        }
        if(y != rhs_.y)
        {
            return false;
        }
        if(w != rhs_.w)
        {
            return false;
        }
        if(h != rhs_.h)
        {
            return false;
        }
        return true;
    }

    bool operator<(const SDL_Rect& rhs_) const
    {
        if(this == &rhs_)
        {
            return false;
        }
        if(x < rhs_.x)
        {
            return true;
        }
        else if(rhs_.x < x)
        {
            return false;
        }
        if(y < rhs_.y)
        {
            return true;
        }
        else if(rhs_.y < y)
        {
            return false;
        }
        if(w < rhs_.w)
        {
            return true;
        }
        else if(rhs_.w < w)
        {
            return false;
        }
        if(h < rhs_.h)
        {
            return true;
        }
        else if(rhs_.h < h)
        {
            return false;
        }
        return false;
    }

    bool operator!=(const SDL_Rect& rhs_) const
    {
        return !operator==(rhs_);
    }
    bool operator<=(const SDL_Rect& rhs_) const
    {
        return operator<(rhs_) || operator==(rhs_);
    }
    bool operator>(const SDL_Rect& rhs_) const
    {
        return !operator<(rhs_) && !operator==(rhs_);
    }
    bool operator>=(const SDL_Rect& rhs_) const
    {
        return !operator<(rhs_);
    }
};

enum SpriteType
{
    ST_TANK_A,
    ST_TANK_B,
    ST_TANK_C,
    ST_TANK_D,
    ST_PLAYER_1,
    ST_PLAYER_2,
    ST_BRICK_WALL,
    ST_STONE_WALL,
    ST_WATER,
    ST_BUSH,
    ST_ICE,
    ST_BONUS_GRENADE,
    ST_BONUS_HELMET,
    ST_BONUS_CLOCK,
    ST_BONUS_SHOVEL,
    ST_BONUS_TANK,
    ST_BONUS_STAR,
    ST_BONUS_GUN,
    ST_BONUS_BOAT,
    ST_SHIELD,
    ST_CREATE,
    ST_DESTROY_TANK,
    ST_DESTROY_BULLET,
    ST_BOAT_P1,
    ST_BOAT_P2,
    ST_EAGLE,
    ST_DESTROY_EAGLE,
    ST_FLAG,
    ST_BULLET,
    ST_LEFT_ENEMY,
    ST_STAGE_STATUS,
    ST_TANKS_LOGO,
    ST_NONE
};

}

namespace Acme
{

}

namespace IceProxy
{

namespace Acme
{

class BaseObject : public virtual ::Ice::Proxy<BaseObject, ::IceProxy::Ice::Object>
{
public:

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

protected:
    /// \cond INTERNAL

    virtual ::IceProxy::Ice::Object* _newInstance() const;
    /// \endcond
};

class Brick : public virtual ::Ice::Proxy<Brick, ::IceProxy::Acme::BaseObject>
{
public:

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

protected:
    /// \cond INTERNAL

    virtual ::IceProxy::Ice::Object* _newInstance() const;
    /// \endcond
};

}

}

namespace Acme
{

/**
 * @brief Base class for game objects
 */
class BaseObject : public virtual ::Ice::Object
{
public:

    typedef BaseObjectPrx ProxyType;
    typedef BaseObjectPtr PointerType;

    virtual ~BaseObject();

    BaseObject()
    {
    }

    /**
     * One-shot constructor to initialize all data members.
     * @param m_frame_display_time Display time of the current animation frame.
     * @param m_current_frame Number of the current animation frame.
     * @param to_erase The variable says whether the object should be deleted.
     * @param collision_rect Collision rectangle; may be smaller than the dimensions of dest_rect.
     * @param dest_rect The target position of the object on the screen.
     * @param src_rect Position on the texture of the currently displayed frame.
     * @param type BaseObject type.
     * @param pos_x Accurate horizontal position of the object.
     * @param pos_y Accurate vertical position of the object.
     */
    BaseObject(::Ice::Int m_frame_display_time, ::Ice::Int m_current_frame, bool to_erase, const ::Acme::SDL_Rect& collision_rect, const ::Acme::SDL_Rect& dest_rect, const ::Acme::SDL_Rect& src_rect, ::Acme::SpriteType type, ::Ice::Double pos_x, ::Ice::Double pos_y) :
        m_frame_display_time(m_frame_display_time),
        m_current_frame(m_current_frame),
        to_erase(to_erase),
        collision_rect(collision_rect),
        dest_rect(dest_rect),
        src_rect(src_rect),
        type(type),
        pos_x(pos_x),
        pos_y(pos_y)
    {
    }

#ifdef ICE_CPP11_COMPILER
    BaseObject(const BaseObject&) = default;
    BaseObject& operator=(const BaseObject&) = default;
#endif

    /**
     * Polymorphically clones this object.
     * @return A shallow copy of this object.
     */
    virtual ::Ice::ObjectPtr ice_clone() const;

    /**
     * Determines whether this object supports an interface with the given Slice type ID.
     * @param id The fully-scoped Slice type ID.
     * @param current The Current object for the invocation.
     * @return True if this object supports the interface, false, otherwise.
     */
    virtual bool ice_isA(const ::std::string& id, const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a list of the Slice type IDs representing the interfaces supported by this object.
     * @param current The Current object for the invocation.
     * @return A list of fully-scoped type IDs.
     */
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a Slice type ID representing the most-derived interface supported by this object.
     * @param current The Current object for the invocation.
     * @return A fully-scoped type ID.
     */
    virtual const ::std::string& ice_id(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    /**
     * Obtains a value factory that instantiates this class.
     * @return The value factory.
     */
    static ::Ice::ValueFactoryPtr ice_factory();

protected:

    /// \cond STREAM
    virtual void _iceWriteImpl(::Ice::OutputStream*) const;
    virtual void _iceReadImpl(::Ice::InputStream*);
    /// \endcond

    /**
     * Display time of the current animation frame.
     */
    ::Ice::Int m_frame_display_time;
    /**
     * Number of the current animation frame.
     */
    ::Ice::Int m_current_frame;

public:

    /**
     * The variable says whether the object should be deleted. If change is equal to @a true, no updating and drawing of the object is skipped.
     */
    bool to_erase;
    /**
     * Collision rectangle; may be smaller than the dimensions of dest_rect.
     */
    ::Acme::SDL_Rect collision_rect;
    /**
     * The target position of the object on the screen.
     */
    ::Acme::SDL_Rect dest_rect;
    /**
     * Position on the texture of the currently displayed frame.
     */
    ::Acme::SDL_Rect src_rect;
    /**
     * BaseObject type.
     */
    ::Acme::SpriteType type;
    /**
     * Accurate horizontal position of the object.
     */
    ::Ice::Double pos_x;
    /**
     * Accurate vertical position of the object.
     */
    ::Ice::Double pos_y;

protected:

    template<typename T, typename S>
    friend struct Ice::StreamWriter;
    template<typename T, typename S>
    friend struct Ice::StreamReader;
};
/// \cond INTERNAL
static ::Ice::ValueFactoryPtr _iceS_BaseObject_init = ::Acme::BaseObject::ice_factory();
/// \endcond

/// \cond INTERNAL
inline bool operator==(const BaseObject& lhs, const BaseObject& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const BaseObject& lhs, const BaseObject& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}
/// \endcond

/**
 * @brief Class responsible for a single piece of wall.
 * @see BaseObject
 */
class Brick : public BaseObject
{
public:

    typedef BrickPrx ProxyType;
    typedef BrickPtr PointerType;

    virtual ~Brick();

    Brick()
    {
    }

    /**
     * One-shot constructor to initialize all data members.
     * @param m_frame_display_time Display time of the current animation frame.
     * @param m_current_frame Number of the current animation frame.
     * @param to_erase The variable says whether the object should be deleted.
     * @param collision_rect Collision rectangle; may be smaller than the dimensions of dest_rect.
     * @param dest_rect The target position of the object on the screen.
     * @param src_rect Position on the texture of the currently displayed frame.
     * @param type BaseObject type.
     * @param pos_x Accurate horizontal position of the object.
     * @param pos_y Accurate vertical position of the object.
     * @param m_collision_count Number of times the bullets hit the wall.
     */
    Brick(::Ice::Int m_frame_display_time, ::Ice::Int m_current_frame, bool to_erase, const ::Acme::SDL_Rect& collision_rect, const ::Acme::SDL_Rect& dest_rect, const ::Acme::SDL_Rect& src_rect, ::Acme::SpriteType type, ::Ice::Double pos_x, ::Ice::Double pos_y, ::Ice::Int m_collision_count) :
        ::Acme::BaseObject(m_frame_display_time, m_current_frame, to_erase, collision_rect, dest_rect, src_rect, type, pos_x, pos_y),
        m_collision_count(m_collision_count)
    {
    }

#ifdef ICE_CPP11_COMPILER
    Brick(const Brick&) = default;
    Brick& operator=(const Brick&) = default;
#endif

    /**
     * Polymorphically clones this object.
     * @return A shallow copy of this object.
     */
    virtual ::Ice::ObjectPtr ice_clone() const;

    /**
     * Determines whether this object supports an interface with the given Slice type ID.
     * @param id The fully-scoped Slice type ID.
     * @param current The Current object for the invocation.
     * @return True if this object supports the interface, false, otherwise.
     */
    virtual bool ice_isA(const ::std::string& id, const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a list of the Slice type IDs representing the interfaces supported by this object.
     * @param current The Current object for the invocation.
     * @return A list of fully-scoped type IDs.
     */
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a Slice type ID representing the most-derived interface supported by this object.
     * @param current The Current object for the invocation.
     * @return A fully-scoped type ID.
     */
    virtual const ::std::string& ice_id(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    /**
     * Obtains a value factory that instantiates this class.
     * @return The value factory.
     */
    static ::Ice::ValueFactoryPtr ice_factory();

protected:

    /// \cond STREAM
    virtual void _iceWriteImpl(::Ice::OutputStream*) const;
    virtual void _iceReadImpl(::Ice::InputStream*);
    /// \endcond

public:

    /**
     * Number of times the bullets hit the wall.
     */
    ::Ice::Int m_collision_count;
};
/// \cond INTERNAL
static ::Ice::ValueFactoryPtr _iceS_Brick_init = ::Acme::Brick::ice_factory();
/// \endcond

/// \cond INTERNAL
inline bool operator==(const Brick& lhs, const Brick& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const Brick& lhs, const Brick& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}
/// \endcond

}

/// \cond STREAM
namespace Ice
{

template<>
struct StreamableTraits< ::Acme::SDL_Rect>
{
    static const StreamHelperCategory helper = StreamHelperCategoryStruct;
    static const int minWireSize = 16;
    static const bool fixedLength = true;
};

template<typename S>
struct StreamWriter< ::Acme::SDL_Rect, S>
{
    static void write(S* ostr, const ::Acme::SDL_Rect& v)
    {
        ostr->write(v.x);
        ostr->write(v.y);
        ostr->write(v.w);
        ostr->write(v.h);
    }
};

template<typename S>
struct StreamReader< ::Acme::SDL_Rect, S>
{
    static void read(S* istr, ::Acme::SDL_Rect& v)
    {
        istr->read(v.x);
        istr->read(v.y);
        istr->read(v.w);
        istr->read(v.h);
    }
};

template<>
struct StreamableTraits< ::Acme::SpriteType>
{
    static const StreamHelperCategory helper = StreamHelperCategoryEnum;
    static const int minValue = 0;
    static const int maxValue = 32;
    static const int minWireSize = 1;
    static const bool fixedLength = false;
};

template<typename S>
struct StreamWriter< ::Acme::BaseObject, S>
{
    static void write(S* ostr, const ::Acme::BaseObject& v)
    {
        ostr->write(v.m_frame_display_time);
        ostr->write(v.m_current_frame);
        ostr->write(v.to_erase);
        ostr->write(v.collision_rect);
        ostr->write(v.dest_rect);
        ostr->write(v.src_rect);
        ostr->write(v.type);
        ostr->write(v.pos_x);
        ostr->write(v.pos_y);
    }
};

template<typename S>
struct StreamReader< ::Acme::BaseObject, S>
{
    static void read(S* istr, ::Acme::BaseObject& v)
    {
        istr->read(v.m_frame_display_time);
        istr->read(v.m_current_frame);
        istr->read(v.to_erase);
        istr->read(v.collision_rect);
        istr->read(v.dest_rect);
        istr->read(v.src_rect);
        istr->read(v.type);
        istr->read(v.pos_x);
        istr->read(v.pos_y);
    }
};

template<typename S>
struct StreamWriter< ::Acme::Brick, S>
{
    static void write(S* ostr, const ::Acme::Brick& v)
    {
        ostr->write(v.m_collision_count);
    }
};

template<typename S>
struct StreamReader< ::Acme::Brick, S>
{
    static void read(S* istr, ::Acme::Brick& v)
    {
        istr->read(v.m_collision_count);
    }
};

}
/// \endcond

namespace Acme
{

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
