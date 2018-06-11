#ifndef SPESA_H
#define SPESA_H

#include "various.h"

void showList(Spesa Elementlista[], int totElem);
int addtoListGuided(Spesa listaSpesa[], int *totElemLista, char elencoCategorie[][maxCatLen], int *totCat, Alimento databaseAlimenti[], int *totDatabaseAlimenti);
int searchElement(Spesa Elementlista[], int totElem, char elemento[]);
int rimElem(Spesa lista[], int *totElem);
int getQuantity(Spesa Elementlista[], int totElem, char elemento[], int pos);
void scalaStruct (Spesa Elementlista[], int *totElem, int startPoint);

#endif