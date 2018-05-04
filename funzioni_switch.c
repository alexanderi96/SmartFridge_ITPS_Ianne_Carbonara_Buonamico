//
// Created by DANI on 03/05/2018.
//
/*
#include "stdio.h"


void aggiungi_account(char file_name[]){
    char user[10];
    char cognome[15];
    char useraccount[15];
    int scelta;
    char password[15];

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

void nomina_amm_secondario(){
}
void nuova_ricetta(){}
void intolleranza(){}
void suggerisci_spesa(){}
void inserisci_acquisto(){}
void menu_settimanale(){}
void ricetta_scadenza(){}
void alimento_input(){}

 */