#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::to_string;

// Function to get the Red, Green and Blue Colors of the RGB
void getRGB(string message, string *red, string *green, string *blue)
{
  int number;
  string rgb[3];
  bool wrongValue = false;

  while (true)
  {
    cout << "\n\t" << message << ": ";

    cin >> rgb[0]; // Red
    cin >> rgb[1]; // Green
    cin >> rgb[2]; // Blue

    for (int i = 0; i < 3; i++)
    {
      try
      {
        number = stoi(rgb[i]); // Converts the string to an int
        if (number < 0 || number > 255)
        {
          wrongValue = true;
        }
      }
      catch (...)
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

int main()
{
  int x; // Temp data
  // CSI Commands
  string csiFg, csiBg, csiFgCommand, csiBgCommand;
  string fgColor[3], bgColor[3];

  csiFg = "38;2";
  csiBg = "48;2";

  // Ask for the RGB Colors [red; green; blue]
  cout << "Please enter the Red, Green and Blue 8-bit colors";
  getRGB("Foreground Color", &fgColor[0], &fgColor[1], &fgColor[2]);
  getRGB("Background Color", &bgColor[0], &bgColor[1], &bgColor[2]);

  csiFgCommand.append(getRGBCommand(csiFg, fgColor));
  csiBgCommand.append(getRGBCommand(csiBg, bgColor));

  cout
      << "\nHere is How I changed the "
      << csiFgCommand
      << csiBgCommand
      << "Color";
  cin >> x;

  return 0;
}