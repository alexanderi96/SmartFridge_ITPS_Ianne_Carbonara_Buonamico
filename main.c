#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "account.h"
#include "mainmenu.h"
#include "file.h"
#include "funzioni_switch.h"
//grazie al grande Niccolo ora so che per i bool non serve importare la seguente libreria...
//#include <stdbool.h>

int main() {
    //ma basta fare:
//    info_alimenti alimenti[100];
    _Bool flag;
    char scelta, user[10], passwd[15];
    FILE *pf;
    do{
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
        scanf("%c", &scelta);
        fflush(stdin);  //Permette di svuotare il buffer della tastiera
        flag=0;
        switch(scelta){
            case '1':
                printf("ciao");
                //avvia funzione demo
                break;
            case '2':
                //avvia il programma vero e proprio
                //se è la prima volta va alla creazione di un account amministratore, altrimenti chiede username e password
                //per vedere se è il primo avvio andremo a leggere un file binario dove ci sarà 0 se è il primo avvio, altrimenti 1 se esiste almeno un account
                if(NULL==(pf=fopen("account.txt","r"))){
                    //è la prima volta che si avvia il programma, andiamo a creare il file fboot.bin
                    if(createNewFile("account.txt")){
                        if(!createAccount("account.txt")){
                           printf("errore\n");
                        }
                    }else{
                        printf("errore\n");
                        }
                }
                fclose(pf);
                //richiesta username e password
                //passaggio a menù principale
                do{
                    flag=1;
                    printf("Login: inserisci nome utente\n");
                    scanf("%s", user);
                    printf("Inserisci la password");
                    scanf("%s", passwd);
                    if(!userAuth(user, passwd, "account.txt")){
                        flag=0;
                        printf("Username o password errati\n");
                    }
                }while (!flag);
                flag=0;
                if(!mainmenu(user, "sas")){
                    printf("errore durante la chiusura del menù principale\n");
                }
                break;
            case '0':
                //uscita dal programma
                flag=1;
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