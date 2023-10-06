#include "ansiCodes.h"
#include "rgbColor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using std::cout;
using std::fstream;
using std::ifstream;
using std::string;

namespace fs = std::filesystem;

// Global file-related variables
char bgColorFilename[] = "defaultBgColor.bin";
char fgColorFilename[] = "defaultFgColor.bin";

// Function to Change the Current Path to the Directory where the .exe is Saved
fs::path changeCwdToBin(string invokeCommand)
{
  fs::path binPath = invokeCommand.substr(0, invokeCommand.length() - 9); // Path where the binaries of the program are being stored
  fs::current_path(binPath);
  return binPath;
}

// Function Used to Save the Default Text Highlight Color as a .bin
void writeDefaultColor(char *filename, string fileContent)
{
  int removeResult;

  ifstream readFile(filename); // Check if the file exists. If so, delete the file
  if (readFile.is_open())
  {
    readFile.close();

    fs::path filePath = fs::current_path();
    filePath.append(filename);

    removeResult = fs::remove(filename);
    /*
    --- remove possible return values

    0: if the file was successfully deleted
    1: if the content of the file was deleted
    -1: if neither the file was deleted nor the its content removed
    */
  }
  else
  {
    readFile.close();
    removeResult = 0; // File doesn't exist
  }

  // Write SGR Command with the Default Color ANSI Escape Code
  fstream writeFile(filename, fstream::out | fstream::binary);
  if (!writeFile.is_open() || (removeResult != 0 && removeResult != 1))
  {
    cout << "\nError: Cannot Write to " << filename;
  }
  else
  {
    for (int i = 0; i < fileContent.length(); i++)
    {
      writeFile.write(&fileContent[i], sizeof(char));
    }
  }
  writeFile.close();
}

// Function to Read the Default Background and Foreground Text Color Format SGR Commands
string readDefaultColor(bool readBgColor)
{
  char c;
  string sgrCommand;

  ifstream colorFormatFile;
  if (readBgColor)
  {
    colorFormatFile.open(bgColorFilename); // Opens the Background Default Color File
  }
  else
  {
    colorFormatFile.open(fgColorFilename); // Opens the Foreground Default Color File
  }

  // Chekc if the file was found
  if (colorFormatFile)
  {
    while (true)
    {
      colorFormatFile >> c;
      if (colorFormatFile.good())
      {
        sgrCommand += c;
      }
      else
      {
        break;
      }
    }
  }
  else
  {
    // SGR Commands if there's any error when trying to open the files
    string sgrCommand = ANSI_START;
    if (readBgColor)
    {
      sgrCommand.append(ANSI_RGB_BG_COLOR);
      sgrCommand.append(BG_RGB_ERROR);
    }
    else
    {
      sgrCommand.append(ANSI_RGB_FG_COLOR);
      sgrCommand.append(FG_RGB_ERROR);
    }
  }
  colorFormatFile.close();

  return sgrCommand;
}
