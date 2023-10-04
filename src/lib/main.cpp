#include "ansiCodes.h"
#include "input.h"
#include "ansiCodes.h"
#include "rgbColor.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::string;

// Help Message
void helpMessage()
{
  string commands[2] = {
      "Get Help Message [-h]",
      "Change Default Text Color [-c]"};

  cout << "Avalaible Commands:";

  cout << "\n\n*** Config and Help";
  for (int i = 0; i < size(commands); i++)
  {
    cout << "\n--- " << commands[i];
  }
  cout << "\n\n*** Run\n--- To Find the Phrase : [phrase... filePath...]";
}

/* This program uses ANSI Escape Codes */
int main(int argv, char *argc[])
{
  /* --- Examples
  1: checking matches .\test.txt // Here, the program searchs for the phrase "checking matches" in the test.txt file
  2: -h // Here the program will print the Help Message
  */

  bool isCommand;
  string fileDir, findPhrase, command;

  if (argv < 2)
  {
    // If the program was executed outside of the terminal

    string _temp;

    helpMessage();
    cout << "\n\n";
    cin >> _temp; // Enter the command or the file path
    if (_temp[0] != '-')
    {
      fileDir = _temp;
      getline(cin, findPhrase); // Gets the word or phrase that will be searched throughout the file
    }
    else
    {
      command = _temp;
      isCommand = true;
      getline(cin, _temp); // In case, the user typed other parameters, this prevent the app to crash
    }
  }
  else if (argv == 2)
  {
    if (argc[1][0] == '-')
    {
      command = argc[1]; // If it Starts with a '-', it's a Built-in Command of the Program
      isCommand = true;
    }
    else
    { // Wrong Command
      cout << "\tWrong Command...\n\n\tAvalaible Commands:\n\t- Config and Help: [-h|-c]\n\t- To Find the Phrase: [phrase... filePath...]";
      return -1; // Error
    }
  }
  else
  {
    // If the program is being executed through the terminal

    int numberWords = sizeof(*argc) - 2;

    fileDir = argc[-1]; // The last argument is the file path
    for (int i = 2; i < numberWords + 2; i++)
    {
      findPhrase.append(argc[i]); // The arguments after the command that invokes the program and before the file path
    }
  }

  if (isCommand = true)
  {
    // Help command
    if (command[1] == 'h')
    {
      helpMessage(); // Print Helper Message
    }
    else if (command[1] == 'c') // Change the Default Color
    {
      bool changeFgColor, changeBgColor, change;
      string sgrCommand;

      do
      {
        changeBgColor = booleanQuestion("Do you Want to Change the Background Color?");
        changeFgColor = booleanQuestion("Do you Want to Change the Foreground Color?");

        if (changeFgColor == true || changeBgColor == true)
        {
          sgrCommand = getRGBTextColor(changeBgColor, changeFgColor); // Asks for the RGB Color and Generates the CSI Command to CHange the Text Color on the Terminal

          cout << "\n\t"
               << sgrCommand << "Example Text" << ANSI_RESET << "\n";
          change = booleanQuestion("\nDo you want to change the Color?");
        }
      } while (change);

      // Save Color as the Default Configuration
    }
    else
    {
      cout << "Error 404: Command not Found. Run '-h' to Check the Available Commands";
    }
  }
  else
  {
    // Reads, and prints the file
  }
  return 0;
}