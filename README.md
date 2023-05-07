# <img src="assets/icon.png" alt="icon" width="6%"/> PacMan Cpp

[![version](https://img.shields.io/badge/version-1.0.1-blue.svg)](https://github.com/LosKeeper/PacManCpp)
[![compiler](https://img.shields.io/badge/compiler-g++-red.svg)](https://github.com/LosKeeper/PacManCpp/blob/main/Makefile)
[![license](https://img.shields.io/badge/license-GPL_3.0-yellow.svg)](https://github.com/LosKeeper/PacManCpp/blob/main/LICENSE)
[![author](https://img.shields.io/badge/author-LosKeeper-blue)](https://github.com/LosKeeper)
[![author](https://img.shields.io/badge/author-EthanAndreas-blue)](https://github.com/EthanAndreas)
> PacMan game in C++ with SDL

## Table of Contents

1. [Table of Contents](#table-of-contents)
2. [Installation](#installation)
   1. [Linux](#linux)
3. [Usage](#usage)
   1. [Controls](#controls)

## Installation
> This project requires [SDL2](https://www.libsdl.org/download-2.0.php) to be installed on your system.
### Linux
To run the game, simply run the following command in the root directory of the project:
```bash
make run
```
This will compile the project and run the executable.
Otherwise, you can run the following commands:
```bash
make
./bin/pacman
```
You can also see documentation for the project by running:
```bash
make doc
```
This will generate documentation in the `html` directory and open it in your default browser.
## Usage
This is a simple PacMan game written in C++ using SDL. The game is played by moving PacMan around the map and eating all the dots. The game ends when all the dots are eaten or PacMan is caught by a ghost.

### Controls

| Key          | Action     |
| ------------ | ---------- |
| `UpArrow`    | Move up    |
| `DownArrow`  | Move down  |
| `LeftArrow`  | Move left  |
| `RightArrow` | Move right |
| `Escape`     | Quit       |
