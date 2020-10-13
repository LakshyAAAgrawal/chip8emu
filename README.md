# Chip-8 Emulator
This is a completely terminal based Chip-8 Emulator written in C++.

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

## Support
The emulator currently supports Chip-8 only and not any of the extension sets like SCHIP-48, XO-CHIP.
The following assumptions are made:
1. ```fx55``` and ```fx65``` do not affect the value of I.
2. ```Dxyn``` instruction clips the sprite if it goes beyond the screen in either horizontal or vertical direction.

## Contributing and Bug Reports
You are welcome to submit bug reports as issues and to create pull requests to solve any existing issue.