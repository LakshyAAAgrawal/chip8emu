![Screenshot 1](/res/Screenshots/animation2.gif)

*Emulator displaying the CHIP-8 logo, drawing Sierpinski Triangle and Playing Tetris*

# Chip-8 Emulator
This is a terminal based Chip-8 Emulator written in C++. ```chip8emu``` can be used to run any CHIP-8 program written for the original specification. Discussed on reddit in [r/programming](https://redd.it/jcdatt) and [r/emulation](https://redd.it/jbpr5p).

## What is CHIP-8
CHIP-8 is an interpreted programming language from the mid 1970s. A number of classic video games have been ported to CHIP-8 including Tetris, Space Invaders, Pong(Included in the [roms](/roms) directory). An active enthusiast community exists even today and participate anually in the [Octojam](https://itch.io/jam/octojam-7) to write programs for the CHIP-8 platform. CHIP 8 programs run on a CHIP 8 virtual machine(Similar to how Java Bytecode runs on a JVM, but in a much much more simplified manner). It was made to ease game development and programming of COSMAC VIP and Telmac 1800 microcomputers. Wikipedia has a very nicely written article on [CHIP 8](https://en.wikipedia.org/wiki/CHIP-8) for further detail.

## What is an emulator
Prior to the execution of a computer program, it is generally compiled to a machine-level code specific to the platform on which it is to be run. A software that enables running a program written for one platform on another is called an emulator([More details](https://en.wikipedia.org/wiki/Emulator)). ```chip8emu``` enables you to run programs written for the original CHIP-8 specification on your computer. The programs to be run on an emulator are distributed as ROM files, which are generally a memory dump of the original cartridge that contained the program. An emulator reads the program from the ROM file and executes it step by step as the original platform would. The above explanation is a simplification and a more in-depth discussion on the topic is available at [Stack Overflow](https://stackoverflow.com/questions/448673/how-do-emulators-work-and-how-are-they-written).

## How does chip8emu look
The image below displays screenshots of different programs(present in the [roms](/roms) directory) running on the emulator. The emulator consists of a 64x32 display demarcated by "#" borders and displays the internal machine state below(First line displays timers and special registers and second line displays the general purpose registers).
![Screenshot 2](/res/Screenshots/animation.gif)

## How to run
Clone the repository and make:
```
git clone https://github.com/LakshyAAAgrawal/c8emu
cd c8emu/
make
```
To run, execute:
```
./bin/c8emu path/to/rom.ch8
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

Pressing 'l'(small 'L') during execution will cause a system interrupt and halt the emulator(exit).

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

## Confirmed Working ROMs
These are the ROMs I have already tested and verified working on ```chip8emu```. Many others should be supported as well. Also checkout [Octojam](https://itch.io/jam/octojam-7) for more recent ROMs.
- roms/demos/Maze (alt) [David Winter, 199x].ch8
- roms/demos/Sierpinski [Sergey Naydenov, 2010].ch8
- roms/demos/Trip8 Demo (2008) [Revival Studios].ch8
- roms/demos/Zero Demo [zeroZshadow, 2007].ch8
- roms/games/Cave.ch8
- roms/games/Figures.ch8
- roms/games/Pong (alt).ch8
- roms/games/Soccer.ch8
- roms/games/Space Invaders [David Winter] (alt).ch8
- roms/games/Tic-Tac-Toe [David Winter].ch8
- roms/games/Tetris [Fran Dachille, 1991].ch8

## ROM Credits
ROMs were taken from [https://github.com/dmatlack/chip8](https://github.com/dmatlack/chip8)

Many ROMs were gotten from [Revival Studios](http://www.revival-studios.com/other.php)

## Note on implementation of instructions
A very interesting bug came up during the testing of the emulator. While playing the ROMs mentioned in [issue #28](https://github.com/LakshyAAAgrawal/chip8emu/issues/28), the games were mostly working except for a few instructions not behaving as expected. Stepping through the Octo debugger revealed a behaviour not explicitly documented in most Chip-8 specifications. The Instructions 8xy4, 8xy5, 8xy6, 8xy7, 8xye modify the Vf register using it as a flag. The earlier implementation of chip8emu was updating the flag register before executig the instruction, however, the Vf flag must be set after the exeuction of the instruction. This is to ensure handling of cases where Vf is itself being operated upon.

## Specification and References
Mainly:
1. [http://devernay.free.fr/hacks/chip8/C8TECH10.HTM](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
2. [http://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf](http://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf)
3. [http://mattmik.com/files/chip8/mastering/chip8.html](http://mattmik.com/files/chip8/mastering/chip8.html)

And a lot of other sources mentioned as comments in the source code at relevant places
