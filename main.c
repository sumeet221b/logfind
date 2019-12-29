#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "./dbg.h"

#define LOGLIST "/home/sumeet/.config/logfind/loglist"

void Die(const char *message);
int IsContain(const char *str, const char *contain);

int main(int argc, char *argv[]) {

    FILE *log_list_file;
    FILE *log_file;
    char **log_list = NULL;
    char *str;
    char *pos;


    int i = 0, strcount = 0;

    //  Open log list
    log_list_file = fopen(LOGLIST, "r");
    if(log_list_file == NULL) {
        Die("Can't open lof_list_file\n");
    }

    str = (char *)malloc(2048);

    // Read lof file names from log list file
    while (fgets(str, 2048, log_list_file) != NULL) {

        // Remove trailing '\n'
        if ((pos=strchr(str, '\n')) != NULL)
            *pos = '\0';

        log_list = (char **)realloc(log_list, (strcount + 1) * sizeof(char *));
        log_list[strcount] = strdup(str);
        strcount++;
    }

    for(i = 0; i < strcount; i++) {

        // Open log file
        log_file = fopen(log_list[i], "r");
        if(log_file == NULL) {
            Die("Can't open log_file\n");
        }
        
        // Read contents of log_file
        while(fgets(str, 1024, log_file)) {
            if ((pos=strchr(str, '\n')) != NULL)
                *pos = '\0';
            printf("%s\n", str);
        }
    }



    // Close log_list_file
    fclose(log_list_file);

    return 0;

}

void Die(const char *message) {

    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

int IsContain(const char *str, const char *contain) {
    int i, j;

    for (i = 0; i < strlen(str); i++) {
        // If first word of the word we want to find in string matched a char in string
        if (contain[0] == str[i]) {
            for (j = 1; j < strlen(contain); j++) {
                if (contain[j] == str[i + j]) {
                    continue;
                } else {
                    break;
                }
            }
            if (contain[j] == '\0') {
                return 1;
            }
        }
    }
    return 0;
}