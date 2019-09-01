#include "../include/mathematicalOperations.hpp"

/**
 * @brief Compute a mathematical operation using modulo
 * @param int
 * @param int
 * @return int
 */
int mathematicalOperations::safeModulo(int a, int b)
{
    return (b + (a%b)) % b;
}