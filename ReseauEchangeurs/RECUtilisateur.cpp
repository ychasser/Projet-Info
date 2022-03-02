/**
 * Fichier de définition des fonctions propres aux réseaux d'échangeurs à simuler
 * Contient les fonctions suivantes :
 *  - SystemeREC1() : Système d'équations caractéristique du réseau 1
 *  - JacobienREC1() : Calcule la jacobienne analytique liée au réseau 1
 *  - SystemeREC2() : Système d'équations caractéristique du réseau 2
 *  - JacobienREC2() : Calcule la jacobienne analytique liée au réseau 2
 *
 * @author Yohann Chasseray
 * Date : 02/03/22
 * Contact: yohann.chasseray@gmail.com
 */

#pragma once
#include "RECUtilisateur.h"
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include "Partage.h"

using namespace std;

// Système d'équations caractéristique du réseau 1
void SystemeREC1(double X[8], double* F, double* param) {

	UnEchangeur ech;

	// Complétion des températures du réseau à partir du vecteur de variables X
	reseau.GetListeEch()[1].SetTsChaud(X[1]);
	reseau.GetListeEch()[1].SetTeFroid(X[3]);
	reseau.GetListeEch()[4].SetTeChaud(X[1]);
	reseau.GetListeEch()[4].SetTsFroid(X[2]);
	reseau.GetListeEch()[3].SetTeFroid(X[2]);
	reseau.GetListeEch()[3].SetTsFroid(X[3]);
	reseau.GetListeEch()[2].SetTsChaud(X[4]);
	reseau.GetListeEch()[3].SetTeChaud(X[4]);

	// Complétion des aires des échangeurs du réseau à partir du vecteur de variables X
	for (int i = 1; i <= reseau.GetNech(); i++) {
		reseau.GetListeEch()[i].SetAire(X[4 + i]);
	}

	// Bilans thermiques sur chacun des échangeurs -> Calcul des valeurs de F(X)
	for (int i = 1; i <= reseau.GetNech(); i++) {
		ech = reseau.GetListeEch()[i];
		F[2 * i] = ech.QF() - ech.GetCoeffU() * ech.GetAire() * ech.DTML();
		F[2 * i - 1] = ech.QF() - ech.QC();
	}
}

// Jacobienne analytique liée au réseau 1
void JacobienREC1(double X[8], double** Jac, double* param) {
	UnEchangeur ech;
	double fcp_f, fcp_c, aire, coeff_u;
	
	// Complétion des températures du réseau à partir du vecteur de variables X
	reseau.GetListeEch()[1].SetTsChaud(X[1]);
	reseau.GetListeEch()[1].SetTeFroid(X[3]);
	reseau.GetListeEch()[4].SetTeChaud(X[1]);
	reseau.GetListeEch()[4].SetTsFroid(X[2]);
	reseau.GetListeEch()[3].SetTeFroid(X[2]);
	reseau.GetListeEch()[3].SetTsFroid(X[3]);
	reseau.GetListeEch()[2].SetTsChaud(X[4]);
	reseau.GetListeEch()[3].SetTeChaud(X[4]);

	// Complétion des aires des échangeurs du réseau à partir du vecteur de variables X
	for (int i = 1; i <= reseau.GetNech(); i++) {
		reseau.GetListeEch()[i].SetAire(X[4 + i]);
	}
	
	// Coefficient de la jacobienne liés aux bilans du premier échangeur
	ech = reseau.GetListeEch()[1];
	fcp_f = ech.GetFluxFroid().GetFcp(); fcp_c = ech.GetFluxChaud().GetFcp();
	aire = ech.GetAire(); coeff_u = ech.GetCoeffU();
	Jac[1][1] = coeff_u * aire * ech.DeltaTmlD();
	Jac[1][3] = -fcp_c + coeff_u * aire * ech.DeltaTmlD();	
	Jac[1][5] = -coeff_u * ech.DTML();
	Jac[2][1] = fcp_c;
	Jac[2][3] = -fcp_f;

	// Coefficient de la jacobienne liés aux bilans du deuxième échangeur
	ech = reseau.GetListeEch()[2];
	fcp_f = ech.GetFluxFroid().GetFcp(); fcp_c = ech.GetFluxChaud().GetFcp();
	aire = ech.GetAire(); coeff_u = ech.GetCoeffU();
	Jac[3][4] = -coeff_u * aire * ech.DeltaTmlD();
	Jac[3][6] = -coeff_u * ech.DTML();
	Jac[4][4] = fcp_c;

	// Coefficient de la jacobienne liés aux bilans du troisième échangeur
	ech = reseau.GetListeEch()[3];
	fcp_f = ech.GetFluxFroid().GetFcp(); fcp_c = ech.GetFluxChaud().GetFcp(); 
	aire = ech.GetAire(); coeff_u = ech.GetCoeffU();
	Jac[5][2] = -fcp_f + coeff_u * aire * ech.DeltaTmlD();
	Jac[5][3] = fcp_f + coeff_u * aire * ech.DeltaTmlG();
	Jac[5][4] = -coeff_u * aire * ech.DeltaTmlG();
	Jac[5][7] = -coeff_u * ech.DTML();
	Jac[6][2] = -fcp_f;
	Jac[6][3] = fcp_f;
	Jac[6][4] = -fcp_c;

	// Coefficient de la jacobienne liés aux bilans du quatrième échangeur
	ech = reseau.GetListeEch()[4];
	fcp_f = ech.GetFluxFroid().GetFcp(); fcp_c = ech.GetFluxChaud().GetFcp();
	aire = ech.GetAire(); coeff_u = ech.GetCoeffU();
	Jac[7][1] = -coeff_u * aire * ech.DeltaTmlG();
	Jac[7][2] = fcp_f + coeff_u * aire * ech.DeltaTmlG();
	Jac[7][8] = -coeff_u * ech.DTML();
	Jac[8][1] = fcp_c;
	Jac[8][2] = fcp_f;

}

