# ![Shoot The Virus](img/spaceship.png) 

Arcade 2D game in C with Gfxlib.


## What's Shoot The Virus
It's a game inspired from space invaders developped in C with Gfxlib.
A french library based on Opengl.
Your goal is to reach the highest score by surviving and killing viruses.
Be ready to fight epic boss.
Save us from the pandemic and kill all the viruses.


## Features
Incomming

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


## License
Incomming

## MEMO TODO
Animations de sprite, thread pour séparer la logique du jeu et les animations en temps réel
Probleme affichages des entités si le x, y et hors de la fenetre
gestion des ennemis à revoir, [actuellement] bloqué à cause du rezise des bullets (seg fault)


## Sources
https://github.com/ttroy50/cmake-examples
http://en.wikipedia.org/wiki/Opaque_pointer#C


