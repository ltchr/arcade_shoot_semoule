# ![Shoot The Virus](img/spaceship.png) 

Arcade 2D game in C with Gfxlib.
This project was possible with the help of
* Neitherman83
* JaysonNrt
* Hivanhoe438


## What's Shoot The Virus
It's a game inspired from space invaders developped in C with Gfxlib.
A french library based on Opengl.
Your goal is to reach the highest score by surviving and killing viruses.
Be ready to fight epic boss.
Save us from the pandemic and kill all the viruses.



## Development process
Tested on Linux Mint 19.x, 20.x, Ubuntu.

Install cmake
Compile and run from the source directory
```shell
$ ./run
```


## Screenshots
![Spaceship](img/spaceship.png)

Debug build
cmake -DCMAKE_BUILD_TYPE=Debug <path>

Release build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo <path>



## TODO
[tableau] score + hscore -> fichier
son de tir et musique de fond
variante ennemies
Animations de sprite, thread pour séparer la logique du jeu et les animations en temps réel


## Sources
https://github.com/ttroy50/cmake-examples
http://en.wikipedia.org/wiki/Opaque_pointer#C

## License

* Source code is licensed under MIT
