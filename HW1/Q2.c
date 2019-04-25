/* CS261- Assignment 1 - Q.2*/
/* Name: Carrie Davis	
 * Date: 10/8/18
 * Solution description: Swaps addresses of integers a & b, decrements value of c and returns value
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
	int * intermed;
	intermed = a;
	a = b;
	b = intermed;
    /*Decrement the value of integer variable c*/
	(c)--;
    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
	int upper = 10;
	int lower = 0;
	srand(time(0)); /*Use time to seed random generator to avoid same random number each time rand called */
	int x = (rand() % (upper - lower + 1)) + lower; /*get random value bt 0 - 10 */
	int y = (rand() % (upper - lower + 1)) + lower;
	int z = (rand() % (upper - lower + 1)) + lower;
    /*Print the values of x, y and z*/
	printf("Value of x: %d Value of y :%d Value of z: %d\n", x, y, z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
	int c = foo(&x, &y, z);
    /*Print the values of x, y and z*/
	printf("Value of x: %d Value of y: %d Value of z: %d\n", x, y, z);
    /*Print the value returned by foo*/
	printf("Value returned by foo: %d\n", c);
    
    return 0;
}
//a) Is the return value different than the value of integer z ? Why or why not?
// Yes, the return of the value c is 1 less than z, because the value or a copy of z was entered and then 1 was subtracted from the value of z
 //and this value was returned not z.

//b) Are the values of integers x and y different before and after calling the function foo(..) ? Why or why not?
// the values are the same because foo did not change the values but the location in where those values are stored. 
//x and y still have same value but stored at different location in memory
    


