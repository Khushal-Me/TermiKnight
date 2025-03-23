#include "Utilities.h"
#include <cstdlib>
#include <iostream> 
#include <limits>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/ioctl.h> 
    #include <stdio.h>     
#endif

/**
 * @brief Generates a random integer within a given range.
 * 
 * @param minVal The minimum value of the range (inclusive).
 * @param maxVal The maximum value of the range (inclusive).
 * @return A random integer between minVal and maxVal.
 */
int Utilities::getRandomInt(int minVal, int maxVal) {
    return (std::rand() % (maxVal - minVal + 1)) + minVal;
}

/**
 * @brief Clears the terminal screen.
 *
 * On Windows, this uses the `cls` system command.  
 * On UNIX-like systems (Linux, macOS), it uses ANSI escape codes to clear the screen.
 */
void Utilities::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code for UNIX
#endif
}

/**
 * @brief Retrieves the width of the terminal in columns.
 *
 * This is used to help with layout calculations, such as centering or aligning text.
 *
 * @return The width of the terminal in number of columns.
 */
int Utilities::getTerminalWidth() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns = 80; // fallback
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return columns;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}

/**
 * @brief Prompts the user to press Enter to continue.
 *
 * This is used to pause the game so the player can read output
 * before the next screen is shown.
 */
void Utilities::waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
