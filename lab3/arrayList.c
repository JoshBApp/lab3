#include <stdlib.h>
#include <stdio.h>
#include "arrayList.h"
#include <string.h>
//getSize not accessed outside of this file so declare it to be static
//static essentially makes it private to this file
static int getSize(primitiveType type);

arrayList * initialize(primitiveType type)
    {   
           //dynamically allocate an array
        arrayList* array = (arrayList*)malloc(sizeof(arrayList));

        //set the array sizes to the values needed
        array->numElements = 0;
        array->arraySize= 4;
        array->type = type;
         array->elementSize = getSize(type);

        array->array = (void*)malloc(array->elementSize * array->arraySize);
        return array;
        
    }
int getSize(primitiveType type)
{
    switch(type)
    {
        case charType: return sizeof(char);
        case shortType: return sizeof(short);
        case intType: return sizeof(int);
    }

    //what if its not one of them..how??
    return -1;

}
void addElement(arrayList * array, void * element)
{
    if(array->numElements == array->arraySize)
    {
        //the array was too large so make a new one 2x the size
        int newSize = array->arraySize * 2;
        void* newArray = (void*)malloc(newSize * array->elementSize);

        //copy step
        memcpy(newArray, array->array, array->arraySize * array->elementSize);
        free(array->array);
        array->array = newArray;
        array->arraySize =newSize;
    }

    //depending on the type put in the positon
    switch(array->type)
    {
        case charType:
        {
            char* cher = (char*)(array->array);
            char* elePtr = (char*)element;
            cher[array->numElements]= *elePtr;
            break;

        }
        
        case shortType:
        {
            short* sho = (short*)(array->array);
            short* shElePtr = (short*)element;
            sho[array->numElements] = *shElePtr;
            break;
        }

        case intType:
        {
            int* in = (int*)(array->array);
            int* inElePtr = (int*)element;
            in[array->numElements] = *inElePtr;
            break;
        }
       }
        array->numElements++;
}


void removeElement(arrayList * array, int index)
{
    int i;
    for(i= index; i < array->numElements - 1; i++)
    {
        switch(array->type)
        {
            case charType:
            {
                char* c = (char*) array->array;
                c[i] = c[i + 1];
                break;
               
            }

            case shortType:
            {
                short* s = (short*) array->array;
                s[i] = s[i+1];
                break;
            }

            case intType:
            {
                int* h = (int*) array->array;
                h[i] = h[i+1];
                break;

            }
        }
     }
        array->numElements--;

    

}
void printArray(arrayList * arylstP)
{

int i;
printf("array size: %d, num elements: %d contents: ",
arylstP->arraySize, arylstP->numElements);
for (i = 0; i < arylstP->numElements; i++)
    {
    if (arylstP->type == charType)
    {
        printf("%02x ",((char *) (arylstP ->array))[i] & 0xff);
    }

    else if (arylstP->type == shortType)
    {
    //fill in the missing code that gets the element and &s it with 0xffff
    
    printf("%04x ", ((short *) (arylstP-> array))[i] & 0xffff);
    }
    else if (arylstP->type == intType)
    {
    printf("%08x ", ((int *)(arylstP->array))[i] & 0xffffffff);
    }
    }
    printf("\n");
}
