#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include "sfs.h"

int is_block_device(const char *path) {
    struct stat sb;
    if (stat(path, &sb) == -1) {
        perror("stat");
        return 0;
    }
    return S_ISBLK(sb.st_mode); // check if its a block device
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s: Device path not properly provided, see usage\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char real_path[PATH_MAX];
    if (realpath(argv[1], real_path) == NULL) {
        perror("realpath");
        exit(EXIT_FAILURE);
    }

    if (!is_block_device(real_path)) {
        fprintf(stderr, "Error: %s is not a block device.\n", real_path);
        exit(EXIT_FAILURE);
    }

    if (access(real_path, W_OK) != 0) {
        perror("Error: Cannot write to the device");
        exit(EXIT_FAILURE);
    }

    printf("You are about to permanently alter device %s, proceed? [y/n]\n", real_path);
    if (getchar() != 'y'){ 
        fprintf(stderr, "Filesystem making cancelled.\n");
        return 0;
    }

    printf("filetime");

    struct metaBlock *root = (struct metaBlock*)calloc(1, BLOCK_SIZE);
    memset(root, '\0',BLOCK_SIZE);
    *root = (struct metaBlock){
        "root",
        "d",
        "rwx------",
        NULL,
        NULL
    };


    int device= open(real_path, O_RDWR | O_CREAT, 0644);
    write(device, root, BLOCK_SIZE);
    fsync(device);
    close(device);




    return 0;
}
