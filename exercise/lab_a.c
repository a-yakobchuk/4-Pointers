/****************************************************************************
 The purpose of this example is to exercise using data and function pointers.
 It also demonstrates the value of using NULL assignments to identify pointer
 issues.
 
 student version 
 
 
 gcc -O1 -Wall -std=c99 -pedantic -g  lab_b.c -o lab_b
 valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./lab_b
 
 
 09/09/2019 R. Repka    Minor formatting changes
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { 
   int entry;
   char string [40];
} Data;

int fun2x(int num);
int fun3x(int num);

Data ramData;


int main(int argc, char *argv[]) {
   int(*function_p)(int);
   int answer;
   Data stackData;
   static Data staticData;
   Data *heapData_p;

   heapData_p = (Data *)malloc(sizeof(Data));   //allocate space for heapData_p
     if (NULL == heapData_p) {	//check mem alloc
	fprintf(stderr, "failed heapData malloc");
	exit(9);
	}
   printf("Program %8p\n", main);   // Print out the addresses of items
   printf("Static data %8p\n", staticData);   // Print out the addresses of items
   printf("Ram data %8p\n", ramData);   // Print out the addresses of items
   printf("Heap data %8p\n", heapData_p);   // Print out the addresses of items
   printf("Stack data %8p\n", stackData);   // Print out the addresses of items

   int i;
   i = fun2x(2);    //call fun2x and pass 2 into it
	printf("Passing the 2X function a %d, I got %d\n", 2, i);
   int y;
   y = fun3x(2);
	printf("Passing the 3X function a %d, I got %d\n", 2, y);
	         
    // Using function pointers
   
   stackData.entry = 1;   // Initialize the stack data
  // strncpy(&stackData.string[0], "Stack", 39); //identical as next line 
   strncpy(stackData.string, "Stack", 39); 
	printf("Heap data values before free: %d %s\n", stackData.entry, stackData.string);
    // Initialize the heap data, free it and use it
   heapData_p -> entry = 2; 
   strncpy(heapData_p->string, "Pointer", 39); 
	printf("Heap data values before free: %d %s\n", heapData_p->entry, heapData_p->string);
   
   free(heapData_p);
   //heapData_p = NULL;
   printf("Heap data values after free: %d %s\n", heapData_p->entry, heapData_p->string);
   return 0;
}


int fun2x(int num) { 
   return(num*2);
}
int fun3x(int num) {
   return(num*3);
}
