[![cpp-logo](https://img.shields.io/badge/C++v17-Solutions-blue.svg?style=flat&logo=c%2B%2B)](
https://en.wikipedia.org/wiki/C++
)

Battle City game, from NES 1985 Namco, for Epic EOS multiplayer, C++17, SDL2, sound.

@todo
 - [x] Release vanilla version with sounds in single Windows *.exe
 - [ ] UnrealEngine UObject-s Serialize/Deserialize, replication
 - [x] refactoring "krystiankaluzny/Tanks"
   - get rid of "new/delete" using smart pointers
   - get rid of the statics of all functionality and any singletons from the remnants of the parent project
   - try "Eigen" to reduce the collision code from "src\app_state\game.*"
 - [x] replication via POD or protobuf or zeroc.ice or cista
 - [ ] try boost/safe_numerics for arithmetic
 - [ ] to use my [HelloEOS](https://github.com/Alex0vSky/HelloEOS) and [BenchEosP2p](https://github.com/Alex0vSky/BenchEosP2p)
 - [ ] everything will be done for building via "cmake"

## Features
The source code of the OOP model is obtained from [KrystianKaluzny](https://github.com/krystiankaluzny/Tanks).
 - refactoring:
    - removed branching of definitions for "Mac/iOS";
    - removed "using namespace std;";
    - removed ".." descents from include paths;
    - removed unnecessary SDL includes from headers, like "#include <SDL2/SDL_events.h>", PCH;
    - moved the *.cpp part to the header, left the *.cpp/*.h pairs for “Ue UHT” for classes for which sending over the network is possible;
    - "#pragma once";
    - translation from Polish into English;
    - code reduction due to: direct use of POD/Aggregate, in-class member initializers;
    - improvements: introduced constants as much as possible where possible.
 - correct minor errors;
 - added audio logic;
 - added audio resources.

The audio solution is obtained from [RippeR37](https://github.com/RippeR37/BattleCity).
Extra "*.ogg" obtained from [sounds-resource.com](https://www.sounds-resource.com/download/3710/)

## Requirements
SDL2.
`SDL2_ttf.dll`
`SDL2_mixer.dll`
`SDL2_image.dll`
`SDL2.dll`

## Install
The application consists of one file and resource directory. Does not require installation. 

## Usage
Player 1 controlls: arrows for movement, fire on [left Alt]

Player 2 controlls(HotSeat): WASD for movement, fire on [right Alt]

## Tests

## Build
Building the project and tests from the source code requires the presence of the __Microsoft Visual Studio 2019 Community__, and using *.sln and *.vcxproj project files.

## Contributing
Can ask questions. PRs are accepted. No requirements for contributing.

## Thanks
 - [KrystianKaluzny](https://github.com/krystiankaluzny/Tanks)
 - [RippeR37](https://github.com/RippeR37/BattleCity)
 - [sounds-resource.com](https://www.sounds-resource.com/download/3710/)
 - [freeconvert.com](https://www.freeconvert.com/wav-to-ogg)
 - [aconvert.com](https://www.aconvert.com/audio/split/)

## License
See the [LICENSE](https://github.com/Alex0vSky/BattleCityEos/blob/main/LICENSE) file for license rights and limitations (MIT).
