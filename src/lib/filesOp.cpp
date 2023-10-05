#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using std::cout;
using std::fstream;
using std::ifstream;
using std::string;

namespace fs = std::filesystem;

// Function Used to Save the Default Text Highlight Color as a .bin
void writeToFile(char *filename, string fileContent, string invokeCommand)
{
  int removeResult;
  fs::path binPath; // Path where the binaries of the program are being stored

  // Check where is the file by analyzing the invokeCommand
  binPath = invokeCommand.substr(0, invokeCommand.length() - 9);
  fs::current_path(binPath);

  // Check if the file exists. If so, delete the file
  ifstream readFile(filename);
  if (readFile.is_open())
  {
    readFile.close();

    fs::path filePath = binPath;
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
    // File doesn't exist
    readFile.close();
    removeResult = 0;
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
      writeFile.write((char *)&fileContent[i], sizeof(char));
    }
  }
  writeFile.close();
}
