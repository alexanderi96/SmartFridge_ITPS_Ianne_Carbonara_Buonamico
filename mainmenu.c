//
// Created by Christian Buonamico on 23/04/2018.
//

#include <stdio.h>
#include "account.h"
//Menù per la visualizzazione e la scelta delle funzioni da eseguire da parte dell'utente

typedef struct{
    char nome[15];
    char categoria[15];
    char gg[2];
    char mese[2];
    char anno[4];
    int quantita;
    int calorie;
    int utilizzo;
}info_alimenti;

int mainmenu(char username[], char password[]){

    char scelta;
    int isadmin; //variabile usata per definire un nuovo account amministratore o non.
    _Bool flag;

    printf("Benvenuto %s\n", username);
    printf("-------------------------------------------\n");
    printf("3: Inserimento nuova ricetta\n");
    printf("4: Comunica intolleranza\n");
    printf("5: Gestione lista della spesa\n");
    printf("9: Comunica alimento e visualizza ricette\n");
    printf("9: Impostazioni\n");

    printf("-------------------------------------------\n");
    printf("0. Logout\n");

    printf("Inserire una delle scelte possibili: \n");
    printf("N.B. Verra' preso in considerazione solo il primo carattere che inserirai\n\n");
    do{
        scanf("%c", &scelta);
        fflush(stdin);  //Permette di svuotare il buffer della tastiera

        flag=1;

        switch(scelta){
            case '1':


                //aggiungi_account
                break;
            case '3':
                printf("3: Inserimento nuova ricetta\n");
                //nuova_ricetta
                break;
            case '4':
                printf("4: Comunica intolleranza");
                //intolleranza
            break;
            case '5':
                printf("Gestione lista della spasa\n");
                printf("1: Suggerisci alimento da inserire nella lista della spesa\n");
                printf("2: Inserisci alimenti da inserire nella lista della spesa\n");
                //suggerisci_spesa(info_alimenti alimenti[], int i);
            break;
            case '7':
                printf("Menù settimanale");
                printf("1: Visualizza il menù settimanale");
                printf("2: Suggerimento nuova ricetta sulla base degli alimenti in scadenza\n");
            break;
            case '9':
                do{
                    printf("Impostazioni\n");
                    printf("1: Inserimento nuovo account\n");
                    printf("2: Nomina amministratore secondario\n");
                    printf("0: indietro\n");
                    scanf("%c", scelta);
                    fflush(stdin);
                    flag=1;
                    switch (scelta){
                        case '1':
                            printf("1: Inserimento nuovo account\n");
                            if(checkAdmin(username, "account.txt")){
                                createAccount("account.txt", isadmin);
                            }else{
                                printf("Non si dispone dei diritti di amministrazione necessari per eseguire questa operazione\n");
                            }
                            break;
                    }
                }while(flag);
                //alimento_input
            break;
            case '0':
                printf("Logout effettuato\n");
                flag=0;
                break;
            default:
                //caso di default
                printf("Per favore, inserisci un valore corretto\n");
                break;
        }
    }while(flag);
    return 1;
}

//Funzione per aggiungere una intolleranza, permanente o temporanea (Funzione 4)
void add_intollerance(char user[], char intollerance[]){
    int scelta_intolleranza;

    FILE *pf;
    pf=fopen("intollerance_user","a");
    if(NULL==(pf=fopen("intollerance_user","a"))){
        printf("Impossibile aprile il file\n");
    }else{
        do{
            printf("Specificare se l'intolleranza e' temporanea: 1 o permanete: 2\n");
            scanf("%d",scelta_intolleranza);
        }while(scelta_intolleranza!=1 || scelta_intolleranza!=2);
        printf("scpecificare le intolleranze:\n");
    }
}


//Funzione per agiungere un elemento alla lista della spesa (Funzione 5)
//è da aggiustare e soprattutto popolare la i ma alcune cose non è possibile farle se prima non se ne fanno altre, però è una bozza :)
void suggerisci_spesa(info_alimenti alimenti[], int i){
    printf("Inserire il nome dell'alimento che si intende aggiungere alla lista della spesa");
    scanf("%s", alimenti[i].nome);
    printf("Inserire la categoria dell'alimento");
    //è preferibile utilizzare un menù di scelta cosi da evitare errori di battitura
    scanf("%s", alimenti[i].categoria);
    printf("Inserire la data di scadenza dell'alimento nel formato gg:mm:aaaa");
    scanf("%s:%s:%s", alimenti[i].gg, alimenti[i].mese, alimenti[i].anno);
    printf("Inserire la quantità acquistata in grammi  o  litri");
    scanf("%d", &alimenti[i].quantita);
    printf("Inserire le cslorie contenute nell'alimento");
    scanf("%d", &alimenti[i].calorie);
    printf("Inserire i giorni in cui l'alimento può ancora essere utilizzato dopo l'apertura");
    scanf("%d", &alimenti[i].utilizzo);
}