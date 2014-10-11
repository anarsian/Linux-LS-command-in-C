/*
 * Filename: displayOwenerName.c
 * Author: Anish Narsian
 * Description: display owner folder.
 * Date: 12/2/2013
 * Sources of Help: Discussion
 */

#include "myls.h"
#include <stdio.h>

#include <sys/types.h>
#include <libgen.h>
#include <pwd.h>


#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>


/*
 * Function name:displayOwnerName( const uid_t uid );
 * Function prototype:void displayOwnerName( const uid_t uid );
 * Description: display the owner folder.
 * Parameters: uid:the id
 * Side Effects: None
 * Error Conditions: None.
 * Return Value: None
 */

void displayOwnerName(const uid_t uid) {

	//password structure
	struct passwd *password;
	password = getpwuid(uid);

	//if password null print uid else name
	if (password == NULL ) {
		(void) printf("%-8u ", (int) uid);
	} else {
		(void) printf("%-8s ", password->pw_name);
	}
}
