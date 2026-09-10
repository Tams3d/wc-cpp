#ifndef WC_HPP
#define WC_HPP

#include <string>

struct Options {
    bool l = false;
    bool w = false;
    bool c = false;
    bool max_line_length = false;
    bool file_from = false;
    bool v = false;
    bool h = false;

    std::string file_name;
};

struct Info {
    size_t lines = 0;
    size_t words = 0;
    size_t chars = 0;
    size_t max_line_length = 0;
    size_t bytes;
};

int check_short_options(Options* flags, const char* flag);
int check_long_options(Options* flags, const char* flag);
int parse_args(Options* flags, char** argsv);

int handle_file_from(Options* flags, Info* counts);
std::size_t count_words(const std::string& line);

#endif