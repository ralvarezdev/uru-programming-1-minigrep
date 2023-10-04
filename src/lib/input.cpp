#include <iostream>

using std::cin;
using std::cout;
using std::string;

bool booleanQuestion(string message)
{
  string input;
  char c;

  while (true)
  {
    cout << message << " [y/N] ";
    cin >> input;

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