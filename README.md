# Minigrep

This repository contains the source code of the Minigrep Terminal Program, which is based on the grep Program for Linux, developed by:

## Developer

- Ramón Álvarez <a href="https://github.com/ralvarezdev">(ralvarezdev)</a>.

## Programming Languages

Only C++.

## Getting Started
To get started with the Minigrep source code, follow these instructions.

## Installation

<ol>
<li>Clone this repository to your local machine using the following command:

```git clone https://github.com/ralvarezdev/uru-programming-1-minigrep```
</li>

<li>Change your Current Working Directory to where the Repository was Cloned</li>

<li>There are Two Ways to Compile the Program:</li>

<ol>
<li>With <strong>G++</strong> (You must have Installed <strong>MinGW Compiler</strong>). Use the following command:

<details>
<summary>Command for Windows</summary>

```g++ -o bin\Minigrep.exe src\main.cpp src\lib\filesOp.cpp src\lib\filesOp.h src\lib\input.cpp src\lib\input.h src\lib\rgbColor.cpp src\lib\rgbColor.h```

</details>

<details>
<summary>Command for Linux</summary>

```g++ -o bin/Minigrep.exe src/main.cpp src/lib/filesOp.cpp src/lib/filesOp.h src/lib/input.cpp src/lib/input.h src/lib/rgbColor.cpp src/lib/rgbColor.h```

</details></li>

<li>With <strong>CMake</strong> (You must have Installed <strong>CMake and Make</strong>). First, Get to the <code>bin</code> Folder inside the Repository. Use the following command:

<details>
<summary>Command for Windows</summary>

```cmake -S ..\ -G "MinGW Makefiles" -B .\ && make```

</details>

<details>
<summary>Command for Linux</summary>

```cmake -S ../ -G "MinGW Makefiles" -B ./ && make```

</details></li></ol>

<li>Run the program by clicking the <code>Minigrep.exe</code> or by using a single-line command as:

```./bin/main.exe phrase to find... filepath...``` (You must enter your own filepath and your own phrase to highlight).
</li>
</ol>

<strong>For a Better User Experience, Resize the Terminal Window to Fullscreen</strong>

## Commands

### Run
```phraseToHighlight... filePath...``` To Highlight the Phrase

### Change Text Colors
```-c``` Change Background and Foreground Color
```-b``` Change Background Color
```-f``` Change Foreground Color

### Help
```-h``` Help
