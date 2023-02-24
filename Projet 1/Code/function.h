/*----------------------------------------------------------------------------*
*
*  functionPlot: enregistre dans un fichier texte une liste de paires (x, f(x))
* permettant de tracer la courbe f(x) entre les points xMin et xMax.
*
*                     INPUTS: fileName   un pointeur valide vers une chaîne de
* caractères
*                             f          un pointeur de fonction valide
*                             xMin       l'abcisse minimale
*                             xMax       l'abcisse maximale
*                             minErrorX  la distance minimale entre 2 points
*                             maxErrorX  assure que la fonction sera évaluée
* en un minimum de points
*                             minErrorY  tolérance sur l'ordonnée
*
*
*                     OUTPUTS: Un fichier texte nommé "fileName" est créé et 
* contient les valeurs de la fonction entre xMin et xMax.                              
*
*
*  functionGetVal: fonction renvoyant la valeur de x comprise entre xMin et 
* Xmax tel que f(x) = fValue à une tolérance près.
*
*                     INPUTS:  f           un pointeur valide vers une fonction 
* de type double.
*
*                            fValue       la valeur de la fonction dont on
* souhaite connaitre l'abscice.
*
*                            xMin et xMax les bornes respectivement inférieure
* et supérieur de l'intervalle que l'on considère
*
*                            tolerance    la précision sur la solution
*
*
*                     OUTPUTS: la valeur de x, à une tolérance près, tel 
* que: f(x) = fValue.
*
*-----------------------------------------------------------------------------*               
*/

#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <stdio.h>

double functionGetVal(double (*f) (double), double fvalue, double xMin, double xMax, double tolerance);


void functionPlot(char *fileName, double (* f)(double), double xMin, double xMax,
double minErrorX, double maxErrorX, double minErrorY);

#endif