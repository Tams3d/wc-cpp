#include <iostream>

#include "wc.hpp"

/**
 * @brief Prints the counts for one file.
 *
 * Prints default (lines, words, bytes) when no flag is set,
 * otherwise prints only the selected columns.
 *
 * @param flags Pointer to the Options structure with selected columns.
 * @param counts Pointer to the Info structure to print.
 * @param label Filename printed after the numbers.
 */
void print_data(const Options* flags,
                const Info* counts,
                const std::string& label) {
    bool none = !flags->l && !flags->w && !flags->c && !flags->m && !flags->L;

    if (none) {
        std::cout << counts->lines << ' ' << counts->words << ' '
                  << counts->bytes << ' ' << label << '\n';
        return;
    }

    bool first = true;
    if (flags->l) {
        std::cout << counts->lines;
        first = false;
    }
    if (flags->w) {
        if (!first) {
            std::cout << ' ';
        }
        std::cout << counts->words;
        first = false;
    }
    if (flags->m) {
        if (!first) {
            std::cout << ' ';
        }
        std::cout << counts->chars;
        first = false;
    }
    if (flags->c) {
        if (!first) {
            std::cout << ' ';
        }
        std::cout << counts->bytes;
        first = false;
    }
    if (flags->L) {
        if (!first) {
            std::cout << ' ';
        }
        std::cout << counts->max_line;
    }
    std::cout << ' ' << label << '\n';
}
