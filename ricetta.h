#ifndef RECETTA_H
#define RICETTA_H

#include "various.h"

int addRecipes(Ricetta ricette[], int totRicette, char elencoCattgorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase);
int addReciApp(Ricetta ricette[], int totRicette, Ricetta riceApp[], int totRicApp, char elencoCategorie[][maxCatLen], int totCat, Alimento database[], int totDatabase, char elencoCatApp[][maxCatLen], int *totCatApp, Alimento alimApp[], int *totAlimApp);

void showRecipes(Ricetta ricette[], int totRicette);
int searchRecipes(Ricetta ricette[], int totRicette, char elemento[]);
int rimrElem(Ricetta ricette[], int totRicette);
void scalarStruct (Ricetta ricette[], int totRicette, int startPoint);

#endif