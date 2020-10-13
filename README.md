# Chip-8 Emulator
This is a completely terminal based Chip-8 Emulator written in C++.
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

## How to exit
The following are the key maps:

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
1. ```fx55``` and ```fx65``` do not affect the value of I.
2. ```Dxyn``` instruction clips the sprite if it goes beyond the screen in either horizontal or vertical direction.

## Contributing and Bug Reports
You are welcome to submit bug reports as issues and to create pull requests to solve any existing issue.

## Customization
Currently, only one customization is allowed. The Chip-8 systems provides programs with an in-system font set consisting of Hex-digits(0-F). The sprites for the same are loaded from [res/sprites.bin](/res/sprites.bin). The user could provide a custom sprite map and load into the emulator by simply changing the file content.

## ROM Credits
ROMs were taken from [https://github.com/dmatlack/chip8](https://github.com/dmatlack/chip8)

## Specification and References
Mainly:
1. [http://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf](http://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf)
2. [http://mattmik.com/files/chip8/mastering/chip8.html](http://mattmik.com/files/chip8/mastering/chip8.html)
3. [http://mattmik.com/files/chip8/mastering/chip8.html](http://mattmik.com/files/chip8/mastering/chip8.html)

And a lot of other sources mentioned as comments in the source code at relevant places