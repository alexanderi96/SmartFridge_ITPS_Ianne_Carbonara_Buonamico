#ifndef INTOLLERANZE_H
#define INTOLLERANZE_H

int addIntollerance(char intolleranze[maxCatLen], char elencoCategorie[][maxCatLen], int *totCat);
void showInto(char Intolleranze[][maxCatLen], int totInto);
int rmInto(char intolleranze[][maxCatLen], int intoDim);

#endif