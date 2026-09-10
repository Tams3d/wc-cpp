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
 *   -L
 *
 * @param flags Pointer to the Options structure to update.
 * @param flag Command-line argument to validate.
 *
 * @return 0 if the option is valid.
 * @return -1 if the option is invalid.
 */
int check_short_options(Options* flags, const char* flag) {
    if (strcmp(flag, "-l") == 0) {
        flags->l = true;
    } else if (strcmp(flag, "-w") == 0) {
        flags->w = true;
    } else if (strcmp(flag, "-c") == 0) {
        flags->c = true;
    } else if (strcmp(flag, "-L") == 0) {
        flags->max_line_length = true;
    } else {
        return -1;
    }

    return 0;
}

/**
 * @brief Checks whether an argument is a supported long option.
 *
 * Supported long options:
 *   --version
 *   --files0-from=<file>
 *
 * When --files0-from=<file> is provided, the filename is stored in
 * Options::file_name.
 *
 * @param flags Pointer to the Options structure to update.
 * @param flag Command-line argument to validate.
 *
 * @return 0 if the option is valid.
 * @return -1 if the option is invalid or the filename is missing.
 */
int check_long_options(Options* flags, const char* flag) {
    const char* files0_from_flag = "--files0-from=";
    const std::size_t PREFIX_LENGTH = strlen(files0_from_flag);

    if (strcmp(flag, "--version") == 0) {
        flags->v = true;
        return 0;
    }

    if (strncmp(flag, files0_from_flag, PREFIX_LENGTH) == 0) {
        const char* start = flag + PREFIX_LENGTH;

        if (*start == '\0') {
            std::cout << "Cannot open " << flag << '\n';
            return -1;
        }

        flags->file_name = start;
        return 0;
    }

    return -1;
}

/**
 * @brief Parses command-line arguments and updates the program options.
 *
 * Long options begin with "--" and short options begin with "-".
 * Non-option arguments are not currently supported.
 *
 * Supported long options:
 *   --version
 *   --files0-from=<file>
 *
 * Supported short options:
 *   -l
 *   -w
 *   -c
 *   -L
 *
 * @param flags Pointer to the Options structure to update.
 * @param argsv Null-terminated array of command-line arguments.
 *
 * @return 0 if all arguments are valid.
 * @return -1 if an invalid argument or option is encountered.
 */
int parse_args(Options* flags, char** argsv) {
    int i = 1;

    while (argsv[i] != nullptr) {
        const char* arg = argsv[i];

        if (arg[0] == '-' && arg[1] == '-') {
            if (check_long_options(flags, arg) != 0) {
                std::cout << "Invalid option: " << arg << '\n';
                return -1;
            }
        } else if (arg[0] == '-') {
            if (check_short_options(flags, arg) != 0) {
                std::cout << "Invalid option: " << arg << '\n';
                return -1;
            }
        } else {
            std::cout << "Invalid argument: " << arg << '\n';
            return -1;
        }

        ++i;
    }

    return 0;
}