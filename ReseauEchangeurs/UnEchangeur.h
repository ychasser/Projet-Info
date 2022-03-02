#pragma once
#include <iostream>
#include <string>
#include "UnFlux.h"


class UnEchangeur
{
private:

    string id;            // Identifiant
    UnFlux flux_chaud;    // Flux chaud passant dans l'échangeur
    UnFlux flux_froid;    // Flux froid passant dans l'échangeur
    double coeff_u;       // Coefficient d'échange de l'échangeur
    double aire;          // Aire d'échange de l'échangeur
    double t_e_chaud;     // Température d'entrée du flux chaud dans l'échangeur
    double t_e_froid;     // Température d'entrée du flux froid dans l'échangeur
    double t_s_chaud;     // Température de sortie du flux chaud dans l'échangeur
    double t_s_froid;     // Température de sortie du flux froid dans l'échangeur

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

