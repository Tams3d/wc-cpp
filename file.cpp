#include <filesystem>
#include <fstream>
#include <sstream>

#include "wc.hpp"

/**
 * @brief Counts the number of whitespace-separated words in a line.
 *
 * @param line The line whose words are counted.
 *
 * @return Number of words found in the line.
 */
std::size_t count_words(const std::string& line) {
    std::stringstream stream(line);
    std::string word;
    std::size_t word_count = 0;

    while (stream >> word) {
        ++word_count;
    }

    return word_count;
}

/**
 * @brief Opens and processes the input file.
 *
 * Reads the file line by line and updates the Info struct
 * with the line, word, and byte counts.
 *
 * @param flags Pointer to the Options struct containing the filename.
 * @param counts Pointer to the Info struct to update.
 *
 * @return 0 if the file was processed successfully.
 * @return -1 if the file could not be opened.
 */
int handle_file_from(Options* flags, Info* counts) {
    std::ifstream input_file(flags->file_name);

    if (!input_file.is_open()) {
        return -1;
    }

    std::string line;

    while (std::getline(input_file, line)) {
        ++counts->lines;
        counts->words += count_words(line);
    }

    counts->bytes = std::filesystem::file_size(flags->file_name);

    return 0;
}