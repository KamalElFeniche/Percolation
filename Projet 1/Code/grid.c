/*
CONVENTION UTILISEE : 0 ------> cellule fermée
                      1 ------> cellule ouverte  
                      2 ------> cellule remplie

*/

#include "grid.h"
#include "easyppm.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

struct Grid_t{
	int n;                                      // nombre de lignes
	int m;                                      // nombre de colonnes
	int **grid;									// percolated = 1 == la fonction gridHasPercolated a déjà été appelée.
	int percolated;								// percolated = 0 == la fonction gridHasPercolated n'a pas encore été appelée.
};


Grid *gridCreate(int n, int m, double d){
	assert(n > 0 && m > 0  && d >= 0 && d <= 1);
	
	Grid *new_grid;
	
	new_grid = malloc(sizeof(Grid));
	if (new_grid == NULL)
	
		exit (-1);


	new_grid->grid = (int**)malloc(n*sizeof(int*)); 
	if (new_grid->grid == NULL) {
		
		free(new_grid);
		
		exit(-1);
	}
	
	int i;
	for (i = 0; i < n; i++) {
		new_grid->grid[i] = (int*)malloc(m*sizeof(int));
		
		if (new_grid->grid[i] == NULL) {
			int j;
			for (j = 0; j < i; j++) {
				free(new_grid->grid[j]);
			}
			free(new_grid->grid);
			free(new_grid);

			exit(-1);			
		}
	}
	
	new_grid->n = n;
	new_grid->m = m;
	new_grid->percolated = 0;
	
	if (d <= 0.5) {   // on ouvre les cases à partir d'une grille 
		int j= 0;		// où toutes les cases sont fermées de base
		i=0;
		
		for (i=0; i < n; i++)
			for (j = 0; j < m; j++)
				new_grid->grid[i][j] = 0;

	int numberOpenCell = ceil(d * n * m);
	
	int rand_1 = 0;
	int rand_2 = 0;
	
	i = 0;
	
	while (i < numberOpenCell) {
		rand_1 = rand()%n;
		rand_2 = rand()%m;
		
		if (new_grid->grid[rand_1][rand_2] != 1) {
			
			new_grid->grid[rand_1][rand_2] = 1;
			i++;
		} 		
	}
	return new_grid;
  	
  	} else {
  			                    // On ferme les cases à partir d'une grille
 								// où toutes les cases sont ouvertes de base
 		int j = 0;
 		i= 0;
 		
 		for (i=0; i < n; i++)
 			for (j = 0; j < m; j++)
 				new_grid->grid[i][j] = 1;
 		
 		int numberClosedCell = n * m - ceil(d * n * m);
 		
 		int rand_1 = 0;
 		int rand_2 = 0;
 		
 		i = 0;
 		
 		while (i < numberClosedCell){
 			
 			rand_1 = rand()%n;
 			rand_2 = rand()%m;
 			
 			if (new_grid->grid[rand_1][rand_2] != 0) {
 				
 				new_grid->grid[rand_1][rand_2] = 0;
 				i++;
 		}

 	
 	}
 	
 	return new_grid;
 	
 	}
}


void gridDestroy(Grid *g){
	assert(g != NULL);
	
	for (int i = 0; i < g->n ; i++)
		free(g->grid[i]);
	
	free(g->grid);
	
	free(g);
	
	return;

}


int gridGetWidth(Grid *g){
	assert(g !=NULL);
	
	return g->m;
}


int gridGetHeight(Grid *g){
	assert(g != NULL);
	
	return g->n;
}


int gridIsCellOpen(Grid *g, int i, int j){
	assert(g != NULL && i < g->n && i >= 0 && j < g->m && j >= 0);
	
	if (g->grid[i][j] == 1)
		
		return 1;
	
	return 0;
}


int gridIsCellClosed(Grid *g, int i, int j){
	assert(g != NULL && i < g->n && i >= 0 && j < g->m && j >= 0);
	
	if (g->grid[i][j] == 0)
		
		return 1;
	
	return 0;
}


int gridIsCellFull(Grid *g, int i, int j){
	assert(g != NULL && i < g->n && i >= 0 && j < g->m && j >= 0);
	
	if (g->percolated == 0)
		
		return 0;

	if (g->grid[i][j] == 2)
		
		return 1;

	return 0;
}


