#include <fcntl.h>
#include <sys/stat.h>  // for sys stat()
#include <unistd.h>

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
int parse_args(Options* flags, char** argsv);