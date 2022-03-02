#include <iostream>
#include "Numerique.h"
#include "math.h"
#include "MathLibC.h"

using namespace std;

/*--------------------------------------------------------------------------*/
/* D�finition du jacobien num�rique	    									*/
/*--------------------------------------------------------------------------*/
void JAC_NUM(double* x, double* f, double** jacob, int ndim, double pas,
	void (*syst) (double*, double*, double*), double* parametre)
{
	int i, j;
	double* g;
	double u;

	// Allocation dynamique de g
	// -------------------------
	g = new double[ndim + 1];

	for (j = 1; j <= ndim; j++)
	{
		u = x[j];
		x[j] = x[j] + x[j] * pas;

		for (i = 1; i <= ndim; i++)
		{
			syst(x, g, parametre);
			jacob[i][j] = (g[i] - f[i]) / pas / u;
		}
		x[j] = u;
	}
	delete[] g;
}


/*-------------------------------------------------------------------------------*/
/*			Fonction permettant de calculer la norme Euclidienne				 */
/*					d'un vecteur de dimension ndim								 */
/*-------------------------------------------------------------------------------*/
double norme(double *x, int ndim)
{
	int i;
	double norm = 0;

	for (i=1; i<=ndim; i++)
	{
		norm = norm +  pow(x[i],2);
	}

	norm = sqrt (norm);
	return (norm);
}

/*----------------------------------------------------------------------------*/
/* Fonction visant � rechercher la composante maximal d'un vecteur de r�els   */
/*----------------------------------------------------------------------------*/
double maxi(double* Tab, int ndim)
{
	int i;
	double max;

	max = Tab[1];

	for (i = 2; i <= ndim; i++)
	{
		if (Tab[i] > max)
		{
			max = Tab[i];
		}
	}
	return (max);
}


