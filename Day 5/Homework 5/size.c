/*
 * size.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 *
 * The program accepts 1 argument - the name of a file. If no arguments are provided, it
 * prompts the user to enter the file name and then prints the size of the file in bytes.
 */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    
    // Buffer to hold the filename
    char filename[1000];
    if (argc <= 1) {
        printf("Enter the name of a file: ");
        scanf("%s", filename);
    } else {
        strcpy(filename, argv[1]); 
    }

    // Get the file size using stat
    struct stat fileStat;
    if (stat(filename, &fileStat) < 0) {
        fprintf(stderr, "Could not get file size for %s\n", filename);
        return 1;
    }

    // Print the file size in bytes
    printf("%s has %lld bytes\n", filename, (long long)fileStat.st_size); 
    return 0;
}