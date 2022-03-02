#pragma once
#include <iostream>
#include <string>
#include "UnEchangeur.h"

class UnReseau
{
protected:

    string id;                 // Identifiant du r�seau
    int n_flux;                // Nombre de flux du r�seau
    int n_ech;                 // Nombre d'�changeurs du r�seau
    UnFlux* liste_flux;        // Liste des flux associ�s au r�seau
    UnEchangeur* liste_ech;    // Liste des �changeurs associ�s au r�seau
    int** topo;                // Matrice topologique traduisant la g�om�trie du r�seau

public:

    UnReseau(string id_res, int n_ech_res, int n_flux_res, UnFlux* liste_flux_res, UnEchangeur* liste_ech_res, int** topo_res);
    UnReseau();
    ~UnReseau();

    void DefinirFluxEntreeRes();
    void DefinirFluxSortieRes();
    void DefinirReseauFichier(string id_fichier);
    void Afficher();

    string GetId();
    int GetNflux();
    int GetNech();
    UnEchangeur* GetListeEch();
    UnFlux* GetListeFlux();
    int** GetTopo();

};

