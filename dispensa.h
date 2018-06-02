#ifndef DISPENSA_H
#define DISPENSA_H

#include "various.h"

//questa libreria sarà la copia esatta di account.c, permetterà di fare le stesse cose solo a livello di dispensa.


int addToStorage(Alimento dispensa[], int totAlimenti);
int searchAlim(Alimento dispensa[], int totAlimenti, char alim[]);

#endif