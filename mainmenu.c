#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "various.h"
#include "spesa.h"
#include "account.h"
#include "ricetta.h"
#include <time.h>
#include "dispensa.h"

int mainmenu(char username[], char password[], int *totUtenti, Utente utenti[]){
	//gestione dell'orario
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

    Ricetta ricette[maxRicette];
    Ricetta menuSettimanale[7];
    Alimento dispensa[maxAlimenti];

    Alimento database[100]; //l'elenco di tutti gli alimenti che si possono acquistare

    char elencoCategorie[totCategorie][maxCatLen];
    Spesa lista[maxAlimenti];
    char scelta;
    int isadmin, totAlimenti=0, totElem=0, rimRis=0, totRicette=0, totDatabase=0, totCat=0, prodinscad=0; //isadmin: variabile usata per definire un nuovo account amministratore o non.
    _Bool flag;
    char userTemp;
    FILE *dis, *spe, *ric, *menu;
    
    /*
    andiamo a controllare se è presente una qualche dispensa, altrimenti la andiamo a creare
    */
    loadCategories(catLocation, elencoCategorie, &totCat);

    loadDatabaseAlimenti(databaseAlimenti, database, &totDatabase);


    /*
    caricamento menù settimanale
    */
    
    if(NULL==(menu=fopen(menulocation,"r"))){  
        createNewFile(menulocation);
    }else{
        loadMenu(menulocation, menuSettimanale);
    }
    fclose(menu);
    
    /*
    fine caricamento menù
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
        printf("Oggi e' il: %2d/%2d/%4d e sono le ore: %2d:%2d\nPassa una buona giornata!\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);

        prodinscad = contaProdScad(dispensa, totAlimenti);
        if(prodinscad>1){
        	printf("ci sono %d prodotti in scadenza\ndi coneguenza la ricetta consigliata per consumare questi prodotti e': %s\n\n", prodinscad, ricette[calcolaRicettaConsigliata(dispensa, totAlimenti, ricette, totRicette)].nome);
        }

        fputs("1. Gestione ricette\n"
            "2. Gestione intolleranze\n"
            "3. Gestione lista della spesa\n"
            "4. Gestione della dispensa\n"
            "5. Impostazioni\n\n"
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
                            puts("Inserimento nuova ricetta\n");
                            if(checkAdmin(utenti, *totUtenti, username)){
                                if (addRecipes(ricette, &totRicette, elencoCategorie, &totCat, database, &totDatabase)){
        							
                                    system("@cls||clear");
                                    puts("<*> Ricetta aggiunta correttamente\n");
                                }
                            }
                            
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
                                rimrElem(ricette, &totRicette);
                                
                                
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
                        "2. Riduci o rimuovi elemento dalla lista della spesa\n"
                        "3. Visualizza la lista della spesa\n"
                        "4. Comunica alimenti acquistatin\n\n"
                        "0. Indietro\n"
                        ">>> ", stdout);
                    /* end Nicolò Mod */


                    scelta = getchar();
                    clearBuffer();
                    system("@cls||clear");
                    switch (scelta){
                        case '1':
                            puts("Suggerisci alimento da inserire nella lista della spesa\n\n");
                            if(addtoListGuided(lista, &totElem, elencoCategorie, &totCat, database, &totDatabase)){
 		                        system("@cls||clear");
         	                    puts("<*> Elemento aggiunto con successo alla lista della spesa\n\n");
               		        }else{
               		        	
               		        	system("@cls||clear");
         	                    puts("<!> Operazione annullata dall'utente\n\n");
               		        }
                        break;
                        case '2':
                            if(totElem>0){
                                rimRis = rimElem(lista, &totElem);
                                system("@cls||clear");
                                if(rimRis == 1){
                                    puts("<!> L'alimento selezionato e'atato ridotto\n\n");
                                }else if(rimRis == 2){
                                    puts("<!> L'elemento selezionato e'stato rimosso\n\n");
                                    totElem--;
                                }else{
                                    puts("<!> Operazione annullata dall'utente\n\n");
                                }
                                saveList(listlocation, lista, totElem);
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
                        case '4':
                        	flag=1;
                        	while(flag){
                        		fputs("Che alimenti hai acquistato?\n"
                        			"1. Tutti quelli presenti nella lista della spesa\n"
        	                		"2. Solo parte degli alimenti presenti nella lista della spesa\n"
           	    	         		"3. Nessun alimento tra quelli presenti nella lista della spesa\n\n"
           		             		"0. Indietro\n"
                  		      		">>> ", stdout);
                    	    	scelta=getchar();
                    	    	clearBuffer();
                    	    	system("@cls||clear");
                       		 	switch(scelta){
                       		 		case '1':
                        				addAllToStorage(dispensa, &totAlimenti, lista, &totElem, database, totDatabase);
                        				system("@cls||clear");
                            			puts("<*> Tutti gli alimenti sono stati inseriti nella dispensa\n\n");
                        			break;
                        			case '2':
                        				//addPartialToStorage();
                        			break;
                        			case '3':
                        				//addToStorage();
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
            case '4':
            	flag=1;
                while(flag){
                    flag=1;
                    fputs("5. Gestione dispensa\n\n"
                        "1. Visualizza gli elementi presenti in dispensa\n"
                        "0. indietro\n\n"
                        ">>> ", stdout);
                    scelta = getchar();
                    system("@cls||clear");
                    clearBuffer();
                    switch (scelta){
                        case '1':
                            puts("1. Visualizzazione degli elementi presenti in dispensa\n\n");
                            showAlimDisp(dispensa, totAlimenti);
                            puts("\n\nPremi un tasto per tornare indietro...\n");
                            getchar();
                            clearBuffer();
                            system("@cls||clear");
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
            break;
            case '5':
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
                                        saveAccount(accountlocation, utenti, *totUtenti);
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