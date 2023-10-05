#include "ansiCodes.h"
#include <iostream>
#include <map>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::map;
using std::string;
using std::to_string;

// Function to get the RGB part from a String Array for the Select Graphic Rendition (SGR)
string getRGBFromString(string rgb[3])
{
  string rgbCommand;

  for (int i = 0; i < 3; i++)
  {
    rgbCommand.append(";");
    rgbCommand.append(rgb[i]); // Append each color to the SGR
  }
  rgbCommand.append("m");

  return rgbCommand;
}

// Function to get the RGB section from an Int Array for the SG
string getRGBFromInt(int rgb[3])
{
  string rgbCommand, rgbColor;

  for (int i = 0; i < 3; i++)
  {
    rgbColor = to_string(rgb[i]);
    rgbCommand.append(";");
    rgbCommand.append(rgbColor);
  }
  rgbCommand.append("m");

  return rgbCommand;
}

// Function to Print a Color with its Code Next to it
void printColor(int rgb[3])
{
  const int charSizeColor = 4; // The Number of Whitespace Used on the Message with the Color as the Background
  string sgrCommand = CSI;

  sgrCommand.append("48;2");
  sgrCommand.append(getRGBFromInt(rgb));
  cout << sgrCommand << ANSI_BOLD << string(charSizeColor, ' ') << ANSI_RESET << " --> " << rgb[0] << " " << rgb[1] << " " << rgb[2];
}

// Function to get the Red, Green and Blue Colors of the RGB 8-bit Color
void getRGB(string message, string *red, string *green, string *blue)
{
  bool wrongValue;
  int number;
  string rgb[3];

  cout << "\n";
  while (true)
  {
    wrongValue = false;
    cout << "\t" << message << ": ";

    for (int i = 0; i < 3; i++)
    {
      cin >> rgb[i]; // 0: Red, 1: Green, 2: Blue
    }
    if (getchar() != '\n') // This prevents the program to crash if the user enters mora than three parameters
    {
      string _temp;
      getline(cin, _temp);
    }

    for (int i = 0; i < 3; i++)
    {
      try
      {
        number = stoi(rgb[i]);          // Converts the string to an int
        if (number < 0 || number > 255) // Checks if the Color is between 0 and 255
        {
          wrongValue = true;
        }
      }
      catch (...) // Checks if All the Characters are Decimal Digits
      {
        wrongValue = true;
      }

      if (wrongValue == true)
      {
        cout << "\t- Wrong Value. It must be an integer in the range of 0-255\n";
        break;
      }
    }

    if (wrongValue == false)
    {
      break;
    }
  }

  // Save the Colors on the Reference Values of the Pointers
  *red = rgb[0];
  *green = rgb[1];
  *blue = rgb[2];
}

// Function to get the SGR Command to Change the Color to either the Foreground or the Background
string getRGBCommand(string colorCommand, string rgb[3])
{
  string sgrCommand = CSI;
  sgrCommand.append(colorCommand);
  sgrCommand.append(getRGBFromString(rgb));

  return sgrCommand;
}

// Get the ANSI Escape Sequence to Change the Text Color on the Terminal with 8-bit RGB Color
string getRGBTextColor(bool changeBgColor, bool changeFgColor)
{
  string sgrCommand; // SGR Command

  /* Color Suggestions
  0: Dark Grey
  1: Dark Red
  2: Dark Green
  3: Purple
  4: Medium Grey
  5: Medium Red
  6: Medium Green
  7: Blue
  8: Light Grey
  9: Light Red
  10: Light Green
  11: Cyan
  */

  int exampleColors[12][3] = {
      {32, 32, 32},
      {102, 0, 0},
      {0, 102, 51},
      {0, 51, 102},
      {128, 128, 128},
      {255, 0, 0},
      {0, 255, 128},
      {0, 128, 255},
      {192, 192, 192},
      {255, 153, 153},
      {153, 255, 204},
      {153, 204, 255}};

  cout << "\n\t**** Some Color Suggestions ***\n";

  int maxCol = 4; // Max Number of Columns
  for (int i = 0; i < sizeof(exampleColors) / sizeof(exampleColors[0]); i++)
  {
    if (i % maxCol == 0 || i == 0)
    {
      cout << "\n\t";
    }
    else
    {
      cout << "\t";
    }
    printColor(exampleColors[i]);
  }

  cout << "\n";
  if (changeBgColor == true)
  {
    string csiBg, bgColor[3];

    csiBg = "48;2";                                                    // Part of the Select Graphic Rendition Subset Command
    getRGB("Background Color", &bgColor[0], &bgColor[1], &bgColor[2]); // Ask for the RGB Colors [red; green; blue]
    sgrCommand.append(getRGBCommand(csiBg, bgColor));
  }
  if (changeFgColor == true)
  {
    string csiFg, fgColor[3];

    csiFg = "38;2";
    getRGB("Foreground Color", &fgColor[0], &fgColor[1], &fgColor[2]);
    sgrCommand.append(getRGBCommand(csiFg, fgColor));
  }

  return sgrCommand;
}