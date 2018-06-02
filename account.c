#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "various.h"




int createAccount(Utente utenti[], int totUtenti, int isadmin){
    char userTemp[25];
    fputs("Inserisci il nome utente\n"
        ">>> ", stdout);
    scanf("%s", userTemp);
    system("@cls||clear");
    clearBuffer();
    if(!searchAccount(utenti, totUtenti, userTemp)){
        strcpy(utenti[totUtenti].user, userTemp);
        fputs("Inserisci il tuo nome\n"
            ">>> ", stdout);
        scanf("%s", utenti[totUtenti].nome);
        system("@cls||clear");
        clearBuffer();
        fputs("Inserisci il tuo cognome\n"
            ">>> ", stdout);
        scanf("%s", utenti[totUtenti].cognome);
        system("@cls||clear");
        clearBuffer();
        fputs("Inserisci la tua età\n"
            ">>> ", stdout);
        scanf("%d", &utenti[totUtenti].eta);
        system("@cls||clear");
        clearBuffer();
        fputs("Inserisci la password\n"
            ">>> ", stdout); //vanno integrate le funzioni per la gestione della passwd
        scanf("%s", utenti[totUtenti].password);
        system("@cls||clear");
        clearBuffer();
        utenti[totUtenti].isadmin=isadmin;
        return 1;
    }else{
        return 0;
    }
}


int userAuth(Utente utenti[], int totUtenti, char user[], char passwd[]){
    for (int i = 0; i < totUtenti; ++i) {
        if(strcmp(user, utenti[i].user) == 0 && strcmp(passwd, utenti[i].password) == 0){
            return 1;
        }
    }
    return 0;
}

int checkAdmin(Utente utenti[], int totUtenti, char user[]){
    for (int i = 0; i < totUtenti; ++i){
        if(0 == strcmp(utenti[i].user, user)){
            return utenti[i].isadmin;
        }        
    }
    return -1;
}

int searchAccount(Utente utenti[], int totUtenti, char user[]){
    for (int i = 0; i < totUtenti; ++i) {
        if(0 == strcmp(user, utenti[i].user)){
            return 1;
        }
    }
    return 0;
}