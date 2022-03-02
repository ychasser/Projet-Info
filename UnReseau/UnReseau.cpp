/**
 * Fichier de d�finition des m�thodes de la classe UnReseau
 * Contient les m�thodes suivantes :
 *  - UnReseau() : Constructeur par d�faut de la classe UnReseau
 *  - UnReseau(*params) : Constructeur de la classe UnReseau
 *  - ~UnReseau() : Destructeur de la classe UnReseau // TODO
 *  - DefinirFluxEntreeRes() : Affecte les temp�rature d'entr�e des flux aux �changeurs dans
 *                             lesquels ils passent en premier, en accord avec la topologie du r�seau
 *  - DefinirFluxSortieRes() : Affecte les temp�rature de sortie des flux aux �changeurs dans
 *                             lesquels ils passent en dernier, en accord avec la topologie du r�seau
 *  - DefinirReseauFichier() : D�finit le r�seau � partir des informations contenues dans un fichier texte
 *  - Afficher() : Affiche les caract�ristiques du r�seau et de ses �changeurs
 *
 * @author Yohann Chasseray
 * Date : 02/03/22
 * Contact: yohann.chasseray@gmail.com
 */

#include <iostream>
#include <algorithm>   
#include "UnReseau.h"
#include "Numerique.h"
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;


