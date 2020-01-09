/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: 
 * Date: 
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}


/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
   
    assert(map!=0);
    HashLink* link;
    HashLink* nextLink;
    for(int i; i  < hashMapCapacity(map); i++)
    {
         link = map->table[i];
         while(link !=NULL)
         {
            nextLink = link->next;
            hashLinkDelete(link);
            link = nextLink;
         }
    
    }
    map->capacity = 0;
    map->size = 0;
    free(map->table); 
   
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap)*capacity);
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map != NULL);
    assert(key != NULL);

    int idx = HASH_FUNCTION(key) % hashMapCapacity(map);

    HashLink* cur = map->table[idx];

    while (cur != NULL) {
       if (hashMapContainsKey(map,key) == 0) {
          return &(cur->value);
       }
       cur = cur->next;
    }     

    return NULL;
}
  /**  // FIXME: implement
    //gets value associated with a particular key
    assert(map!=0);
    assert(key!=NULL);
    int idx = HASH_FUNCTION(key) % hashMapCapacity(map);
    if (idx < 0) {
            idx += hashMapCapacity(map);
        }
    struct HashLink* link = map->table[idx];
    while(link != NULL)
    {
        if (key == link->key)
        {
            printf("Value found ");
            return &(link->value);
        }
        link = link->next;
    }
    return NULL;  //if corresponding key not found return null
}


 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
    int i;
    HashMap * newHM = hashMapNew(capacity);
    for( i=0; i < hashMapCapacity(map);i++)
    {
        HashLink* current = map->table[i];
        while(current){
   //int* value = hashMapGet(map,map->table[i]->key);  
        hashMapPut(newHM,current->key,current->value); 
        current = current->next;   
        }
    }
    hashMapCleanUp(map);
    map->size = newHM->size;
    map->capacity = newHM->capacity;
    map->table = newHM->table;
    free(newHM);

}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
  if (hashMapTableLoad(map) >= MAX_TABLE_LOAD)
{
       resizeTable(map, 2 * map->capacity);
   }
   // Compute index
   int idx = HASH_FUNCTION(key) % (map->capacity);
   if (idx < 0)
{
       idx += map->capacity;
   }
   // Add to bucket
   HashLink* link = map->table[idx];
   HashLink* newLink = NULL;
   if (link == NULL) {
       // Bucket is currently empty
       newLink= hashLinkNew(key, value, NULL);
       map->table[idx] = newLink;
       map->size++;
       return;
   }
   else
{ //bucket contains @ least 1 link
       while (link != NULL)
{
           if (strcmp(link->key, key) == 0)
{ //link w/ key already exists
               link->value = value;
               return;
           }
           link = link->next;
       }
       // Link with given key does not already exist, create new Link
       newLink = hashLinkNew(key, value, map->table[idx]);
       map->table[idx] = newLink;
       map->size++;
       return;
   }


}
    // FIXME: implement
    //value associated with a particular key.
    /**
    assert(map!=0);
    if (hashMapTableLoad(map) >= MAX_TABLE_LOAD)
    {
        resizeTable(map, hashMapCapacity(map)*2);
    }
    int idx = HASH_FUNCTION(key) % map->capacity;
    if (idx < 0) 
    {
       idx += hashMapCapacity(map);
    }

      if (hashMapContainsKey(map, key)) {
        int* val = hashMapGet(map, key);
        (*val) += value;
    } else {
        HashLink* new = hashLinkNew(key, value, NULL);

        assert(new != NULL);

        if (map->table[idx] == NULL) {
           map->table[idx] = new;
        } else {
           HashLink* cur = map->table[idx];
           while(cur->next) {
              cur = cur->next;
           }
           cur->next = new;
        }
        map->size++;
    }
}
   // HashLink* link = map->table[idx];
   // HashLink* newLink = NULL;
   // if(link == NULL)
   // {
   //     newLink = hashLinkNew(key, value, NULL);
   //     map->table[idx] = newLink;
   //     map->size++;
   // }
    //else{
    //    while(link->next) 
   //     {
   //         link = link->next;
   //     }
   //     link->next = newLink;
   // }

   /** if (hashMapContainsKey(map, key)) 
    {
        int* val = hashMapGet(map, key);
        *val += value;
    } 
    else {
        HashLink* newLink = hashLinkNew(key, value, NULL);

        assert(newLink != NULL);

        if (map->table[idx] == NULL) {
           map->table[idx] = newLink;
        } else {
           HashLink* current = map->table[idx];
           while(current->next) {
              current = current->next;
           }
           current->next = newLink;
        }
        map->size++;
    }
    */
    //because adding new we need to move to next location in array
   // HashLink* newLink = hashLinkNew(key,value,NULL);
   // assert(newLink !=0);
   // if(map->table[idx])
  //  {
  //      while(map->table[idx]!=NULL)
   //     {
  //          if(hashMapContainsKey(map,key)==0){
   //             map->table[idx]->value=value;
  //          }
  //        map->table[idx] = map->table[idx]->next;
   //     }
  //  }
  //  map->table[idx] = newLink; /* add to bucket */  
  //  map->size++;  
  


/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map!=0);
    assert(key!=0);
    assert(hashMapSize > 0);
    if(hashMapContainsKey(map, key)){
      int idx = HASH_FUNCTION(key) % hashMapCapacity(map);
        if (idx < 0) {
            idx += hashMapCapacity(map);
        }
		struct HashLink *current = map->table[idx];
		struct HashLink *previous = NULL;
    
        if (current != NULL) {
            if (hashMapContainsKey(map,key)== 0) 
            {
                map->table[idx] = current->next;
            } 
            else 
            {
                while (hashMapContainsKey(map,key) ==1) 
                {
                    previous = current;
                    current = current->next;
                }
          
                if(previous) 
                {
                    previous->next = current->next;
                }
            }
        }   
        hashLinkDelete(current);
        map->size--;
    }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map!=0);
    assert(key!=0);
    int idx = HASH_FUNCTION(key) % hashMapCapacity(map);
        if (idx < 0) {
            idx += hashMapCapacity(map);
        }
    //int *compare = hashMapGet(map,key);
   // if(compare != NULL){
    HashLink* current = map->table[idx];
    while(current!=NULL){
        if(current->key == key)
        {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    assert(map!=0);

    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
    assert(map!=0);
    return hashMapCapacity(map)- hashMapSize(map);
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    assert(map!=0);
    float size = (float) hashMapSize(map);
    float cap = (float) hashMapCapacity(map);

    return size / cap;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < hashMapCapacity(map); i++)
    {
        struct HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf("(%s: %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
