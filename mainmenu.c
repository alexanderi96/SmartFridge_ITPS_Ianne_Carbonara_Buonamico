//
// Created by Christian Buonamico on 23/04/2018.
//

#include <stdio.h>
//Menù per la visualizzazione e la scelta delle funzioni da eseguire da parte dell'utente
int mainmenu(char username[], char password[]){

    char scelta;
    _Bool flag;

    printf("Menu' principale degli account\n");
    printf("-------------------------------------------\n");
    printf("1. Aggiungere nuova intolleranza\n");
    printf("2. Gestione del menu' della settimana\n");
    printf("3. Gestione della lista della spesa\n");
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
                printf("Avvio funzione per le intolleranze\n");
                break;
            case '2':
                printf("Avvio gestione del menu' della settimana\n");
                break;
            case '3':
                printf("Avvio gestione della lista della spesa\n");
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