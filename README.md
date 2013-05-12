# Minecraft Flat!
This is a game created for my Computer Science 102 course's final project in Spring 2013.
It is a top-down endless survival game using the Minecraft characters.
See the [Game Design Document](GameDesignDoc.md) for a detailed description of the game.

#### Copyright and license information
Copyright (C) 2013 Eric Gauderman
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License version 2.0 as published by the Free Software Foundation.
See the [LICENSE](LICENSE.txt) for the full text of the GNU General Public License version 2.0.

### Compile & Run Instructions
#### Compile Instructions
The user should use the following procedure to compile the code, in a Linux terminal, with Qt 4.8 or higher installed:
```shell
qmake -project
qmake
make
```
#### Doxygen Instructions
The user should use the following procedure to generate and view Doxygen-generated documentation for this project, in a Linux terminal, with Doxygen installed:
```shell
doxygen -g config.txt
doxygen config.txt
firefox html/index.html
```
#### Commands to run
The user should use one of the following commands to run the program (from a Linux terminal):

To begin with a pre-filled list of high scores:
```shell
./minecraft_flat example_scores.txt
```
To begin with a new, empty list of high scores:
```shell
./minecraft_flat scores.txt
```
