#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "various.h"
#include "spesa.h"
#include "account.h"
#include "ricetta.h"

int mainmenu(char username[], char password[], int *totUtenti, Utente utenti[]){
    Ricetta ricette[maxRicette];
    Alimento dispensa[maxAlimenti];
    Spesa lista[maxAlimenti];
    char scelta;
    int isadmin, totAlimenti=0, totElem=0, rimRis=0, totRicette=0; //isadmin: variabile usata per definire un nuovo account amministratore o non.
    _Bool flag;
    char userTemp;
    FILE *dis, *spe, *ric;
    
    /*
    andiamo a controllare se è presente una qualche dispensa, altrimenti la andiamo a creare
    */
    if(NULL==(dis=fopen(dispensalocation,"r"))){  
        createNewFile(dispensalocation);
    }else{
        loadStorage(dispensalocation, dispensa, &totAlimenti);
    }
    fclose(dis);

    if(NULL==(ric=fopen(repiceslocation,"r"))){  
        createNewFile(repiceslocation);
    }else{
        loadRecipes(repiceslocation, ricette, &totRicette);
    }
    fclose(ric);

    if(NULL==(spe=fopen(listlocation,"r"))){  
        createNewFile(listlocation);
    }else{
        loadList(listlocation, lista, &totElem);  
    }
    fclose(spe);


    system("@cls||clear");
    while(1){
        printf("Benvenuto %s\n\n", username);
        fputs("1. Gestione ricette\n"
            "2. Gestione intolleranze\n"
            "3. Gestione lista della spesa\n"
            "4. Impostazioni\n\n"
            "0. Logout\n"
            ">>> ", stdout);
        scelta = getchar(); //Permette di svuotare il buffer della tastiera
        clearBuffer();
        system("@cls||clear");
        switch(scelta){
            case '1':
                flag=1;
                while(flag){
                    fputs("Gestione ricette\n\n"
                        "1. Aggiungi una nuova ricetta\n"
                        "2. Visualizza le ricette\n"
                        "3. Ricerca per ingrediente\n"
                        "4. Rimuovi ricetta\n\n"
                        "0. Indietro\n"
                        ">>> ", stdout);
                    scelta = getchar();
                    clearBuffer();
                    system("@cls||clear");
                    switch (scelta){
                        case '1':
                            puts("1. Aggiungi una nuova ricetta\n\n");
                            if(checkAdmin(utenti, *totUtenti, username)){
                                if (addRecipes(ricette, totRicette)){
        							createNewFile(ricette[totRicette].ingrePos); //andiamo a creare il file contenente gli ingredienti per questa ricetta
                                    totRicette++;
                                    system("@cls||clear");
                                    puts("<*> Ricetta aggiunta correttamente\n\n");
                                }
                            }else{
                                //altrimenti andrà a fare una richiesta all'admin
                                //che dovrà decidere se accettarla o meno al prossimo login
                            }
                            saveRecipes(repiceslocation, ricette, totRicette);
                            
                        break;
                        case '2':
                            puts("3. Visualizzazione delle ricette disponibili\n");
                            showRecipes(ricette, totRicette);
                            puts("\n\nPremi un tasto per tornare indietro...\n");
                            getchar();
                            clearBuffer();
                            system("@cls||clear");
                        break;
                        case '3':
                        break;
                        case '4':

                            
                            if(totRicette>0){
     
                                system("@cls||clear");
                                rimrElem(ricette, totRicette);
                                
                                saveRecipes(repiceslocation, ricette, totRicette);
                            }else{
                                puts("<!> Non è presente alcuna ricetta\n");
                            }
                            

                        break;
                        case '0':
                            flag=0;
                        break;
                        default:
                            system("@cls||clear");
                            puts("<!> Perfavore, scegli tra le opzioni disponibili\n\n");
                        break;
                    }
                }




                

                
            break; 
            case '2':
                puts("4. Comunica intolleranza");
                //intolleranza
            break;
            case '3':
                flag=1;
                while(flag){
                    /* Nicolò Mod */
                    fputs("Gestione lista della spesa\n\n"
                        "1. Suggerisci alimento da inserire nella lista\n"
                        "2. Effettua una modifica su gli elementi da acquistare\n"
                        "3. Visualizza la lista della spesa\n\n"
                        "0. Indietro\n"
                        ">>> ", stdout);
                    /* end Nicolò Mod */


                    scelta = getchar();
                    clearBuffer();
                    system("@cls||clear");
                    switch (scelta){
                        case '1':
                            puts("1. Suggerisci alimento da inserire nella lista della spesa\n\n");
                            if(checkAdmin(utenti, *totUtenti, username)){
                                if (addtoList(lista ,totElem)){
                                    totElem++;
                                    system("@cls||clear");
                                    puts("<*> Elemento aggiunto con successo alla lista della spesa\n\n");
                                }
                            }else{
                                //altrimenti andrà a fare una richiesta all'admin
                                //che dovrà decidere se accettarla o meno al prossimo login
                            }
                            saveList(listlocation, lista, totElem);
                        break;
                        case '2':
                            if(totElem>0){
                                rimRis = rimElem(lista, totElem);
                                system("@cls||clear");
                                if(rimRis == 1){
                                    puts("<!> L'alimento selezionato e'atato ridotto\n\n");
                                }else if(rimRis == 2){
                                    puts("<!> L'elemento selezionato e'stato rimosso\n\n");
                                    totElem--;
                                }else{
                                    puts("<!> Operazione annullata dall'utente\n\n");
                                }
                                saveStorage(dispensalocation, dispensa, totAlimenti);
                            }else{
                                puts("<!> Non è presente nessun elemento nella lista della spesa\n\n");
                            }
                        break;
                        case '3':
                            puts("3. Visualizza la lista della spesa\n");
                            showList(lista, totElem);
                            puts("\n\nPremi un tasto per tornare indietro...\n");
                            getchar();
                            clearBuffer();
                            system("@cls||clear");
                        break;
                        case '0':
                            flag=0;
                        break;
                        default:
                            system("@cls||clear");
                            puts("<!> Perfavore, scegli tra le opzioni disponibili\n\n");
                        break;
                    }
                }
                //suggerisci_spesa(info_alimenti alimenti[], int i);
            break;
            case '4':
                flag=1;
                while(flag){
                    flag=1;
                    fputs("5. Impostazioni\n\n"
                        "1. Inserimento nuovo account\n"
                        "2. Modifica grado utente\n"
                        "0. indietro\n\n"
                        ">>> ", stdout);
                    scelta = getchar();
                    system("@cls||clear");
                    clearBuffer();
                    switch (scelta){
                        case '1':
                            if(*totUtenti<maxUtenti){    
                                puts("1. Inserimento nuovo account\n\n");
                                if(checkAdmin(utenti, *totUtenti, username)){
                                    while(flag){
                                        flag=0;
                                        fputs("Desideri creare un account amministratore?\n"
                                            "s/n\n"
                                            ">>> ", stdout);
                                        scelta = getchar();
                                        clearBuffer();
                                        switch (scelta){
                                           case 's':
                                                isadmin=1;
                                            break;
                                            case 'n':
                                                isadmin=0;
                                            break;
                                            default:
                                                flag=1;
                                                system("@cls||clear");
                                                puts("<!> Seleziona tra s/n\n\n");
                                            break;
                                        }
                                        system("@cls||clear");
                                    }
                                    if(createAccount(utenti, *totUtenti, isadmin)){
                                        puts("<!> Utente salvato correttamente\n\n");
                                        *totUtenti = *totUtenti + 1;
                                        saveAccount("account.txt", utenti, *totUtenti);
                                    }else{
                                        printf("<!> Username già esistente\n\n");
                                    }
                                }else{
                                    system("@cls||clear");
                                    printf("<!> Non si dispone dei diritti di amministrazione necessari per eseguire questa operazione\n\n");
                                }
                            }else{
                                system("@cls||clear");
                                printf("<!> Hai raggiunto il numero massimo di account\n\n");        
                            }
                        break;
                        case '2':
                            //qualcosa
                        break;
                        case '0':
                            flag=0;
                            system("@cls||clear");
                        break;
                        default:
                            system("@cls||clear");
                            puts("<!> Perfavore, scegli tra le opzioni disponibili\n\n");
                        break;
                    }
                }
                //alimento_input
            break;
            case '0':
                return 1;
            break;
            default:
                system("@cls||clear");
                puts("<!> Perfavore, scegli tra le opzioni disponibili\n\n");
            break;
        }
    }
}