/**
 * Fichier de définition des méthodes de la classe UnEchangeur
 * Contient les méthodes suivantes :
 *  - UnEchangeur() : Constructeur par défaut de la classe UnEchangeur
 *  - UnEchangeur(*params) : Constructeur de la classe UnEchangeur
 *  - ~UnEchangeur() : Destructeur de la classe UnEchangeur //TODO
 *  - QC() : Calcule la quantité de chaleur cédée par le flux chaud au sein de l'échangeur
 *  - QF() : Calcule la quantité de chaleur captée par le flux froid au sein de l'échangeur
 *  - DTML() : Calcule la différence de température logarithmique moyenne de l'échangeur
 *  - DeltaTmlG() : Calcule la différence de température logarithmique moyenne à gauche de l'échangeur
 *  - DeltaTmlD() : Calcule la différence de température logarithmique moyenne à droite de l'échangeur
 *  - EchangeurValide() : Vérifie la bonne définition de l'échangeur (égalité des flux, cohérence des températures)
 *  - Afficher() : Affiche les caractéristiques de l'échangeur
 * 
 * 
 * @author Yohann Chasseray
 * Date : 02/03/22
 * Contact: yohann.chasseray@gmail.com
 */

#include <iostream>
#include <math.h>
#include "UnEchangeur.h"
using namespace std;



// ===========================================DEBUT================================================== //
// Constructeur par défaut de la classe UnEchangeur
UnEchangeur::UnEchangeur() {

    id = "";
    coeff_u = 0;
    aire = 0;
    t_s_chaud = 0;
    t_e_chaud = 0;
    t_s_froid = 0;
    t_e_froid = 0;

}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Constructeur de la classe UnEchangeur
UnEchangeur::UnEchangeur(string id_ech, UnFlux flux_chaud_ech, UnFlux flux_froid_ech, double coeff_u_ech, double aire_ech) {

    id = id_ech;
    flux_chaud = flux_chaud_ech;
    flux_froid = flux_froid_ech;
    coeff_u = coeff_u_ech;
    aire = aire_ech;
    // Les températures ne sont normalement pas connues à l'initialisation
    t_s_chaud = 0;
    t_e_chaud = 0;
    t_s_froid = 0;
    t_e_froid = 0;

}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Destructeur de la classe UnEchangeur
UnEchangeur::~UnEchangeur() {
    // TODO           
}
// ============================================FIN=================================================== //


