// src\Version.h - versioning, use PE-file resources via BattleCityEos.rc, file will be patched in CI
#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
#define A0S_VERSION_MAJOR 0
#define A0S_VERSION_MINOR 1
#define A0S_VERSION_PATCH 0
#define A0S_VERSION_BUILD 0

#define A0S_stringify(a) A0S_stringify_(a)
#define A0S_stringify_(a) #a

#define A0S_STRING_VERSION \
	    A0S_stringify( A0S_VERSION_MAJOR ) \
	"." A0S_stringify( A0S_VERSION_MINOR ) \
	"." A0S_stringify( A0S_VERSION_PATCH ) \
	"." A0S_stringify( A0S_VERSION_BUILD )

namespace syscross { namespace BattleCityEos {
struct Version { 
	static const char *getSemver( ) {
		static const char *szSemver = A0S_STRING_VERSION;
		return szSemver;
	}
};
}} // namespace syscross::BattleCityEos
