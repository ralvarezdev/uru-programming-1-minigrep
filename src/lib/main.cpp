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
  bool askExit, exit, isCommand;
  char command;
  string findPhrase, sgrCommand;
  string errorMessage = "Error: Wrong Command. Run '-h' to Check the Available Commands"; // Message Print when there's a Wrong Command as Input

  fs::path fileDir;
  fs::path userPath = fs::current_path();     // get Current Working Directory
  fs::path binPath = changeCwdToBin(argv[0]); // Change Current Working Directory

  do
  {
    askExit = exit = isCommand = false;      // Reset Value
    sgrCommand = readCompleteDefaultColor(); // Get Default Text Color Saved

    if (argc == 1)
    {
      // If the program was executed outside of the terminal
      askExit = true;

      helpMessage();
      printTitle(sgrCommand, "ENTER A COMMAND"); // Ask User Input

      string args;
      cin >> args; // Enter the command
      if (args[0] == '-')
      {
        command = args[1];
        isCommand = true;
        getline(cin, args); // In case, the user typed other parameters, this prevent the app to crash
      }
      else
      {
        findPhrase = args; // First argument should be the first word of the phrase to hightlight if found

        bool newArg = false;
        char c;
        string firstArg, secondArg; // First argument, and second one
        getline(cin, args);         // Get all the User input
        for (int i = 0; i < args.length(); i++)
        {
          c = args[i];
          if (c != ' ')
          {
            secondArg += c;
          }
          else
          {
            newArg = true;
            firstArg = secondArg; // Detected argument
            secondArg = "";
          }

          if (newArg == true && secondArg.length() > 0) // There's another argument. Add the last argument to the phrase that will be highlighted
          {
            newArg = false;

            findPhrase.append(firstArg);
            findPhrase += ' ';
          }
        }
        fileDir = secondArg; // Last input is the filepath
      }
    }
    else
    {
      askExit = false; // Run once and exit
      exit = true;     // Exit the Program After the first Loop

      if (argv[1][0] == '-')
      {
        command = argv[1][1]; // If it Starts with a '-', it's a Built-in Command of the Program
        isCommand = true;
      }
      else if (argc < 3)
      {
        string tempInput;
        cout << errorMessage; // Wrong Command
        cout << "\n\n-- Press ENTER to Exit: ";
        getline(cin, tempInput);
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

        // Check which is the phrase to highlight
        for (int i = 1; i < argc - 1; i++)
        {
          findPhrase.append(argv[i]); // The arguments after the command that invokes the program and before the file path
          findPhrase.append(" ");
        }
      }
    }

    // If it's a Command, run it's function
    if (isCommand)
    {
      if (command == 'h')
      {
        // Help Message Command
        if (argc == 1)
        {
          askExit = false;
          exit = false;
          cout << ANSI_CLEAR;
        }
        else
        {
          helpMessage(); // Print Helper Message
        }
      }
      else
      {
        switch (command)
        {
        case 'c': // Change both Foreground and Background Color
        case 'b':
          getRGBTextColor(true); // Asks for the RGB Color and Generates the CSI Command to Change the Text Color on the Terminal

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
      // Reads, and prints the file

      bool foundInCurrentLine;
      char c;
      int timesFound = 0, foundInLines = 0;     // Counters
      int findLength = findPhrase.length() - 1; // Length of the Phrase that will be found. It has a whitespace at the end, so I substract a minus 1
      string outputMessage;                     // Output Message

      ifstream findInFile;
      findInFile.open(fileDir); // Checking File...
      if (!findInFile)
      {
        cout << "Error: File doesn't Exit or doesn't have the Permissions to Read it";
        findInFile.close();
        return -1;
      }
      else if (findLength != 1)
      {
        // Read line by line
        bool coincidence;
        string line;
        int lineLength, lineLeftLength, i;

        while (getline(findInFile, line))
        {
          i = 0;
          foundInCurrentLine = false;
          coincidence = false;
          lineLength = line.length();  // Length of the line read
          lineLeftLength = lineLength; // Number of characters of the line string that hasn't been read

          for (int s = 0; s < lineLength; s++)
          {
            c = line[s]; // Get character of string
            if (!coincidence)
            {
              if (c != findPhrase[0])
              {
                i++;
              }
              else
              {
                coincidence = true;
                if (i != 0)
                {
                  outputMessage.append(line.substr(s - i, i));
                }
                i = 1;
              }
            }
            else
            {
              if (c != findPhrase[i])
              {
                coincidence = false;
                i++;
              }
              else if (i != findLength - 1)
              {
                i++;
              }
              else
              {
                timesFound++; // Number of coincidences
                outputMessage.append(sgrCommand);
                outputMessage.append(line.substr(s - i, findLength));
                outputMessage.append(ANSI_RESET);

                i = 0;
                coincidence = false;

                if (!foundInCurrentLine)
                {
                  foundInLines++;
                  foundInCurrentLine = true;
                }
              }
            }

            lineLeftLength--;

            // Check if the Phrase can be found on what's left of the current line
            if ((findLength > lineLeftLength + i && coincidence) || (findLength > lineLeftLength && !coincidence))
            {
              outputMessage.append(line.substr(lineLength - lineLeftLength - i, lineLeftLength + i));
              break;
            }
          }
          outputMessage += '\n';
        }
      }
      else
      {
        // Read character by character
        while (true)
        {
          findInFile >> std::noskipws >> c;
          if (findInFile.good())
          {
            if (c == '\n')
            {
              foundInCurrentLine = false;
            }

            if (c != findPhrase[0])
            {
              outputMessage += c;
            }
            else
            {
              timesFound++;
              outputMessage.append(sgrCommand);
              outputMessage += c;
              outputMessage.append(ANSI_RESET);

              if (!foundInCurrentLine)
              {
                foundInLines++;
                foundInCurrentLine = true;
              }
            }
          }
          else
          {
            outputMessage += '\n';
            break;
          }
        }
      }
      findInFile.close();

      int nWp = 2; // Number of Whitespaces before and after Headings

      // Output Message
      if (argc == 1)
        cout << ANSI_CLEAR;

      cout << sgrCommand << string(nWp, ' ') << "Find Phrase" << string(nWp, ' ') << ANSI_RESET
           << string(nWp * 2, ' ') << findPhrase << "\n\n"
           << outputMessage << "\n"
           << sgrCommand << string(nWp, ' ') << timesFound << string(nWp, ' ') << ANSI_RESET << " Coincidences in " << sgrCommand << string(nWp, ' ') << foundInLines << string(nWp, ' ') << ANSI_RESET << " Lines";
    }

    if (askExit)
    {
      exit = booleanQuestion("\n\n-- Do you want to Exit the Program?");
      cout << ANSI_CLEAR;
    }
  } while (!exit);

  return 0;
}