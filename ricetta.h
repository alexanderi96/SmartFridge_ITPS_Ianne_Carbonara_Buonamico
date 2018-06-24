#ifndef RECETTA_H
#define RICETTA_H

#include "various.h"

int addRecipes(Ricetta ricette[], int *totRicette, char elencoCattgorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase);
void showRecipes(Ricetta ricette[], int totRicette);
void showSingleRecipe(Ricetta ricetta);
int calcTotKcal(Ricetta ricetta);
int searchRecipes(Ricetta ricette[], int totRicette, char elemento[]);
int rimrElem(Ricetta ricette[], int *totRicette);
void scalarStruct (Ricetta ricette[], int totRicette, int startPoint);
int calcolaRicettaConsigliata(Alimento dispensa[], int totAlimenti, Ricetta ricette[], int totRicette);
int searchRecipesById(int id, Ricetta ricette[], int totRicette);
void showInstructions(Ricetta ricetta);
int getPossibleRepice(Ricetta ricette[], int totRicette, Alimento dispensa[], int totAlimenti, int nPerMang);
int incUsageById(int id_ricetta, Ricetta ricette[], int totRicette);
int getPossibleRepiceI(Utente utente, Ricetta ricette[], int totRicette);
int ifRepiceGI(Utente utente, Ricetta ricetta);
int checkIntollerance(char intolleranza[], Ricetta ricetta);
int getPossibleRepiceSingleI(char intolleranza[], Ricetta ricette[], int totRicette);
int showPossibleRecipesD(Ricetta ricette[], int totRicette, Alimento dispensa[], int totAlimenti, int nPerMang);

#endif