/*--------------------------------------------------------------------------*/
/* Sous-programme de r�solution d'un syst�me d'�quations non-lin�aires		*/
/* par la m�thode de Newton-Raphson											*/
/*																			*/
/* AUTEURS :G.HETREUX 								               			*/
/* DATE : 25/02/2001														*/
// ARGUMENTS																//
//																			//
// int dim : Dimension du syst�me � r�soudre                                //
// int itemax : Nombre maximum d'it�rations si                              //
//              aucune convergence/stagnation                               //
//                                                                          //
// int* ite : compteur d'iterations                                         //
// double* crit_conver : crit�re de convergence (epsilon 1)                 //
// double* crit_arret : crit�re de stagnation (epsilon 2)                   //
// double* sol : vecteur solution calcul� au cours de la m�thode            //
// int derivee : choix sur le mode de calcul                                //
//               du jacobien (1 : Analytique, 2: Num�rique)                 //
//                                                                          //
// double pas : pas utilis� pour la calcul du jacobien num�rique            //
// int relax : choix sur le mode de relaxation                              //
//             (1 : pas de relaxation, 2 : relaxation num�rique)            // 
//                                                                          //
// enum STATUT* statut : Indicateur sur le statut de la m�thode             //
//                       (EN_COURS, CONVERGENCE,                            //
//                       STAGNATION_DU_PAS, NBRE_ITERATION_DEPASSE)         //
//                                                                          //
// void (*syst) (double*, double*, double*) : Nom de la fonction            //
//                                            repr�sentant le syst�me �     //
//                                            r�soudre (voir Fonctions.cpp) //
//                                                                          //
// void (*syst) (double*, double*, double*) : Nom de la fonction            //
//                         repr�sentant le jacobien analytique du syst�me   //
//                         � r�soudre (voir Fonctions.cpp)                  //
//                                                                          //
// double* Fsol : Valeur du syst�me � la solution                           //
// double* parametre : vecteur de param�tres � passer aux syst�mes          //
//                     param�tr�s                                           //
//                                                                          //
// VARIABLES                                                                //
//                                                                          //
// int i, ite_relax : compteurs                                             //
// Deter : Indique si le d�terminant de la matrice                          //
//         jacobienne a pu etre calcul�                                     //
//                                                                          //
// Norme : Norme de Fsol (ou F_relax)                                       //
// alpha : coefficient de la relaxation num�rique                           //
// pivot_min : zero de la m�thode du pivot (DMRINV)                         //
// type_calcul : Pr�cision sur le choix de calcul                           //
//               � employer pour MRINV (voir MathLibC.h)                    //
//                                                                          //
// A : Matrice � inverser repr�sentant le syst�me d'equations lin�aires     //
// H : Pas calcul� par r�solution du syst�me d'�quations lin�aires          //
// Y : Vecteur solution mis � jour                                          //
// Evol : Vecteur repr�sentant l'�volution de la solution                   //
//        d'une it�ration sur l'autre                                       //
//                                                                          //
// F_relax : Valeur du syst�me au cours de la relaxation                    //
//                                                                          //
/*--------------------------------------------------------------------------*/
void newton_raph(int ndim, int itemax, int* ite, double* crit_conver, double* crit_arret,
	double* sol, int derivee, double pas, int relax, enum STATUT* statut, void (*syst) (double*, double*, double*),
	void (*JAC) (double*, double**, double*), double* Fsol, double* parametre)
{
	int i, ite_relax;
	double Deter;
	double Norme;
	double alpha;

	const double pivot_min = 1e-30;
	const int type_calcul = 1;

	// Declaration et allocation dynamique des tableaux de travail 
	double** A; // matrice de dimension (n, n+1)
	double* H; // vecteur de dimension n
	double* Y; // vecteur de dimension n
	double* Evol; // vecteur de dimension 
	double* F_relax;

	H = new double[ndim + 1];
	Y = new double[ndim + 1];
	Evol = new double[ndim + 1];
	F_relax = new double[ndim + 1];

	A = new double* [ndim + 1];
	for (i = 1; i <= ndim; i++)
	{
		A[i] = new double[ndim + 1 + 1];
	}


	// D�but de la boucle de calcul - Initialisation
	*ite = 0;
	syst(sol, Fsol, parametre); // Intitialisation de F
	Norme = norme(Fsol, ndim); // Initialisation de la norme de F
	*statut = EN_COURS; // Initialisation du statut de la m�thode

	do
	{
		//  Test sur le crit�re de convergence
		if (Norme > *crit_conver)
		{
			(*ite)++; // Incr�ment du nombre d'it�rations
			if (*ite <= itemax)
			{
				// Calcul du Jacobien
				switch (derivee)
				{
				case 1: // Jacobien analytique
					JAC(sol, A, parametre);
					break;
				case 2: // Jacobien num�rique
					JAC_NUM(sol, Fsol, A, ndim, pas, syst, parametre);
					break;
				}
				// Remplissage de la matrice A : d�finition du syst�me d'�quations lin�aires
				for (i = 1; i <= ndim; i++)
				{
					A[i][ndim + 1] = -Fsol[i];
				}

				// Appel a Mrinv : proc�dure de r�solution de systeme d'equations lineaires
				MRINV(A, A, ndim, 0, Deter, pivot_min, H, type_calcul);

				// Calcul de sol au pas suivant
				switch (relax)
				{
				case 1: // Pas de ralaxation
					for (i = 1; i <= ndim; i++)
					{
						Y[i] = sol[i] + H[i];
					}
					break;
				case 2: // Relaxation num�rique
					alpha = 1; // Initialisation du coefficient alpha
					ite_relax = 0;
					do {
						for (i = 1; i <= ndim; i++)
						{
							Y[i] = sol[i] + alpha * H[i]; // Calcul de la nouvelle solution
						}
						syst(Y, F_relax, parametre); // Evaluation de F
						alpha = alpha / 2.; // Relaxation par r�duction du param�tre alpha
						ite_relax++; // On incr�mente le compteur
					} while (norme(F_relax, ndim) > Norme && ite_relax < 5); // Tant que la norme du nouveau F (F_relax)
																			 //est sup�rieure � l'ancienne

				}


				// Calcul de l'�volution entre deux it�rations
				for (i = 1; i <= ndim; i++)
				{
					Evol[i] = fabs((Y[i] - sol[i]) / sol[i]);
				}

				// Si la m�thode ne stagne pas, on met � jour la solution
				if (maxi(Evol, ndim) > *crit_arret)
				{
					for (i = 1; i <= ndim; i++)
					{
						sol[i] = Y[i];
					}
					syst(sol, Fsol, parametre); // Mise � jour de F
					Norme = norme(Fsol, ndim); // Mise � jour de la norme de F
					cout << Norme << endl;
				}
				else
				{
					*statut = STAGNATION_DU_PAS;
				}
			}
			else
			{
				*statut = NBRE_ITERATION_DEPASSE;
			}

		}
		else
		{
			*statut = CONVERGENCE;
		}

	} while (*statut == EN_COURS);

	// Mise � jour des param�tres de sortie
	*crit_arret = maxi(Evol, ndim);
	*crit_conver = Norme;

	// Destruction des structures dynamiques
	delete[] H;
	delete[] Evol;
	delete[] Y;
	delete[] F_relax;

	for (i = 1; i <= ndim; i++)
	{
		delete[] A[i];
	}
	delete[] A;
}

/*-------------------------------------------------------------------------------*/
/*			Fonction qui retourne l'indice ligne de la valeur maximale           */
/*					    de la colonne d'une matrice			        	     	 */
// ARGUMENTS :                                                                   //
// int** matrix : Matrice dans laquelle est faite la recherche                   //
// int col : indice de la colonne concern�e par la recherche                     //
// int n_lig : nombre de lignes de la matrice                                    //
// SORTIE :                                                                      //
// int max : indice de l'�l�ment le plus grand de la colonne                     //
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