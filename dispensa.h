#ifndef DISPENSA_H
#define DISPENSA_H

#include "various.h"

//questa libreria sarà la copia esatta di account.c, permetterà di fare le stesse cose solo a livello di dispensa.

int compareExpiry(Alimento alimento);
//addToStorage(dispensa, &totAlimenti, elencoCategorie, *&totCat, databaseAlimenti, &totDatabase);
int addToStorage(Alimento dispensa[], int *totAlimenti, char elencoCategorie[][maxCatLen], int *totCat, Alimento databaseAlimenti[], int *totDatabaseAlimenti);
int addPartialToStorage(Alimento dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista, Alimento database[], int totDatabase);
void addNewAliment(Alimento dispensa[], int *totAlimenti, char nome[], int quantita, Alimento database[], int totDatabase);
int addAllToStorage(Alimento dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista, Alimento database[], int totDatabase);
int searchAlimDisp(Alimento dispensa[], int totAlimenti, char alim[]);
void showAlimDisp(Alimento dispensa[], int totAlimenti);
void contaProdScad(Alimento dispensa[], int totAlimenti, int *countScad, int *countInScad);
int isInScadenza(Alimento alimento);
int rimScad(Alimento dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista);
void scalaStructA (Alimento alimento[], int *totAlim, int startPoint);
void showSingleAlim(Alimento alimento);
int getQuantityR(Alimento dispensa[], int totAlimenti, char alim[], int startPoint);
void rimIng(Alimento dispensa[], int *totAlimenti, Ingredienti ingredienti[], int totIngredienti);

#endif