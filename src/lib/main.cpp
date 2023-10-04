#include "ansiCodes.h"
#include "input.h"
#include "rgbColor.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::string;

/* This program uses ANSI Escape Codes */
int main()
{
  /* --- Examples
  1: .\test.txt checking matches // Here, the program searchs for the phrase "checking matches" in the test.txt file
  2: -h // Here the program will print the Help Message
  */

  // File directory
  string tempInput, fileDir, command, findPhrase;

  cin >> tempInput; // Enter the command or the file path
  if (tempInput[0] != '-')
  {
    fileDir = tempInput;
    getline(cin, findPhrase); // Gets the word or phrase that will be searched throughout the file
  }
  else
  {
    command = tempInput;
    getline(cin, tempInput); // In case, the user typed other parameters, this prevent the app to crash
  }

  // If it starts with a '-', it's a command
  if (command[0] == '-')
  {
    // Help command
    if (command[1] == 'h')
    {
      // Print Helper Message
    }
    else if (command[1] == 'c') // Change the Default Color
    {
      bool changeFgColor, changeBgColor, genRGB;
      string csiCommand;

      changeBgColor = booleanQuestion("\nDo you Want to Change the Background Color?");
      changeFgColor = booleanQuestion("Do you Want to Change the Foreground Color?");

      if (changeFgColor == true || changeBgColor == true)
      {
        genRGB = booleanQuestion("Do you Want to Create the RGB Color?"); // Asks if the User Wants to Set the RGB Color or Use One of the ANSI Command Colors
        if (genRGB == true)
        {
          csiCommand = getRGBTextColor(changeBgColor, changeFgColor); // Asks for the RGB Color and Generates the CSI Command to CHange the Text Color on the Terminal
        }
        else
        {
          // Get the Command with ANSI Default Codes
        }
      }

      // Save Color as the Default Configuration
    }
    else
    {
      cout << "Error 404: Command not Found";
    }
  }
  else
  {
    // Reads, and prints the file
  }
  return 0;
}