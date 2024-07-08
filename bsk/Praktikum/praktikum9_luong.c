/* Nhat-Lam Luong inf3381; 23-November-2020 */

#include <stdio.h> //scanf, fprinf, stderr, perror
#include <string.h> //strerror, strcat
#include <errno.h> //errno
#include <stdlib.h> //EXIT_FAILURE
#include <fcntl.h> //open
#include <unistd.h> //link 
#include <error.h> //error
#include <sys/stat.h> //stat

int main (int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("Nhat-Lam Luong; inf3381: BSK Praktikum %i\n", 9);
    
    char * file = argv[1];
    char * underline = "_";
    char * newfile = malloc(strlen(file)+strlen(underline)+1);
    strcat(newfile, underline);
    strcat(newfile, file);
    printf("...creating link from %s to %s...\n", file, newfile);
    if (link(file, newfile) == -1){
        error(errno, errno, "Error link()");
        return EXIT_FAILURE;
    }
    
    struct stat file_info;
    printf("...retrieve file information and write into struct_object...\n");
    if (stat(file, &file_info) == -1){ 
        perror("Error fstat()"); 
        return EXIT_FAILURE; 
    }

    printf("\n\nFile information for: %s\n", file);
	printf("\t\tino_t inode_number: %ld\n", file_info.st_ino);
    printf("\t\toff_t file_size: %lu\n", file_info.st_size);
    printf("\t\tnlink_t hardlink_n: %lu\n", file_info.st_nlink);
    printf("\t\tuid_t user_id: %d\n", file_info.st_uid);
    printf("\t\tgid_t group_id: %d\n", file_info.st_gid); 

	return 0;
}