/*----------------------------------------------------------------------------*
 *!!!!!!Les numéro de ligne et de colonnes sont numérotées à partir de 0 !!!!!!
 *
 *
 *  gridCreate: Crée un pointeur de type Grid contenant une grille
 * de taille n par m et dont la densité de cases ouvertes est égale à d.
 *               	  
 *                    INPUTS:  n 		 Le nombre de lignes de la grille
 *                             m         Le nombre de colonnes de la grille
 *                             d         La densité de cases ouvertes compris
 * entre 0 et 1
 * 
 *                    OUTPUTS: new_grid  le pointeur vers la variable de type 
 * de type Grid souhaitéé ou NULL
 * 
 *
 *
 *  gridDestroy: Libère l'espace en mémoire pris par la grille
 *
 *                    INPUTS:  g         un pointeur valide vers une variable
 * de type Grid
 *
 *                    OUTPUTS: /
 *
 *
 *  gridGetWith: Renvoie la largeur de la grille.
 *                    
 *                    INPUTS:  g         un pointeur valide vers une variable
 * de type Grid
 *
 *                    OUTPUTS: la largeur de la grille
 *
 *
 *  gridGetHeight: Renvoie la hauteur de la grille.
 * 
 *                    INPUTS:  g         un pointeur valide vers une variable
 * de type Grid
 *
 *                    OUTPUTS: la hauteur de la grille
 *
 *
 *  gridIsCellOpen:  Renvoie 1 si la cellule ciblée est ouverte, 0 sinon.
 *
 *                    INPUTS:  g          un pointeur valide vers une vraiable
 * de type Grid
 *                             i          un numéro de ligne valide
 *                             j          un numéro de colonne valide
 *
 *                    OUTPUTS:   1 si la cellule ciblée est ouverte, 0 sinon.
 *
 *
 *  gridIsCellClosed: Renvoie 1 si la cellule ciblée est fermée, 0 sinon.
 *
 *                    INPUTS:  g          un pointeur valide vers une variable
 * de type Grid 
 *                             i          un numéro de ligne valide
 *                             j          un numéro de colonne valide
 *
 *                    OUTPUTS:   1 si la cellule ciblée est fermée, 0 sinon.
 *
 *
 *  gridIsCellFull: Renvoie 1 si la cellule ciblée est remplie, 0 sinon.
 *
 *                    INPUTS:  g         un pointeur valide vers une variable 
 * de type Grid qui a déjà été appelée par la fonction gridHasPercolated  
 *                             i         un numéro de ligne valide
 *                             j         un numéro de colonne valide
 *
 *                    OUTPUTS:   1 si la cellule ciblée est remplie, 0 sinon.
 *
 *
 *  gridSetOpen: Marque la cellule ciblée comme ouverte.
 *
 *                    INPUTS: g         un pointeur valide vers une variable
 * de type Grid
 *                            i         un numéro de ligne valide
 *                            j         un numéro de colonne valide
 *                    
 *                    OUTPUTS:  la cellule (i,j) est marquée comme ouverte
 *
 *
 * gridSetClose: Marque la cellule ciblée comme fermée.
 *                
 *                    INPUTS: g         un pointeur valide vers une grille
 *                            i         un numéro de ligne valide
 *                            j         un numéro de colonne valide
 *
 *                    OUPUTS: la cellule (i,j) est marquée comme fermée
 *
 * gridSetFull: Marque la cellule ciblée comme remplie.
 *
 *                    INPUTS: g         un pointeur valide vers une grille
 *                            i         un numéro de ligne valide
 *                            j         un numéro de colonne valide
 *                    
 *                    OUTPUTS:  la cellule (i,j) est marquée comme remplie
 *
 *
 *
 *  gridHasPercolated: Vérifie si une grille donné en argument percole ou non
 *  après avoir marquée les cases remplies comme tel.
 *                    INPUTS: g          un pointeur valide vers une variable 
 * de type Grid
 *                    OUTPUTS: 1 si la grille percole, 0 sinon.
 *                               
 *
 *
 *  gridPrint: affiche la Grille sur la sortie standard à l'aide des caractères
 *            suivant: # , o et d'un espace
 *            où : # représente une cellule fermée.
 *                 o représente une cellule remplie.
 *                 l'espace représente une cellule ouverte non remplie.
 *
 *                    INPUTS: g          un pointeur valide vers une variable
 * de type Grid             
 *                    
 *                    OUTPUTS: /
 *
 *
 *  gridPrintPPM: génère un fichier ppm représentant la grille où une case noire
 *               représente une cellule fermée, une case blanche représente une
 *               cellule ouverte et une case bleu représente une cellule repmlie.
 *
 *                  INPUTS: g           un pointeur valide vers une variable 
 * de type Grid                         
 *                          fileName    une chaine de caractères contenant 
 * le nom du fichier qui sera généré.
 *                    
 *                  OUTPUTS: un fichier ppm nommé "fileName" représentant 
 * la grille.
 *-----------------------------------------------------------------------------*
 */

#ifndef GRID_H_
#define GRID_H_
#include "easyppm.h"

typedef struct Grid_t Grid;

Grid *gridCreate(int n, int m, double d);


void gridDestroy(Grid *g);


int gridGetWidth(Grid *g);


int gridGetHeight(Grid *g);


int gridIsCellOpen(Grid *g, int i, int j);


int gridIsCellClosed(Grid *g, int i, int j);


int gridIsCellFull(Grid *g, int i, int j);


void gridSetOpen(Grid *g, int i, int j);


void gridSetClosed(Grid *g, int i, int j);


void gridSetFull(Grid *g, int i, int j);


int gridHasPercolated(Grid *g);


void gridPrint(Grid *g);


void gridPrintPPM(Grid *g, char *fileName);



#endif