#ifndef WC_HPP
#define WC_HPP

#include <cstddef>
#include <string>
#include <vector>

struct Options {
    bool l = false;
    bool w = false;
    bool c = false;
    bool m = false;
    bool L = false;
    bool v = false;
    bool h = false;
    bool file_from = false;

    std::string file_name;
    std::vector<std::string> files;
};

struct Info {
    std::size_t lines = 0;
    std::size_t words = 0;
    std::size_t chars = 0;
    std::size_t bytes = 0;
    std::size_t max_line = 0;
};

std::size_t count_words(const std::string& line);

int check_short_options(Options* flags, const char* flag);
int check_long_options(Options* flags, const char* flag);
int parse_args(Options* flags, int argc, char** argsv);

void print_data(const Options* flags, const Info* counts,
                const std::string& label);

int process_file(const std::string& file_name, Info* counts);

std::vector<std::string> read_file_names(const std::string& file_name);

#endif
