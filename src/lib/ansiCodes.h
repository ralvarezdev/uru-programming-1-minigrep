#ifndef ANSI_CODES_H
#define ANSI_CODES_H

// 'x1b' is called ESC at the ASCII table, to customize the text color, we always start with a ESC
#define ANSI_START "\x1b"
// Control Sequence Introducer (CSI)
#define CSI "\x1b["
// ANSI Code to reset the Text Format
#define ANSI_RESET "\x1b[0m"

#endif