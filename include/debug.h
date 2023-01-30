#ifdef DEBUG
/**
 * @brief Macro qui permet d'afficher des messages de debug en vert dans le
 * terminal
 * @param x commande executée si compilée avec l'option de debug
 */
#define DEB(x)          \
    cout << "\e[0;32m"; \
    x;                  \
    cout << "\e[0m";
#else
/**
 * @brief Macro qui permet d'afficher des messages de debug en vert dans le
 * terminal
 * @param x commande executée si compilée avec l'option de debug
 */
#define DEB(x) while (0)
#endif