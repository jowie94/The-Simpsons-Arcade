![The Simpsons GIF](docs/head.gif)

# [The Simpsons Arcade](https://jowie94.github.io/The-Simpsons-Arcade/) 👾
Welcome to my own take of the classic The Simpsons arcade game.

This is a really simplified version of the original [arcade version](https://en.wikipedia.org/wiki/The_Simpsons_(video_game)) of The Simpsons. It is build using SDL and C++.

The graphics are partly extracted from [Spriters Resource](https://www.spriters-resource.com/arcade/simpsons/) and manually ripped. All the sounds found in the game are also manually ripped.

## How To Play 🎮
To play the game, download the .zip from [GitHub releases](https://github.com/jowie94/The-Simpsons-Arcade/releases) and extract it to any folder. Once extracted, execute __The Simpsons Arcade.exe__.

When the game is loaded press the space bar to begin playing. Currently it only has Homer as a playable character, but more players will be added in the future.

- Marge (Red Homer) is controlled using _W_, _A_, _S_, _D_ for movement, _Z_ for attacking, and _X_ for jumping.
- Homer is controlled using _T_, _F_, _G_, _H_ for movement, _v_ for attacking, and _b_ for jumping.
- Bart (Inverse Homer) is controlled using _U_, _H_, _J_, _K_ for movement, _N_ for attacking, and _M_ for jumping.
- Lisa (Brown Homer) is controlled using _Up_, _Left_, _Down_, _Right_ for movement, _0_ for attacking, and _1_ for jumping.

You can do air attacks by pressing attack while jumping.

Check out my gameplay on [Youtube](https://youtu.be/r7dJv6fVXPc) 😄

## How to build the game ⚙
To build the game, you just need to open it in Visual Studio (Linux will be added in the future) and compile it. If you want to play it inside Visual Studio, you will have to modify the __Execution folder__ under the debug settings of the __The Simpsons Arcade__ project, and make it point to $(SolutionDir)External.

## License
MIT © Joel Lopez

Enjoy!
