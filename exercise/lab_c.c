/****************************************************************************
 The purpose of this example is to exercise, using pointers
 
 student version 
 
 gcc -O1 -Wall -std=c99 -pedantic -g  lab_c.c -o lab_c
 valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./lab_c
 
 09/09/2019 R. Repka    Minor formatting changes
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*---------------------------------------------------------------------------
  These data structures are used to simulated a very simple linked list
---------------------------------------------------------------------------*/
typedef struct Node{
    int index;      
    struct Node *next;        
    char string[40]; //shortcut to malloc right away instead of doing char string and then malloc
} Node;

typedef struct {
    int nterms;      
    Node *front;         
} Wrapper;


// Function prototypes
void printList(Wrapper *wrapper_p);

int main(int argc, char *argv[]) {
   Wrapper *wrapper_p =(Wrapper *) malloc(sizeof(Wrapper));
	if (NULL == wrapper_p) {
	fprintf(stderr, "wrapper malloc failed");
	exit(9);
	}
   Node *node_p;
   Node *temp_p;
   
    // Wire the first node in
   node_p = NULL;
   node_p = (Node*)malloc(sizeof(Node));
	if(NULL == node_p) {
	fprintf(stderr, "node_p malloc failed");
	exit(9);
	}
   node_p->index = 1;
   /*
   node_p->string[40] = (char*)malloc(sizeof(char) * 40);
	if(NULL == node_p->string) {
	fprintf(stderr, "string malloc failed");
	exit(9);
	}
   */
   strncpy(node_p->string, "one", 40);
   node_p->next = NULL;  
   wrapper_p->front = node_p;    
   printf("Printing 1 node linked list\n");
   printList(wrapper_p);  
   
     // Wire the second node in 
   temp_p = NULL;
   temp_p = (Node*)malloc(sizeof(Node));
	if (NULL == temp_p) {
	fprintf(stderr, "temp_p malloc failed");
	exit(9);
	}  
   node_p->next = temp_p; 
   temp_p->index = 2;
   temp_p->next = NULL;
   strncpy(temp_p->string, "two", 40);
   printf("Printing 2 node linked list\n");
   printList(wrapper_p);

   // Clean up memory
   free(node_p->next);
   node_p->next = NULL;
   free(node_p);
   node_p = NULL;
   free(wrapper_p);
   wrapper_p = NULL;
      
   return 0;
}

// Walk the linked list and print the contents 
void printList(Wrapper *wrapper_p) {
   Node *currentNode = wrapper_p->front;
//Wrapper *currentNode = wrapper_p;  //current is pointer to keep track of node currently printing
   int nodeNum = 1;
   while (currentNode != NULL) {
      printf("node %d contains the string '%s'\n", nodeNum, currentNode->string);
      currentNode = currentNode->next;
      nodeNum = nodeNum + 1;
  }
}
