// stdafx.h - pch

#ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmicrosoft-include"
#	pragma clang diagnostic ignored "-Wmicrosoft-cast"
//-fmacro-backtrace-limit=0
#endif // __clang__

// ...

#ifdef __clang__
#	pragma clang diagnostic pop
#endif // __clang__


// allow rand_s
#define _CRT_RAND_S
// disable min and max macros
#define NOMINMAX
#if defined(DEBUG) || defined(_DEBUG)
#	include <crtdbg.h>
#endif
#pragma warning( push )
#pragma warning( disable: 5039 )

// // Including SDKDDKVer.h defines the highest available Windows platform.
// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.
#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <Windows.h>
#include <WinSock2.h>
// C RunTime Header Files
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include <chrono>

// SDL stuff
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// GoogleProtobuf
#ifdef A0S_SCHEMA_PROTOBUF
#	include "proto/acme.pb.h"
#endif // A0S_SCHEMA_PROTOBUF

#ifdef A0S_SCHEMA_ICE
#	include <IceUtil/PushDisableWarnings.h>

// From src\schema\ice\sliced\acme.h, __acme_h__, generated from file `acme.ice'
#	include <Ice/ProxyF.h>
#	include <Ice/ObjectF.h>
#	include <Ice/ValueF.h>
#	include <Ice/Exception.h>
#	include <Ice/LocalObject.h>
#	include <Ice/StreamHelpers.h>
#	include <Ice/Comparable.h>
#	include <Ice/Proxy.h>
#	include <Ice/Object.h>
#	include <Ice/GCObject.h>
#	include <Ice/Value.h>
#	include <Ice/Incoming.h>
#	include <Ice/FactoryTableInit.h>
#	include <IceUtil/ScopedArray.h>
#	include <Ice/Optional.h>
#	include <IceUtil/UndefSysMacros.h>

// From src\schema\ice\sliced\acme.cpp, generated from file `acme.ice'
#	include <Ice/LocalException.h>
#	include <Ice/ValueFactory.h>
#	include <Ice/OutgoingAsync.h>
#	include <Ice/InputStream.h>
#	include <Ice/OutputStream.h>

#	include <Ice/Initialize.h>

#	include <IceUtil/PopDisableWarnings.h>
#endif // A0S_SCHEMA_ICE

#ifdef A0S_SCHEMA_CISTA
#pragma warning( disable: 4308 )
#pragma warning( disable: 4018 )
#	include "cista.h"
#	define BOOST_DATE_TIME_NO_LIB
#	define BOOST_REGEX_NO_LIB
#	define BOOST_FILESYSTEM_NO_LIB
#	include <boost/asio.hpp>
#	include <boost/asio/experimental/as_single.hpp>
#	include <boost/asio/experimental/as_tuple.hpp>
#	if BOOST_VERSION < 107700 && BOOST_VERSION > 108000
#		error "my msvc support only boost BOOST_LIB_VERSION 1_77-1_80"
#	endif //BOOST_VERSION != 107700
#	include <variant>
#endif // A0S_SCHEMA_CISTA

#pragma warning( pop )
