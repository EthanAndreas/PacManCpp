#ifdef DEBUG
/**
 * @brief Macro which allows to print debug messages in green in the terminal
 * @param x command executed if compiled with the debug option
 */
#define DEB(x) x;
#else
/**
 * @brief Macro which allows to print debug messages in green in the terminal
 * @param x command executed if compiled without the debug option
 */
#define DEB(x) while (0)
#endif