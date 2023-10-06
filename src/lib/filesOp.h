#include <string>

using std::string;

// GLobal Variables for the Filename of the Default Background and Foreground Color
extern char bgColorFilename[], fgColorFilename[];

#ifndef FILES_OP_H
#define FILES_OP_H

void changeCwdToBin(string invokeCommand);
void writeToFile(char *filename, string fileContent);
string readFile(bool readBgColor);

#endif