//
// Created by aless on 20/04/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "passwd.h"
#include "file.h"
#include "account.h"


int createAccount(char file_name[], int isadmin){
    //permette di creare un nuovo account

    utente utente;
    _Bool flag;
    printf("fif\n");
    do{
        flag=1;
        printf("Inserisci il nome utente (max 10 caratteri):\n");
        scanf("%s", utente.user);
        if(!searchOnTxt(utente.user, file_name)){
            FILE *pf=fopen(file_name, "a");
            if(pf==NULL){
                printf("errore\n");
            }else{
                printf("Inserisci il tuo nome\n");
                scanf("%s", utente.nome);
                printf("Inserisci il tuo cognome\n");
                scanf("%s", utente.cognome);
                printf("Inserisci la tua età\n");
                scanf("%d", &utente.eta);
                printf("Inserisci la password\n"); //vanno integrate le funzioni per la gestione della passwd
                scanf("%s", utente.password);
                utente.isadmin=isadmin;
                fprintf(pf, "%s\t%s\t%s\t%d\t%s\t%d\n", utente.user,utente.nome,utente.cognome,utente.eta,utente.password,utente.isadmin);
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
        fscanf(pf,"%s\t%s\t%s\t%d\t%s\t%d\n", utente.user, utente.nome, utente.cognome, &utente.eta, utente.password, &utente.isadmin);
        if(0 == strncmp(utente.user, user, strlen(user)) && 0 == strncmp(utente.password, passwd, strlen(passwd))){
            fclose(pf);
            return 1;
        }
    }
    fclose(pf);
    return 0;
}

int checkAdmin(char user[], char file_name[]){
    utente utente;
    FILE *pf;
    pf=fopen(file_name, "r");
    while(!feof(pf)){
        fscanf(pf,"%s\t%s\t%s\t%d\t%s\t%d\n", utente.user, utente.nome, utente.cognome, &utente.eta, utente.password, &utente.isadmin);
        if(0 == strcmp(utente.user, user)){
            fclose(pf);
            return utente.isadmin;
        }
    }
    fclose(pf);
    return -1;
}