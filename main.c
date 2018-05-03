#include <stdio.h>
#include <string.h>
#include "account.h"
#include "mainmenu.h"
#include "file.h"
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
                    if(!createNewFile("account.csv")){
                        printf("errore\n");
                    }else{
                        create("account.csv");
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
                //uscita dal programma
                printf("Programma terminato\n");
                break;
            default:
                //caso di default
                printf("Per favore, inserisci un valore corretto\n");
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