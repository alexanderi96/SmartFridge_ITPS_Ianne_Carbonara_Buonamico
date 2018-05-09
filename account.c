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
    char useraccount[15];
    int scelta;
    char password[15];

    printf("Inserisci il nome utente:\n");
    scanf("%s", user);
    if(searchOnFile(user, "account.csv")){
        FILE *pf=fopen(file_name, "a");
        if(pf==NULL){
            printf("errore\n");
        }else{
            fprintf(pf, "%s,%s", user, user);
        }
    }else{
        printf("username già esistente\n");
        return 1;
    }
    return 0;
}

int delete(char file_name[]){


}

int setAdmin(char file_name[]){


}