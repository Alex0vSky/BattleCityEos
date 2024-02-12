[![cpp-logo](https://img.shields.io/badge/C++v17-Solutions-blue.svg?style=flat&logo=c%2B%2B)](
https://en.wikipedia.org/wiki/C++
)

Battle City game, from NES 1985 Namco, for Epic EOS multiplayer, C++17, SDL2, sound.

@todo
 - [ ] refactoring "krystiankaluzny/Tanks" 
   - get rid of `new/delete` using smart pointers
   - get rid of the statics of all functionality and any singletons from the remnants of the parent project
   - try `Eigen` to reduce the collision code from `src\app_state\game.*`
 - [ ] join [HelloEOS] and [BenchP2p]
 - [ ] replication via POD
 - [ ] UnrealEngine UObject-s Serialize/Deserialize, replication
 - [ ] everything will be done for building via "cmake".

## Features
The source code of the OOP model is obtained from [KrystianKaluzny](https://github.com/krystiankaluzny/Tanks).
 - refactoring

The audio solution is obtained from [RippeR37](https://github.com/RippeR37/BattleCity).
 - refactoring
 - extra "*.ogg" obtained from [sounds-resource.com](https://www.sounds-resource.com/download/3710/)

## Requirements
SDL2

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