// ===========================================DEBUT================================================== //
// Constructeur par d�faut de la classe UnReseau
UnReseau::UnReseau() {
	id = "";
	n_ech = 0;
	n_flux = 0;
	liste_flux = NULL;
	liste_ech = NULL;
	topo = NULL;
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Constructeur de la classe UnReseau -- Rarement utilis�, la d�finition
// des attributs se faisant g�n�ralement � partir d'un fichier (m�thode DefinirReseauFichier)
UnReseau::UnReseau(string id_res, int n_ech_res, int n_flux_res, UnFlux* liste_flux_res, UnEchangeur* liste_ech_res, int** topo_res){

	id = id_res;
	n_ech = n_ech_res;
	n_flux = n_flux_res;
	liste_flux = liste_flux_res;
	liste_ech = liste_ech_res;
	topo = topo_res;

}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Destructeur de la classe UnReseau
UnReseau::~UnReseau() {
	// TODO           
}
// ============================================FIN=================================================== //


// ===========================================DEBUT================================================== //
// M�thode permettant d'affecter les temp�rature d'entr�e des flux aux �changeurs
// dans lesquels ils passent en premier, en accord avec la topologie du r�seau.
void UnReseau::DefinirFluxEntreeRes() {

	for (int i = 1; i <= n_ech; i++) { // Parcours des lignes de la topologie (�changeurs)
		for (int j = 1; j <= n_flux; j++) { // Parcours des colonnes de la topologie (flux)
			if (topo[i][j] == 1) { // Si le flux j passe en premier dans l'�changeur i
				if (liste_flux[j].GetType() == "Chaud") // Si le flux est un flux chaud
				{
					liste_ech[i].SetTeChaud(liste_flux[j].GetTe()); // Affecter temp�rature d'entr�e
																	// du flux dans le r�seau � t_e_c
					                                                // de l'echangeur
				}
				if (liste_flux[j].GetType() == "Froid") // Si le flux est un flux froid
				{
					liste_ech[i].SetTeFroid(liste_flux[j].GetTe()); // Affecter temp�rature d'entr�e
																	// du flux dans le r�seau � t_e_f
					                                                // de l'echangeur
				}
			}
		}
	}
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// M�thode permettant d'affecter les temp�rature de sortie des flux aux �changeurs
// dans lesquels ils passent en dernier, en accord avec la topologie du r�seau.
void UnReseau::DefinirFluxSortieRes() {
	int max;
	for (int j = 1; j <= n_flux; j++) { // Parcours des colonnes de la topologie (flux)
		max = maxColMatrix(topo, j, n_flux); // R�cup�rer l'indice (ligne) de la valeur
		                                            // maximale de la colonne j de la topologie
		if (liste_flux[j].GetType() == "Chaud") // Si le flux j est un flux chaud
		{
			liste_ech[max].SetTsChaud(liste_flux[j].GetTs());// Affecter temp�rature de sortie
														     // du flux dans le r�seau � t_s_c
					                                         // de l'echangeur de la ligne d'indice max 
		}
		if (liste_flux[j].GetType() == "Froid") // Si le flux j est un flux froid
		{
			liste_ech[max].SetTsFroid(liste_flux[j].GetTs()); // Affecter temp�rature de sortie
														      // du flux dans le r�seau � t_s_f
					                                          // de l'echangeur de la ligne d'indice max
		}
		
	}
}
// ============================================FIN=================================================== //


// ===========================================DEBUT================================================== //
// M�thode permettant de d�finir le r�seau � partir des
// informations contenues dans un fichier texte
void UnReseau::DefinirReseauFichier(string id_fichier) {
	fstream fichier; // Objet de lecture du fichier
	string id_res, line, type_flux, id_ech, id_flux;
	double fcp_flux, t_e_flux, t_s_flux, coeff_u_ech, aire_ech;
	UnFlux flux_chaud, flux_froid;
	fichier.open(id_fichier, ios::in); // Ouverture du fichier 
	if (fichier.is_open()) {
		fichier >> id_res; // Identifiant (premi�re ligne du fichier)
		id = id_res;

		getline(fichier, line);
		fichier >> n_ech; // Nombre d'�changeurs (deuxi�me ligne du fichier)

		getline(fichier, line);
		fichier >> n_flux; // Nombre de flux (troisi�me ligne du fichier)

		// Allocation des listes des flux et �changeurs
		liste_flux = new UnFlux[n_flux + 1];
		liste_ech = new UnEchangeur[n_ech + 1];
		for (int i = 1; i <= n_flux; i++) { // Lecture des flux (lignes 4 � 7 du fichier)
			getline(fichier, line);
			fichier >> id_flux >> type_flux >> fcp_flux >> t_e_flux >> t_s_flux;
			UnFlux flux_i(id_flux, type_flux, fcp_flux, t_e_flux, t_s_flux); // Construction du flux
			liste_flux[i] = flux_i;
		}


		getline(fichier, line);
		topo = new int* [n_ech + 1]; // Allocation de la matrice topologique
		for (int i = 1; i <= n_ech; i++) { // Lecture des lignes de la matrice (ligne 8 � 11 du fichier)
			topo[i] = new int[n_flux + 1]; // Allocation des lignes de la matrice
			for (int j = 1; j <= n_flux; j++) {
				fichier >> topo[i][j]; // Lecture de l'indice [i][j]
			}
			getline(fichier, line); // Ligne suivante
		}

		// Affectation des flux et attributs des �changeurs
		for (int i = 1; i <= n_ech; i++) { // Parcours des echangeurs (lignes 12 � 19)
			for (int j = 1; j <= n_flux; j++) { // Parcours des flux
				if (topo[i][j] != 0) { // Si le flux j passe dans l'�changeur i 
					if (liste_flux[j].GetType() == "Chaud") // Si le flux est un flux chaud
					{
						flux_chaud = liste_flux[j]; // On a trouv� le flux chaud de l'�changeur i
					}
					if (liste_flux[j].GetType() == "Froid") // Si le flux est un flux froid
					{
						flux_froid = liste_flux[j]; // On a trouv� le flux froid de l'�changeur i
					}
				}
			}

			fichier >> coeff_u_ech; // Coefficient d'�change
			getline(fichier, line); // Ligne suivante
			fichier >> aire_ech; // Aire d'�change
			getline(fichier, line); // Ligne suivante

			id_ech = "E1"; // TODO : A changer pour int�grer Ei 
			UnEchangeur ech(id_ech, flux_chaud, flux_froid, coeff_u_ech, aire_ech); // Construction de l'�changeur
			liste_ech[i] = ech; // Affectation � la liste d'�changeurs du r�seau
		}

		fichier.close(); // Fermeture du fichier
	}
	DefinirFluxEntreeRes(); // Affectation des temp�ratures d'entr�es des flux dans le r�seau aux �changeurs
	DefinirFluxSortieRes(); // Affectation des temp�ratures de sortie des flux dans le r�seau aux �changeurs
}
// ============================================FIN=================================================== //


// ===========================================DEBUT================================================== //
// M�thode permettant d'afficher les caract�ristiques d'un r�seau et de ses �changeurs
void UnReseau::Afficher() {
	cout << "====================================\n";
	// Affichage des caract�riqtiques du r�seau
	cout << "Identifiant du reseau : " << id << "\n";
	cout << "Reseau a  " << n_ech << " echangeurs et " << n_flux << "flux \n";
	
	// Affichage des �changeurs (les flux sont �galement affich�s lors de l'appel
	// des m�thodes d'afffichage des �changeurs)
	cout << "Liste des echangeurs et flux associes : \n";
	for (int i = 1; i <= n_ech; i++) {
		liste_ech[i].Afficher();
	}
	cout << "====================================\n\n";
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// ------------------------------------------ Getters ----------------------------------------------- //
string UnReseau::GetId() {
	return id;
}
int UnReseau::GetNflux() {
	return n_flux;
}
int UnReseau::GetNech() {
	return n_ech;
}
UnEchangeur* UnReseau::GetListeEch() {
	return liste_ech;
}
UnFlux* UnReseau::GetListeFlux() {
	return liste_flux;
}
int** UnReseau::GetTopo() {
	return topo;
}
// ============================================FIN=================================================== //

