/**
 * Fichier de définition des méthodes de la classe UnReseau
 * Contient les méthodes suivantes :
 *  - UnReseau() : Constructeur par défaut de la classe UnReseau
 *  - UnReseau(*params) : Constructeur de la classe UnReseau
 *  - ~UnReseau() : Destructeur de la classe UnReseau // TODO
 *  - DefinirFluxEntreeRes() : Affecte les température d'entrée des flux aux échangeurs dans
 *                             lesquels ils passent en premier, en accord avec la topologie du réseau
 *  - DefinirFluxSortieRes() : Affecte les température de sortie des flux aux échangeurs dans
 *                             lesquels ils passent en dernier, en accord avec la topologie du réseau
 *  - DefinirReseauFichier() : Définit le réseau à partir des informations contenues dans un fichier texte
 *  - Afficher() : Affiche les caractéristiques du réseau et de ses échangeurs
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
// Constructeur par défaut de la classe UnReseau
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
// Constructeur de la classe UnReseau -- Rarement utilisé, la définition
// des attributs se faisant généralement à partir d'un fichier (méthode DefinirReseauFichier)
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
// Méthode permettant d'affecter les température d'entrée des flux aux échangeurs
// dans lesquels ils passent en premier, en accord avec la topologie du réseau.
void UnReseau::DefinirFluxEntreeRes() {

	for (int i = 1; i <= n_ech; i++) { // Parcours des lignes de la topologie (échangeurs)
		for (int j = 1; j <= n_flux; j++) { // Parcours des colonnes de la topologie (flux)
			if (topo[i][j] == 1) { // Si le flux j passe en premier dans l'échangeur i
				if (liste_flux[j].GetType() == "Chaud") // Si le flux est un flux chaud
				{
					liste_ech[i].SetTeChaud(liste_flux[j].GetTe()); // Affecter température d'entrée
																	// du flux dans le réseau à t_e_c
					                                                // de l'echangeur
				}
				if (liste_flux[j].GetType() == "Froid") // Si le flux est un flux froid
				{
					liste_ech[i].SetTeFroid(liste_flux[j].GetTe()); // Affecter température d'entrée
																	// du flux dans le réseau à t_e_f
					                                                // de l'echangeur
				}
			}
		}
	}
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Méthode permettant d'affecter les température de sortie des flux aux échangeurs
// dans lesquels ils passent en dernier, en accord avec la topologie du réseau.
void UnReseau::DefinirFluxSortieRes() {
	int max;
	for (int j = 1; j <= n_flux; j++) { // Parcours des colonnes de la topologie (flux)
		max = maxColMatrix(topo, j, n_flux); // Récupérer l'indice (ligne) de la valeur
		                                            // maximale de la colonne j de la topologie
		if (liste_flux[j].GetType() == "Chaud") // Si le flux j est un flux chaud
		{
			liste_ech[max].SetTsChaud(liste_flux[j].GetTs());// Affecter température de sortie
														     // du flux dans le réseau à t_s_c
					                                         // de l'echangeur de la ligne d'indice max 
		}
		if (liste_flux[j].GetType() == "Froid") // Si le flux j est un flux froid
		{
			liste_ech[max].SetTsFroid(liste_flux[j].GetTs()); // Affecter température de sortie
														      // du flux dans le réseau à t_s_f
					                                          // de l'echangeur de la ligne d'indice max
		}
		
	}
}
// ============================================FIN=================================================== //


// ===========================================DEBUT================================================== //
// Méthode permettant de définir le réseau à partir des
// informations contenues dans un fichier texte
void UnReseau::DefinirReseauFichier(string id_fichier) {
	fstream fichier; // Objet de lecture du fichier
	string id_res, line, type_flux, id_ech, id_flux;
	double fcp_flux, t_e_flux, t_s_flux, coeff_u_ech, aire_ech;
	UnFlux flux_chaud, flux_froid;
	fichier.open(id_fichier, ios::in); // Ouverture du fichier 
	if (fichier.is_open()) {
		fichier >> id_res; // Identifiant (première ligne du fichier)
		id = id_res;

		getline(fichier, line);
		fichier >> n_ech; // Nombre d'échangeurs (deuxième ligne du fichier)

		getline(fichier, line);
		fichier >> n_flux; // Nombre de flux (troisième ligne du fichier)

		// Allocation des listes des flux et échangeurs
		liste_flux = new UnFlux[n_flux + 1];
		liste_ech = new UnEchangeur[n_ech + 1];
		for (int i = 1; i <= n_flux; i++) { // Lecture des flux (lignes 4 à 7 du fichier)
			getline(fichier, line);
			fichier >> id_flux >> type_flux >> fcp_flux >> t_e_flux >> t_s_flux;
			UnFlux flux_i(id_flux, type_flux, fcp_flux, t_e_flux, t_s_flux); // Construction du flux
			liste_flux[i] = flux_i;
		}


		getline(fichier, line);
		topo = new int* [n_ech + 1]; // Allocation de la matrice topologique
		for (int i = 1; i <= n_ech; i++) { // Lecture des lignes de la matrice (ligne 8 à 11 du fichier)
			topo[i] = new int[n_flux + 1]; // Allocation des lignes de la matrice
			for (int j = 1; j <= n_flux; j++) {
				fichier >> topo[i][j]; // Lecture de l'indice [i][j]
			}
			getline(fichier, line); // Ligne suivante
		}

		// Affectation des flux et attributs des échangeurs
		for (int i = 1; i <= n_ech; i++) { // Parcours des echangeurs (lignes 12 à 19)
			for (int j = 1; j <= n_flux; j++) { // Parcours des flux
				if (topo[i][j] != 0) { // Si le flux j passe dans l'échangeur i 
					if (liste_flux[j].GetType() == "Chaud") // Si le flux est un flux chaud
					{
						flux_chaud = liste_flux[j]; // On a trouvé le flux chaud de l'échangeur i
					}
					if (liste_flux[j].GetType() == "Froid") // Si le flux est un flux froid
					{
						flux_froid = liste_flux[j]; // On a trouvé le flux froid de l'échangeur i
					}
				}
			}

			fichier >> coeff_u_ech; // Coefficient d'échange
			getline(fichier, line); // Ligne suivante
			fichier >> aire_ech; // Aire d'échange
			getline(fichier, line); // Ligne suivante

			id_ech = "E1"; // TODO : A changer pour intégrer Ei 
			UnEchangeur ech(id_ech, flux_chaud, flux_froid, coeff_u_ech, aire_ech); // Construction de l'échangeur
			liste_ech[i] = ech; // Affectation à la liste d'échangeurs du réseau
		}

		fichier.close(); // Fermeture du fichier
	}
	DefinirFluxEntreeRes(); // Affectation des températures d'entrées des flux dans le réseau aux échangeurs
	DefinirFluxSortieRes(); // Affectation des températures de sortie des flux dans le réseau aux échangeurs
}
// ============================================FIN=================================================== //


// ===========================================DEBUT================================================== //
// Méthode permettant d'afficher les caractéristiques d'un réseau et de ses échangeurs
void UnReseau::Afficher() {
	cout << "====================================\n";
	// Affichage des caractériqtiques du réseau
	cout << "Identifiant du reseau : " << id << "\n";
	cout << "Reseau a  " << n_ech << " echangeurs et " << n_flux << "flux \n";
	
	// Affichage des échangeurs (les flux sont également affichés lors de l'appel
	// des méthodes d'afffichage des échangeurs)
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

