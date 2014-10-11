/*
 * Filename: nameSortAscending.s
 * Author: Anish Narsian
 * Description : sort in ascending order.
 * Date: 12/2/2013
 * Sources of help: Discussion
 * 
 */
.global	nameSortAscending 
.section ".data"
.section ".text" 

 /*
 * Funtion name: int nameSortAscending
 * Funtion prototype: int nameSortAscending(const void *p1, const void *p2);
 * Description: sort in ascending order
 * Parameters:
 *    arg 1: ptr1: ptr struct 1
 *    arg 2: ptr2 -- ptr struct 2
 * Side Effects: None
 * Error Conditions: None
 * Registers used.
 *    %i0 - ptr 1
 *    %i1 = ptr 2
 *    %o0, o1 - input registers 
 */

nameSortAscending:
	
  save  %sp, -(92)&-8, %sp

	! mov ptrs to o0 and o1
  mov   %i0, %o0
  mov   %i1, %o1


  call  strcmp   ! call strcmp
  nop
  mov   %o0, %i0

ret      !ret restore
restore



	
