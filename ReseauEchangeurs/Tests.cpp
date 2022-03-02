/**
 * Fichier de définition des fonctions de test pour les différents modules de la solution Projet Info
 * Contient les fonctions de test suivantes :
 *  - TestUnFlux() : Teste les méthodes de la classe UnFlux 
 *  - TestUnEchangeur() : Teste les méthodes de la classe UnEchangeur 
 *  - TestREC1(fichier) : Teste la définition du réseau 1 proche de la solution
 *  - TestREC2(fichier) : Teste la définition du réseau 2 proche de la solution
 *
 * @author Yohann Chasseray
 * Date : 02/03/22
 * Contact: yohann.chasseray@gmail.com
 */
#include <iostream>
#include <string>
#include "UnFlux.h"
#include "UnEchangeur.h"
#include "UnReseau.h"
#include "Tests.h"
#include "RECUtilisateur.h"
#include "Partage.h"

using namespace std;


// ===========================================DEBUT================================================== //
// Fonction dédiée au test des méthodes du module UnFlux 
void TestUnFlux()
{
    UnFlux flux_a("A", "Chaud", 30, 170, 60); // Definition flux a
    UnFlux flux_b("B", "Chaud", 15, 150, 70); // Definition flux b
    UnFlux flux_c("C", "Froid", 20, 20, 125); // Definition flux c
    UnFlux flux_d("D", "Froid", 40, 80, 140); // Definition flux d

    flux_a.Afficher(); // Affichage flux a
    flux_b.Afficher(); // Affichage flux a
    flux_c.Afficher(); // Affichage flux a
    flux_d.Afficher(); // Affichage flux a
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Fonction dédiée au test des méthodes du module UnEchangeur
void TestUnEchangeur()
{
    UnFlux flux_a("A", "Chaud", 30, 170, 60);
    UnFlux flux_b("B", "Chaud", 15, 150, 70);
    UnFlux flux_c("C", "Froid", 20, 20, 125);
    UnFlux flux_d("D", "Froid", 40, 80, 140);

    UnEchangeur ech_3("E3", flux_a, flux_d, 0.8, 164.792); // Definition echangeur 3

    // Affectation des températures
    ech_3.SetTeChaud(170);
    ech_3.SetTeFroid(80);
    ech_3.SetTsChaud(90);
    ech_3.SetTsFroid(140);

    ech_3.Afficher(); // Affichage de l'échangeur

    // Test des différentes méthodes
    cout << "Echangeur verifie ? : " << ech_3.EchangeurValide(0.01) << "\n";
    cout << "DTML : " << ech_3.DTML() << "\n";
    cout << "DTMLG : " << ech_3.DeltaTmlD() << "\n";
    cout << "DTMLD : " << ech_3.DeltaTmlG() << "\n";
    cout << "QC : " << ech_3.QC() << "\n";
    cout << "QF : " << ech_3.QF() << "\n";
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Fonction dédiée au test de la définition du réseau 1 
void TestREC1(string fichier) {

    // Déclaration et allocation des variables
    UnReseau reseau;
    double* F;
    double** Jac;
    F = new double[8];
    Jac = new double* [8];
    for (int i = 1; i <= 8; i++) {
        Jac[i] = new double[8];
        for (int j = 1; j <= 8; j++) {
            Jac[i][j] = 0;
        }
    }

    double X[8] = {90, 35, 80, 90, 68.8, 164.8, 68.5, 7.1}; // Vecteur proche de la solution
                                                            //TB TC34 TC13 TA A1 A2 A3 A4
    reseau.DefinirReseauFichier(fichier); // Définition du réseau à partir du fichier correspondant
    SystemeREC1(X, F); // Calcul de l'état du réseau proche de la solution
    JacobienREC1(X, Jac); // Valeur de la jacobienne proche de la solution

    // Affichage de la valeur du réseau et de la jacobienne proche de la solution
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            cout << Jac[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "=================================\n";
    for (int i = 1; i <= 8; i++) {
        cout << F[i] << " ";
    }
    cout << "=================================\n";
}
// ============================================FIN=================================================== //

// ===========================================DEBUT================================================== //
// Fonction dédiée au test de la définition du réseau 2 
void TestREC2(string fichier) {

    // Déclaration et allocation des variables
    UnReseau reseau;
    double* F;
    double** Jac;
    F = new double[8];
    Jac = new double* [8];
    for (int i = 0; i < 8; i++) {
        Jac[i] = new double[8];
        for (int j = 0; j < 8; j++) {
            Jac[i][j] = 0;
        }
    }

    double X[7] = {157.5, 25, 87.5, 200.6296, 180.2410, 9.952352, 5.00015};// Vecteur proche de la solution
    reseau.DefinirReseauFichier(fichier);// Définition du réseau à partir du fichier correspondant
    SystemeREC2(X, F);// Calcul de l'état du réseau proche de la solution
    JacobienREC2(X, Jac);// Valeur de la jacobienne proche de la solution
    
    // Affichage de la valeur du réseau et de la jacobienne proche de la solution
    reseau.Afficher();
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            cout << Jac[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "=================================\n";
    for (int i = 0; i < 7; i++) {
        cout << F[i] << " ";
    }
    cout << "=================================\n"; 
}
// ============================================FIN=================================================== //
