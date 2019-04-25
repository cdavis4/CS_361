/*
 * CS 261 Assignment 5
 * Name: Alex Miranda 
 * Date: 5/14/2016
 */

#include "dynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TESTING

#ifndef TESTING
static void adjustHeap(DynamicArray* heap, int last, int position, compareFunction compare);
static void buildHeap(DynamicArray* heap, compareFunction compare);
#endif

struct DynamicArray
{
    TYPE* data;
    int size;
    int capacity;
};

// --- Dynamic array ---

static void setCapacity(DynamicArray* array, int capacity)
{
    TYPE* data = malloc(sizeof(TYPE) * capacity);
    for (int i = 0; i < array->size; i++)
    {
        data[i] = array->data[i];
    }
    free(array->data);
    array->data = data;
    array->capacity = capacity;
}

static void init(DynamicArray* array, int capacity)
{
    assert(capacity > 0);
    array->data = NULL;
    array->size = 0;
    setCapacity(array, capacity);
}

DynamicArray* dyNew(int capacity)
{
    DynamicArray* array = malloc(sizeof(DynamicArray));
    init(array, capacity);
    return array;
}

void dyDelete(DynamicArray* array)
{
    free(array->data);
    free(array);
}

void dyAdd(DynamicArray* array, TYPE value)
{
    if (array->size >= array->capacity)
    {
        setCapacity(array, 2 * array->capacity);
    }
    array->data[array->size] = value;
    array->size++;
}

void dyAddAt(DynamicArray* array, TYPE value, int position)
{
    assert(position <= array->size);
    dyAdd(array, value);
    for (int i = array->size - 1; i > position; i--)
    {
        dySwap(array, i, i - 1);
    }
}

void dyPut(DynamicArray* array, TYPE value, int position)
{
    assert(position < array->size);
    array->data[position] = value;
}

void dyRemoveAt(DynamicArray* array, int position)
{
    assert(position < array->size);
    for (int i = position; i < array->size - 1; i++)
    {
        array->data[position] = array->data[position + 1];
    }
    array->size--;
}

TYPE dyGet(DynamicArray* array, int position)
{
    assert(position < array->size);
    return array->data[position];
}

int dySize(DynamicArray* array)
{
    return array->size;
}

void dySwap(DynamicArray* array, int position1, int position2)
{
    assert(position1 < array->size);
    assert(position2 < array->size);
    TYPE temp = array->data[position1];
    array->data[position1] = array->data[position2];
    array->data[position2] = temp;
}

// --- Stack ---

void dyStackPush(DynamicArray* stack, TYPE value)
{
    dyAdd(stack, value);
}

void dyStackPop(DynamicArray* stack)
{
    dyRemoveAt(stack, stack->size - 1);
}

TYPE dyStackTop(DynamicArray* stack)
{
    return dyGet(stack, stack->size - 1);
}

int dyStackIsEmpty(DynamicArray* stack)
{
    return stack->size == 0;
}

// --- Bag ---

