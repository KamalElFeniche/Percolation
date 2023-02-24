#include "function.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double functionGetVal(double (*f) (double), double fvalue, double xMin, double xMax, double tolerance){
	assert(f != NULL);

	double fMin = f(xMin);
	double fMax = f(xMax);
	
	assert((fMin-fvalue) * (fMax-fvalue) < 0);
	
	if (xMax < xMin) {
		
		double tmp = xMax;
		xMax = xMin;
		xMin = tmp;
	}

	double xMid;
	
	while (xMax - xMin > tolerance) {
		
		xMid = (xMin + xMax)/2;
		
		if ((fMin-fvalue) * (f(xMid)-fvalue) <= 0) {
			
			xMax = xMid;
		
		} else {
			
			xMin = xMid;
		}
	}

	return (xMax+ xMin)/2;	
}


static void recurFunctionPlot(FILE *fp, double (* f)(double), double xMin, double xMax,
double minErrorX, double maxErrorX, double minErrorY){
	assert(fp != NULL && f != NULL);

	if (fabs(xMax-xMin) < minErrorX)
		return;
	
	double xMid= (xMin+xMax)/2;
	double fMid = f(xMid); 
	
	if (fabs(xMax-xMin) >= maxErrorX || fabs(fMid - (f(xMin)+f(xMax))/2) > minErrorY) {
		
		recurFunctionPlot(fp, f, xMin, xMid, minErrorX, maxErrorX, minErrorY);
		
		fprintf(fp, "%lf %lf \n", xMid, fMid);
		
		recurFunctionPlot(fp, f, xMid, xMax, minErrorX, maxErrorX, minErrorY);
		
	}	
}


void functionPlot(char *fileName, double (* f)(double), double xMin, double xMax,
double minErrorX, double maxErrorX, double minErrorY){
	assert( fileName != NULL && f != NULL);
	
	if (xMin > xMax) {
		
		double tmp = xMax;
		xMax = xMin;
		xMin = tmp;
	}

	FILE *fp;		
	fp=fopen(fileName, "w");
		
	assert(fp != NULL);
	
	fprintf(fp, "%lf %lf \n", xMin, f(xMin));
	
	recurFunctionPlot(fp, f, xMin, xMax, minErrorX, maxErrorX, minErrorY);

	fprintf(fp, "%lf %lf", xMax, f(xMax));
	
	fclose(fp);
}

