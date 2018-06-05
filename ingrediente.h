#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include "various.h"

int addIngredientsGuided(Ingredienti ingredienti[], int totIngredienti, char elencoCattgorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase);
int addIngredientsAppGuided(Ingredienti ingredienti[], int totIngredienti, char elencoCattgorie[][maxCatLen], int totCat, Alimento database[], int totDatabase, char elencoCatApp[][maxCatLen], int *totCatApp, Alimento alimApp[], int *totAlimApp);
int searchIngredient(Ingredienti ingredienti[], int totIngredienti, char elemento[]);

#endif