#include <algorithm>
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
        Info counts;
        if (process_stream(std::cin, &counts) != 0) {
            std::cerr << "wc: stdin read error\n";
            return 1;
        }
        print_data(&flags, &counts, "");
        return 0;
    }
    int exit_code = 0;
    Info total;
    bool stdin_done = false;
    for (const std::string& name : files) {
        Info counts;
        if (name == "-") {
            if (stdin_done) {
                counts = Info{};
            } else if (process_stream(std::cin, &counts) != 0) {
                std::cerr << "wc: stdin read error\n";
                exit_code = 1;
                continue;
            } else {
                stdin_done = true;
            }
            print_data(&flags, &counts, "-");
        } else if (process_file(name, &counts) != 0) {
            std::cerr << "wc: " << name << ": no such file\n";
            exit_code = 1;
            continue;
        } else {
            print_data(&flags, &counts, name);
        }
        total.lines += counts.lines;
        total.words += counts.words;
        total.chars += counts.chars;
        total.bytes += counts.bytes;
        total.max_line = std::max(total.max_line, counts.max_line);
    }
    if (files.size() > 1) {
        print_data(&flags, &total, "total");
    }
    return exit_code;
}
