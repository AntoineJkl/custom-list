#include "custom_ls.h"

void print_directory(const char* dir_path, int depth)
{
    DIR* d;               // Directory stream
    struct dirent* dir;   // Directory entry structure
    struct stat filestat;
    char* path;

    // Open the directory specified by the user
    d = opendir(dir_path);

    if(d)
    {
        while((dir = readdir(d)) != NULL)
        {
            // Skip the special entries "." and ".."
            if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
                continue;

            // Construct the full path
            if(asprintf(&path, "%s/%s", dir_path, dir->d_name) == -1)
            {
                perror("asprintf failed");
                continue;
            }

            // Get file status
            if(stat(path, &filestat) == -1)
            {
                perror("stat failed");
                free(path);
                continue;
            }

            // Print tabs for depth level
            for(int i = 0; i < depth; ++i)
            {
                printf("\t");
            }

#ifdef CustomLS_USE_ARROW
            printf("-> ");
#endif

            // Check file type and print the name
            if(S_ISDIR(filestat.st_mode))
            {
                // Directory
#ifdef CustomLS_USE_COLOR_BLUE
                printf("\033[1;34m%s\033[0m\n", dir->d_name);   // Blue
#else
                printf("%s\n", dir->d_name);
#endif
                print_directory(path,
                                depth + 1);   // Recursively call the function for the
                                              // subdirectory, increasing depth
            }
            else
            {
                // File
                if(filestat.st_mode & S_IXUSR)
                {
                    // Executable file
#ifdef CustomLS_USE_COLOR_GREEN
                    printf("\033[1;32m%s\033[0m\n", dir->d_name);   // Green
#else
                    printf("%s\n", dir->d_name);
#endif
                }
                else
                {
#ifdef CustomLS_USE_COLOR_YELLOW
                    printf("\033[1;33m%s\033[0m\n", dir->d_name);   // Yellow
#else
                    printf("%s\n", dir->d_name);
#endif
                }
            }

            free(path);
        }

        closedir(d);
    }
    else
    {
        perror("Cannot open directory");
    }
}