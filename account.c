//
// Created by aless on 20/04/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "passwd.h"
#include "file.h"
#include "account.h"


int createAccount(char file_name[]){
    //permette di creare un nuovo account

    utente utente;
    _Bool flag;
    printf("fif\n");
    do{
        flag=1;
        printf("Inserisci il nome utente (max 10 caratteri):\n");
        scanf("%s", utente.user);
        if(!searchOnTxt(utente.user, "account.txt")){
            FILE *pf=fopen(file_name, "a");
            if(pf==NULL){
                printf("errore\n");
            }else{
                fprintf(pf, "%s,", utente.user);
                fflush(stdin);
                printf("Inserisci il tuo nome\n");
                scanf("%s", utente.nome);
                fprintf(pf, "%s,", utente.nome);
                fflush(stdin);
                printf("Inserisci il tuo cognome\n");
                scanf("%s", utente.cognome);
                fprintf(pf, "%s,", utente.cognome);
                fflush(stdin);
                printf("Inserisci la tua età\n");
                scanf("%d", &utente.eta);
                fprintf(pf, "%d,", utente.eta);
                fflush(stdin);
                printf("Inserisci la password\n"); //vanno integrate le funzioni per la gestione della passwd
                scanf("%s", utente.password);
                fprintf(pf, "%s,", utente.password);
                fflush(stdin),
                utente.isadmin=1;
                fprintf(pf, "%d\n", utente.isadmin);
                printf("Utente salvato correttamente\n");
            }
            fclose(pf);
        }else{
            flag=0;
            printf("username già esistente\n");
        }
    }while(!flag);
    return 1;
}

int delete(char file_name[]){


}

int setAdmin(char file_name[]){


}

int userAuth(char user[], char passwd[], char file_name[]){
    utente utente;
    FILE *pf;
    pf=fopen(file_name, "r");
    while(!feof(pf)){
        printf("ciaone");
        fscanf(pf,"%s,%s,%s,%d,%s,%d\n", utente.user, utente.nome, utente.cognome, &utente.eta, utente.password, &utente.isadmin);
        if(0 == strcmp(utente.user, user)&& 0 == strcmp(utente.password, passwd)){
            fclose(pf);
            return 1;
        }
    }
    fclose(pf);
    return 0;
}