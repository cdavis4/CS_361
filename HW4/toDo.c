/*
 * CS 261 Assignment 4
 * Name: 
 * Date: 
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }     
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
    switch(command)
{ 
    case 'l':{
        char fileName[100];
        printf("Please enter the filename: ");
        fgets(fileName, 100, stdin);
            if (fileName[strlen(fileName) - 1] == '\n') {
                fileName[strlen(fileName) - 1] = 0;
            }
         printf("File name %s\n",fileName);
         FILE * input_file = fopen(fileName, "r");
        if (input_file == NULL){
            fprintf(stderr, "Cannot open %s\n",fileName);
            return;
            }
        listLoad(list, input_file);
        printf("The list has been loaded successfully from the file.\n");
        fclose(input_file);
        break;
    }
    case 's':{
        char fileName[100];
        printf("Please enter the filename: ");
        fgets(fileName, 100, stdin);
            if (fileName[strlen(fileName) - 1] == '\n') {
                fileName[strlen(fileName) - 1] = 0;
            }
        FILE * output_file = fopen(fileName, "w");
        if (output_file == NULL){
        fprintf(stderr, "Cannot open %s\n",fileName);
        return;
        }
        listSave(list,output_file);
        printf("The list has been saved successfully to the file.\n");
        fclose(output_file);
        break;
        }
    case 'a':{
        char name[100];
        int priority;
        printf("Enter name for task: ");
        fgets(name, 100, stdin);
        fflush(stdin);
        printf("You typed: %s\n", name);
        printf("Enter priority value for task: ");
        scanf("%d",&priority);
        while(getchar() != '\n');
        printf("You typed: %d\n", priority);
        Task* newTask = taskNew(priority,name);
        dyHeapAdd(list,newTask,taskCompare);
        printf("New Task has been added %s \n",name);
        break;
    }
    case 'g':{
          if (dySize(list) == 0) {
              printf("Task List Is Empty, Add a Task\n");
          }
          else{
            Task* firstTask =  (struct Task *)dyHeapGetMin(list);
            
            printf("First Task is : %s\n", firstTask->name);
            printf("The Priority Listed: %d\n", firstTask->priority);
          }
          break;
    }
    case 'r':{
        
         if (dySize(list) == 0) {
              printf("Task List Is Empty, Add a Task\n");
          }
          else{
            Task* firstTask =  (struct Task*)dyHeapGetMin(list);
            
            printf("First Task will be removed called  %s\n", firstTask->name);
            printf("The Priority listed for this task was %d\n", firstTask->priority);
            dyHeapRemoveMin(list,taskCompare);
            taskDelete(firstTask);
          }
          break;
    }
    case 'p':{
        if(dySize(list)==0){
            printf("Task List Is Empty, Add a Task\n");
        }
        else{
       // dyHeapSort(list,taskCompare);
        listPrint(list);
        }
        break;
    }
    case 'e':{
        printf("exiting program\n");
        while(dySize(list) !=0){
            Task* delete_task =  (struct Task*)dyHeapGetMin(list);
            
            printf("First Task will be removed called  %s\n", delete_task->name);
            printf("The Priority listed for this task was %d\n", delete_task->priority);
            dyHeapRemoveMin(list,taskCompare);
            taskDelete(delete_task);
        }
        dyDelete(list);
        exit(0);
        break;
        }
    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}