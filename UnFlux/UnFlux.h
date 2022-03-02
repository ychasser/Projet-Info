#pragma once
#include <iostream>
#include <string>
using namespace std;

class UnFlux
{
private:

    string id;              // Identifiant du flux
    string type;            // Type de flux (Chaud ou Froid)
    double fcp;             // Flux calorifique
    double t_e;             // Temp�rature du flux en entr�e du r�seau
    double t_s;             // Temp�rature du flux en sortie du r�seau

public:

    UnFlux(string id_flux, string type_flux, double fcp_flux, double t_e_flux, double t_s_flux);
    UnFlux();
    ~UnFlux();

    double QuantiteChaleur();
    void Afficher();

    string GetId();
    string GetType();
    double GetFcp();
    double GetTe();
    double GetTs();
   
    void SetId(string id_flux);
    void SetType(string type_flux);
    void SetFcp(double fcp_flux);
    void SetTe(double t);
    void SetTs(double t);
};

