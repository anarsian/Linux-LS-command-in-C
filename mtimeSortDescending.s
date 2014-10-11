/*
 * Filename: mtimeSortDescending.s
 * Author: Anish Narsian
 * Description : Sort mtime into descending order
 * Date: 12/2/2013
 * Sources of help: Discussion
 * 
 */
.global	mtimeSortDescending
.section ".data"
.section ".text"

 /*
 * Funtion name: int mtimeSortDescending
 * Funtion prototype: int mtimeSortDescending(const void *p1, const void *p2);
 * Description: Sort mtime into descending order
 * Parameters:
 *    arg 1: ptr1: ptr struct 1
 *    arg 2: ptr2: ptr struct 2
 * Side Effects: None.
 * Error Conditions: none
 * Registers used.
 *    %o0 -Local reg 
 *    %o2 - Local reg 
 *    %o3 - Local reg 
 *    %o4 - Local reg 
 *
 *
 */

mtimeSortDescending:
	
	
  set  mtime_offSet, %o3  ! set mtime offset

	
  ld   [%o3], %o4   !load mtime to o4
  ld   [%o0 + %o4], %o0	
  ld   [%o1 + %o4], %o1	

  sub  %o1, %o0, %o0  !subtract mtimeoffsets and store result in o0
	
retl	! ret restore
nop


