# Ketchup Maze

Ketchup Maze is an extension of the [TomatBoot](https://github.com/TomatOrg/TomatBoot) bootloader, implementing a labyrinth game as an extra menu option.
The project is written in C, with the help of [EDK2](https://github.com/tianocore/edk2).

Its **innovative element** is the addition of an UEFI game in an already-existing functional bootloader.

The project has been done as part of the "Systems with Microprocessors" course at University Politehnica of Bucharest. 

# Preview

Main menu         |  Level selection
:-------------------------:|:-------------------------:
![](/screenshots/main_menu.jpeg)  |  ![](/screenshots/level_menu.jpeg)

Color selection         |  Gameplay
:-------------------------:|:-------------------------:
![](/screenshots/green.jpeg)  |  ![](/screenshots/win.jpeg)

## Usage

The project was developed, compiled and tested on Linux.

### Dependencies
The following dependencies are required for running the project:
- [QEMU](https://www.qemu.org/)
- [EDK2](https://github.com/tianocore/edk2)
- C complier
   NASM complier
```
sudo apt-get install build-essential qemu nasm ovmf
```
To prepare the EDK2 development environment, the instructions on their website will be followed.<br>
I recommend the following [method / tutorial](https://wiki.ubuntu.com/UEFI/EDK2).

### Compilation
Clone the project, and proceed with the following commands:

```
cd KetchupMaze
make
```

To delete the generated sources:
```
make clean
```

### Testing
Running the project in QEMU is facilitated by the _build_and_test.sh_ script.
```
cd bin
./build_and_test.sh
```

Press _ESC_ in QEMU, and then load and boot the corresponding filesystem using those commands:
```
> fs0:
> bootx64
```

The extension of the initial project can be seen through the G (Game) option.


## Similar (standalone) projects
- [The UEFI Maze Game](https://uefi.blogspot.com/2016/11/the-uefi-maze-game-part-1.html)
- [Firmware Maze](https://github.com/liute62/Firmware-UEFI-Maze-Game)

### Innovative element
The project binds together the UEFI game concept with a functional bootloader. <br>
Thus, it can be used in the future even outside a virtual machine (e.g. QEMU) as the main bootloader of a computing system.

## Implementation details

### Personal contributions
Intergal personal contribution with the files:
- src/menus/ChooseLevel.c
- src/menus/GameUtils.c
- src/menus/EasyGameMenu.c
- src/menus/MediumGameMenu.c
- src/menus/HardGameMenu.c
- src/util/MemUtils.c

Partially, added code to the following existing files:
- src/menus/Menus.h
- src/menus/Menus.c
- src/menus/MainMenu.c

### Description of functions implemented
Initially, I tried to understand the source project, in order to integrate the game into it as well as possible. The need for the functions was deduced gradually, observing the portions of the code that are repeated / are very complex to write. <br>
Most of the functions used are in src/menus/GameUtils.c, and the main implementations are:

#### Labyrinth drawing - DrawMaze()
The pattern of drawing the source bootloader logo follows. <br>
Thus, a CHAR8 type array is defined for each maze to be drawn. CHAR8 is used because UEFI colors are defined this way (by tags, eg: EFI_RED, EFI_GREEN). <br>
Next are defined the dimensions of the array (2 dimensions - it will be accessed as a matrix), and the coordinates of the top left corner, where the drawing will start. The source project wrapper used: DrawImage(...), which uses the UEFI Graphics Output Protocol.

#### Color change - DrawMazeColor(CHAR8 maze_color)
Different CHAR8 type arrays are defined for each color + an array on which the character will move. It is not an efficient method, but it is the only one found at the moment, thanks to the necessary macros (#define). The function receives the desired color and draws the desired maze on the screen as a color, copying each time the maze in which the character will move.

#### Character movement - int moveInMaze(int pos, int height, int moves[4])
The function uses the UEFI Standard Input Text Protocol, and defines the possible moves in a certain position, making the connection with their drawing in the maze.<br>
The function receives the position for which the moves are defined (pos), the height of the maze (height), and an array in which the positions are specified (moves[4]). The order of the keys is W, A, S, D (up, left, down, right), and the possible positions are marked with 1, the impossible ones with 0. An example of an array: [1, 0, 0, 0], means that the only valid move is up (W key).

### Encountered problems

#### Video performance
The game performs a lot of operations with the Graphics Output Protocol, crowding the video memory. With each valid move in the maze, its image will be reloaded, as well as in the case of color change, for example. <br>
The attempt to implement more complex mazes will crowd the video memory, enough to produce a visual disturbance: the loading time of the lines will increase and the "refresh" of the maze is very slow.<br><br>
Solving the problem would involve rethinking the entire implementation of the moves in the mazes, but it is taken into account in the future for the progress of the project.

#### -W-unused-function warnings
When compiling, warnings of the type -W-unused-function appear, because the useful functions are not used in the same file, but in other files.<br><br>
For a "clean" compilation, pragmas were added in these cases.

