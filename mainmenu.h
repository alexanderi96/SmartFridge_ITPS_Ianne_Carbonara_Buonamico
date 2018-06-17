//
// Created by Christian Buonamico on 23/04/2018.
//

#ifndef MAINMENU_H
#define MAINMENU_H

#include "various.h"

int mainmenu(char username[], char password[], int *totUtenti, Utente utenti[], char elencoCategorie[][maxCatLen], int *totCat);
int globalSearch(char searchWord[], Utente account[], int totAccount, Alimento dispensa[], int totAlimenti, Ricetta ricette[], int totRicette, Alimento databaseAlimenti[], int totAlimDat, Spesa lista[], int totElemLista);

 
#endif