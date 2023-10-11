#include <string>

using std::string;

#ifndef RGB_COLOR_H
#define RGB_COLOR_H

// Background and Foreground Colors in case of an error trying to Load the User's defined colors
#define BG_RGB_ERROR ";32;32;32m"
#define FG_RGB_ERROR ";153;204;255m"

void printColorSuggestions(); // Example Colors
void getRGBTextColor(bool changeBgColor);

#endif