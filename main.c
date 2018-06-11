#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"
#include "account.h"
#include "mainmenu.h"
#include "various.h"




int main() {
	
	


    _Bool flag=1;
    char userTemp[25], passwd[25], userLogin[25], scelta;
    Utente utenti[maxUtenti]; //vettore di utenti
    int totUtenti=0;
    FILE *pf;
    system("@cls||clear");
    while(flag){
    	
        fputs("Smart Fridge 0.03 Alpha\n\n"


            "1. Avviare la modalita' DEMO\n"
            "2. Avviare il programma\n\n"
            "0. Termina programma\n"
            ">>> ", stdout);
        scelta = getchar();  
        clearBuffer(); //Permette di svuotare il buffer della tastiera
        system("@cls||clear"); //pulisce la schermata video
        switch(scelta){
            case '1':
                //avvia funzione demo... aggiornamento del 02.06.2018, forse non l'avremo mai hahaha non serve...
                break;
            case '2':
                //se è la prima volta va alla creazione di un account amministratore, altrimenti chiede username e password
                //per vedere se è il primo avvio andremo a leggere un file binario dove ci sarà 0 se è il primo avvio, altrimenti 1 se esiste almeno un account
                if(NULL==(pf=fopen(accountlocation,"r"))){
                    //è la prima volta che si avvia il programma, andiamo a creare la struttura delle directory
                    make_directory(databasedir);
                    make_directory(ricettedir);
                    //e creiamo i primi file di archiviazione
                    createNewFile(accountlocation);
                    if(!createAccount(utenti, totUtenti, 1)){
                        system("@cls||clear");
                        printf("<!> Username già esistente\n\n");
                    }
                    totUtenti++;
                    saveAccount(accountlocation, utenti, totUtenti);
                }else{
                    //carico gli account in memoria
                    loadAccount(accountlocation, utenti, &totUtenti);
                }
                fclose(pf);
                //richiesta username e password
                //passaggio a menù principale 
                flag=0;
                do{  
                	puts("Login:\n");
                    //Schermata di login
                    fputs("Username:\n"
                        ">>> ", stdout);
                    scanf("%s", userLogin);
                    system("@cls||clear");
                    puts("Login:\n");
                    fputs("Password\n"
                        ">>> ", stdout);
                    scanf("%s", passwd);
                    if(userAuth(utenti, totUtenti, userLogin, passwd)){
                        flag=1;
                        clearBuffer();
                        mainmenu(userLogin, passwd, &totUtenti, utenti);
                    }else{
                        system("@cls||clear");
                        puts("<!> Username o password errati\n\n");
                    }
                }while (!flag); 
            break;
            case '0':
                //uscita dal programma
                flag=0;
                system("@cls||clear");
            break;
            default:
                system("@cls||clear");
                puts("<!> Perfavore, scegli tra le opzioni disponibili\n\n");
            break;
        }
    }
    return 0;
}