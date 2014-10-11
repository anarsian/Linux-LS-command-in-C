/*
 * Filename: displaypermissions.c
 * Author: Anish Narsian
 * Description: displays the permission bits.
 * Date: 12/2/2013
 * Sources of Help: Discussion.
 */

#include "myls.h"
#include <stdio.h>
#include <errno.h>

#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/types.h>

/*
 * Function name:displayPermissions( const mode_t mode );
 * Function prototype:void displayPermissions( const mode_t mode );
 * Description: display the permission bits
 * Parameters: mode: the way/mode to display in
 * Side Effects: None
 * Error Conditions: None.
 * Return Value: None
 */

 void displayPermissions( const mode_t mode ) {
    //checking user bit set, and Read bit set and masking
 	if ((mode & S_IRUSR) && (mode & S_IREAD))    {   
        (void) printf("r");
    }
    else
    {
        (void) printf("-");
    }

    //checking if condition: Write bit set and IWUSR bit set
    if ((mode & S_IWUSR) && (mode & S_IWRITE))    {
        (void) printf("w");
    }
    else
    {
        (void) printf("-");
    }

    //checking ifcondition : exec and IXUSR bit set
    if ((mode & S_IXUSR) && (mode & S_IEXEC))    {
        (void) printf("x");
    }
    else
    {
        (void) printf("-");
    }

    //Bit groups checking
    //
    //
    //


    if ((mode & S_IRGRP) && (mode & S_IREAD))    {   
        (void) printf("r");
    }
    else
    {
        (void) printf("-");
    }

    //write bit set cehcking
    if ((mode & S_IWGRP) && (mode & S_IWRITE))    {
        (void) printf("w");
    }
    else
    {
        (void) printf("-");
    }

    //exec bit set checking
    if ((mode & S_IXGRP) && (mode & S_IEXEC))    {
        (void) printf("x");
    }
    else
    {
        
        (void) printf("-");
    }




   //
   //
   //
   //



    //read bit set checking
    if ((mode & S_IROTH) && (mode & S_IREAD))    {   
        (void) printf("r");
    }
    else    {
        (void) printf("-");
    }

    //write bit set checking
    if ((mode & S_IWOTH) && (mode & S_IWRITE))    {
        (void) printf("w");
    }
    else    {
        (void) printf("-");
    }

    //exec bit set checkinh
    if ((mode & S_IXOTH ) && (mode & S_IEXEC))    {
        (void) printf("x");
    }
    else    {
        (void) printf("-");
    }



 }
