# Sinus approximation using Taylor series

A program for approximating the sinus function using the Taylor series expansion.  
Implemented in C for my university simulations course.


## Main usage

Program flags:
- `-d` - the angle in degrees
- `-r` - the angle in radians
- `-n` - number of terms in the Taylor series
- `-o` - output CSV file
- `-y` - yes to all interactive questions (e.g. overwrite output file)
- `-?` - help

Flags `-d` and `-r` cannot be used at once.

Example usage:
```bash
./main -d 45 -n 10 # Approximate sin(45deg) using 10 terms of the Taylor series
```


## Compare usage

The `compare` program is used to compare the results of the sinus approximation with the `sin` function from the `math.h` library.

Program flags:
- `-l` - lower bound angle in radians
- `-u` - upper bound angle in radians
- `-s` - step size for angles
- `-o` - output CSV file
- `-t` - upper bound of number of terms in the Taylor series
- `-y` - yes to all interactive questions (e.g. overwrite output file)
- `-?` - help

You can then use the `generate_charts.py` script to generate visualization charts of the data.


## Build

To build the program, run:
```bash
make
```