// Système d'équations caractéristique du réseau 2
void SystemeREC2(double X[7], double* F, double* param) {

	UnEchangeur ech;

	// Complétion des températures du réseau à partir du vecteur de variables X
	reseau.GetListeEch()[3].SetTsChaud(X[1]);
	reseau.GetListeEch()[4].SetTeChaud(X[1]);
	reseau.GetListeEch()[4].SetTsFroid(X[2]);
	reseau.GetListeEch()[2].SetTeFroid(X[2]);
	reseau.GetListeEch()[3].SetTsFroid(X[3]);
	reseau.GetListeEch()[1].SetTeFroid(X[3]);
	reseau.GetListeEch()[1].SetTsChaud(105); // Cas particulier ou une température est fixée
	reseau.GetListeEch()[2].SetTeChaud(105); // Cas particulier ou une température est fixée

	// Complétion des aires des échangeurs du réseau à partir du vecteur de variables X
	for (int i = 1; i <= reseau.GetNech(); i++) {
		reseau.GetListeEch()[i].SetAire(X[3 + i]);
	}

	// Bilans thermiques sur chacun des échangeurs -> Calcul des valeurs de F(X)
	for (int i = 1; i <= reseau.GetNech()-1; i++) {
		ech = reseau.GetListeEch()[i];
		F[2 * i - 1] = ech.QF() - ech.GetCoeffU() * ech.GetAire() * ech.DTML();
		F[2 * i] = ech.QF() - ech.QC();
	}
	ech = reseau.GetListeEch()[4];
	F[7] = ech.QF() - ech.GetCoeffU() * ech.GetAire() * ech.DTML();

}

// Jacobienne analytique liée au réseau 2
void JacobienREC2(double X[7], double** Jac, double* param) {
	UnEchangeur ech;
	double fcp_f, fcp_c, aire, coeff_u;

	// Complétion des températures du réseau à partir du vecteur de variables X
	reseau.GetListeEch()[3].SetTsChaud(X[1]);
	reseau.GetListeEch()[4].SetTeChaud(X[1]);
	reseau.GetListeEch()[4].SetTsFroid(X[2]);
	reseau.GetListeEch()[2].SetTeFroid(X[2]);
	reseau.GetListeEch()[3].SetTsFroid(X[3]);
	reseau.GetListeEch()[1].SetTeFroid(X[3]);
	reseau.GetListeEch()[1].SetTsChaud(105); // Cas particulier ou une température est fixée
	reseau.GetListeEch()[2].SetTeChaud(105); // Cas particulier ou une température est fixée

	// Complétion des aires des échangeurs du réseau à partir du vecteur de variables X
	for (int i = 1; i <= reseau.GetNech(); i++) {
		reseau.GetListeEch()[i].SetAire(X[3 + i]);
	}

	// Coefficient de la jacobienne liés aux bilans du premier échangeur
	ech = reseau.GetListeEch()[1];
	fcp_f = ech.GetFluxFroid().GetFcp(); fcp_c = ech.GetFluxChaud().GetFcp();
	aire = ech.GetAire(); coeff_u = ech.GetCoeffU();
	Jac[1][3] = -fcp_f + coeff_u * aire * ech.DeltaTmlD();
	Jac[1][4] = -coeff_u*ech.DTML();
	Jac[2][3] = -fcp_f;

	// Coefficient de la jacobienne liés aux bilans du deuxième échangeur
	ech = reseau.GetListeEch()[2];
	fcp_f = ech.GetFluxFroid().GetFcp(); fcp_c = ech.GetFluxChaud().GetFcp();
	aire = ech.GetAire(); coeff_u = ech.GetCoeffU();
	Jac[3][2] = -fcp_f + coeff_u * aire * ech.DeltaTmlD();
	Jac[3][5] = -coeff_u * ech.DTML();
	Jac[4][2] = -fcp_f;

	// Coefficient de la jacobienne liés aux bilans du troisème échangeur
	ech = reseau.GetListeEch()[3];
	fcp_f = ech.GetFluxFroid().GetFcp(); fcp_c = ech.GetFluxChaud().GetFcp();
	aire = ech.GetAire(); coeff_u = ech.GetCoeffU();
	Jac[5][1] = -coeff_u * aire * ech.DeltaTmlD();
	Jac[5][3] = fcp_f + coeff_u * aire * ech.DeltaTmlG();
	Jac[5][6] = -coeff_u * ech.DTML();
	Jac[6][1] = fcp_c;
	Jac[6][3] = fcp_f;
	
	// Coefficient de la jacobienne liés aux bilans du quatrième échangeur
	ech = reseau.GetListeEch()[4];
	fcp_f = ech.GetFluxFroid().GetFcp(); fcp_c = ech.GetFluxChaud().GetFcp();
	aire = ech.GetAire(); coeff_u = ech.GetCoeffU();
	Jac[7][1] = -coeff_u * aire * ech.DeltaTmlG();
	Jac[7][2] = fcp_f + coeff_u * aire * ech.DeltaTmlG();
	Jac[7][7] = -coeff_u * ech.DTML();
	
}
