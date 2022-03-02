#pragma once
#include <iostream>
#include <string>
#include "UnFlux.h"


class UnEchangeur
{
private:

    string id;            // Identifiant
    UnFlux flux_chaud;    // Flux chaud passant dans l'�changeur
    UnFlux flux_froid;    // Flux froid passant dans l'�changeur
    double coeff_u;       // Coefficient d'�change de l'�changeur
    double aire;          // Aire d'�change de l'�changeur
    double t_e_chaud;     // Temp�rature d'entr�e du flux chaud dans l'�changeur
    double t_e_froid;     // Temp�rature d'entr�e du flux froid dans l'�changeur
    double t_s_chaud;     // Temp�rature de sortie du flux chaud dans l'�changeur
    double t_s_froid;     // Temp�rature de sortie du flux froid dans l'�changeur

public:

    UnEchangeur(string id_ech, UnFlux flux_chaud_ech, UnFlux flux_froid_ech, double coeff_u_ech, double aire_ech);
    UnEchangeur();
    ~UnEchangeur();

    double QC();
    double QF();
    double DTML();
    double DeltaTmlG();
    double DeltaTmlD();
    bool EchangeurValide(double eps);
    void Afficher();

    string GetId();
    UnFlux GetFluxChaud();
    UnFlux GetFluxFroid();
    double GetCoeffU();
    double GetAire();
    double GetTeChaud();
    double GetTeFroid();
    double GetTsChaud();
    double GetTsFroid();

    void SetId(string id_ech);
    void SetFluxChaud(UnFlux t);
    void SetFluxFroid(UnFlux t);
    void SetAire(double aire_ech);
    void SetCoeffU(double coeff_u_ech);
    void SetTeChaud(double t);
    void SetTeFroid(double t);
    void SetTsChaud(double t);
    void SetTsFroid(double t);
};

