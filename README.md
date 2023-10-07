# Minigrep

This repository contains the source code of the Minigrep Terminal Program, which is based on the grep Program for Linux, developed by:

## Developer

- Ramón Álvarez <a href="https://github.com/ralvarezdev">(ralvarezdev)</a>.

## Programming Languages

Only C++.

## Getting Started
To get started with the Minigrep source code, follow these instructions.

### Installation
1. Create a folder named as ```minigrep````. Change the Current Working Directory to that one.
1. Clone this repository to your local machine using the following command:
    ```git clone https://github.com/ralvarezdev/minigrep```
2. To successfully compile this program, use the following command:
    ```g++ -o bin\main.exe src\lib\main.cpp src\lib\rgbColor.cpp src\lib\rgbColor.h src\lib\input.cpp src\lib\input.h src\lib\ansiCodes.h src\lib\filesOp.cpp src\lib\filesOp.h``` (You must have MinGW Compiler installed in your local machine).
3. Run the program by clicking the```main.exe``` inside the ```bin``` folder or by using a single-line command as:
    ```.\bin\main.exe phrase to find... filepath...``` (You must enter your own filepath and your own phrase to highlight).
