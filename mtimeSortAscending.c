/*
 * Filename: mtimeSortAscending.c
 * Author: Anish Narsian
 * Description: sort st_mtime parameter of pointers
 * Date: 12/2/2013
 * Sources of Help: Discussion
 */

#include "myls.h"
#include <stdio.h>
#include <errno.h>

#include <stdlib.h>
#include <string.h>

#include <sys/types.h>

/*
 * Function name:mtimeSortAscending( const void *p1, const void *p2 )
 * Function prototype:int mtimeSortAscending( const void *p1, const void *p2)
 * Description: sort st_mtime parameter of pointers
 * Parameters: ptr1, ptr2 - pointers to two anagrams
 * Side Effects: None
 * Error Conditions: None. 
 * Return Value: int strcmp val(0, num>0 or num<0)
 */

int mtimeSortAscending(const void *p1, const void *p2) {

	struct fileInfo * ptr1 = (struct fileInfo *) p1;
	struct fileInfo * ptr2 = (struct fileInfo *) p2;

	//return difference
	return (ptr1->stbuf.st_mtime - ptr2->stbuf.st_mtime);
}

