#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::to_string;

// Function to get the Red, Green and Blue Colors of the RGB 8-bit Color
void getRGB(string message, string *red, string *green, string *blue)
{
  bool wrongValue = false;
  int number;
  string rgb[3];

  cout << "\n";
  while (true)
  {
    cout << "\t" << message << ": ";

    cin >> rgb[0]; // Red
    cin >> rgb[1]; // Green
    cin >> rgb[2]; // Blue

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
        cout << "\t- Wrong Value. It must be in the range of 0-255\n";
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

// Function to get the CSI Command to Change the Color to either the Foreground or the Background
string getRGBCommand(string colorCommand, string rgb[3])
{
  string csiCommand = "\x1b["; // Control Sequence Introducer (CSI)
  csiCommand.append(colorCommand);

  for (int i = 0; i < 3; i++)
  {
    csiCommand.append(";");
    csiCommand.append(rgb[i]); // Append each color to the CSI Command
  }
  csiCommand.append("m");

  return csiCommand;
}

// Get ANSI Code to Change the Text Color on the Terminal with 8-bit RGB Color
string getANSITextColor(bool changeBgColor, bool changeFgColor)
{
  string csiCommand; // CSI Command

  if (changeBgColor == true)
  {
    string csiBg, bgColor[3];

    csiBg = "48;2";
    getRGB("Background Color", &bgColor[0], &bgColor[1], &bgColor[2]); // Ask for the RGB Colors [red; green; blue]
    csiCommand.append(getRGBCommand(csiBg, bgColor));
  }
  if (changeFgColor == true)
  {
    string csiFg, fgColor[3];

    csiFg = "38;2";
    getRGB("Foreground Color", &fgColor[0], &fgColor[1], &fgColor[2]);
    csiCommand.append(getRGBCommand(csiFg, fgColor));
  }

  return csiCommand;
}