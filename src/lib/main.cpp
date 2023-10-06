#include "ansiCodes.h"
#include "filesOp.h"
#include "input.h"
#include "ansiCodes.h"
#include "rgbColor.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::ifstream;
using std::string;

namespace fs = std::filesystem;

/* This program uses ANSI Escape Codes */
int main(int argc, char **argv)
{
  /* --- Examples
  1: checking matches .\test.txt // Here, the program searchs for the phrase "checking matches" in the test.txt file
  2: -h // Here the program will print the Help Message
  */

  bool isCommand = false;
  char command;
  string findPhrase;
  string errorMessage = "Error: Wrong Command. Run '-h' to Check the Available Commands"; // Message Print when there's a Wrong Command as Input

  fs::path fileDir;
  fs::path userPath = fs::current_path();
  fs::path binPath = changeCwdToBin(argv[0]); // Change Current Working Directory

  if (argc == 1)
  {
    // If the program was executed outside of the terminal
    helpMessage();

    string temp;
    cout << "\n\n";
    cin >> temp; // Enter the command
    if (temp[0] == '-')
    {
      command = temp[1];
      isCommand = true;
      getline(cin, temp); // In case, the user typed other parameters, this prevent the app to crash
    }
    else
    {
      fileDir = temp;           // First input is the filepath
      getline(cin, findPhrase); // Gets the word or phrase that will be searched throughout the file
    }
  }
  else
  {
    if (argv[1][0] == '-')
    {
      command = argv[1][1]; // If it Starts with a '-', it's a Built-in Command of the Program
      isCommand = true;
    }
    else if (argc < 2)
    {
      cout << errorMessage;
      return -1;
    }
    else
    {
      isCommand = false;

      // File Path
      if (argv[argc - 1][0] == '.')
      {
        fileDir = userPath;

        string tempPath; // File directory path inside the userPath
        char c;
        for (int i = 2; i < sizeof(argv[argc - 1]) / sizeof(char); i++)
        {
          c = argv[argc - 1][i];
          if (c != '/')
          {
            tempPath += c;
          }
          else
          {
            tempPath.append("\\");
          }
        }

        fileDir = fileDir / tempPath; // Join the two filepaths
      }
      else
      {
        fileDir = argv[argc - 1]; // The last argument is the complete file path
      }
      cout << fileDir;

      for (int i = 1; i < argc - 1; i++)
      {
        findPhrase.append(argv[i]); // The arguments after the command that invokes the program and before the file path
        findPhrase.append(" ");
      }
    }
  }

  if (isCommand)
  {
    if (command == 'h')
    {
      helpMessage(); // Print Helper Message
    }
    else
    {
      switch (command)
      {
      case 'c':
      case 'b':
        getRGBTextColor(true); // Asks for the RGB Color and Generates the CSI Command to CHange the Text Color on the Terminal

        if (command != 'c')
        {
          break;
        }
        else
        {
          cout << "\n\n";
        }
      case 'f':
        getRGBTextColor(false);
        break;
      default:
        cout << errorMessage;
        return -1;
      }
    }
  }
  else
  {
    // Output Message
    string findMessage;

    // Reads, and prints the file
    string sgrBgCommand = readDefaultColor(true);  // SGR Command of the Default Background Color
    string sgrFgCommand = readDefaultColor(false); // SGR Command of the Default Foreground Color
  }
  return 0;
}