#ifndef MENUSETTIMANALE_H
#define MENUSETTIMANALE_H

int generaMenu(Menu menuSett[], Ricetta ricette[], int totricette);
int searchCurrentMenu(Menu menuSett[], Data oggi);
int checkListandStorage(Spesa spesa[], int *totLista, Alimento dispensa[], int totAlimenti, Menu menuSettimanale[], Ricetta ricette[], int totRicette);
int ifIngredientsInStorage(Alimento aliTemp[], int totAlitemp, Alimento dispensa[], int totAlimenti, Spesa spesa[], int *totLista);
void checkTimeandcook(Utente utente, Ricetta ricette[], int totRicette, Menu menuSettimanale[], Alimento dispensa[], int *totAlimenti, Spesa spesa[], int *totLista, Alimento database[], int *totDatabase, char elencoCategorie[][maxCatLen], int *totCat);
void startCooking(Ricetta ricetta, Alimento dispensa[], int *totAlimenti, Ricetta ricette[], int totRicette, int nPersMang);
void copyIngredienttoAliment(Alimento alimenti[], Ingredienti ingredienti[], int dimensione);		
void multiplyForPNum(Alimento alimenti[], int totAlimenti, int nPers);
int checkPresenceForXPeople(Ricetta ricette[], int totRicette, Ricetta ricetta, Alimento dispensa[], int *totAlimenti, Spesa spesa[], int *totLista, Alimento database[], int *totDatabase, char elencoCategorie[][maxCatLen], int *totCat, int nPerMang);

#endif