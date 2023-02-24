#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "grid.h"
#include "function.h"
#include <assert.h>
#include "easyppm.h"
#include <math.h>

int M;
int N;
int T;


static double calculProba(double d){
	assert(d >= 0 && d <= 1);
	
	int count = 0;
	int a = 0;
	
	for(int i = 0; i < T; i++){
		Grid *gridTest = gridCreate(M,N,d);
		
		assert(gridTest != NULL);
		
		a = gridHasPercolated(gridTest);
		count = count + a;
		
		gridDestroy(gridTest);
	}
	
	double proba = (double)count / T;

	return proba;
}



int main(int argc, char *argv[]) {
    if (argc != 4) {
        return -1;
    }
    
    int gridHeight = atoi(argv[1]); 
    int gridWidth = atoi(argv[2]); 
    int nbrTrial = atoi(argv[3]);

    M = gridHeight;
    N = gridWidth;
    T = nbrTrial;

    time_t t;
    srand((unsigned) time(&t));

   	char fileName[100];
    snprintf(fileName, sizeof(fileName), "percolation-plot-%d-%d-%d.txt", M, N, T);
	
	double xMin = 0;
	double xMax = 1;
	double minErrorX = 0.01; 
	double maxErrorX = 0.7;
	double minErrorY = 0.01;
	
	functionPlot(fileName, calculProba, xMin, xMax, minErrorX, maxErrorX, minErrorY);
	
	double fvalue = 0.5;
	double tolerance = 0.01;
	
	double val = functionGetVal(calculProba, fvalue, xMin, xMax, tolerance);
   	printf("P,%d,%d (d) = 0.5 ===> d =  %f \n", N, M, val);

    return 0;
}
