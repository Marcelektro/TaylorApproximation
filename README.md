# Sinus approximation using Taylor series

A program for approximating the sinus function using the Taylor series expansion.  
Implemented in C for my university simulations course.


## Usage

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

## Build

To build the program, run:
```bash
make
```


