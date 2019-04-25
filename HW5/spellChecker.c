#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//declare hashfunction
int HASH_FUNCTION(char*);

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
     char* word = nextWord(file);
   
    while (word) {
       hashMapPut(map, word, 1);
       free(word);
       word = nextWord(file);
    }

    free(word);
}


/**
* Get minimum of three values 
* @param integers a,b,c
*/

int Minimum (int a, int b, int c) {
  int mi;

    mi = a;
    if (b < mi) {
      mi = b;
    }
    if (c < mi) {
      mi = c;
    }
    return mi;

  }

/**
 * Levenshtein Distance calculation
 * credit info in https://people.cs.pitt.edu/~kirk/cs1501/Pruhs/Spring2006/assignments/editdistance/Levenshtein%20Distance.htm
 * @param input word
 * @param input key
 * returns cost
 */
int comparisonCheck(char* s, char* t)
{
    assert(s!=NULL);
    assert(t !=NULL);
    int n = strlen(s);
    int m = strlen(t);
    assert(n > 0);
    assert(m > 0);
    int i; // iterates through s
    int j; // iterates through t
    char s_i; // ith character of s
    char t_j; // jth character of t
    int cost; // cost
    //Construct a matrix containing 0..m rows and 0..n columns.
    int d[n+1][m+1];               
    //	Initialize the first row to 0..n.
    for(i=0; i <=n; i++)
    {
        d[i][0] = i;
    }
    //Initialize the first column to 0..m.
    for(j=0; j <=m; j++)
    {
        d[0][j] = j;
    }
    //Examine each character of s (i from 1 to n).
     for (i = 1; i <= n; i++) {
      s_i = s[i - 1];
    //	Examine each character of t (j from 1 to m).
     for (j = 1; j <= m; j++) {

        t_j = t[j - 1];
    //If s[i] equals t[j], the cost is 0.
    if (s_i == t_j) {
          cost = 0;
        }
    //If s[i] doesn't equal t[j], the cost is 1.
    else {
          cost = 1;
        }
    //Set cell d[i,j] of the matrix equal to the minimum of
    //The cell immediately above plus 1: d[i-1,j] + 1.
    //The cell immediately to the left plus 1: d[i,j-1] + 1.
    //The cell diagonally above and to the left plus the cost: d[i-1,j-1] + cost.
     //After the iteration steps (3, 4, 5, 6) are complete, the distance is found in cell d[n,m].
     d[i][j] = Minimum (d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1] + cost);
     }
    }
    // Step 7
    return d[n][m];
}
/**
 * Sets hashmap link value to 1
 * argument.
 * @param HashMap
 */
void setsCostToOne(HashMap* map)
{
    assert(map != NULL);
    for (int i = 0; i < hashMapCapacity(map); i++){
        HashLink* current = map->table[i];
       while(current){
            current->value = 1;
            current = current->next;
       }
    }   
}
/**
 * Prints the 5 keys in hashmap with lowest Levenshtein distance
 * arguments.
 * @param HashMap
 * @param inputCost
 * @param numGuess
 */
void lowestCost(HashMap* map,int inputCost, int numGuess){
    assert(map!=0);
    assert(inputCost >=0);
    assert(numGuess > 0);
    int j = 0;
    if(inputCost > 15)
    {
        printf(" ?. Could not find any further suggested words. ");
        return;
    }
    for (int i = 0; i < hashMapCapacity(map); i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            while (link != NULL)
            {
                if(link->value <= inputCost && j < numGuess){
                    printf("'%s' ", link->key);
                    j ++;
                 }
                link = link->next;
            }
        }
    }
    if(j < numGuess)
    {
        lowestCost(map,inputCost+1,numGuess-j);
    }
    else{printf(" ?\n");}
}


/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    int redo = 0;
    while (!quit)
    {
        do // validate input
        {
            fflush(stdin);
            printf("Enter a word or \"quit\" to quit: ");
            scanf("%[^\n]s", inputBuffer); 
           
            while(getchar() != '\n');
            redo =0;
            for(int i = 0; i < strlen(inputBuffer); i++){
                inputBuffer[i] = tolower(inputBuffer[i]);
            
                if (inputBuffer[i] >= 'a' && inputBuffer[i] <= 'z' && (inputBuffer[i] != ' ')) {
                       redo  +=0; 
                } else{redo +=1;} 
            } 
            if(redo >= 1)
                {
                    printf("Invalid Entry. Remove spaces or non letter characters.\n ");
                }
        }while(redo > 0);
      
        //Fix me:  implement the spell checker code here..
        
        if(hashMapContainsKey(map,inputBuffer))
        {
            
            printf("\nThe inputted word %s",inputBuffer);
            printf(" is spelled correctly\n");
        }
        else{
            printf("The inputted word %s",inputBuffer);
            printf(" is spelled incorrectly, Did you mean ");
            HashLink *current;
            for (int i = 0; i < hashMapCapacity(map); i++) {
                current = map->table[i];
                while(current != NULL) {
                    //if (strlen(current->key) == strlen(inputBuffer)) {
                   // did not get a better match when using this even though notes mention to do so.
                    //current->value= 0;
                   // }
                    int cost = comparisonCheck(current->key, inputBuffer);
                    hashMapPut(map,current->key,cost);
                    current = current->next;
                }
            }
            //print the lowest cost values up to 5 guesses
            lowestCost(map,1, 5);
            setsCostToOne(map);  //sets cost back to 1 for all values
        }
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    hashMapDelete(map);
    return 0;
}
