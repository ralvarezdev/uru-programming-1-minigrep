#include <string>

using std::string;

#ifndef RGB_COLOR_H
#define RGB_COLOR_H

// Background and Foreground Colors in case of an error trying to Load the User's defined colors
#define BG_RGB_ERROR ";32;32;32m"
#define FG_RGB_ERROR ";0;255;128m"

void printColorSuggestions();
void getRGBTextColor(bool changeBgColor);

#endif