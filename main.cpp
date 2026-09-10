#include <iostream>

#include "wc.hpp"
int main(int argc, char** argv) {
    bool is_parsing_valid = false;
    if (argc > 1) {
        Options flags;
        is_parsing_valid = parse_args(&flags, argv);
        if (is_parsing_valid != 0) {
            return 1;
        }

        if (flags.v) {
            std::cout << "Version 0.1.0\n";
            return 0;
        }
        if (flags.h) {
            std::cout << "I'm here to help you!\n";
            return 0;
        }
    }
    return 0;
}