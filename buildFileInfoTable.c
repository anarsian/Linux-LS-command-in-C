/*
 * Filename: buildFileInfo.c
 * Author: Anish Narsian
 * Description: builds the table of data.
 * Date:  12/2/2013
 * Sources of Help: discussion
*/

#include <stdlib.h>
#include <string.h>
#include "myls.h"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

/*
 * Function name:buildFileInfoTable(const char 
 *       *filename, struct fileInfo ** const tablePtr);
 * Function prototype:int buildFileInfoTable(const char *filename,
 *                  struct fileInfo ** const tablePtr);
 * Description: build the table of files.
 * Parameters: filename - the name of passed in file.
 *             tabelPtr - the ptr to the tablf of data.
 * Side Effects: None
 * Error Conditions: 
 * Return Value: 0, signyfing no error
 */

  int buildFileInfoTable(const char *filename,
    struct fileInfo ** const tablePtr) {

    struct dirent *direct; 
    DIR *dir; 
  

    char container[MAXNAMLEN];

    char name[MAXNAMLEN]; //hold name for struct

    int numOfEntries = 0; 

    struct fileInfo *infoFile; //hold file info
    struct stat st; //stat struct


	//error printing 
    if (lstat(filename, &st) == -1) {
      (void) fprintf(stderr, "lstat -- ");
      (void) perror(filename);
      return 1;
    }
    if (S_ISDIR(st.st_mode) != 1) {
	//it is not dir
	
    //malloc mem for fileInfo ptr struct
    infoFile = (struct fileInfo *) malloc(sizeof(struct fileInfo));
    if (infoFile == NULL ) { //error printing
      (void) fprintf(stderr,
          "Trying to malloc a struct fileInfo ""(in buildFileInfoTable())\n");
      exit(1);
    }
    //copy filename
    (void) strncpy(infoFile[0].name, filename, MAXNAMLEN);
    infoFile[0].stbuf = st;
    *tablePtr = infoFile;
    return 0; 
    }




	//if it is a directory
    if (S_ISDIR(st.st_mode) == 1) {

		//opens the directory and stores it in dir.
      dir = opendir(filename);

		//prinst the filename
      (void) printf("%s:\n", filename);
		//if the directory is null, prins the reqgd error
      if (dir == NULL ) {
       (void) fprintf(stderr, "opendir -- ");
       (void) perror(filename);
       exit(1) ;
      }

		//otherwise mallocs memory 
      infoFile = (struct fileInfo *) malloc(sizeof(struct fileInfo));
		//if error in infoFile, prints error and returns
      if (infoFile == NULL ) {
        (void) fprintf(stderr, "Trying to malloc a struct fileInfo "
			 "(in buildFileInfoTable())\n");
         exit(1);
      }

		//otherwise, for each file in the direcory
      while ((direct = readdir(dir)) != NULL ) {
        (void) strncpy(name, filename, MAXNAMLEN);
        (void) snprintf(container, MAXNAMLEN, "%s/%s",name, direct->d_name);
	//class lstat on th dircontainer.
        (void) lstat(container, &st);

       


        infoFile = (struct fileInfo *) realloc(infoFile, 
              sizeof(struct fileInfo) * (numOfEntries + 1));

        
	//print error if cannot malloc memory
	if (infoFile== ((struct fileInfo *) malloc(sizeof(struct fileInfo))))
       	{
          (void) fprintf(stderr,"Trying to realloc another struct "
                              "fileInfo (in buildFileInfoTable())\n");


          (void) fprintf(stderr,"Only partial info will be displayed.\n");
          exit(1); //exit
        }

			//increment the numof entries
        numOfEntries++;

			//copy name of the file
        (void) strncpy(infoFile[numOfEntries - 1].name, direct->d_name, 
			 MAXNAMLEN);
			//copies the stbuf struct
        infoFile[numOfEntries - 1].stbuf = st;

     }
     *tablePtr = infoFile;
     return numOfEntries;

  }

 return 0; //no error status

 }


