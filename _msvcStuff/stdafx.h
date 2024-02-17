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
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <stdexcept>
#include <iostream>

#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <intrin.h>

#include <iomanip>
#include <conio.h>
#include <cassert>

#include <filesystem>
#include <fstream>
#include <functional>

// SDL stuff
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>

// GoogleProtobuf
#include "proto/acme.pb.h"

#pragma warning( pop )
