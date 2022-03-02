#pragma once
#include <iostream>
#include <string>
#include "UnEchangeur.h"

class UnReseau
{
protected:

    string id;                 // Identifiant du réseau
    int n_flux;                // Nombre de flux du réseau
    int n_ech;                 // Nombre d'échangeurs du réseau
    UnFlux* liste_flux;        // Liste des flux associés au réseau
    UnEchangeur* liste_ech;    // Liste des échangeurs associés au réseau
    int** topo;                // Matrice topologique traduisant la géométrie du réseau

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

