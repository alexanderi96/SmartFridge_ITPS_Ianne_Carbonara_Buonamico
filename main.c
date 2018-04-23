#include <stdio.h>
#include <string.h>
#include "account.h"
#include "mainmenu.h"
#include "file.h"
//grazie al grande Niccolo ora so che per i bool non serve importare la seguente libreria...
//#include <stdbool.h>

int main() {
    //ma basta fare:
    _Bool flag;
    char scelta;
    FILE *pf;
    printf("Smart Fridge 0.01 Alpha\n\n");
    // Visualizzazione delle scelte che potrà effettuare l'utente
    printf("Visualizzazione del menu' delle scelte \n");
    printf("----------------------------------\n");
    printf("1. Avviare la modalita' DEMO\n");
    printf("2. Avviare il programma\n");
    printf("----------------------------------\n");
    printf("0. Termina programma\n\n");
    printf("Inserire una delle scelte possibili:\n");
    printf("N.B. Verra' preso in considerazione solo il primo carattere che inserirai\n\n");
    do{
        scanf("%c", &scelta);
        fflush(stdin);  //Permette di svuotare il buffer della tastiera
        flag=1;
        switch(scelta){
            case '1':
                printf("ciao");
                //avvia funzione demo
                break;
            case '2':
                //avvia il programma vero e proprio
                //se è la prima volta va alla creazione di un account amministratore, altrimenti chiede username e password
                //per vedere se è il primo avvio andremo a leggere un file binario dove ci sarà 0 se è il primo avvio, altrimenti 1 se esiste almeno un account
                if(NULL==(pf=fopen("account.csv","r"))){
                    printf("suca");
                    //è la prima volta che si avvia il programma, andiamo a creare il file fboot.bin
                    if(!createNewCsv("account.csv")){
                        printf("errore\n");
                    }
                    //poi avvio la procedura per creare un account
                }else {
                    fclose(pf);
                    //richiesta username e password
                    //passaggio a menù principale
                    if(mainmenu("g", "sas")){

                    }
                }
                break;
            case '0':
                //escita dal programma
                printf("Programma terminato\n");
                break;
            default:
                //default non fare nulla
                printf("Per favore, inserisci un valore corretto\n");
                flag=0;
                break;
        }
    }while(!flag);
    return 0;
    }