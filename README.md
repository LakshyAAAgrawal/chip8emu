# Chip-8 Emulator
This is a terminal based Chip-8 Emulator written in C++. The code has been written modularly to ease different implementations of specifics like Graphics(Terminal based, ncurses based, SDL based, etc) and Input(Touch based, Keyboard based, etc) and enable embedding of the emulator core in other systems.

## What is CHIP-8
CHIP-8 is an interpreted programming language from the mid 1970s. Chip 8 programs run on a Chip 8 virtual machine. It was made to ease the programmability of COSMAC VIP and Telmac 1800 microcomputers. Wikipedia has a very nicely written article on the topic [here](https://en.wikipedia.org/wiki/CHIP-8) for further detail.

## How does it look
The image below displays screenshots of different programs(present in the [roms](/roms) directory) running on the emulator. The emulator consists of a 64x32 display demarcated by "#" borders and displays the internal machine state below(First line displays timers and special registers and second line displays the general purpose registers).
![Screenshot 1](/res/Screenshots/animation.gif)

## How to run
Clone the repository and make:
```
git clone https://github.com/LakshyAAAgrawal/c8emu
cd c8emu/
make
```
To run, execute:
```
./bin/c8emu path/to/rom
```
For example, to run the Tic-Tac-Toe program from the ```roms``` directory, execute:
```
./bin/c8emu roms/games/Tic-Tac-Toe\ \[David\ Winter\].ch8
```

## Input to the emulator
The left-most 4x4 keys of the QWERTY keyboard("1234", "qwer", "asdf", "zxcv") are used for input as follows:

| Chip 8 Key       | Keyboard     |
| :------------- | :----------: |
| 0 | 'x' |
| 1 | '1' |
| 2 | '2' |
| 3 | '3' |
| 4 | 'q' |
| 5 | 'w' |
| 6 | 'e' |
| 7 | 'a' |
| 8 | 's' |
| 9 | 'd' |
| A | 'z' |
| B | 'c' |
| C | '4' |
| D | 'r' |
| E | 'f' |
| F | 'v' |

Pressing 'l' during execution will halt the emulator.

## Assumptions and compatibility
The emulator currently supports Chip-8 only and not any of the extension sets like SCHIP-48, XO-CHIP.
The following assumptions are made:
1. Instructions ```fx55``` and ```fx65``` do not affect the value of I.
2. Instruction ```Dxyn``` clips the sprite if it goes beyond the screen in either horizontal or vertical direction.
3. Instructions ```8xyE``` and ```8xy6``` leave Vy unaffected and modify Vx in-place.

## Contributing and Bug Reports
You are welcome to submit bug reports as issues and to create pull requests to solve any existing issue.

## Customization
Currently, only one customization is allowed. The Chip-8 systems provides programs with an in-system font set consisting of Hex-digits(0-F). The sprites for the same are loaded from [res/sprites.bin](/res/sprites.bin). The user could provide a custom sprite map and load into the emulator by simply changing the file content.

## ROM Credits
ROMs were taken from [https://github.com/dmatlack/chip8](https://github.com/dmatlack/chip8)

Many ROMs were gotten from [Revival Studios](http://www.revival-studios.com/other.php)

## Specification and References
Mainly:
1. [http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#7xkk](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#7xkk)
2. [http://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf](http://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf)
3. [http://mattmik.com/files/chip8/mastering/chip8.html](http://mattmik.com/files/chip8/mastering/chip8.html)

And a lot of other sources mentioned as comments in the source code at relevant places
