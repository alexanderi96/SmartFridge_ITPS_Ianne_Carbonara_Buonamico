//
// Created by aless on 20/04/2018.
//

#ifndef SMARTFRIDGE_ITPS_IANNE_CARBONARA_BUONAMICO_ACCOUNT_H
#define SMARTFRIDGE_ITPS_IANNE_CARBONARA_BUONAMICO_ACCOUNT_H

#endif //SMARTFRIDGE_ITPS_IANNE_CARBONARA_BUONAMICO_ACCOUNT_H

typedef struct{
    char user[25];
    char nome[25];
    char cognome[25];
    char password[25];
    int eta;
    _Bool isadmin;
}utente;

int createAccount(char file_name[], int isadmin);
int delete(char file_name[]);
int setAdmin(char file_name[]);
int userAuth(char user[], char passwd[], char file_name[]);
int checkAdmin(char user[], char file_name[]);