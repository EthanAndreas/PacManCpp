#ifdef DEBUG
/**
 * @brief Macro which allows to print debug messages in green in the terminal
 * @param x command executed if compiled with the debug option
 */
#define DEB(x)          \
    cout << "\e[0;32m"; \
    x;                  \
    cout << "\e[0m";
#else
/**
 * @brief Macro which allows to print debug messages in green in the terminal
 * @param x command executed if compiled without the debug option
 */
#define DEB(x) while (0)
#endif