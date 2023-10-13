#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

// ------- DO NOT EDIT ANY CODE IN THIS FILE -------

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc == 1) {    //if there are no args, set the file to standard input
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");    //open the file and attempt to read it
        if (fp == NULL) {
            error(1, errno, "cannot access '%s'", argv[1]);
        }
    }

    char *line;
    int n = 1;
    //either fp to be read by read_line will be a "real" file or stdin... which is cool i guess
    while ((line = read_line(fp)) != NULL) {    //while read_line tells us there are lines to read
        if (*line != '\0') {    //as long as we're reading actual characters from the line
            printf("%6d  %s", n++, line);    //print the line number and the line itself, then increment the line number
        }
        printf("\n");
        free(line);    //free the memory we used bc we don't need it anymore
    }
    fclose(fp);    //i guess you gotta do that for some reason
    return 0;
}
