#include "ansiCodes.h"
#include "filesOp.h"
#include "input.h"
#include "ansiCodes.h"
#include "rgbColor.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <string.h> // Just for the strlen function

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
        for (int i = 2; i < strlen(argv[argc - 1]); i++)
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
    string outputMessage;
    int findLength = findPhrase.length() - 1; // Length of the Phrase that will be found. It has a whitespace at the end, so I substract a minus 1

    // Reads, and prints the file
    string sgrCommand = readDefaultColor(true); // SGR Command of the Default Background Color
    sgrCommand.append(readDefaultColor(false)); // SGR Command of the Default Foreground Color

    // Checking File...
    ifstream findInFile;
    findInFile.open(fileDir);

    bool newLine = false; // Boolean to check if there's a new line
    char c;
    string tempMessage; // Temporary Message that later will be append to the outputMessage
    int i = 0, j = 0, lastLineFound;
    int timesFound, foundInLines; // Counters
    if (!findInFile)
    {
      cout << "Error: File doesn't Exit or doesn't have the Permissions to Read it";
      findInFile.close();
      return -1;
    }
    else
    {
      while (true)
      {
        findInFile >> std::noskipws >> c; // Doesn't skip Whitespaces
        if (findInFile.good())
        {
          if (c != findPhrase[i] || i == findLength)
          {
            if (i != findLength)
            {
              outputMessage.append(tempMessage);
            }
            tempMessage = ""; // Clear string
            i = 0;
          }

          if (c != findPhrase[i])
          {
            outputMessage += c;
            if (c == '\n')
            {
              newLine = true;
              j++;
            }
          }
          else
          {
            tempMessage += c;
            i++;

            if (i == findLength)
            {
              timesFound++; // Number of coincidences
              outputMessage.append(sgrCommand);
              outputMessage.append(tempMessage);
              outputMessage.append(ANSI_RESET);

              if (lastLineFound != j)
              {
                lastLineFound = j;
                foundInLines++;
                newLine = false;
              }
            }
          }
        }
        else
        {
          break;
        }
      }
    }
    findInFile.close();

    cout << outputMessage;
    cout << '\n'
         << string(50, '-') << '\n';
    cout << sgrCommand << string(2, ' ') << timesFound << string(2, ' ') << ANSI_RESET << " Coincidences in ";
    cout << sgrCommand << string(2, ' ') << foundInLines << string(2, ' ') << ANSI_RESET << " Lines";
  }
  return 0;
}