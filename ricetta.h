#ifndef RECETTA_H
#define RICETTA_H

#include "various.h"

int addRecipes(Ricetta ricette[], int totRicette, char elencoCattgorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase);
void showRecipes(Ricetta ricette[], int totRicette);
int searchRecipes(Ricetta ricette[], int totRicette, char elemento[]);
int rimrElem(Ricetta ricette[], int totRicette);
void scalarStruct (Ricetta ricette[], int totRicette, int startPoint);

#endif