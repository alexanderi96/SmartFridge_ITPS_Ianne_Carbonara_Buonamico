#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "various.h"
#include "intolleranze.h"




int createAccount(Utente utenti[], int totUtenti, int isadmin, Categorie elencoCategorie[], int *totCat){
    _Bool flag=1;
    char userTemp[25], scelta;
    fputs("Inserisci il nome utente\n"
        ">>> ", stdout);
    scanf("%s", userTemp);
    system("@cls||clear");
    clearBuffer();
    if(-1==searchAccount(utenti, totUtenti, userTemp)){
        utenti[totUtenti].totinto=0;
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
        fputs("Inserisci la tua data di nascita in formato gg/mm/aaaa\n"
            ">>> ", stdout);
        scanf("%2d/%2d/%4d", &utenti[totUtenti].eta.gg, &utenti[totUtenti].eta.mm, &utenti[totUtenti].eta.aaaa);
        system("@cls||clear");
        clearBuffer();
        fputs("Inserisci la password\n"
            ">>> ", stdout); //vanno integrate le funzioni per la gestione della passwd
        scanf("%s", utenti[totUtenti].password);
        system("@cls||clear");
        clearBuffer();
        utenti[totUtenti].isadmin=isadmin;
        strcpy(utenti[totUtenti].intopos, accountdir);
        strcat(utenti[totUtenti].intopos, userTemp);
        make_directory(utenti[totUtenti].intopos);
        strcat(utenti[totUtenti].intopos, "/intolleranze.txt");
        while(flag){
            system("@cls||clear");
            if(utenti[totUtenti].totinto=0){
                fputs("Desideri inserire qualche intolleranza?\n"
                    "s/n\n"
                    ">>> ", stdout);
            }else{
                fputs("Desideri inserire qualche altra intolleranza?\n"
                    "s/n\n"
                    ">>> ", stdout);
            }
            scelta=getchar();
            clearBuffer();
            switch(scelta){
                case 's':
                    if(addIntollerance(utenti[totUtenti].intolleranze[utenti[totUtenti].totinto], elencoCategorie, *&totCat)){
                        utenti[totUtenti].totinto++;
                    }
                break;
                case 'n':
                    flag=0;
                break;
                default:
                    system("@cls||clear");
                    puts("<!> Inserisci un valore corretto\n");
                break;
            }    
        }
        utenti[totUtenti].id=totUtenti;
        return 1;
    }else{
        return 0;
    }
}


int userAuth(Utente utenti[], int totUtenti, char user[], char passwd[]){
    for (int i = 0; i < totUtenti; ++i) {
        if(strcmp(user, utenti[i].user) == 0 && strcmp(passwd, utenti[i].password) == 0){
            return utenti[i].id;
        }
    }
    return -1;
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
            return i;
        }
    }
    return -1;
}

void showAccount(Utente utente){
    char isadmin[6];
    /*
    char user[25];
    char nome[25];
    char cognome[25];
    char password[25];
    int eta;
    _Bool isadmin;
    char intopos[50];
    int totinto;
    char intolleranze[maxCatLen][maxCatLen];
    */
    if(utente.isadmin){
        strcpy(isadmin, "Admin");
    }else{
        strcpy(isadmin, "Normal");
    }
    printf("|%-30s|%-30s|%-30s|\n"
        "|------------------------------|------------------------------|------------------------------|------------------------------|\n"
        "|%-30s|%-30s|%-30s|%-30s|\n", "Username","Nome", "Cognome", utente.user, utente.nome, utente.cognome, isadmin);
}

int getUser(Utente utenti[], int totUtenti, char username[], int userId){
    for (int i = 0; i < totUtenti; ++i){
        if(utenti[i].id==userId){
            strcpy(username, utenti[i].username);
            return 1;
        }
    }
    return 0;
}