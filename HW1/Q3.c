/* CS261- Assignment 1 - Q.3*/
/* Name: Carrie Davis
 * Date: 10/8/18
 * Solution description: This program takes sets of alphabetic characters 
 * separated by underscores or special char
 * returns them in camelCase removing underscores.
 */

#include <stdio.h>
#include <stdlib.h>

char toUpperCase(char ch){
  /*Convert ch to upper case, assuming it is in lower case currently*/
	if (ch >= 'a' && ch <= 'z')
	{
		return ch + 'A' - 'a';
	}
	else
	{
		return ch;
	}
}

char toLowerCase(char ch){
  /*Convert ch to lower case, assuming it is in upper case currently*/  
	if (ch >= 'A' && ch <= 'Z')
	{
		return ch + 'a' - 'A';
	}
	else
	{
		return ch;
	}
}

int stringLength(char s[]) {
   /*Return the length of the string*/
	int length;
	length = 0;
	while(s[length] != '\0')
	{
		length++;
	}
	return length;
}

void camelCase(char* word)
{
	/*Convert to camelCase*/
	int length = stringLength(word); // get length of string
	int i, j;
	j =0;
	for (i = 0; i < length; i++)
	{
		word[i] = toLowerCase(word[i]);

		while (word[i] == '_')
        {
			if(i != 0) // do not want to camel case first alphabetic char
			{
				word[i + 1] = toUpperCase(word[i + 1]);
			}
			for (j = i; word[j] != '\0'; ++j)
			{
				word[j] = word[j + 1];
			}
			word[j] = '\0';
		}   

	}
	
}


int main() {

	/*Read the string from the keyboard*/
	char string[25];
	printf("Please enter string:");

    /* Remove trailing newline, if there. */
	scanf("%[^\t\n]s",&string);;// data into scanf must be pointers

	//clean up string and validate
	int l = stringLength(&string);
	int flagAlpha = 0; 
	int flagOthers = 0;
	int end, begin; 
	end = l -1;
	begin = 0;
	
	//removes characters that are not alphabetic at end of string by setting end of string to the last alphabetic char
   while ((l > 0) && (!((string[end] >= 'a' && string[end] <= 'z') || (string[end] >= 'A' && string[end] <= 'Z')) || string[end] == '\0'))
	{
		string[end] ='\0';
		end--;
		l--; // makes the next for loop take into account the shortened, cleaned up string
	}
	//checks for non alpha characters at beginning of string and removes but only if there is a non alpha char at beginning
	while((l > 0) &&(!((string[begin] >= 'a' && string[begin] <= 'z') || (string[begin] >= 'A' && string[begin] <= 'Z')) || string[begin] == '\0'))
	{
			for(int i =0 ; i < l; i++)
		{
			string[i] = string[i+ 1];
		}
		l--;// makes the next for loop take into account the shortened, cleaned up s
	}
	//validate if there is a non leading or ending non alpha char and at least on alpha char
	for (int i = 0; i < l; i++)
	{
		if((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z'))
		{
			flagAlpha++; //this shows string has an alphabetic char
		}
		if(flagAlpha > 0 && (!((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z'))))
		{
			flagOthers++; //shows input string has char other than alphabetic if at least has one alphabetic char in beginning
			string[i] ='_'; //sets that char to _
		}	
	}
		
	if (flagAlpha == 0 || flagOthers == 0)
	{
		printf("invalid input string\n");
	}
	else{
	
		/*Call camelCase*/
		camelCase(&string);

		/*Print the new string*/
		printf("This is the new word :  %s \n", &string);
	}
	return 0;
}

