/* path_handling.h */
#ifndef PATH_HANDLING_H
#define PATH_HANDLING_H

#include <stddef.h>

int find_command_in_path(char *command, char *path, char *full_path, size_t buf_size); 

#endif

