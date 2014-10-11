/*
 * Filename: displayFileInfo.c
 * Author: Anish Narsian
 * Description: displays all the list files.
 * Date: 11/27/2013
 * Sources of Help: Discussion.
 */
#include <sys/types.h>
#include <libgen.h>
#include <sys/mkdev.h>

#include <time.h>
#include <sys/time.h>

#include "myls.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



/*
 * Function name:displayFileInfo( struct fileInfo * const table, 
 *    const int entries, const int displayMode );
 * Function prototype:void displayFileInfo( struct fileInfo * const table,
 *    const int entries, const int displayMode );
 * Description: check flags and displays
 * Parameters: table: the ptr to the data
 *             entries: numof entries to table
 *             displayMode: the passed in parameters.
 * Side Effects: None
 * Error Conditions: None. 
 * Return Value: none.
 */

void displayFileInfo(struct fileInfo * const table, const int entries,
        const int displayMode) {

    //name of the file
    char name[MAXNAMLEN];

    //flags for ISBLK and ISCHR
    int bFlag1 = 0;
    int bFlag2 = 0;

    //to hold the time, date etc.
    time_t timing;
    if (displayMode & TFLAG) { //tflag check
        //rflag check
        if (displayMode & RFLAG) {
            (void) qsort(table, entries, sizeof(struct fileInfo),
                    mtimeSortAscending);  //qsort based on mtimeAscending

            if (!(displayMode & AFLAG) && !(displayMode & LFLAG)) {
                int i = 0;
                for (i = 0; i < entries; i++) {
                    //copy name of file
                    (void) strncpy (name, table[i].name, MAXNAMLEN);

                    if (name[0] != '.') {
                        (void) printf("%s\n", (table + i)->name);
                    }
                }
            }

        }

        else {


            (void) qsort(table, entries, sizeof(struct fileInfo),
                    mtimeSortDescending);//qsort based on mtimedescending

            if (!(AFLAG & displayMode) && !(LFLAG & displayMode)) {
                int i = 0;
                for (i = 0; i < entries; i++) {
                    (void) strncpy (name, table[i].name, MAXNAMLEN);

                    if (name[0] != '.') {
                        (void) printf("%s\n", (table + i)->name);
                    }
                }
            }

        }

    }


    else if ((displayMode & RFLAG) && !(displayMode & TFLAG)) {
        
        (void) qsort(table, entries, sizeof(struct fileInfo),
                nameSortDescending); //qsort based on Descending order

        if (!(displayMode & LFLAG)) {
            
            if (!(displayMode & AFLAG)) {
                int i = 0;
                for (i = 0; i < entries; i++) {
                    
                    (void) strncpy (name, table[i].name, MAXNAMLEN);
                    //copies and print name
		    


                    if (name[0] != '.') {
                        (void) printf("%s\n", (table + i)->name);
                    }
                }
            }
        }
    }

    //qsort based on Ascending order
    if (!(displayMode & TFLAG) && !(displayMode & RFLAG)) {



        (void) qsort(table, entries, sizeof(struct fileInfo),
                nameSortAscending);
    }
    if ((displayMode & LFLAG) && (displayMode & AFLAG)) {
        int i = 0;
        for (i = 0; i < entries; i++) {
            //prints the d,b,l,c for different modes
            (void) strncpy (name, table[i].name, MAXNAMLEN);

            if (S_ISDIR(((table[i]).stbuf).st_mode) == 1) {
                
		    (void) printf("d");
            }

            else if (S_ISLNK(((table[i]).stbuf).st_mode) == 1) {
                (void) printf("l");

            }

            else if (S_ISBLK((table[i].stbuf).st_mode) == 1) {
                (void) printf("b");
                bFlag2 = 1;


            }

            else if (S_ISCHR((table[i].stbuf).st_mode) == 1) {
                (void) printf("c");
                bFlag1 = 1;
            }

            else {
                (void) printf("-");
            }

            //permission bits
            (void) displayPermissions((table[i].stbuf).st_mode);

            //nlink var
            (void) printf("%4d ", (int) ((table[i].stbuf).st_nlink));

            //owner directory
            displayOwnerName((table[i].stbuf).st_uid);

            //group directory
            displayGroupName((table[i].stbuf).st_gid);
            if (bFlag2 || bFlag1) {
                (void) printf("%31d,%31d",
                        (int) major((table[i].stbuf).st_rdev),
                        (int) minor((table[i].stbuf).st_rdev) );

                bFlag2 = 0;
                bFlag1 = 0;
            } else {
                
                (void) printf("%7ld", (table[i].stbuf).st_size);
		//size
            }

            

            timing = (table[i].stbuf).st_mtime;//calculate time
            if (((int) timing) > (time(NULL ) - 15724800)) {
                //calculating the time
                char * t1 = ctime(&timing);
                char * s1 = strchr(t1, ' ');
                char * s2 = strrchr(t1, ':');
                *s2 = '\0';

                //priting the time
		
                (void) printf(" %s", s1 + 1);

            }

            else {
                //calculating the hours month etc
                char * t1 = ctime(&timing);

                char * r1 = strchr(t1, ' ');
                char * r2 = strchr(t1, ':');
                r2 -= 3;

                char * r3 = strrchr(t1, ' ');
                char * r4 = strrchr(t1, '\n');

                *r2 = '\0';
                *r4 = '\0';

                //printung month etc
                (void) printf(" %s  %s", r1 + 1, r3 + 1);
            }

            //finally printing the name
            (void) printf(" %s\n", (table + i)->name);

        }
    }

    //if only 'l' flag
    if ((displayMode & LFLAG) && !(displayMode & AFLAG)) {
        int i = 0;
        for (i = 0; i < entries; i++) {
            //copies the name of thje file
            (void) strncpy (name, table[i].name, MAXNAMLEN);

            if (name[0] != '.') {

                //prints the dlbc acc to stmode
                if (S_ISDIR(((table[i]).stbuf).st_mode) == 1) {
                    (void) printf("d");
                }

                else if (S_ISLNK((table[i].stbuf).st_mode == 1)) {
                    (void) printf("l");
                }

                else if (S_ISBLK((table[i].stbuf).st_mode) == 1) {
                    (void) printf("b");
                    bFlag2 = 1;
                }

                else if (S_ISCHR((table[i].stbuf).st_mode) == 1) {
                    (void) printf("c");
                    bFlag1 = 1;
                }

                else {
                    (void) printf("-");
                }

                //permission bits
                (void) displayPermissions((table[i].stbuf).st_mode);

                //nlink var
                (void) printf("%4d ",
                        (int) ((table[i].stbuf).st_nlink));

                //owner directory
                displayOwnerName((table[i].stbuf).st_uid);
                //group directoy
                displayGroupName((table[i].stbuf).st_gid);
                if (bFlag2 || bFlag1) {
                    (void) printf("%31d,%31d ",
                            (int) major((table[i].stbuf).st_rdev),
                            (int) minor((table[i].stbuf).st_rdev) );

                    bFlag2 = 0;
                    bFlag1 = 0;
                } else {
                    (void) printf("%7ld", (table[i].stbuf).st_size);
                }
                timing = (table[i].stbuf).st_mtime;
                if (((int) timing) > (time(NULL ) - 15724800)) {
                    //calculate time
                    char * t1 = ctime(&timing);

                    char * s1 = strchr(t1, ' ');
                    char * s2 = strrchr(t1, ':');

                    *s2 = '\0';

                    //print the time
                    (void) printf(" %s", s1 + 1);

                } else {

                    //calculating month day etc
                    char * t1 = ctime(&timing);

                    char * r1 = strchr(t1, ' ');
                    char * r2 = strchr(t1, ':');
                    r2 -= 3;

                    char * r3 = strrchr(t1, ' ');


                    char * r4 = strrchr(t1, '\n');
                    *r2 = '\0';
                    *r4 = '\0';
                    (void) printf("%s  %s", r1 + 1, r3 + 1);
                }

                //print name of file at end.
                (void) printf(" %s\n", (table + i)->name);

            }

        }

    }





    if ((displayMode & AFLAG) && !(displayMode & LFLAG)) {
        if (entries == 1) {
            (void) printf("%s\n", table[0].name);

	    
        } 

	
	else {
            int i = 0;
            for (i = 0; i < entries; i++) {
                (void) printf("%s\n", (table + i)->name);
            }
        }
    }



    if (!(AFLAG & displayMode) && !(LFLAG & displayMode)
            && !(RFLAG & displayMode) && !(TFLAG & displayMode)) {
        int i = 0;
        for (i = 0; i < entries; i++) {
            //copy name and print
            (void) strncpy (name, table[i].name, MAXNAMLEN);

            if (name[0] != '.') {
                (void) printf("%s\n", (table + i)->name);
            }
        }
    }
}
