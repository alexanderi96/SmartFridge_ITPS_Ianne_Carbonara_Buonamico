#include "stdio.h"
#include "account.h"
//grazie al grande Niccolo ora so che per i bool non serve importare la seguente libreria...
//#include <stdbool.h>



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



void lista_spesa(info_alimenti alimenti[], int i);



int main() {
    //ma basta fare:
    info_alimenti alimenti[100];
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
                pf=fopen("fboot.bin","r");
                if(pf){
                    fscanf(pf, "%d\t", &first);
                    fclose(pf);
                }else{
                    printf("Errore 01 chiusura del programma in corso..\n");
                }
                if(first){
                    //richiesta username e password
                    //vado al menù principale
                    printf("sas");
                }else{
                    //avvio la procedura per creare un account

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


//è da aggiustare e soprattutto popolare la i ma alcune cose non è possibile farle se prima non se ne fanno altre, però è una bozza :)
void lista_spesa(info_alimenti alimenti[], int i){

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