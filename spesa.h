#ifndef SPESA_H
#define SPESA_H

#include "various.h"

void showList(Spesa Elementlista[], int totElem);
int copyToList(Spesa listaSpesa[], int *totElemLista, Alimento alimento);
int addtoListGuided(Spesa listaSpesa[], int *totElemLista, char elencoCategorie[][maxCatLen], int *totCat, Alimento databaseAlimenti[], int *totDatabaseAlimenti);
int searchElement(Spesa Elementlista[], int totElem, char elemento[]);
int rimElem(Spesa lista[], int *totElem);
int getQuantity(Spesa Elementlista[], int totElem, char elemento[], int pos);
void scalaStruct (Spesa Elementlista[], int *totElem, int startPoint);
void mainmenusel4(Alimento dispensa[], int *totAlimenti, Spesa lista[], int *totElem, Alimento database[], int *totDatabase, char elencoCategorie[][maxCatLen], int *totCat);

#endif