static int findFirst(DynamicArray* array, TYPE value, compareFunction compare)
{
    for (int i = 0; i < array->size; i++)
    {
        if (compare(value, array->data[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

void dyBagAdd(DynamicArray* bag, TYPE value)
{
    dyAdd(bag, value);
}

void dyBagRemove(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = findFirst(bag, value, compare);
    if (position != -1)
    {
        dyRemoveAt(bag, position);
    }
}

int dyBagContains(DynamicArray* bag, TYPE value, compareFunction compare)
{
    return findFirst(bag, value, compare) != -1;
}

// --- Ordered bag ---

static int binarySearch(DynamicArray* array, TYPE value, compareFunction compare)
{
    int low = 0;
    int high = array->size - 1;
    while (low <= high)
    {
        int middle = (low + high) / 2;
        if (compare(value, array->data[middle]) < 0)
        {
            high = middle - 1;
        }
        else if (compare(value, array->data[middle]) > 0)
        {
            low = middle + 1;
        }
        else
        {
            return middle;
        }
    }
    return low;
}

void dyOrderedAdd(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = binarySearch(bag, value, compare);
    dyAddAt(bag,value, position);
}

void dyOrderedRemove(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = binarySearch(bag, value, compare);
    if (compare(value, bag->data[position]) == 0)
    {
        dyRemoveAt(bag, position);
    }
}

int dyOrderedContains(DynamicArray* bag, TYPE value, compareFunction compare)
{
    int position = binarySearch(bag, value, compare);
    return compare(value, dyGet(bag, position)) == 0;
}

// --- Heap ---

/**
 * Adjusts heap to maintain the heap property.
 * @param heap
 * @param last  index to adjust up to.
 * @param position  index where adjustment starts.
 * @param compare  pointer to compare function.
 */
void adjustHeap(DynamicArray* heap, int last, int position, compareFunction compare)
{
    // FIXME: implement
    assert(heap !=0);
    assert(last <= dySize(heap));
    int left = (2 * position) + 1;
    int right = (2 * position) + 2;
    int smallest;

    if (right < last) {
        assert(left < dySize(heap));
        assert(right < dySize(heap));
        if (compare(dyGet(heap, left), dyGet(heap, right)) == -1) {
            smallest = left;
         }else {
            smallest = right;
        }
        if (compare(dyGet(heap, position), dyGet(heap, smallest)) == 1) {
            dySwap(heap, position, smallest);
            position = smallest;
            adjustHeap(heap, last, position, compare);
        }
        else{
            return;
        }
    } else if (left < last) {
        if (compare(dyGet(heap, position), dyGet(heap, left)) == 1) {
            dySwap(heap, position, left);
            position = left;
            adjustHeap(heap, last, position, compare);
        }
        else{return;}
    }else
    {return;}
}

/**
 * Builds a valid heap from an arbitrary array.
 * @param heap  array with elements in any order.
 * @param compare  pointer to compare function.
 */
void buildHeap(DynamicArray* heap, compareFunction compare)
{
    // FIXME: implement
    assert(heap !=0);
    assert(dySize(heap)>0);
    int size = dySize(heap);
    
    for (int i = (size / 2) - 1; i >= 0; i--) {
        adjustHeap(heap, size, i, compare);
    }
}

/**
 * Adds an element to the heap.
 * @param heap
 * @param value  value to be added to heap.
 * @param compare  pointer to compare function.
 */
void dyHeapAdd(DynamicArray* heap, TYPE value, compareFunction compare)
{
    // FIXME: implement
    assert(heap != 0);
    int parent;
    //assert(dySize(heap)>0);
    int position = (dySize(heap));
    dyAdd(heap, value);
    assert(dySize(heap)>0);
    
    while(position != 0){
        parent = (position-1)/2;
           if(position <=2)
        {
            parent = 0;
        }

        if(compare(dyGet(heap,position),dyGet(heap,parent)) == -1) {
            dySwap(heap, parent,position);
            if(parent > 0)
            {
            position = parent;
            }
        }
        else if(compare(dyGet(heap,position),dyGet(heap,parent)) == 0){
            if(parent > 0)
            {
                position = parent;
            }
            DynamicArray* temp = dyNew(dySize(heap));
            temp->size = dySize(heap);
            printf("TempAizw %d",temp->size);
            for(int i = position; i < temp->size; i++){
                int j = i+1;
                if (dyGet(heap,j) == value)
                {
                    dyPut(temp,dyGet(heap,j)+1,i);
                }
            }
            dyCopy(temp,heap);
            free(temp);
        }
        else {return;}
    }
}

/**
 * Removes the first element, which has the min priority, form the heap.
 * @param heap
 * @param compare  pointer to the compare function.
 */
void dyHeapRemoveMin(DynamicArray* heap, compareFunction compare)
{
    // FIXME: implement
    assert(heap != 0);
    assert(dySize(heap) > 0);
 
    int last = dySize(heap) - 1;
   /*Copy rhw last element to the first position */
    dyPut(heap,dyGet(heap,last),0);
    dyRemoveAt(heap,last);
    adjustHeap(heap,last, 0, compare);
}

/**
 * Returns the first element, which has the min priority, from the heap.
 * @param heap
 * @return  Element at the top of the heap.
 */
TYPE dyHeapGetMin(DynamicArray* heap)
{
    // FIXME: implement
    assert(heap != 0);
    assert(dySize(heap) > 0);
    return dyGet(heap,0);
}

/**
 * Sorts arbitrary array in-place.
 * @param heap  array with elements in arbitrary order.
 * @param compare  pointer to the compare function.
 */
void dyHeapSort(DynamicArray* heap, compareFunction compare)
{
    // FIXME: implement
    int i;
    assert(heap!=0);
    assert(dySize(heap)>0);
    buildHeap(heap, compare);
  
    for (i= dySize(heap)-1; i >= 0; i--) {
       dySwap(heap, 0, i);
       adjustHeap(heap, i, 0, compare);  
    }
}

// --- Iterator ---

DynamicArrayIterator* dyIteratorNew(DynamicArray* array)
{
    DynamicArrayIterator* iterator = malloc(sizeof(DynamicArrayIterator));
    iterator->array = array;
    iterator->current = 0;
    return iterator;
}

void dyIteratorDelete(DynamicArrayIterator* iterator)
{
    free(iterator);
}

int dyIteratorHasNext(DynamicArrayIterator* iterator)
{
    return iterator->current < iterator->array->size;
}

TYPE dyIteratorNext(DynamicArrayIterator* iterator)
{
    TYPE value = dyGet(iterator->array, iterator->current);
    iterator->current++;
    return value;
}

void dyIteratorRemove(DynamicArrayIterator* iterator)
{
    iterator->current--;
    dyRemoveAt(iterator->array, iterator->current);
}

// --- Utility ---

void dyPrint(DynamicArray* array, printFunction print)
{
    printf("\nsize: %d\ncapacity: %d\n[\n", array->size, array->capacity);
    for (int i = 0; i < array->size; i++)
    {
        printf("%d : ", i);
        print(array->data[i]);
        printf("\n");
    }
    printf("]\n");
}

void dyCopy(DynamicArray* source, DynamicArray* destination)
{
    free(destination->data);
    init(destination, source->capacity);
    for (int i = 0; i < dySize(source); i++)
    {
        destination->data[i] = source->data[i];
    }
    destination->size = dySize(source);
}