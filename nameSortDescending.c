/*
 * Filename: nameSortDescending.c
 * Author: Anish Narsian
 * Description: compare name using strcmp.
 * Date: 12/2/2013
 * Sources of Help: Discussion.
 */

#include <stdlib.h>
#include <string.h>
#include "myls.h"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

/*
 * Function nameSortDescending( const void *p1, const void *p2 );
 * Function prototype:int nameSortDescending(const void *p1, const void *p2 );
 * Description: compares the name using strcmp
 * Parameters: 
 *          p1: name1 
 *          p2: name2
 * Side Effects: None
 * Error Conditions: None.
 * Return Value: int result of strcmp
 */

int nameSortDescending(const void *p1, const void *p2) {
	struct fileInfo * ptr1 = (struct fileInfo *) p1;
	struct fileInfo * ptr2 = (struct fileInfo *) p2;

	//returing strcmp  val
	return strcmp(ptr2->name, ptr1->name);
}

