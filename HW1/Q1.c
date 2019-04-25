/* CS261- Assignment 1 - Q.1*/
/* Name: Carrie Davis
 * Date:10/8/18
 * Solution description: print students scores and calculate avg, min and max of scores
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student *stud;
	stud = (struct student*)malloc(sizeof(stud) * 10); //multiply the number of elements needed by size of elements
     /*Return the pointer*/
	return stud;
}

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
IDs being between 1 and 10, scores between 0 and 100*/
	int upperID = 10;
	int lowerID = 1;
	int upperScore = 100;
	int lowerScore = 0;
	int flag;
	int scoreValue;
	int idValue;

	//loop through positions in struct array brute force method idea from stackoverflow questions 1608181
	for (int i = 0; i < 10; i++)
	{
		do {
			flag = 1;
			srand(time(0)); /*Use time to seed random generator to avoid same random number each time rand called */
			scoreValue = (rand() % (upperScore - lowerScore + 1)) + lowerScore; /*get random value  */
			idValue = (rand() % (upperID - lowerID + 1)) + lowerID; /*get random value  */
			//loop through and check if value is used
			for (int j = 0; j < i && flag == 1; j++) 
			{
				if (students[j].id == idValue || students[j].score == scoreValue) 
				{
					flag = 0;
				}
			}

		} while (flag != 1);
		students[i].id = idValue;
		students[i].score = scoreValue;
	}

}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	for (int i = 0; i < 10; i++)
	{
		printf("ID%d Score %d\n", students[i].id, students[i].score);
	}
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
ten students*/
	//initalize scores to the first element so not null
	int min = students[0].score;
	int max = students[0].score;
	int avg = 0;
	
	//assert(students != NULL); //should produce error message if pointer array is null

	for (int i = 0; i < 10; i++)
	{
		if (students[i].score < min)
		{
			min = students[i].score;
		}
		if (students[i].score > max)
		{
			max = students[i].score;
		}
		avg = avg + students[i].score;
	}
	avg = avg / 10;
	printf("MAX Score: %d MIN Score: %d AVG Score: %d\n", max, min, avg);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	if(stud != NULL);
		free(stud);
}

int main(){
    struct student* stud = NULL;
    /*Call allocate*/
	stud = allocate();
    printf("Be patient program is slow but works \n");
    /*Call generate*/
	generate(stud);
    /*Call output*/
	output(stud);
    /*Call summary*/
	summary(stud);
    
    /*Call deallocate*/
	deallocate(stud);

    return 0;
}

