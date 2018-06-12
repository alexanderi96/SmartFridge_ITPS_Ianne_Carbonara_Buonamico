//
// Created by aless on 21/04/2018.
//

#ifndef FILE_H
#define FILE_H

#include "various.h"

int createNewFile(const char nome[]);
int saveAccount(const char nome[], Utente utneti[], int totUtenti);
int saveStorage(const char nome[], Alimento dispensa[], int totAlimenti);
int saveList(const char nome[], Spesa lista[], int totElem);
int getDim(const char nome[]);
int loadAccount(const char nome[], Utente utenti[], int *totUtenti); //restituisce il numero di account caricato, altrimenti 0 se non si riesce ad effettuare il caricamento
int loadStorage(const char nome[], Alimento dispensa[], int *totAlimenti);
int loadList(const char nome[], Spesa spesa[], int *totElem);
int loadRecipes(const char nome[], Ricetta ricette[], int *totRicette);
int saveRecipes(const char nome[], Ricetta ricette[], int totRicette);
int saveIngredients(const char nome[], Ingredienti ingredienti[], int totIngredienti);
int loadIngredients(const char nome[], Ingredienti ingredienti[], int totIngredienti);
int loadDatabaseAlimenti(const char nome[], Alimento database[], int *numeroAlimenti);
int loadCategories(const char nome[], char categorie[][maxCatLen], int *totCat);
int saveCategories(const char nome[], char categorie[][maxCatLen], int totCat);
int saveAlim(const char nome[], Alimento database[], int totDatabase);
int loadMenu(const char nome[], Ricetta menu[]);

#endif