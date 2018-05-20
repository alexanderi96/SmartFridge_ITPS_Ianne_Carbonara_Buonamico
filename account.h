//
// Created by aless on 20/04/2018.
//

#ifndef SMARTFRIDGE_ITPS_IANNE_CARBONARA_BUONAMICO_ACCOUNT_H
#define SMARTFRIDGE_ITPS_IANNE_CARBONARA_BUONAMICO_ACCOUNT_H

#endif //SMARTFRIDGE_ITPS_IANNE_CARBONARA_BUONAMICO_ACCOUNT_H

typedef struct{
    char user[10];
    char nome[10];
    char cognome[10];
    char password[15];
    int eta;
    _Bool isadmin;
}utente;

int createAccount(char file_name[]);
int delete(char file_name[]);
int setAdmin(char file_name[]);
int userAuth(char user[], char passwd[], char file_name[]);