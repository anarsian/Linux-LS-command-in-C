/*
 * Filename: displayGroupName.s
 * Author: Anish Narsian
 * Description : Used to diplay the group dir
 * Date: 12/2/2013
 * Sources of help: Discussion
 * 
 */

.global	displayGroupName                       
.section ".data"
fmt1:
.asciz "%-8s "
fmt2:
.asciz "%-8ld "
.section ".text" 

 /*
 * Funtion name: displayGroupName()
 * Funtion prototype: void displayGroupName(const gid_t gid);
 * Description: displays the group dir
 * Parameters:
 *    arg 1: gid:  the group id
 * Side Effects: None.
 * Error Conditions: none
 * Registers used.
 *    %i0 - arg 1: gid
 *    %o0 - output from getgrgid and input for printf
 *    %o1 - input for printf
 *    %l0 - to copy the result
 *
 */

displayGroupName:
  save  %sp, -(92)&-8, %sp !sav func
  mov   %i0, %o0
  call	getgrgid !call getgrgid
  nop

  mov    %o0, %l0     !move to l0 

  cmp    %l0, %g0     !compare with 0 
  be printFmt           !branch
  nop

  set fmt1, %o0    !else do following
  ld [%l0], %o1  
  call printf
  nop
  ba retRest           !branch ending
  nop

printFmt:
	
  set fmt2, %o0   
  mov %i0, %o1
  call printf
  nop

retRest:
  ret              !ret restore label
  restore
