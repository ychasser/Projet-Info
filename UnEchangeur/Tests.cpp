/**
 * Fichier de définition des fonctions de test pour les différents modules de la solution Projet Info
 * Contient les fonctions de test suivantes :
 *  - TestUnFlux() : Teste les méthodes de la classe UnFlux 
 *  - TestUnEchangeur() : Teste les méthodes de la classe UnEchangeur 
 *
 * @author Yohann Chasseray
 * Date : 02/03/22
 * Contact: yohann.chasseray@gmail.com
 */
#include <iostream>
#include <string>
#include "UnFlux.h"
#include "UnEchangeur.h"
#include "Tests.h"

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
