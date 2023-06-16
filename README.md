# Myzdin-x86_64

## Gameplay
![](image/Myzdin_progress.webp)

## About
A simple 2D palformer game written in C using SDL2. This game is only supported for Linux. This game is in alpha software. There are going to be features missing.

## Dependencies
* gcc (GNU GCC Compiler)
	* build-essential (Debian and Ubuntu distros and its derivatives)
* libsdl2-dev
* libsdl2-mixer-dev
* libsld2-image-dev
* meson
* ninja-build

## Manual Install (Ubuntu 22.04.2 LTS)
![manual_install_sdl2](./manual_install_sdl2.md)

## Building the project
Go the root of my repository
```
cd Myzdin-x86_64
```

Set up the build directory with meson
```
meson build
```

Go to build directory
```
cd build
```

Compile the project
```
meson compile
```

## Tidy script
This script sets up the build directory with **clang** as the default compiler in order for **clang-tidy** to work with this project.

### Dependencies required for this script to work
* clang
* clang-tidy
* clang-tools (optional)
	* if you want to work with clang-check or clang-format

### Tidy script tutorial

Make the script executable
```
chmod +x tidy-project.sh
```

Pass -h flag to get help with this script
```
./tidy-project.sh -h
```

Output ==>
```
-h    help
-r    remove the clang-tooling directory
-s    setup the clang-tooling directory
-t    tidy the project
```

To setup the build directory with clang as the default compiler, pass the -s flag
```
./tidy-project.sh -s
```

You will see a directory called **clang-tooling**

To tidy the project, pass the -t flag
```
./tidy-project.sh -t
```

To remove the build directory you created from the script, pass the -r flag
```
./tidy-project.sh -r
```

You will see that the **clang-toolling** directory got deleted

## Assets (Music, Art and Soundeffects)
<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />I created the music, art and soundeffects for this game. The assets are licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
