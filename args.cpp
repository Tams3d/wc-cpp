#include <cstring>
#include <iostream>

#include "wc.hpp"

/**
 * @brief Checks whether an argument is a supported short option.
 *
 * Supported short options:
 *   -l
 *   -w
 *   -c
 *   -m
 *   -L
 *   -v
 *   -h
 *
 * @param flags Pointer to the Options structure to update.
 * @param flag Short option to parse.
 *
 * @return 0 if the option is recognized.
 * @return -1 if the option is not supported.
 */
int check_short_options(Options* flags, const char* flag) {
    if (strcmp(flag, "-l") == 0) {
        flags->l = true;
    } else if (strcmp(flag, "-w") == 0) {
        flags->w = true;
    } else if (strcmp(flag, "-c") == 0) {
        flags->c = true;
    } else if (strcmp(flag, "-m") == 0) {
        flags->m = true;
    } else if (strcmp(flag, "-L") == 0) {
        flags->L = true;
    } else if (strcmp(flag, "-v") == 0) {
        flags->v = true;
    } else if (strcmp(flag, "-h") == 0) {
        flags->h = true;
    } else {
        return -1;
    }
    return 0;
}

/**
 * @brief Checks whether an argument is a supported long option.
 *
 * Supported long options:
 *   --lines
 *   --words
 *   --bytes
 *   --chars
 *   --max-line-length
 *   --help
 *   --version
 *   --files0-from=<file>
 *
 * When --files0-from=<file> is provided, the filename is stored in
 * Options::file_name.
 *
 * @param flags Pointer to the Options structure to update.
 * @param flag Long option to parse.
 *
 * @return 0 if the option is recognized.
 * @return -1 if the option is invalid or the filename is missing.
 */
int check_long_options(Options* flags, const char* flag) {
    if (strcmp(flag, "--lines") == 0) {
        flags->l = true;
        return 0;
    }
    if (strcmp(flag, "--words") == 0) {
        flags->w = true;
        return 0;
    }
    if (strcmp(flag, "--bytes") == 0) {
        flags->c = true;
        return 0;
    }
    if (strcmp(flag, "--chars") == 0) {
        flags->m = true;
        return 0;
    }
    if (strcmp(flag, "--max-line-length") == 0) {
        flags->L = true;
        return 0;
    }
    if (strcmp(flag, "--help") == 0) {
        flags->h = true;
        return 0;
    }
    if (strcmp(flag, "--version") == 0) {
        flags->v = true;
        return 0;
    }

    const char* prefix = "--files0-from=";
    if (strncmp(flag, prefix, strlen(prefix)) == 0) {
        const char* value = flag + strlen(prefix);
        if (*value == '\0') {
            std::cerr << "wc: --files0-from needs a value\n";
            return -1;
        }
        flags->file_name = value;
        flags->file_from = true;
        return 0;
    }

    return -1;
}

/**
 * @brief Parses command-line arguments and updates the program options.
 *
 * Long options begin with "--" and short options begin with "-".
 * Non-option arguments are treated as file operands.
 *
 * Supported long options:
 *   --lines
 *   --words
 *   --bytes
 *   --chars
 *   --max-line-length
 *   --help
 *   --version
 *   --files0-from=<file>
 *
 * Supported short options:
 *   -l
 *   -w
 *   -c
 *   -m
 *   -L
 *   -v
 *   -h
 *
 * @param flags Pointer to the Options structure to update.
 * @param argc Argument count.
 * @param argsv Argument vector.
 *
 * @return 0 if all arguments are valid.
 * @return -1 if an invalid option is encountered.
 */
int parse_args(Options* flags, int argc, char** argsv) {
    for (int i = 1; i < argc; ++i) {
        const char* arg = argsv[i];
        if (arg[0] == '-' && arg[1] == '-') {
            if (check_long_options(flags, arg) != 0) {
                std::cerr << "wc: invalid option: " << arg << '\n';
                return -1;
            }
        } else if (arg[0] == '-') {
            if (check_short_options(flags, arg) != 0) {
                std::cerr << "wc: invalid option: " << arg << '\n';
                return -1;
            }
        } else {
            flags->files.emplace_back(arg);
        }
    }
    return 0;
}
