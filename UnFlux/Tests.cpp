/**
 * Fichier de définition des fonctions de test pour les différents modules de la solution Projet Info
 * Contient les fonctions de test suivantes :
 *  - TestUnFlux() : Teste les méthodes de la classe UnFlux 
 *
 * @author Yohann Chasseray
 * Date : 02/03/22
 * Contact: yohann.chasseray@gmail.com
 */
#include <iostream>
#include <string>
#include "UnFlux.h"
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

