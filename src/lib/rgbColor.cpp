#include "ansiCodes.h"
#include "input.h"
#include "filesOp.h"
#include <iostream>
#include <iomanip>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::setfill;
using std::setw;
using std::string;
using std::to_string;

// Print Some Color Suggestions
void printColorSuggestions()
{
  const int charSizeColor = 4; // The Number of Whitespace Used on the Message with the Color as the Background
  const int maxCol = 4;        // Max Number of Columns
  string rgbColor, sgrCommand = CSI;

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

  int colorSuggestions[12][3] = {
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

  cout << "\t**** Some Color Suggestions ***\n";
  for (int i = 0; i < sizeof(colorSuggestions) / sizeof(colorSuggestions[0]); i++)
  {
    if (i % maxCol == 0 || i == 0)
    {
      cout << "\n";
    }

    // Print a Color with its Code Next to it
    sgrCommand.append("48;2");
    // Loop to get the RGB section from an Int Array for the SGR
    for (int j = 0; j < 3; j++)
    {
      rgbColor = to_string(colorSuggestions[i][j]);
      sgrCommand.append(";");
      sgrCommand.append(rgbColor);
    }
    sgrCommand.append("m");

    // Cell with Color
    cout << "\t" << sgrCommand << string(charSizeColor, ' ') << ANSI_RESET << " --> ";
    // RGB Number
    for (int j = 0; j < 3; j++)
    {
      cout << setfill(' ') << setw(3) << colorSuggestions[j];
      if (j != 2)
      {
        cout << ' ';
      }
    }
  }
}

// Function to get the Red, Green and Blue Colors of the RGB 8-bit Color
void saveRGB(string message, string csiPrefix, string invokeCommand, char *filename)
{
  bool wrongValue, change;
  int n;
  string rgb[3], sgrCommand = CSI;

  cout << "\n";
  do
  {
    while (true)
    {
      wrongValue = false;
      cout << "\t" << message << ": ";

      for (int i = 0; i < 3; i++)
      {
        cin >> rgb[i]; // 0: Red, 1: Green, 2: Blue
      }

      if (getchar() != '\n') // This prevents the program to crash if the user enters more than three parameters
      {
        string temp;
        getline(cin, temp);
      }

      for (int i = 0; i < 3; i++)
      {
        try
        {
          n = stoi(rgb[i]);     // Converts the string to an int
          if (n < 0 || n > 255) // Checks if the Color is between 0 and 255
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

    sgrCommand.append(csiPrefix);
    // Loop to get the RGB part from a String Array for the Select Graphic Rendition (SGR)
    for (int i = 0; i < 3; i++)
    {
      sgrCommand.append(";");
      sgrCommand.append(rgb[i]); // Append each color to the SGR
    }
    sgrCommand.append("m");

    cout << "\n\t/// " << sgrCommand << " Example Text " << ANSI_RESET << " ///\n";
    change = booleanQuestion("\n\t--- Do you want to change the Color?");
  } while (change);

  writeToFile(filename, sgrCommand, invokeCommand); // Save Color as the Default Configuration
}

// Get the ANSI Escape Sequence to Change the Text Color on the Terminal with 8-bit RGB Color. If changeBgColor is false, it will Change the Foreground
void getRGBTextColor(bool changeBgColor, string invokeCommand)
{
  if (changeBgColor == true)
  {
    saveRGB("\n*** Background Color", "48;2", invokeCommand, "defaultBgColor.bin");
  }
  else
  {
    saveRGB("\n*** Foreground Color", "38;2", invokeCommand, "defaultFgColor.bin");
  }
}