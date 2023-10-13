#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>


//this function reads a file and prints the last n lines of that file
//if n is larger than the # of lines in the file, the whole file is printed
void print_last_n(FILE *fp, int n) {
    char *queue[n];    //this is the circular queue of n strings (this is a char ** too i guess)
    bool parbool[n];    //parallel boolean array to show that memory has or has not been allocated at a given index in queue[]
    int count = 0;    //this will be used for some modular arithmetic to grab values from queue

    //initialize parbool to false;
    for (int i = 0; i < n; i++) {
        parbool[i] = 0;
    }

    char *line = read_line(fp);    //read from the file and store the return value for later
    //Read lines from the file until we hit EOF
    while (line) {
        //if there is a reference to heap memory in queue, free that memory so we can overwrite
        if (parbool[count % n]) {
            free(queue[count % n]);
        }
        
        //write line into queue
        queue[count % n] = line;
        //mark parbool to show there has been memory written to this part of queue
        parbool[count % n] = true;
        //read another line
        line = read_line(fp);
        count++;
    }
    
    //allows us to read only from the written parts of our circular queue (in case n > # of files)
    int range;
    range = (count < n) ? count : n;
    //loop through (the written part of) queue and print out the relevant lines
    for (int i = 0; i < range; i++) {
        printf("%s\n", queue[count % range]);
        free(queue[count % range]);
        count++;
    }
}

// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------

int convert_arg(const char *str, int max) {
    char *end;
    long n = strtol(str, &end, 10);
    if (*end != '\0') {
        error(1, 0, "Invalid number '%s'", str);
    }
    if (n < 1 || n > max) {
        error(1, 0, "%s is not within the acceptable range [%d, %d]", str, 1, max);
    }
    return n;
}

int main(int argc, char *argv[]) {
    int num = 10;

    if (argc > 1 && argv[1][0] == '-') {
        num = convert_arg(argv[1] + 1, 100000);
        argv++;
        argc--;
    }

    FILE *fp;
    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            error(1, errno, "cannot access '%s'", argv[1]);
        }
    }
    print_last_n(fp, num);
    fclose(fp);
    return 0;
}
