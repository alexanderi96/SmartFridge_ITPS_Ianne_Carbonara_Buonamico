#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "various.h"
#include "spesa.h"
#include "account.h"
#include "ricetta.h"
#include <time.h>
#include "dispensa.h"
#include "prodotti.h"
#include "ingrediente.h"
#include "mainmenu.h"
#include "intolleranze.h"

int mainmenu(char username[], char password[], int *totUtenti, Utente utenti[], char elencoCategorie[][maxCatLen], int *totCat){
	//gestione dell'orario
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

    Ricetta ricette[maxRicette];
    int menuSettimanale[totPastiSett];
    Alimento dispensa[maxAlimenti];

    Alimento database[100]; //l'elenco di tutti gli alimenti che si possono acquistare

    int menu[totPastiSett];
    
    Spesa lista[maxAlimenti];
    char scelta, searchWord[50];
    int isadmin, totAlimenti=0, totElem=0, rimRis=0, totRicette=0, totDatabase=0, prodinscad=0, contScad=0, contInScad=0; //isadmin: variabile usata per definire un nuovo account amministratore o non.
    _Bool flag;
    char userTemp;
    FILE *dis, *spe, *ric, *menuPtr;
    
    /*
    andiamo a controllare se è presente una qualche dispensa, altrimenti la andiamo a creare
    */
    

    loadDatabaseAlimenti(databaseAlimenti, database, &totDatabase);


    /*
    caricamento menù settimanale
    */
    
    if(NULL==(menuPtr=fopen(menulocation,"r"))){  
        createNewFile(menulocation);
    }else{
        loadMenu(menulocation, menuSettimanale);
    }
    fclose(menuPtr);
    
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

    contaProdScad(dispensa, totAlimenti, &contScad, &contInScad);
    system("@cls||clear");
    while(1){
    	
        printf("Benvenuto %s\n\n", username);
        printf("Oggi e' il: %d/%d/%d e sono le ore: %d:%d\nPassa una buona giornata!\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);



        
        if(contInScad>0){
        	printf("Ci sono %d prodotti in scadenza\n\n", contInScad);
            //da consigliare una ricetta
        }
        if(contScad>0){
            printf("Ci sono %d prodotti scaduti in frigo, avvio della procedura per l'eleiminazione\n"
                "Premi invio per continuare\n", contScad);
            
            getchar();

            rimScad(dispensa, &totAlimenti, lista, &totElem);
            contScad=0;
        }

        fputs("1. Gestione ricette\n"
            "2. Gestione intolleranze\n"
            "3. Gestione lista della spesa\n"
            "4. Gestione della dispensa\n"
            "5. Impostazioni\n"
            "6. Cerca\n\n" //funzione che permette di effettuare una ricerca in TUTTO il database, stampando informazioni sui risultati! esattamente come una pagina google
            "0. Logout\n"
            ">>> ", stdout);
        scelta = getchar(); 
        clearBuffer(); //Permette di svuotare il buffer della tastiera
        system("@cls||clear");
        switch(scelta){
            case '1':
                flag=1;
                while(flag){
                    fputs("Gestione ricette\n\n"
                        "1. Aggiungi una nuova ricetta\n"
                        "2. Visualizza le ricette\n"
                        "3. Rimuovi ricetta\n\n"
                        "0. Indietro\n"
                        ">>> ", stdout);
                    scelta = getchar();
                    clearBuffer();
                    system("@cls||clear");
                    switch (scelta){
                        case '1':
                            puts("Inserimento nuova ricetta\n");
                            if(checkAdmin(utenti, *totUtenti, username)){
                                if (addRecipes(ricette, &totRicette, elencoCategorie, *&totCat, database, &totDatabase)){
        							
                                    system("@cls||clear");
                                    puts("<*> Ricetta aggiunta correttamente\n");
                                }
                            }else{
                                system("@cls||clear");
                                puts("<*> Devi essere amministratore per aggiungere  una nuova ricetta\n");    
                            }
                            
                        break;
                        case '2':
                            puts("2. Visualizzazione delle ricette disponibili\n");
                            showRecipes(ricette, totRicette);
                            puts("\n\nPremi invio per tornare indietro...\n");
                            getchar();
                            system("@cls||clear");
                        break;
                        case '3': 
                            if(totRicette>0){
                                system("@cls||clear");
                                if(!rimrElem(ricette, &totRicette)){
                                    system("@cls||clear");
                                    puts("<!> nessuna ricetta e' stata rimossa\n");
                                }else{
                                    system("@cls||clear");
                                    puts("<*> Ricetta rimossa correttamente\n");
                                }  
                            }else{
                                puts("<!> Non e' presente alcuna ricetta\n");
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
                fputs("Gestione intolleranze\n\n"
                    "1. Aggiungi intolleranza\n"
                    "2. Rimuovi intolleranza\n\n"
                    "0. Ingietro\n"
                    ">>> ", stdout);
                //intolleranza
            break;
            case '3':
                flag=1;
                while(flag){
                    fputs("Gestione lista della spesa\n\n"
                        "1. Suggerisci alimento da inserire nella lista\n"
                        "2. Riduci o rimuovi elemento dalla lista della spesa\n"
                        "3. Visualizza la lista della spesa\n"
                        "4. Comunica alimenti acquistati\n\n"
                        "0. Indietro\n"
                        ">>> ", stdout);


                    scelta = getchar();
                    clearBuffer();
                    system("@cls||clear");
                    switch (scelta){
                        case '1':
                            puts("Suggerisci alimento da inserire nella lista della spesa\n\n");
                            if(addtoListGuided(lista, &totElem, elencoCategorie, *&totCat, database, &totDatabase)){
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
                                puts("<!> Non e' presente nessun elemento nella lista della spesa\n\n");
                            }
                        break;
                        case '3':
                            puts("3. Visualizza la lista della spesa\n");
                            showList(lista, totElem);
                            puts("\n\nPremi un tasto per tornare indietro...\n");
                            getchar();
                            system("@cls||clear");
                        break;
                        case '4':
                        	flag=1;
                        	while(flag){
                        		fputs("Che alimenti hai acquistato?\n\n"
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
                                        if(totElem>0){
                                            addAllToStorage(dispensa, &totAlimenti, lista, &totElem, database, totDatabase);
                                            loadList(listlocation, lista, &totElem);
                                            system("@cls||clear");
                                            puts("<*> Tutti gli alimenti sono stati inseriti nella dispensa\n\n");
                                        }else{
                                            puts("<*> Non sono presenti elementi da acquistare, premi 3 per aggiungere un prodotto esterno alla lista della spesa\n");
                                        }
                        			break;
                        			case '2':
                                        if(totElem>0){
                                            addPartialToStorage(dispensa, &totAlimenti, lista, &totElem, database, totDatabase);
                                            loadList(listlocation, lista, &totElem);
                                            system("@cls||clear");
                                            puts("<*> Tutti gli alimenti sono stati inseriti nella dispensa\n\n");
                                        }else{
                                            puts("<*> Non sono presenti elementi da acquistare, premi 3 per aggiungere un prodotto esterno alla lista della spesa\n");
                                        }
                        			break;
                        			case '3':
                        				addToStorage(dispensa, &totAlimenti, elencoCategorie, *&totCat, database, &totDatabase);
                                        system("@cls||clear");
                                        puts("<*> Tutti gli alimenti sono stati inseriti nella dispensa\n\n");
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
                            flag=1;
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
                        "1. Visualizza gli elementi presenti in dispensa\n\n"
                        "0. indietro\n"
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
                        "3. Ripristino ai dati di fabbrica\n\n"
                        "0. indietro\n"
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
                                    if(createAccount(utenti, *totUtenti, isadmin, elencoCategorie, *&totCat)){
                                        system("@cls||clear");
                                        puts("<!> Utente salvato correttamente\n\n");
                                        *totUtenti = *totUtenti + 1;
                                        saveAccount(accountlocation, utenti, *totUtenti);
                                    }else{
                                        system("@cls||clear");
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
            case '6':
                system("@cls||clear");
                fputs("6. Cerca\n\n"
                    "Questa funzione ti permette di ottenere informazioni riguardo tutto cio' che e' immagazzinato in questo programma\n"
                    "inserisci semplicemente il nome di un prodotto, una ricetta oppure un username, qua sotto ti comparira' tutto quello di cui hai bisogno!\n\n"
                    ">>> ", stdout);
                scanf("%s", searchWord);
                clearBuffer();
                if(!globalSearch(searchWord, utenti, *totUtenti, dispensa, totAlimenti, ricette, totRicette, database, totDatabase, lista, totElem)){
                    system("@cls||clear");
                    puts("<!> Nessuna corrispondenza\n");
                }else{
                    puts("\nPremi un tasto per continuare...");
                    getchar();
                    system("@cls||clear");
                }
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

int globalSearch(char searchWord[], Utente account[], int totAccount, Alimento dispensa[], int totAlimenti, Ricetta ricette[], int totRicette, Alimento databaseAlimenti[], int totAlimDat, Spesa lista[], int totElemLista){
    int totRis=0; //indica il numero di corrispondenze
    int posDat=searchAlimNocat(databaseAlimenti, totAlimDat, searchWord);
    int posDisp=searchAlimDisp(dispensa, totAlimenti, searchWord);
    int posRic=searchRecipes(ricette, totRicette, searchWord);
    int posSpe=searchElement(lista, totElemLista, searchWord);
    int posAcc=searchAccount(account, totAccount, searchWord);
    _Bool flagIng=0;
    
    puts("|--------------------------------------------------------------------------------------------|");  
    if (posDat>-1){
        printf("|%-92s|\n", "Info di base dell'alimento:");
        printf("|Nome: %-86s|\n"
            "|Categoria: %-81s|\n"
            "|Giorni massimi di utilizzo prima della scadenza: %-43d|\n"
            "|Kcal per 100g: %-77d|\n|%-92s|\n", databaseAlimenti[posDat].nome, databaseAlimenti[posDat].categoria, databaseAlimenti[posDat].giorniMaxUtil, databaseAlimenti[posDat].kcal, "");
        if(posSpe>-1){
            //dico se è presente nella lista della spesa
            printf("|Nella lista della spesa hai %-2d unita' di questo prodotto%-36s|\n|%-92s|\n", lista[posSpe].quantita, "", "");
        }else{
            printf("|Questo prodotto non e' presente nella tua lista della spesa%-32s|\n", "");
        }
        if (posDisp>-1){
            printf("|Hai %-3d unita' di questo prodotto in dispensa%-47s|\n|%-92s|\n", dispensa[posDisp].quantita, "", "");
            if(isInScadenza(dispensa[posDisp])==1){
                printf("|Attenzione, il seguente alimento scadra' il giorno %2d.%2d.%4d%-31s|\n", dispensa[posDisp].scadenza.gg, dispensa[posDisp].scadenza.mm, dispensa[posDisp].scadenza.aaaa, "");
            }
        }else{
            printf("|Questo prodotto non è presente in dispensa%-50s|\n", "");
        }
        for (int i = 0; i < totRicette; ++i){
            if(searchIngredient(ricette[i].ingredienti, ricette[i].totIngredienti, searchWord)>-1){
                if(!flagIng){
                    puts("Inoltre il prodotto e'presente nelle seguenti ricette:\n");
                    printf("\n|%-30s|%-30s|%-30s|\n", "Nome", "Paese", "tempo di preparazione");
                    puts("|------------------------------|------------------------------|------------------------------|");
                    flagIng=1;
                }
                showSingleRecipe(ricette[i]);
          }
        } //ho finito di mostrare le ricette

    }
    
    if(posRic>-1){
        printf("|Info relative alla ricetta:%-65s|\n", "");
        printf("|Nome ricetta: %-78s|\n"
            "|Nazione: %-83s|\n"
            "|Tempo di preparazione: %-3d min.%-61s|\n|%-92s|", ricette[posRic].nome, ricette[posRic].paese, ricette[posRic].tempoPrep, "", "");
        showIngredients(ricette[posRic].ingredienti, ricette[posRic].totIngredienti);
        printf("|%-92s|Numero totale di kcal:%d\n", "", calcTotKcal(ricette[posRic]));
    }
    if(posAcc>-1){
        printf("|Info relative all'account:%-66s|\n|%-92s|\n", "", "");
        showAccount(account[posAcc]);
        if(account[posAcc].totinto>0){
            printf("|--------------------------------------------------------------------------------------------|------------------------------|\n"
                "|%-92s|\n|%-92s|\n", "L'utente e' intollerante alle seguenti categorie di prodotti:", "");
            showInto(account[posAcc].intolleranze, account[posAcc].totinto);
        }
    }
     puts("|--------------------------------------------------------------------------------------------|");
    if(posDat == -1 && posAcc == -1 && posRic == -1){
        return 0;
    }else{
        return 1;
    }
}