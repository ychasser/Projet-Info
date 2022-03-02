#pragma once
#include "UnReseau.h"

void SystemeREC1(double X[8], double*, double* param = NULL);
void JacobienREC1(double X[8], double**, double* param = NULL);

void SystemeREC2(double X[7], double*, double* param = NULL);
void JacobienREC2(double X[7], double**, double* param = NULL);
