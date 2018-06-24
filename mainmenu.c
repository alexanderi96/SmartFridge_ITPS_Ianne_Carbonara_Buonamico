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
#include "menusettimanale.h"

int mainmenu(char username[], char password[], int *totUtenti, Utente utenti[], char elencoCategorie[][maxCatLen], int *totCat){
	//gestione dell'orario
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

    Data oggi;

    Ricetta ricette[maxRicette];
    Menu menuSettimanale[totGiorniSett];
    Alimento dispensa[maxAlimenti];

    Alimento database[maxAlimenti]; //l'elenco di tutti gli alimenti che si possono acquistare
    
    Spesa lista[maxAlimenti];
    char scelta, searchWord[50], userTemp;
    _Bool flag;
    int isadmin, totAlimenti=0, totElem=0, rimRis=0, totRicette=0, totDatabase=0, prodinscad=0, contScad=0, contInScad=0, isInTime=0, posUtente, check, flagCoock=1; //isadmin: variabile usata per definire un nuovo account amministratore o non.
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
        loadMenu(menulocation, menuSettimanale, &isInTime);
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


    //se la data dell'ultimo alimento è passata va ad impostare il flag isInTime su 0 permettendo la generazione di un nuovo menù settimanale
    if(compareToCurrentDate(menuSettimanale[6].giorno)){
        isInTime=0;
    }

     /*
        per andare a creare il menù sommiamo i prodotti presenti in dispensa più quelli presenti nella lista della spesa
        Se la somma dovesse essere essere sufficente a preparare le ricette per i prossimi due giorni si informerà l'utente che deve andare a fare la spesa.
        Altrimenti si dirà "Nella dispensa non hai i prodotti necessari a fare le ricette per i prossimi due giorni, ti metto tutto nella lista della spesa."

        inoltre se il programma dovesse essere avviato tra le 12-15 e 19-22 il programma dirà "è ora di cucinare, per oggi a pranzo ti consiglio questa ricetta. vuoi cominciare a cucinare?"
        altrimenti andrà ad inserire i prodotti necessari nella lista della spesa. (dando come alternativa il link per scaricare l'app di just eat!)
        */    

    if(!isInTime){
            //andiamo a generare il menù settimanale
        isInTime=generaMenu(menuSettimanale, ricette, totRicette);
        saveMenu(menulocation, menuSettimanale, isInTime);
    }

    contaProdScad(dispensa, totAlimenti, &contScad, &contInScad);
    setCurrentDate(&oggi, 0);
    if ((oggi.hh>=12 && oggi.hh<15) || (oggi.hh>=19 && oggi.hh<22)){
        flagCoock=1;
    }else{
        flagCoock=0;
    }
    system("@cls||clear");
    while(1){

        setCurrentDate(&oggi, 0);
    	

        if(flagCoock){
            checkTimeandcook(utenti[searchAccount(utenti, *totUtenti, username)], ricette, totRicette, menuSettimanale, dispensa, &totAlimenti, lista, &totElem, database, &totDatabase, elencoCategorie, *&totCat);
            flagCoock=0;
            system("@cls||clear");
        }

        if(contInScad>0){
        	printf("Ci sono %d prodotti in scadenza\n"
                "Pertanto ti consiglio di andare a vedere quali ricette puoi fare con questi ingredienti attraverso la funzione cerca.\n\n"
                "|--------------------|------------------------------|--------------------|--------------------|--------------------|\n", contInScad);
            for (int i = 0; i < totAlimenti; ++i){
                if(isInScadenza(dispensa[i])){
                    showSingleAlim(dispensa[i]);
                }
            }
<<<<<<< HEAD
            puts("");
            //da consigliare una ricetta
=======
            
>>>>>>> baf051b1fbc81f6ceedd7162d48fceea96960689
        }
        if(contScad>0){
            printf("Ci sono %d prodotti scaduti in dispensa, avvio della procedura per l'eleiminazione\n"
                "Premi invio per continuare\n", contScad);
            
            getchar();

            rimScad(dispensa, &totAlimenti, lista, &totElem);
            contScad=0;
        }

        //controlliamo se abbiamo a disposizione gli alimenti per cucinare 

        check=checkListandStorage(lista, &totElem, dispensa, totAlimenti, menuSettimanale, ricette, totRicette);
        if(check==1){
            puts("<!> Ricordati di fare la spesa, gli alimenti presenti nella dispensa non sono sufficienti a cucinare le pietanze per i prossimi due giorni!\n");
        }else if(check==2){
            puts("<!> Attenzione gli alimenti presenti in dispensa e nella lista della spesa non sono sufficienti a cucinare le pietanze per i prossimi due giorni!\n"
                "Tranquillo, ho provveduto ad aggiornare la lista della spesa per tuo conto, ma non dimenticarti di fare la spesa.\n");
        }

        //andiamo a controllare se è ora di pranzo!



        printf("Benvenuto %s\n\n"
            "Oggi e' il: %d/%d/%d e sono le ore: %d:%d\n"
            "Passa una buona giornata!\n\n", username, oggi.gg, oggi.mm, oggi.aaaa, oggi.hh, oggi.min);

    
        fputs("1. CUCINIAMO!\n"
            "2. Ricettario\n"
            "3. Gestione intolleranze\n" //da completare!
            "4. Lista della spesa\n"
            "5. Gestione della dispensa\n"
            "6. Impostazioni\n"
            "7. Cerca\n\n" //funzione che permette di effettuare una ricerca in TUTTO il database, stampando informazioni sui risultati! esattamente come una pagina google
            "0. Logout\n"
            ">>> ", stdout);
        scelta = getchar(); 
        clearBuffer(); //Permette di svuotare il buffer della tastiera
        system("@cls||clear");
        switch(scelta){
            case '1':
                checkTimeandcook(utenti[searchAccount(utenti, *totUtenti, username)], ricette, totRicette, menuSettimanale, dispensa, &totAlimenti, lista, &totElem, database, &totDatabase, elencoCategorie, *&totCat);
            break;
            case '2':
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
                            while(flag){
                                puts("2. Visualizzazione delle ricette disponibili\n");
                                puts("\n\n1. Visualizza le ricette dalla più calorica alla meno calorica\n");
                                puts("2. Visualizza le ricette dalla più utilizzata alla meno utilizzata\n\n");
                                puts("0. Torna al menù\n");
                                scelta=getchar();
                                switch (scelta){
                                    case '1':
                                        ordinacalorie(ricette, totRicette);
                                        getchar();
                                    break;
                                    case '2':
                                       ordinautilizzo(ricette, totRicette);
                                       getchar();
                                    break;
                                    case '0':
                                        flag=0;
                                    break;
                                    default:
                                        system("@cls||clear");
                                        puts("<!> Per favore inserisci una scelta corretta!\n");
                                    break;
                                }
                            }
                            flag=1;
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
                            }else if(totRicette=4){
                                puts("<!> Attenzione, non è consigliabile avere meno di 4 ricette nel ricettario\n");
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
            case '3':
                puts("!! COMING SOON !!\n\n"
                    "Premi invio per tornare indietro . . .");
                getchar();
                system("@cls||clear");
                
            break;         
            case '4':
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
                                    puts("<!> L'alimento selezionato e'stato ridotto\n\n");
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
                            puts("\n\nPremi invio per tornare indietro...\n");
                            getchar();
                            system("@cls||clear");
                        break;
                        case '4':
                            mainmenusel4(dispensa, &totAlimenti, lista, &totElem, database, &totDatabase, elencoCategorie, *&totCat);
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
            case '5':
            	flag=1;
                while(flag){
                    flag=1;
                    fputs("Gestione dispensa\n\n"
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
            case '6':
                flag=1;
                while(flag){
                    flag=1;
                    fputs("Impostazioni\n\n"
                        "1. Inserimento nuovo account\n"
                        "2. Modifica grado utente\n"
                        "3. Ripristino ai dati di fabbrica\n"
                        "4. Modifica password\n\n"
                        "0. Indietro\n"
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
                            if(checkAdmin(utenti, *totUtenti, username)){
                                if(modifyUserPrivilege(utenti, *totUtenti)){
                                    puts("<*> Modifica effettuata correttamente\n");
                                    saveAccount(accountlocation, utenti, *totUtenti);
                                }else{
                                        puts("<!> Inserimento annullato\n");
                                    }
                            }else{
                                system("@cls||clear");
                                printf("<!> Non si dispone dei diritti di amministrazione necessari per eseguire questa operazione\n\n");
                            }
                        break;
                        case '3':
                            //ripristino ai dati di fabbrica da parte dell'amministratore
                            puts("!! COMING SOON !!\n\n"
                                "Premi invio per tornare indietro . . .");
                            getchar();
                            system("@cls||clear");
                        break;
                        case '4':
                            while(flag){
                                fputs("Modifica password.\n"
                                    "1. Modifica password\n\n"
                                    "0. Indietro\n"
                                    ">>> ", stdout);
                                scelta=getchar();
                                clearBuffer();
                                system("@cls||clear");
                                switch(scelta){
                                    case'1':
                                        if(modificaPassword(&utenti[searchAccount(utenti, *totUtenti, username)])){
                                            saveAccount(accountlocation, utenti, *totUtenti);
                                            puts("<*> Password salvata correttamente\n");
                                        }else{
                                            puts("<!> Errore");
                                        }
                                        flag=0;
                                    break;
                                    case '0':
                                        flag=0;
                                        system("@cls||clear");
                                        getchar();
                                    break;
                                    default:
                                        system("@cls||clear");
                                        puts("<!> Per favore inserisci una scelta corretta!\n");
                                    break;
                                }
                            }flag=1;
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
            case '7':
                system("@cls||clear");
                fputs("Cerca\n\n"
                    "Questa funzione ti permette di ottenere informazioni riguardo tutto cio' che e' immagazzinato in questo programma\n"
                    "inserisci semplicemente il nome di un prodotto, una ricetta oppure un username, qua sotto ti comparira' tutto quello di cui hai bisogno!\n\n"
                    ">>> ", stdout);
                scanf("%s", searchWord);
                clearBuffer();
                if(!globalSearch(searchWord, utenti, *totUtenti, dispensa, totAlimenti, ricette, totRicette, database, totDatabase, lista, totElem)){
                    system("@cls||clear");
                    puts("<!> Nessuna corrispondenza\n");
                }else{
                    puts("\nPremi invio per tornare indietro...");
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
        printf("|%-92s|\n|%-92s|\n"
            "|Nome: %-86s|\n"
            "|Categoria: %-81s|\n"
            "|Giorni massimi di utilizzo prima della scadenza: %-43d|\n"
            "|Kcal per 100g: %-77d|\n|%-92s|\n", "Info di base dell'alimento:", "", databaseAlimenti[posDat].nome, databaseAlimenti[posDat].categoria, databaseAlimenti[posDat].giorniMaxUtil, databaseAlimenti[posDat].kcal, "");
        if(posSpe>-1){
            //dico se è presente nella lista della spesa
            printf("|Nella lista della spesa hai %-2d unita' di questo prodotto%-36s|\n|%-92s|\n", lista[posSpe].quantita, "", "");
        }else{
            printf("|Questo prodotto non e' presente nella tua lista della spesa%-33s|\n", "");
        }
        if (posDisp>-1){
            printf("|Hai %-3d unita' di questo prodotto in dispensa%-47s|\n|%-92s|\n", dispensa[posDisp].quantita, "", "");
            if(isInScadenza(dispensa[posDisp])==1){
                printf("|Attenzione, il seguente alimento scadra' il giorno %2d.%2d.%4d%-31s|\n", dispensa[posDisp].scadenza.gg, dispensa[posDisp].scadenza.mm, dispensa[posDisp].scadenza.aaaa, "");
            }
        }else{
            printf("|%-92s|\n"
                "|%-92s|\n", "Questo prodotto non e' presente in dispensa", "");
        }
        for (int i = 0; i < totRicette; ++i){
            if(searchIngredient(ricette[i].ingredienti, ricette[i].totIngredienti, searchWord)>-1){
                if(!flagIng){
                    
                    printf("|%-92s|\n"
                        "|%-92s|\n"
                        "\n|%-30s|%-30s|%-30s|%-30s|\n"
                        "|%-92s|\n", "Inoltre il prodotto e'presente nelle seguenti ricette:", "------------------------------|------------------------------|------------------------------|------------------------------", "Nome", "Paese", "tempo di preparazione", "Contatore preparazioni", "------------------------------|------------------------------|------------------------------|------------------------------");
                    flagIng=1;
                }
                showSingleRecipe(ricette[i]);
          }
        } //ho finito di mostrare le ricette

    }
    
    if(posRic>-1){
        printf("\n|%-92s|\n|%-92s|\n" 
            "|Nome ricetta: %-78s|\n"
            "|Nazione: %-83s|\n"
            "|Tempo di preparazione: %-3d min.%-61s|\n"
            "|La seguente ricetta e' stata preparata %-3d volte%-44s|\n", "Info relative alla ricetta:", "", ricette[posRic].nome, ricette[posRic].paese, ricette[posRic].tempoPrep, "", ricette[posRic].nVolteUs, "");
        showIngredients(ricette[posRic].ingredienti, ricette[posRic].totIngredienti);
        printf("|%-92s|Numero totale di kcal:%d\n", "", calcTotKcal(ricette[posRic]));
    }
    if(posAcc>-1){
        printf("|Info relative all'account:%-66s|\n|%-92s|\n", "", "");
        showAccount(account[posAcc]);
        if(account[posAcc].totinto>0){
                printf("|%-92s|\n|%-92s|\n", "L'utente e' intollerante alle seguenti categorie di prodotti:", "");
            showInto(account[posAcc].intolleranze, account[posAcc].totinto);
        }else{
            printf("|L'utente non risulta essere intollerante ad alcun alimento%-34s|\n", "");
        }
    }
     puts("|--------------------------------------------------------------------------------------------|");
    if(posDat == -1 && posAcc == -1 && posRic == -1){
        return 0;
    }else{
        return 1;
    }
}