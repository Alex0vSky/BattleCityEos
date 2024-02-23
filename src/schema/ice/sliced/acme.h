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
     * @param m_current_frame Number of the current animation frame.
     */
    explicit BaseObject(int m_current_frame) :
        m_current_frame(m_current_frame)
    {
    }

    /**
     * Obtains a tuple containing all of the value's data members.
     * @return The data members in a tuple.
     */
    std::tuple<const int&> ice_tuple() const
    {
        return std::tie(m_current_frame);
    }

    /**
     * Obtains the Slice type ID of this value.
     * @return The fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    /**
     * Number of the current animation frame.
     */
    int m_current_frame;
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
     * @param m_current_frame Number of the current animation frame.
     * @param m_collision_count Number of times the bullets hit the wall.
     */
    Brick(int m_current_frame, int m_collision_count) :
        Ice::ValueHelper<Brick, BaseObject>(m_current_frame),
        m_collision_count(m_collision_count)
    {
    }

    /**
     * Obtains a tuple containing all of the value's data members.
     * @return The data members in a tuple.
     */
    std::tuple<const int&, const int&> ice_tuple() const
    {
        return std::tie(m_current_frame, m_collision_count);
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

template<typename S>
struct StreamReader<::Acme::BaseObject, S>
{
    static void read(S* istr, ::Acme::BaseObject& v)
    {
        istr->readAll(v.m_current_frame);
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
     * @param m_current_frame Number of the current animation frame.
     */
    explicit BaseObject(::Ice::Int m_current_frame) :
        m_current_frame(m_current_frame)
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

public:

    /**
     * Number of the current animation frame.
     */
    ::Ice::Int m_current_frame;
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
     * @param m_current_frame Number of the current animation frame.
     * @param m_collision_count Number of times the bullets hit the wall.
     */
    Brick(::Ice::Int m_current_frame, ::Ice::Int m_collision_count) :
        ::Acme::BaseObject(m_current_frame),
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

template<typename S>
struct StreamWriter< ::Acme::BaseObject, S>
{
    static void write(S* ostr, const ::Acme::BaseObject& v)
    {
        ostr->write(v.m_current_frame);
    }
};

template<typename S>
struct StreamReader< ::Acme::BaseObject, S>
{
    static void read(S* istr, ::Acme::BaseObject& v)
    {
        istr->read(v.m_current_frame);
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