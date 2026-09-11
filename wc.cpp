#include "wc.hpp"

#include <sstream>
#include <string>

/**
 * @brief Counts the number of whitespace-separated words in a line.
 *
 * @param line The line whose words are counted.
 *
 * @return Number of words found in the line.
 */
std::size_t count_words(const std::string& line) {
    std::stringstream words(line);
    std::string word;
    std::size_t count = 0;

    while (words >> word) {
        count++;
    }

    return count;
}
