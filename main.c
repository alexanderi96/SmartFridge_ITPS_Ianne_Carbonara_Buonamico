#include <stdio.h>
//grazie al grande Niccolo ora so che per i bool non serve importare la seguente libreria...
//#include <stdbool.h>

int main() {
    //ma basta fare:
    _Bool flag=1;
    char scelta;
    printf("Smart Fridge 0.01 Alpha\n\n");
    do{
        printf("Premi 1 per la demo o 2 per avviare il programma\nAltrimenti premi 0 per uscire\n");
        scanf("%1s", &scelta);
        switch(scelta){
            case '1':
                printf("ciao");
                //avvia funzione demo
                break;
            case '2':
                //avvia il programma vero e proprio
                break;
            case '0':
                //esci
                flag=0;
                break;
            default:
                //default non fare nulla
                printf("Inserisci un valore corretto\n");
                break;
        }
    }while(!flag);
    return 0;
}
