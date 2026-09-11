#include <iostream>

#include "wc.hpp"

/**
 * @brief Program entry point.
 *
 * Parses options, builds the file list, and prints
 * the counts for each file.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 *
 * @return 0 on success, 1 on error.
 */
int main(int argc, char** argv) {
    Options flags;
    if (parse_args(&flags, argc, argv) != 0) {
        return 1;
    }
    if (flags.v) {
        std::cout << "wc 0.1.0\n";
        return 0;
    }
    if (flags.h) {
        std::cout << "Usage: wc [-l -w -c -m -L] [FILE]...\n";
        return 0;
    }

    std::vector<std::string> files = flags.files;
    if (flags.file_from) {
        files = read_file_names(flags.file_name);
    }
    if (files.empty()) {
        std::cerr << "wc: no files given\n";
        return 1;
    }

    for (const std::string& name : files) {
        Info counts;
        if (process_file(name, &counts) != 0) {
            std::cerr << "wc: " << name << ": no such file\n";
            continue;
        }
        print_data(&flags, &counts, name);
    }
    return 0;
}