// ===========================================DEBUT================================================== //
// Méthode permettant de calculer la quantité de chaleur cédée
// par le flux chaud au sein de l'échangeur
// Sortie :
// double qc : Quantité de chaleur cédée
double UnEchangeur::QC() {
    double qc;
    qc = flux_chaud.GetFcp() * (t_e_chaud - t_s_chaud); // t_e_chaud > t_s_chaud
    return qc;
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Méthode permettant de calculer la quantité de chaleur récupérée
// par le flux froid au sein de l'échangeur
// Sortie :
// double qf : Quantité de chaleur récupérée
double UnEchangeur::QF() {
    double qf;
    qf = flux_froid.GetFcp() * (t_s_froid - t_e_froid); // t_s_froid > t_e_froid
    return qf;
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Méthode permettant de calculer la différence de température
// logarithmique moyenne de l'échangeur
// Sortie :
// double dtml : différence de température logarithmique moyenne
double UnEchangeur::DTML() {
    double dtml;
    double dt_droite;
    double dt_gauche;
    dt_gauche = t_e_chaud - t_s_froid; // Différence de température à gauche (echangeur contre-courant)
    dt_droite = t_s_chaud - t_e_froid; // Différence de température à droite (echangeur contre-courant)
    dtml = (dt_gauche - dt_droite) / log(dt_gauche / dt_droite); // Calcul de DTML
    return dtml;
}

// ===========================================DEBUT================================================== //
// Méthode permettant de calculer la différence de température
// logarithmique moyenne à gauche de l'échangeur
// Sortie :
// double dtml : différence de température logarithmique moyenne à gauche
 double UnEchangeur::DeltaTmlG() {
     double delta_tml_g;
     double dt_droite;
     double dt_gauche;
     dt_gauche = t_e_chaud - t_s_froid; // Différence de température à gauche (echangeur contre-courant)
     dt_droite = t_s_chaud - t_e_froid; // Différence de température à droite (echangeur contre-courant)
     delta_tml_g = DTML()/dt_gauche*(dt_gauche - DTML()) / (dt_gauche - dt_droite);
     return delta_tml_g;
 }
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Méthode permettant de calculer la différence de température
// logarithmique moyenne à droite de l'échangeur
// Sortie :
// double dtml : différence de température logarithmique moyenne à droite
double UnEchangeur::DeltaTmlD() {
    double delta_tml_d;
    double dt_droite;
    double dt_gauche;
    dt_gauche = t_e_chaud - t_s_froid; // Différence de température à gauche (echangeur contre-courant)
    dt_droite = t_s_chaud - t_e_froid; // Différence de température à droite (echangeur contre-courant)
    delta_tml_d = DTML() / dt_droite * (dt_droite - DTML()) / (dt_gauche - dt_droite);
    return delta_tml_d;
}
// ============================================FIN=================================================== //


// ===========================================DEBUT================================================== //
// Méthode permettant de vérifier la bonne définition de l'échangeur
// (égalité des flux, cohérence des températures)
// Sortie :
// bool verif : indicateur de validité (true : echangeur valide, false : echangeur invalide)
bool UnEchangeur::EchangeurValide(double eps) {
    double dt_droite;
    double dt_gauche;
    bool verif;
    dt_gauche = t_e_chaud - t_s_froid; // Différence de température à gauche (echangeur contre-courant)
    dt_droite = t_s_chaud - t_e_froid; // Différence de température à droite (echangeur contre-courant)

    verif = ((t_e_chaud - t_s_chaud) >= 0); // Cohérence des températures d'entrée et sortie du flux chaud
    verif = verif and ((t_e_froid - t_s_froid) <= 0); // Cohérence des températures d'entrée et sortie du flux froid 
    verif = verif and (coeff_u > 0); // Coefficient d'échange positif
    verif = verif and (aire > 0); // Aire positive
    verif = verif and (dt_gauche >= 0); // Cohérence des températures à gauche
    verif = verif and (dt_droite >= 0); // Cohérence des températures à droite
    verif = verif and (abs(QF() - QC()) <= eps); // Égalité des flux thermiques cédés et reçus
    verif = verif and (abs(QF() - coeff_u * aire * DTML()) <= eps); // Égalité du flux cédé et du flux échangé

    return verif;
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Méthode permettant d'afficher les caractéristiques d'un échangeur et de ses flux
void UnEchangeur::Afficher() {
    cout << "====================================\n";
    cout << "Identifiant de l'echangeur : " << id << "\n";
    // Affichage des flux
    flux_chaud.Afficher();
    flux_froid.Afficher();

    // Affichage des températures d'entrée et sortie des flux dans l'échangeur
    cout << "Temperature d'entree du flux chaud : " << t_e_chaud << "\n";
    cout << "Temperature de sortie du flux chaud : " << t_s_chaud << "\n";
    cout << "Temperature d'entree du flux froid : " << t_e_froid << "\n";
    cout << "Temperature de sortie du flux froid : " << t_s_froid << "\n";
    // Affichage des caractériqtiques de l'échangeur
    cout << "Coefficient global d'echange U (kW/oC/m2) :" << coeff_u << "\n";
    cout << "Aire d'echange A (m2) : " << aire << "\n";
    cout << "====================================\n\n";
}


// ===========================================DEBUT================================================== //
// ------------------------------------ Getters et setters ------------------------------------------ //
string UnEchangeur::GetId() {
    return id;
}
UnFlux UnEchangeur::GetFluxChaud() {
    return flux_chaud;

}
UnFlux UnEchangeur::GetFluxFroid() {
    return flux_froid;
}
double UnEchangeur::GetCoeffU() {
    return coeff_u;
}
double UnEchangeur::GetAire() {
    return aire;
}
double UnEchangeur::GetTeChaud() {
    return t_e_chaud;
}
double UnEchangeur::GetTeFroid() {
    return t_e_froid;
}
double UnEchangeur::GetTsChaud() {
    return t_s_chaud;
}
double UnEchangeur::GetTsFroid() {
    return t_s_froid;
}

void UnEchangeur::SetAire(double aire_ech) {
    aire = aire_ech;
}
void UnEchangeur::SetCoeffU(double coeff_u_ech) {
    coeff_u = coeff_u_ech;
}
void UnEchangeur::SetId(string id_ech) {
    id = id_ech;
}
void UnEchangeur::SetFluxChaud(UnFlux flux_chaud_ech) {
    flux_chaud = flux_chaud_ech;
}
void UnEchangeur::SetFluxFroid(UnFlux flux_froid_ech) {
    flux_froid = flux_froid_ech;
}
void UnEchangeur::SetTeChaud(double t) {
    t_e_chaud = t;
}
void UnEchangeur::SetTsChaud(double t) {
    t_s_chaud = t;
}
void UnEchangeur::SetTeFroid(double t) {
    t_e_froid = t;
}
void UnEchangeur::SetTsFroid(double t) {
    t_s_froid = t;
}
// ============================================FIN=================================================== //
