#include <iostream>

using std::cin;
using std::cout;
using std::getline;
using std::string;

// Help Message
void helpMessage()
{
  string colorCommands[3] = {
      "Background and Foreground [-c]", "Background [-b]", "Foreground [-f]"};

  cout << "Avalaible Commands:";
  cout << "\n\n*** Help [-h]";
  cout << "\n\n*** Change Default Text Color";
  for (int i = 0; i < size(colorCommands); i++)
  {
    cout << "\n--- " << colorCommands[i];
  }
  cout << "\n\n*** Run\n--- To Find the Phrase : [filePath... phrase...]";
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