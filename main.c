#include <stdio.h>
#include "account.h"
#include "file.h"
//grazie al grande Niccolo ora so che per i bool non serve importare la seguente libreria...
//#include <stdbool.h>

int main() {
    //ma basta fare:
    _Bool flag;
    char scelta;
    int first;
    FILE *pf;
    printf("Smart Fridge 0.01 Alpha\n\n");
    do{
        printf("Premi 1 per la demo o 2 per avviare il programma\nAltrimenti premi 0 per uscire\n");
        scanf("%1s", &scelta);
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
                if(NULL==(pf=fopen("fboot.bin","r"))){
                    printf("suca");
                    //è la prima volta che si avvia il programma, andiamo a creare il file fboot.bin
                    if(!createNewBin("fboot")){
                        printf("errore\n");
                    }
                    //poi avvio la procedura per creare un account
                }else {
                    fclose(pf);
                    //richiesta username e password
                    //vado al menù principale
                    printf("sas");
                }
                break;
            case '0':
                //esci
                break;
            default:
                //default non fare nulla
                printf("Inserisci un valore corretto\n");
                flag=0;
                break;
        }
    }while(!flag);
    return 0;
}