#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include "various.h"

int addIngredientsGuided(Ingredienti ingredienti[], int *totIngredienti, char elencoCattgorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase);
int searchIngredient(Ingredienti ingredienti[], int totIngredienti, char elemento[]);
void showIngredients(Ingredienti ingredienti[], int totIngredienti);

#endif