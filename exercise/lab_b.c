/****************************************************************************
 The purpose of this example is to exercise, creating, using and destroying
 pass by pointer and pass by value data structures
 
 student version 
 
 gcc -O1 -Wall -std=c99 -pedantic -g  lab_a.c -o lab_a
 valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./lab_a
 
 
 09/09/2019 R. Repka    Minor formatting changes
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*---------------------------------------------------------------------------
  The polynomial data structure contains the number of (size) of the
  allocated array of polynomial coefficients 
  e.g     nterms = 4;
          polyCoef = malloc(sizeof(double)*4);    
---------------------------------------------------------------------------*/
typedef struct {
    unsigned int nterms;      /* number of terms */
    double *polyCoef;         /* coefficients         */
} Poly;

// Function prototypes
void createPoly(Poly *p, int n);
Poly *createPoly_p(int n);
void destroyPoly(Poly *p);
void destroyPoly_p(Poly *p);
void printPolyRef(Poly *p);
void printPolyVal(Poly data);

int main(int argc, char *argv[]) {
   Poly stackPoly;         // Stack data structure
   Poly *poly_p;           // Pointer 
   poly_p = malloc(sizeof(double)*10);

   createPoly(&stackPoly, 10);  // Create and use the data structure
   printPolyRef(&stackPoly);  // Print using pass by pointer AND value
   printPolyVal(stackPoly);
   destroyPoly(&stackPoly);
   
   poly_p = createPoly_p(10);   // Create and use the pointer as a data structure
   printPolyRef(poly_p);   // Print using pass by pointer AND value
   printPolyVal(*poly_p);
   destroyPoly(&stackPoly);
   destroyPoly_p(poly_p);

   poly_p = malloc(sizeof(Poly));
   createPoly(poly_p,10); 
   printPolyRef(poly_p);
   printPolyVal(*poly_p); 
   destroyPoly(poly_p);
   free(poly_p);
   poly_p = NULL;
   return 0;
}

/*---------------------------------------------------------------------------
  Create a test polynomial using a pointer to the data structure
---------------------------------------------------------------------------*/
void createPoly(Poly *p, int n) {
	p->nterms = n;
	p->polyCoef = malloc(sizeof(double) * n);
	if (NULL == p->polyCoef) {
	fprintf(stderr, "malloc error\n");
	exit(9);
	}
	for (int i=0; i<n; i++) {
	p->polyCoef[i] = i*2;
}
	   
}


/*---------------------------------------------------------------------------
  Create a test polynomial using a pointer to the data structure
---------------------------------------------------------------------------*/
// Destroy data structure based test polynomial 
void destroyPoly(Poly *p){
	free(p->polyCoef); 
	p->polyCoef = NULL;
}

/*---------------------------------------------------------------------------
  Create a test polynomial returning a pointer to the data structure
---------------------------------------------------------------------------*/
Poly *createPoly_p(int n){
	Poly *p = malloc(sizeof(Poly));
	if (NULL == p) {
	fprintf(stderr, "malloc error\n");
	exit(9);
	} 
	p->nterms = n;
	p->polyCoef = malloc(sizeof(double) * n);
	if (NULL == p->polyCoef) {
	fprintf(stderr, "malloc error\n");
	exit(9);
	}
	for (int i=0; i<n; i++) {
	p->polyCoef[i] = i*2;
}	
	return(p); 
}

/*---------------------------------------------------------------------------
  Destroy pointer based test polynomial 
---------------------------------------------------------------------------*/
void destroyPoly_p(Poly *p){
free(p->polyCoef);
p->polyCoef = NULL;
free(p);
p = NULL;
	   
}

/*---------------------------------------------------------------------------
  Prints the polynomial data passing by reference
---------------------------------------------------------------------------*/
void printPolyRef(Poly *p){
	printf("Print poly by reference: ");	
	for(int i=0; i<p->nterms; i++) {
	   printf("%2.0f ", p->polyCoef[i]);  //%2.0f means print so that
					//theres 2 spaces before the decimal 
	} 				// and 0 spaces after so basically
	printf("\n");			// like 02. but shows up as 2
}

/*---------------------------------------------------------------------------
  Prints the polynomial data passing by value
---------------------------------------------------------------------------*/
void printPolyVal(Poly data){
 printf("Print poly by value: ");
 for (int i=0; i<data.nterms; i++) {
    printf("%2.0f ",data.polyCoef[i]);
 }  
 printf("\n");
}



