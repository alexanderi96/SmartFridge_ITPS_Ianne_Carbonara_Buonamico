#ifndef PRODOTTI_H
#define PRODOTTI_H

void showCategories(char elencoCattgorie[][maxCatLen], int totCat);
void showAliments(Alimento database[], int totDatabase, char categoria[]);
int searchCat(char categorie[][maxCatLen], int totCat, char elemento[]);
int searchAlim(Alimento database[], int totAlim, char elemento[], char categoria[]);
int searchAlimNocat(Alimento database[], int totAlim, char elemento[]);
int addAliments(Alimento database[], int *totDatabase, char categoriaTemp[], char alimentsTemp[], int kcal, int giorniMaxUtil);
void addCat(char categoriaTemp[], char elencoCategorie[][maxCatLen], int *totCat);
int checkPresenceOrAdd(char elencoCategorie[][maxCatLen], int *totCat, Alimento databaseAlimenti[], int *totDatabaseAlimenti, char alimentsTemp[]);
void rimCat(char elencoCategorie[][maxCatLen], int *totCat, int startPoint);

#endif
