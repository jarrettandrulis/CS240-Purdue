
#include <stdio.h>
#include <stdlib.h>

#include "rpn.h"

#define MAXCOLS 80
#define MAXROWS 40

char plot[MAXROWS][MAXCOLS];

void clearPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      plot[i][j] = ' ';
    }
  }
}

void printPlot()
{
  for (int i = MAXROWS-1; i >= 0 ; i--) {
    for (int j = 0; j < MAXCOLS; j++) {
      printf("%c", plot[i][j]);
    }
    printf("\n");
  }
}

void plotXY(int x, int y, char c) {
  if ( x <0 || x>=MAXCOLS || y < 0 || y >=MAXROWS) return;
  plot[y][x]=c;
}

void createPlot( char * funcFile, double minX, double maxX) {
  int nvals = MAXCOLS;
  double yy[MAXCOLS];
  double xx[MAXCOLS];
  clearPlot();
	int i = 0;
	while(i<MAXCOLS){
		double x = minX + (maxX-minX) * i / MAXCOLS; // X-value
		double y = rpn_eval(funcFile,x); // Y-value
		xx[i] = x;
		yy[i] = y;
		i++;
	}
	i = 0;
	double minY = yy[0];
	double maxY = yy[0];
	while(i < MAXCOLS){
		if(yy[i] > maxY)
			maxY = yy[i];
		if(yy[i] < minY)
			minY = yy[i];
		i++;
	}
	i = 0;
	while( i < MAXCOLS){
		if(minY < 0 && maxY > 0)
			plotXY(i,MAXROWS/2,'_');
		else if(maxY < 0)
			plotXY(i,MAXROWS,'_');
		else if(maxY > 0)
			plotXY(i,0,'_');	
		i++;
	}
	i = 0;
	while( i < MAXROWS){
		plotXY(MAXCOLS/2,i,'|');
		i++;
	}
	i = minX;
	while( i < MAXCOLS){
		int x = i;
		int y = (int) ((yy[i]-minY)*MAXROWS/(maxY-minY));
		plotXY(x,y,'*');
		i++;
	};
  // Evaluate function and store in vector yy

  //Compute maximum and minimum y in vector yy
  
  //Plot x axis

  //Plot y axis

  // Plot function. Use scaling.
  // minX is plotted at column 0 and maxX is plotted ar MAXCOLS-1
  // minY is plotted at row 0 and maxY is plotted at MAXROWS-1

  printPlot();

}

int main(int argc, char ** argv)
{
  printf("RPN Plotter.\n");
  if (argc < 4) {
    printf("Usage: plot func-file xmin xmax\n");
    exit(1);
  }
  int minX = atoi(argv[2]);
  int maxX = atoi(argv[3]);
  createPlot(argv[1],minX,maxX);

  // Get arguments
  
  //createPlot(funcName, minX, maxX);
}
