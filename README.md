## Asteroids Game Recreation

Recreated the classic Asteroids game in SFML!

![](https://media.giphy.com/media/WItEjASFX6fhe9gsUY/giphy.gif)

Link to game and more details <b>(please click!)</b>  
https://happyteam.itch.io/asteroids-game-remake

Gameplay of the recreated game  
https://youtu.be/pBtrTyjbm7E

## Features

- Player : Ship animation, smooth movement controls, and spawn invulnerability
- Alien : Enemy AI with random movement patterns, ability to shoot, and audio queues.
- Screen Wrap
- Collision Detection
- Asteroid : Multiple types with different size and speed. Spawn control and location control (will not spawn on player, and only spawns on the edge of the map)
- OOP practices implmented for classes (Ex: WindowsManager, Player, Bullet, InterfaceManager)

## Build

If you did want to build the application on your own device you would need to install SFML-2.5.1 on your system.
Steps can be found on the SFML website.
You would also need to reroute the make file to the path with the SFML library.

Once a successful build is done with the make command,
you will also need to ensure the openal32.dll library is in the same filepath as the executable.
The openal32 library cannot be statically linked unlike the other .dll files that are in the SFML bin.

## Assets Used

- [Background Space](https://bacteri.itch.io/background-space)
- [Asteroids Mini Templates (KENNEY)](https://raphaeljaes.itch.io/asteroids-mini-template)
- [Alien UFO Pack (KENNEY)](https://www.kenney.nl/assets/alien-ufo-pack)
- [Pixel Font Thaleah](https://tinyworlds.itch.io/free-pixel-font-thaleah)

#### Created with SFML.

![](https://media.giphy.com/media/k46qOThO6r3s5j4YYQ/giphy.gif)
