#ifndef DISPENSA_H
#define DISPENSA_H

#include "various.h"

//questa libreria sarà la copia esatta di account.c, permetterà di fare le stesse cose solo a livello di dispensa.


int addAllToStorage(Dispensa dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista, Alimento database[], int totDatabase);
int searchAlimDisp(Dispensa dispensa[], int totAlimenti, char alim[]);
void showAlimDisp(Dispensa dispensa[], int totAlimenti);
void contaProdScad(Dispensa dispensa[], int totAlimenti, int *countScad, int *countInScad);
int isInScadenza(Dispensa alimento);
int rimScad(Dispensa dispensa[], int *totAlimenti);
void scalaStructA (Dispensa alimento[], int *totAlim, int startPoint);
void showSingleAlim(Dispensa elmento);

#endif