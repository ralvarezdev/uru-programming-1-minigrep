#include <iostream>
#include <iomanip>
#include <filesystem>
#include "filesOp.h"
#include "ansiCodes.h"

using std::cin;
using std::cout;
using std::getline;
using std::left;
using std::setfill;
using std::setw;
using std::string;

namespace fs = std::filesystem;

// Print Section Title
void printTitle(string sgrCommand, string message)
{
  int nTitle = 50; // Output String Size of the Section Titles

  cout << CSI << sgrCommand << setw(nTitle) << setfill(' ') << left << message << ANSI_RESET << '\n';
}

// Help Message
void helpMessage()
{
  string sgrCommand = readCompleteDefaultColor();
  string colorCommands[3] = {
      "[-c] Change Background and Foreground Color", "[-b] Change Background Color", "[-f] Change Foreground Color"};

  printTitle(sgrCommand, "MINIGREP");
  cout << "Run:\n"
       << "-- [phraseToHighlight... filePath...] To Highlight the Phrase"
       << "\nCommands:\n"
       << "-- [-h] Help\n";

  for (int i = 0; i < size(colorCommands); i++)
  {
    cout << "-- " << colorCommands[i] << '\n';
  }

  printTitle(sgrCommand, "CURRENT PATH");
  cout << fs::current_path() << '\n';
}

// Boolean Question
bool booleanQuestion(string message)
{
  string input;
  char c;

  while (true)
  {
    cout << message << " [y/N] ";
    getline(cin, input);

    c = tolower(input[0]);
    if (c == 'y')
    {
      return true;
    }
    else if (c == 'n')
    {
      return false;
    }
    else
    {
      cout << "\t- Wrong Input: It's a Yes/No Question. You must type 'y', 'Y' or 'n', 'N'"
           << "\n";
    }
  }
}