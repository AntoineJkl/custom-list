#include "custom_ls.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    // Start the recursion from the provided directory or the current directory
    print_directory(argc > 1 ? argv[1] : ".", 0);   // Depth starts at 0
    return 0;
}