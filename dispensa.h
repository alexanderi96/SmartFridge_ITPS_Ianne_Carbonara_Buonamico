#ifndef DISPENSA_H
#define DISPENSA_H

#include "various.h"

//questa libreria sarà la copia esatta di account.c, permetterà di fare le stesse cose solo a livello di dispensa.


int addAllToStorage(Alimento dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista, Alimento database[], int totDatabase);
int searchAlimDisp(Alimento dispensa[], int totAlimenti, char alim[]);
void showAlimDisp(Alimento dispensa[], int totAlimenti);

#endif