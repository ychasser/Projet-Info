#include <iostream>
#include "Tests.h"
#include "Numerique.h"
#include "RECUtilisateur.h"
#include "Partage.h"


int main()
{
	int i;
	int saisie, ndim;
	int itemax, ite;
	int derivee;
	int relax;

	enum STATUT statut;

	FILE* fichier;

	double pas;
	double crit_conver;
	double crit_arret;
	double* F;
	double* X;

	reseau.DefinirReseauFichier("Reseau2.txt"); // Définition du réseau

	fopen_s(&fichier, "InitREC2.txt", "r"); // Ouverture du fichier de configuration

	// Mode de saisie 
	cout << " Choississez votre mode de saisie des données " << endl;
	cout << " CLAVIER ----> 1 " << endl;
	cout << " FICHIER ----> 2 " << endl;

	cin >> saisie;

	if (saisie == 1)  // Lecture des informations saisies par le clavier
	{
		cout << "Dimension du probleme à traiter" << endl;
		cin >> ndim;
		cout << "Type de derivee employee " << endl;
		cout << "Derivee analytique ---->  taper 1  " << endl;
		cout << "Derivee numerique  ---->  taper 2  " << endl;
		cin >> derivee;

		
		if (derivee == 2)
		{
			printf("Donner la valeur du pas pour le calcul de la derivee \n");
			cin >> pas;
		}

		cout << "Relaxation ? " << endl;
		cout << "Pas de relaxation ---->  taper 1  " << endl;
		cout << "Relaxation numérique  ---->  taper 2  " << endl;
		cin >> relax;

		cout << "Valeur du critere d'arret : " << endl;
		cin >> crit_arret;
		cout << "Valeur du critere de convergence " << endl;
		cin >> crit_conver;
		cout << "Nombre maximal d'iterations " << endl;
		cin >> itemax;

	}
	else if (saisie == 2)  // Lecture de la configuration dans le fichier dédié
	{
		fscanf_s(fichier, "%d", &ndim);
		fscanf_s(fichier, "%d", &derivee);

		if (derivee == 2)
		{
			pas = 0.000001;
		}

		fscanf_s(fichier, "%d", &relax);
		fscanf_s(fichier, "%lf", &crit_arret);
		fscanf_s(fichier, "%lf", &crit_conver);
		fscanf_s(fichier, "%d", &itemax);

	}

	// Allocation dymamique de x et  F
	X = new double[ndim + 1];
	F = new double[ndim + 1];

	// Valeur d'initialisation
	if (saisie == 1) // Initialisation par le clavier
	{
		cout << "Valeur initiales du vecteur inconnu" << endl;
		for (i = 1; i <= ndim; i++)
		{
			cin >> X[i];
		}
	}
	else if (saisie == 2)
	{
		for (i = 1; i <= ndim; i++)
		{
			fscanf_s(fichier, "%lf", &(X[i]));
		}
		fclose(fichier);
	}

	// Appel à la procédure de calcul
	newton_raph(ndim, itemax, &ite, &crit_conver, &crit_arret, X, derivee, pas, relax, &statut, SystemeREC2, JacobienREC2, F);

	switch (statut) // Affichage du résultat
	{
	case CONVERGENCE:
		printf(" Le systeme a une solution (CONVERGENCE=%le,  ARRET=%le\n", crit_conver, crit_arret);
		for (i = 1; i <= ndim; i++)
		{
			cout << "X[" << i << "] = " << X[i] << endl;
			cout << "F[" << i << "] = " << F[i] << endl;
		}
		cout << "nbre d'iterations = " << ite << endl;
		break;

	case STAGNATION_DU_PAS:
		printf(" Le systeme n'a pas de solution : stagnation du pas \n (CONVERGENCE=%le,  ARRET=%le\n", crit_conver, crit_arret);
		for (i = 1; i <= ndim; i++)
		{
			cout << "X[" << i << "] = " << X[i] << endl;
			cout << "F[" << i << "] = " << F[i] << endl;
		}
		cout << "nbre d'iterations = " << ite << endl;
		break;

	case NBRE_ITERATION_DEPASSE:
		printf(" Nombre d'iteration dépasse \n (CONVERGENCE=%le,  ARRET=%le\n", crit_conver, crit_arret);
		for (i = 1; i <= ndim; i++)
		{
			cout << "X[" << i << "] = " << X[i] << endl;
			cout << "F[" << i << "] = " << F[i] << endl;
		}
		cout << "nbre d'iterations " << ite << endl;
		break;
	}
	delete[] X;
	delete[] F;
	
}
