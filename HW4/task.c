/*
 * CS 261 Assignment 4
 * Name: 
 * Date: 
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name)
{
    // FIXME: implement
     Task* task = malloc(sizeof(Task));
     strcpy(task->name,name);
     task->priority = priority;
    return task;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
    // FIXME: implement
    Task* taskL = (Task*)left;
    Task* taskR = (Task*)right;

    if(taskL->priority < taskR->priority)
    {
        return -1;
    }
    else if(taskL->priority > taskR->priority)
    {
        return 1;
    }
    else if(taskL->priority == taskR->priority)
    {
        if(taskL->name[0] < taskR->name[0])
        {
            return -1;
        }
        if(taskL->name[0] > taskR->name[0])
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("%d %s", task->priority, task->name);
}
