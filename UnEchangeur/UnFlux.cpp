/**
 * Fichier de définition des méthodes de la classe UnFlux
 * Contient les méthodes suivantes :
 *  - UnFlux() : Constructeur par défaut de la classe UnFlux
 *  - UnFlux(*params) : Constructeur de la classe UnFlux
 *  - ~UnFlux() : Destructeur de la classe UnFlux //TODO
 *  - QuantiteChaleur() : Calcule la quantité de chaleur transportée par le flux
 *  - Afficher() : Affiche les caractériqtiques du flux
 * 
 * 
 * @author Yohann Chasseray
 * Date : 02/03/22
 * Contact: yohann.chasseray@gmail.com
 */

#include <iostream>
#include "UnFlux.h"
using namespace std;

// ===========================================DEBUT================================================== //
// Constructeur par défaut de la classe UnFlux
UnFlux::UnFlux() {
	id = "";
	type = "";
	fcp = 0;
	t_e = 0;
	t_s = 0;
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Constructeur de la classe UnFlux
UnFlux::UnFlux(string id_flux, string type_flux, double fcp_flux, double t_e_flux, double t_s_flux) {
	id = id_flux;
	type = type_flux;
	fcp = fcp_flux;
	t_e = t_e_flux;
	t_s = t_s_flux;
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Destructeur de la classe UnFlux
UnFlux::~UnFlux() {
	// TODO           
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Méthode permettant de calculer la quantité de chaleur transportée par le flux
// Sortie :
// double qc : Quantité de chaleur transportée (qc > 0)
double UnFlux::QuantiteChaleur()
{
	double qc = 0;
	if (type == "Chaud") // Si le flux est un flux chaud (te > ts)
	{
		qc = fcp * (t_e - t_s);
	}
	if (type == "Froid") // Si le flux est un flux froid (te < ts)
	{
		qc = fcp * (t_s - t_e); 
	}
	
	return qc;
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Méthode permettant d'afficher un flux
void UnFlux::Afficher() {
	
	double qc;

	cout << "====================================\n";

	// Affichage de l'identifiant et du type de flux
	cout << "Id du flux : " << id << " -- ";
	if (type == "Chaud")
	{
		cout << "Flux Chaud\n";
	}
	if (type == "Froid")
	{
		cout << "Flux Froid\n";
	}
	
	// Affichage des différents attributs du flux
	cout << "Flux calorifique : " << fcp << "\n";
	cout << "Temperature de specification d'entree : " << t_e << "\n";
	cout << "Temperature de specification de sortie : " << t_s << "\n";
	qc = QuantiteChaleur(); // Calcul de qc
	cout << "Quantite de chaleur transportee : " << qc << "\n"; // Affichage de qc
	cout << "====================================\n\n";

}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// -------------------------------------- Getters et setters ---------------------------------------- //
string UnFlux::GetId() {
	return id;
}
string UnFlux::GetType() {
	return type;
}
double UnFlux::GetFcp() {
	return fcp;
}
double UnFlux::GetTe() {
	return t_e;
}
double UnFlux::GetTs() {
	return t_s;
}

void UnFlux::SetId(string id_flux) {
	id = id_flux;
}
void UnFlux::SetType(string type_flux) {
	type = type_flux;
}
void UnFlux::SetFcp(double fcp_flux) {
	fcp = fcp_flux;
}
void UnFlux::SetTe(double t) {
	t_e = t;
}
void UnFlux::SetTs(double t) {
	t_s = t;
}
// ============================================FIN=================================================== //