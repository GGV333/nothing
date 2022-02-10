/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */


/*
#define UNIX
#define UNIX_DEBUG
*/

#ifdef UNIX
#include <stdio.h>
#define Exit exit
#else
#include "syscall.h"
#endif /* UNIX */

#define SIZE (1024)

int A[SIZE];	/* size of physical memory; with code, we'll run out of space!*/

int
main()
{
    int i, j, tmp, n, choose, flag;
    PrintString("Input the size of the array (1<= size <= 100): ");
    n = ReadNum();

    /* first initialize the array, in reverse sorted order */
    for (i = 0; i < n; i++) {
        A[i] = ReadNum();
    }

    PrintString("Choose the order sorted: \n");
    PrintString("1. Ascending\n");
    PrintString("2. Descending\n");
    choose = ReadNum();

    if (choose==1){
        flag = -1;
    }
    else if (choose==2)
        flag = 1;
    else   
        flag = 0;
    /* then sort! */
    for (i = 0; i < n; i++) {
        for (j = 0; j < (n - i-1); j++) {
	   if ((A[j] - A[j + 1])*flag < 0) {	/* out of order -> need to swap ! */
	      tmp = A[j];
	      A[j] = A[j + 1];
	      A[j + 1] = tmp;
    	   }
        }
    }
    PrintString("Your sequence numbers:\n");
    for (i = 0; i < n; i++) {
        PrintNum(A[i]);
        PrintChar(' ');
    }
    PrintChar('\n');
/*
#ifdef UNIX_DEBUG
    for (i=0; i<SIZE; i++) {
        printf("%4d ", A[i]);
	if (((i+1) % 15) == 0) {
		printf("\n");
        }
        if (A[i] != i) {
            fprintf(stderr, "Out of order A[%d] = %d\n", i, A[i]);
            Exit(1);
        }   
    }
    printf("\n");
#endif  UNIX_DEBUG 

    for (i=0; i<SIZE; i++) {
        if (A[i] != i) {
            Exit(1);
        }   
    }

    Exit(0);

*/  Halt();
}
