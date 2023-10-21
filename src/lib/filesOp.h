#include <string>
#include <filesystem>

using std::string;

namespace fs = std::filesystem;

// Global Variables for the Filename of the Default Background and Foreground Color
extern char bgColorFilename[], fgColorFilename[];

#ifndef FILES_OP_H
#define FILES_OP_H

fs::path changeCwdToBin(string invokeCommand);
void writeDefaultColor(char *filename, string fileContent);
string readDefaultColor(bool readBgColor);
string readCompleteDefaultColor();

#endif