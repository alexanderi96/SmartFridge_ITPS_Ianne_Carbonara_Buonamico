#ifndef SPESA_H
#define SPESA_H

#include "various.h"

void showList(Spesa Elementlista[], int totElem);
void showCategories(char elencoCattgorie[][maxCatLen], int totCat);
void showAliments(Alimento database[], int totDatabase, char categoria[]);
int addtoListGuided(Spesa Elementlista[], int totElem, char elencoCattgorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase);
int searchElement(Spesa Elementlista[], int totElem, char elemento[]);
int searchCat(char categorie[][maxCatLen], int totCat, char elemento[]);
int searchAlim(Alimento database[], int totAlim, char elemento[], char categoria[]);
int searchAlimNocat(Alimento database[], int totAlim, char elemento[]);
int rimElem(Spesa lista[], int totElem);
int getQuantity(Spesa Elementlista[], int totElem, char elemento[], int pos);
void scalaStruct (Spesa Elementlista[], int totElem, int startPoint);

#endif