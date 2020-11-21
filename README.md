# Mario sokoban avec SDL2

Mario sokoban avec SDL2 est mon approche de ce que propose **Matéo** de **Open clasroom** dans le livre *Apprenez a programmer en language C* \
Le projet utilise sdl2 sdl2_ttf et sdl2 image

## Sous Windows

il vous faut juste gcc le reste est dans le projet

### Pour installer gcc

[Cliker ici](http://www.mingw.org/wiki/howto_install_the_mingw_gcc_compiler_suite)

## Sous Linux

**Disclaimer** je ne travaille pas avec une distribution de linux donc vous êtes prévenus:expressionless:

### Pour installer sdl2 sdl_ttf et sdl_image

```Bash
apt-get install libsdl2-dev
apt-get install libsdl2-ttf-dev
apt-get install libsdl2-image-dev
```

## Pour compiller

* normalement

```bash
gcc src\*.c -o bin\mario -I include -I include\SDL -L lib **-lmingw32** -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
```

Ne pas utiliser -lmingw32 sur linux

* avec débogage ajouter l'option -g
* sans fenêtre(console) ajouter l'option -mwindows

## Setup

Si vous utilliser visual studio code tout est paramétrer
les changements qu'il faudrait peut etre faire ,si tout ne marche
pas seront au niveau des chemins

## Contact

Je suis Ruchdane AMADOU\
[Email](ruchdaneabiodun@gmail.com)\
[lien du projet](https://github.com/Ruchdane/Game)\
Merci pour votre temps et contacter moi s'il y a de probléme :smile:
