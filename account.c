//
// Created by aless on 20/04/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "passwd.h"
#include "file.h"

int createAccount(char file_name[]){
    //permette di creare un nuovo account
    char user[10];

    printf("Inserisci il nome utente:\n");
    scanf("%s", user);
    if(searchOnFile(user)){
        FILE *pf=fopen(file_name, "a");
        if(pf==NULL){
            printf("errore\n");
        }else{

        }
    }else{
        printf("username già esistente\n");
    }


    printf("Inserisci il nome utente:\n");
    scanf("%s", user);
    printf("Inserire il cognome utente:\n");
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

int delete(char file_name[]){


}

int setAdmin(char file_name[]){


}