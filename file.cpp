#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "wc.hpp"

/**
 * @brief Read names from list file.
 * @param file_name List path.
 * @return Names found.
 */
std::vector<std::string> read_file_names(const std::string& file_name) {
    std::vector<std::string> names;
    std::ifstream in(file_name, std::ios::binary);
    if (!in.is_open()) {
        return names;  // cannot open, empty
    }

    std::string cur;
    char ch;
    while (in.get(ch)) {
        if (ch == '\0') {
            names.push_back(cur);
            cur.clear();
        } else {
            cur += ch;
        }
    }
    if (!cur.empty()) {
        names.push_back(cur);
    }
    return names;
}

/**
 * @brief Count one file.
 * @param file_name File path.
 * @param counts Result.
   @return 0 on success, 1 on error.
*/
int process_file(const std::string& file_name, Info* counts) {
    std::ifstream in(file_name, std::ios::binary);
    if (!in.is_open()) {
        return 1;
    }

    *counts = Info{};
    bool in_word = false;
    std::size_t len = 0;
    char ch;

    while (in.get(ch)) {
        counts->bytes++;

        if (ch == '\n') {
            counts->lines++;
            counts->max_line = std::max(len, counts->max_line);
            len = 0;
            in_word = false;
        } else {
            len++;
            if (ch == ' ' || ch == '\t') {
                in_word = false;
            } else if (!in_word) {
                counts->words++;
                in_word = true;
            }
        }
    }

    counts->chars = counts->bytes;
    counts->max_line = std::max(len, counts->max_line);
    return 0;
}
