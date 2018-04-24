//
// Created by aless on 20/04/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "passwd.h"
#include "file.h"

int create(char username[], char passwd[], char file_name[], _Bool admn){
    //permette di creare un nuovo account
    char user[10];
    char cognome[15];
    char useraccount[20];
    char scelta;
    char password[30];
    printf("Inserisci il nome utente:\n");
    printf("Max 10 caratteri\n");
    scanf("%s", user);
    printf("Inserire il cognome utente:\n");
    printf("Max 15 caratteri\n");
    scanf("%s",cognome);
    printf("Inserire un username:\n");
    printf("Max 20 caratteri\n");
    scanf("%s",useraccount);
    printf("Scegliere 1 per generare automaticamente la password e 2 per inserirla manualmente\n");
    scanf("%c",&scelta);
    if(scelta==1){
        //Generazione automatica della password
    }else{
        //Inserimento manuale della password
        printf("Inserire la password per l'account\n");
        printf("Max 30 caratteri\n");
        scanf("%s",password);
    }
    printf("Visualizzazione della password\n%s",password);
}

int delete(char username[], char passwd[], char file_name[]){


}

int setAdmin(char username[], char passwd[], char file_name[]){


}