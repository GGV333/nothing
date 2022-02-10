/* add.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int
main()
{
  char *a;
  ReadString(a, 100);
  PrintString(a);
  Halt();
  /* not reached */
}
