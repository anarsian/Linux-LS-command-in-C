/*
 * Filename: myls.c
 * Author: Anish Narsian
 * Description: call buildInfo and displayInfo files.
 * Date: 12/2/2013
 * Sources of Help: Discussiom
 */

#include "myls.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>

#include <time.h>
#include <sys/time.h>

#include <string.h>
#include <ctype.h>
#include <sys/types.h>

/*
 * Function name:main (int argc, char *argv[])
 * Function prototype:int main (int argc, char *argv[]);
 * Description: call buildInfo and displayInfo files.
 * Parameters: argc: numof args
 *             argv: args take from cmd lime
 * Side Effects: None
 * Error Conditions: Lots of error checking done to ensure that what is got
 *                   is correct output
 * Return Value: none
 */

//required vars
struct stat stbuf;


int mtime_offSet = offsetof(struct fileInfo, stbuf.st_mtime);
int main(int argc, char *argv[]) {
    
    const char *filename; //capture filename

    //table1 for all the fileInfo 
    struct fileInfo ** const table1 =
            (struct fileInfo ** const ) malloc(
                    sizeof(struct fileInfo));
    int choice;


    
    int entry; //num of entries
    int bits = 0x0;// the biitstring


    //checking all args and updating bits
    while ((choice = getopt(argc, argv, "alrt")) != EOF) {
        switch (choice) {
        case 'a':
            bits |= AFLAG;
            break;
        case 'l':
            bits |= LFLAG;
            break;
        case 'r':
            bits |= RFLAG;
            break;
        case 't':
            bits |= TFLAG;
            break;
        case '?':
            (void) fprintf(stderr, "Usage: %s [-alrt] [file ...]\n",
                    argv[0]);
            exit(1);

        }
    }

    //call buildFileInfo and displayfileinfo
    if (argv[optind] != NULL ) {
        for (; optind < argc; optind++) {
            filename = argv[optind];
            //calculating entry for condition.
            entry = buildFileInfoTable(filename, table1);



            (void) displayFileInfo(*table1, entry,
                    (const int) bits);
            //free memory
            (void) free(*table1);
        }
    } else {
        //calculate numofentries.
        entry = buildFileInfoTable(".", table1);

        //calling displayFileinfo on table1
        (void) displayFileInfo(*table1, entry,
                (const int) bits);

        (void) free(*table1);
    }

    return 0; //no error status

}