static void recurPercolated(Grid *g, int i, int j, int k){
 assert(g != NULL);

 assert(i >= 0 && i < g->n && j >= 0 && j < g->m);

 assert(k == 0 || k == 1);

  if (k == 0) {	   // Première fois que la fonction est appelée -> Cas de base
  	
  	for (int j = 0; j < g->m; j++) {
  		
  		if (g->grid[0][j] == 1) {	// Remplissage de la première ligne
  			g->grid[0][j] = 2;		// Si la case correspondante le permet
  			
  			if (g->grid[1][j] == 1) {
  				
  				g->grid[1][j] = 2;
  				recurPercolated(g, 1, j, 1);
  			}
  		}
  	
  	}

  	return;
  
  } else {         // Ce n'est pas la première fois que la fonction est appelée
  	
  	if (i+1 <= g->n-1) {
  		
  		if (g->grid[i+1][j] == 1) {
  			
  			g->grid[i+1][j] = 2;
  			recurPercolated(g, i+1, j, 1);
  		}
  	}
  	if (j+1 <= g->m-1) {
  		
  		if (g->grid[i][j+1] == 1) {
  			
  			g->grid[i][j+1] = 2;
  			recurPercolated(g, i, j+1, 1);
  		}
  	}
  	if (i-1 >= 0) {
  		
  		if (g->grid[i-1][j] == 1) {  		
  			
  			g->grid[i-1][j] = 2;
  			recurPercolated(g, i-1, j, 1);
  		}
 	}
  	if (j-1 >= 0) {
  		
  		if (g->grid[i][j-1] == 1) {
  			
  			g->grid[i][j-1] =2;
  			recurPercolated(g, i, j-1, 1);
  		}
  	}
  }
  return;
}


int gridHasPercolated(Grid *g){
	assert(g != NULL);
	
	assert(g->n > 0 && g->m > 0);
	
	if (g->n != 1) {
		
		recurPercolated(g, 0, 0, 0);  

		g->percolated = 1;

		for (int j=0; j < g->m; j++) {
		
			if (g->grid[g->n-1][j] == 2) {
				
				
				return 1;
			}
		}
	
	return 0;	 	
	
	} else {		// Si le nombre de ligne de la grille vaut 1 alors
					// il suffit de remplir les cases ouvertes
		for (int j = 0; j < g->m; j++) {
			
			if (g->grid[0][j] == 1)
				
				g->grid[0][j] = 2;
		}

		g->percolated = 1;
		
		for (int j = 0; j < g->m; j++) {
			
			if (g->grid[0][j] == 2) {
				
				
				return 1;
			}
		}

		return 0;
	}

}



void gridPrint(Grid *g){
	assert(g != NULL);
	
	for (int i = 0; i < g->n; i++) {
		
		printf("|");
		
		for (int j = 0; j < g->m; j++) {
			
			if (g->grid[i][j] == 0) {
				printf("#");
				
				}else{
					
					if (g->grid[i][j] == 1)
						printf(" ");
					
					else
						printf("o");
				}
			
		}
		
		printf("| \n");
	
	}
}


void gridSetOpen(Grid *g, int i, int j){
	assert(g != NULL && i < g->n && i >= 0 && j < g->m && j >= 0);
	
	g->grid[i][j] = 1;
	
	return;
}


void gridSetClosed(Grid *g, int i, int j){
	assert(g != NULL && i < g->n && i >= 0 && j < g->m && j >= 0);
	
	g->grid[i][j] = 0;
	
	return;
}


void gridSetFull(Grid *g, int i, int j){
	assert(g != NULL && i < g->n && i >= 0 && j < g->m && j >= 0);

	g->grid[i][j] = 2;
	
	return;
}


static void drawSquare(PPM *ppm, int x, int y, int length, ppmcolor colorFill){
	assert(ppm != NULL && length > 0);
	
	ppmcolor grey = easyppm_rgb(120, 120, 120);
	
	int i =0;
	int j=0;
	
	for (i = 0; i < length; i++) {
		
		easyppm_set(ppm, x, y+i, grey);  //"grey" correspond aux côtés du carré
		
		for (j = 1; j < length-2; j++) {
			
			if (i == 0 || i == length-1) {
				
				easyppm_set(ppm, x+j, y+i, grey);
			
			} else {
				
				easyppm_set(ppm, x+j, y+i, colorFill);
			}
		}

		easyppm_set(ppm, x + j, y + i, grey);
	
	}
}


void gridPrintPPM(Grid *g, char *fileName){
	assert(g != NULL);
	
	assert(fileName != NULL);
	
	int width = gridGetWidth(g);
	int height = gridGetHeight(g);
	int length = 10;   // Facteur permettant d'agrandir la longueur des côtés
	
	PPM ppm1 = easyppm_create(width * length, height * length, IMAGETYPE_PPM);
	
	easyppm_clear(&ppm1, easyppm_rgb(255, 255, 255));
	
	ppmcolor black = easyppm_rgb(0, 0, 0);
	ppmcolor white = easyppm_rgb(255, 255, 255);
	ppmcolor blue = easyppm_rgb(0, 0, 255);
	
	for (int i = 0; i < height; i++) {
		
		for (int j = 0; j < width; j++) {
			
			if (g->grid[i][j] == 0) {
				
				drawSquare(&ppm1, j * length, i * length, length, black);
			
			} else {
				
				if (g->grid[i][j] == 1) {
					
					drawSquare(&ppm1, j * length, i * length, length, white);
				
				} else {
					
					drawSquare(&ppm1, j * length, i * length, length, blue);
				}
			}
		}
	}
	
	easyppm_write(&ppm1, fileName);
}


