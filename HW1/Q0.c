/* CS261- Assignment 1 - Q. 0*/
/* Name: Carrie Davis	
 * Date: 10/8/18
 * Solution description: prints the value and address of x, and related pointers to x.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){

     /*Print the value and address of the integer pointed to by iptr*/
	printf("From fooA; Value of x: %d Address of x:  %p\n", *iptr, iptr);

     /*Increment the value of the integer pointed to by iptr by 5*/
	int * newPtr;
	newPtr = iptr;
	*newPtr = (*newPtr) + 5;
	      
     /*Print the address of iptr itself*/
	int *ip = iptr;  
	printf("From fooA; the address of iptr: %p\n", &iptr);
}


void fooB(int* jptr){
	
     /*Print the value and address of the integer pointed to by jptr*/
	printf("From fooB; Value of x: %d Address of x: %p\n", *jptr, jptr);
	
     /*Decrement jptr by 1*/
	*jptr--;  // I decremented jptr itself not the value pointed to by jptr.  
	
     /*Print the address of jptr itself*/
	int *jp = jptr;
	printf("From fooB Updated Address of jptr: %p\n", &jptr);
}


int main(){
    
    /*Declare an integer x and initialize it randomly to a value in [0,10] */
	int upper = 10;
	int lower = 0;
	srand(time(0)); /*Use time to seed random generator to avoid same random number each time rand called */
	int x = (rand() % (upper - lower + 1)) + lower; /*get random value bt 0 - 10 */

    /*Print the value and address of x*/
	printf("Value of x: %d Address of x: %p\n", x, &x);

    /*Call fooA() with the address of x*/
	fooA(&x);
    /*Print the value of x*/
	printf("Updated value of x: %d\n", x); 
	// Question from 3. Is the value of x different than the value that was printed at first ? Yes. 
	//The pointer used in arguement for fooA references x. Then fooA adds 5 to the value of the reference.

    /*Call fooB() with the address of x*/
	fooB(&x);
    
    /*Print the value and address of x*/
	
	printf("From main; the current value of x: %d The current address of x: %p\n", x, &x);
	//Are the value and address of x different than the value and address that were printed before the call to fooB(..)? NO. 
	//Because the value was not changed in fooB nor the address of x. I changed only the value of the address of jptr that points to x.
    return 0;
}


