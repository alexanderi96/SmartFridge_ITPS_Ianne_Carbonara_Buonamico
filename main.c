#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"
#include "account.h"
#include "mainmenu.h"
#include "various.h"




int main() {
    Categorie elencoCategorie[totCategorie];
    _Bool flag=1;
    char userTemp[25], passwd[25], userLogin[25], scelta;
    Utente utenti[maxUtenti]; //vettore di utenti
    int totUtenti=0, totCat=0, userId;
    FILE *pf;
    system("@cls||clear");
    while(flag){
    	
        fputs("Smart Fridge 0.03 Alpha\n\n"        
            "Nell'inserimento dei dati si raccomanda di non utilizzare spazi\n\n"
            "1. Avviare il programma\n\n"
            "0. Termina programma\n"
            ">>> ", stdout);
        scelta = getchar();  
        clearBuffer(); //Permette di svuotare il buffer della tastiera
        system("@cls||clear"); //pulisce la schermata video
        switch(scelta){
            case '1':
                loadCategories(catLocation, elencoCategorie, &totCat);
                //se è la prima volta va alla creazione di un account amministratore, altrimenti chiede username e password
                //per vedere se è il primo avvio andremo a leggere un file binario dove ci sarà 0 se è il primo avvio, altrimenti 1 se esiste almeno un account
                if(NULL==(pf=fopen(accountlocation,"r"))){
                    //è la prima volta che si avvia il programma, andiamo a creare la struttura delle directory
                    make_directory(databasedir);
                    make_directory(ricettedir);
                    make_directory(accountdir);
                    
                    //e creiamo i primi file di archiviazione
                    createNewFile(accountlocation);
                    if(!createAccount(utenti, totUtenti, 1, elencoCategorie, &totCat)){
                        system("@cls||clear");
                        printf("<!> Username già esistente\n\n");
                    }
                    system("@cls||clear");
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

                    userId=userAuth(utenti, totUtenti, userLogin, passwd);
                    if(-1<userId){
                        flag=1;
                        clearBuffer();
                        mainmenu(userId, &totUtenti, utenti, elencoCategorie, &totCat);
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