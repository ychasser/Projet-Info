#include <iostream>
#include "Numerique.h"
#include "math.h"

using namespace std;


/*-------------------------------------------------------------------------------*/
/*			Fonction qui retourne l'indice ligne de la valeur maximale           */
/*					    de la colonne d'une matrice			        	     	 */
// ARGUMENTS :                                                                   //
// int** matrix : Matrice dans laquelle est faite la recherche                   //
// int col : indice de la colonne concernée par la recherche                     //
// int n_lig : nombre de lignes de la matrice                                    //
// SORTIE :                                                                      //
// int max : indice de l'élément le plus grand de la colonne                     //
/*-------------------------------------------------------------------------------*/
int maxColMatrix(int** matrix, int col, int n_lig) {
	int max, imax;
	max = matrix[1][col];
	imax = 1;

	for (int i = 2; i <= n_lig; i++) {
		if (matrix[i][col] > max) {
			max = matrix[i][col];
			imax = i;
		}
	}
	return imax;
}