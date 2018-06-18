#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "various.h"



int createAccount(Utente utenti[], int totUtenti, int isadmin, Categorie elencoCategorie[], int *totCat);
int userAuth(Utente utenti[], int totUtenti, char user[], char passwd[]);
int checkAdmin(Utente utenti[], int totUtenti, char user[]);
int searchAccount(Utente utenti[], int totUtenti, char user[]);
void showAccount(Utente utente);
int getUser(Utente utenti[], int totUtenti, char username[], int userId)

#endif