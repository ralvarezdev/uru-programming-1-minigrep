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
  int n, i, j, k;              // Counters
  string rgbColor;

  int colorSuggestions[6][3][3] = {
      {{32, 32, 32},     // Dark Gray
       {128, 128, 128},  // Medium Gray
       {192, 192, 192}}, // Light Gray
      {{102, 0, 51},     // Dark Pink
       {255, 0, 127},    // Medium Pink
       {255, 153, 204}}, // Light Pink
      {{102, 0, 0},      // Dark Red
       {255, 0, 0},      // Medium Red
       {255, 153, 153}}, // Light Red
      {{0, 102, 51},     // Dark Green
       {0, 255, 128},    // Medium Green
       {153, 255, 204}}, // Light Green
      {{0, 51, 102},     // Dark Blue
       {0, 128, 255},    // Medium Blue
       {153, 204, 255}}, // Light Blue
      {{51, 0, 102},     // Dark Purple
       {127, 0, 255},    // Medium Purple
       {204, 153, 255}}  // Light Purple
  };

  // Color Table Data
  int numberRGB = sizeof(colorSuggestions[0][0]);              // Size of Elements that are part of the RGB Array
  int numberColors = sizeof(colorSuggestions) / numberRGB;     // Number of Different Colors
  int tintsPerColor = sizeof(colorSuggestions[0]) / numberRGB; // Tints Variations per Color of the Same Type
  int typesColor = numberColors / tintsPerColor;               // Number of Color Types

  cout << "\t**** Some Color Suggestions ***\n";
  j = -1;
  for (n = 0; n < numberColors; n++)
  {
    string sgrCommand = CSI; // WARNING: Its Content is being erase by Re-declaring in each Iteration

    if (n % typesColor == 0 || n == 0)
    {
      cout << "\n";
      i = 0;
      j++;
    }

    // Print a Color with its Code Next to it
    sgrCommand.append(ANSI_RGB_BG_COLOR);
    // Loop to get the RGB section from an Int Array for the SGR
    for (k = 0; k < 3; k++)
    {
      rgbColor = to_string(colorSuggestions[i][j][k]);
      sgrCommand.append(";");
      sgrCommand.append(rgbColor);
    }
    sgrCommand.append("m");

    // Cell with Color
    cout << "\t" << sgrCommand << string(charSizeColor, ' ') << ANSI_RESET;
    // RGB Number
    for (k = 0; k < 3; k++)
    {
      cout << ' ' << setfill(' ') << setw(3) << colorSuggestions[i][j][k];
    }

    i++;
  }
}

// Function to get the Red, Green and Blue Colors of the RGB 8-bit Color
void saveRGB(string message, string csiPrefix, bool changeBgColor)
{
  bool wrongValue, change;
  int n, rgbInt[3];
  string rgbString[3], sgrCommand;

  cout << "\n";
  do
  {
    while (true)
    {
      sgrCommand = CSI;

      wrongValue = false;
      cout << "\n\t" << message << ": ";

      for (int i = 0; i < 3; i++)
      {
        cin >> rgbString[i]; // 0: Red, 1: Green, 2: Blue
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
          n = stoi(rgbString[i]); // Converts the string to an int
          if (n < 0 || n > 255)   // Checks if the Color is between 0 and 255
          {
            wrongValue = true;
          }
          else
          {
            rgbInt[i] = n; // Saved as an Int to Get Rid of Floats if the User Entered One
          }
        }
        catch (...) // Checks if All the Characters are Decimal Digits
        {
          wrongValue = true;
        }

        if (wrongValue)
        {
          cout << "\t- Wrong Value. It must be an integer in the range of 0-255\n";
          break;
        }
      }

      if (!wrongValue)
      {
        break;
      }
    }

    sgrCommand.append(csiPrefix);
    // Loop to get the RGB part from a String Array for the Select Graphic Rendition (SGR)
    for (int i = 0; i < 3; i++)
    {
      sgrCommand.append(";");
      sgrCommand.append(to_string(rgbInt[i])); // Append each color to the SGR
    }
    sgrCommand.append("m");

    cout << "\n\t/// " << sgrCommand << " Example Text " << ANSI_RESET << " ///\n";
    change = booleanQuestion("\n\t--- Do you want to change the Color?");
  } while (change);

  // Save Color as the Default Configuration
  if (changeBgColor)
  {
    writeDefaultColor(bgColorFilename, sgrCommand);
  }
  else
  {
    writeDefaultColor(fgColorFilename, sgrCommand);
  }
}

// Get the ANSI Escape Sequence to Change the Text Color on the Terminal with 8-bit RGB Color. If changeBgColor is false, it will Change the Foreground
void getRGBTextColor(bool changeBgColor)
{
  printColorSuggestions();

  if (changeBgColor)
  {
    saveRGB("*** Background Color", ANSI_RGB_BG_COLOR, changeBgColor);
  }
  else
  {
    saveRGB("*** Foreground Color", ANSI_RGB_FG_COLOR, changeBgColor);
  }
}