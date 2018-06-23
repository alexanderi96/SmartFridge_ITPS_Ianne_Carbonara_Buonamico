#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "various.h"
#include "ricetta.h"
#include "ingrediente.h"
#include "prodotti.h"
#include "file.h"
#include "dispensa.h"

/* La seguente funzione permette di visualizzare tutte le ricette presenti
* La funzione stamperà il nome della ricetta, il paese di provenienza e il tempo di preparazione
*/

void showRecipes(Ricetta ricette[], int totRicette){
	printf("\n|%-30s|%-30s|%-30s|%-30s|\n", "Nome", "Paese", "tempo di preparazione", "Contatore preparazioni");
	puts("|------------------------------|------------------------------|------------------------------|------------------------------|");
	for (int i = 0; i < totRicette; ++i){
		printf("|%-30s|%-30s|%-25d min.|%-30d|\n", ricette[i].nome, ricette[i].paese, ricette[i].tempoPrep, ricette[i].nVolteUs);
	}
	fputs("|--------------------------------------------------------------------------------------------|------------------------------|", stdout);
}

/* La seguente funzione permette di visualizzare una singola ricetta
* La funzione stamperà il nome della ricetta, il paese di provenienza e il tempo di preparazione
*/

void showSingleRecipe(Ricetta ricetta){
	printf("\n|%-30s|%-30s|%-30s|%-30s|\n", "Nome", "Paese", "tempo di preparazione", "Contatore preparazioni");
	puts("|------------------------------|------------------------------|------------------------------|------------------------------|");
	printf("|%-30s|%-30s|%-25d min.|%-30d|\n", ricetta.nome, ricetta.paese, ricetta.tempoPrep, ricetta.nVolteUs);
	fputs("|------------------------------|------------------------------|------------------------------|------------------------------|", stdout);
}

/* La seguente funzione permtte di determinare le Kcal totali per una ricetta
*/

int calcTotKcal(Ricetta ricetta){
	int totKcal=0;
	for (int i = 0; i < ricetta.totIngredienti; ++i){
		totKcal=totKcal+ricetta.ingredienti[i].kcal;
	}
	return totKcal;
}

/* La seguente funzione permette di inserire una nuova ricetta
* La funzione controllerà se la ricetta esiste confrontando il nome della stessa,
* permetterà di inserire il nome della ricetta, il paese di provenienza e gli ingredienti per prepararla
*/

int addRecipes(Ricetta ricette[], int *totRicette, char elencoCattgorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase){
    char ricTemp[25], scelta, fileTempNameIng[100], fileTempNamePrep[100];
    int pos, num;
    _Bool flag=1;
    fputs("Inserisci il nome della ricetta che vuoi aggiungere\n"
    	">>> ", stdout);
    scanf("%s", ricTemp);
    clearBuffer();
    system("@cls||clear");
    pos = searchRecipes(ricette, *totRicette, ricTemp); 
    if(pos==-1){
        strcpy(ricette[*totRicette].nome, ricTemp);
        puts("Inserimento nuova ricetta\n");
        fputs("Da che paese proviene?\n"
        	">>> ", stdout);
        scanf("%s", ricette[*totRicette].paese);
    	clearBuffer();
   		system("@cls||clear");
        strcpy(fileTempNameIng, ricettedir);
    	strcat(fileTempNameIng, ricTemp);
    	make_directory(fileTempNameIng);
    	strcpy(fileTempNamePrep, fileTempNameIng);
    	strcat(fileTempNameIng, "/ingredienti.txt");
    	strcat(fileTempNamePrep, "/preparazione.txt");
    	strcpy(ricette[*totRicette].ingrePos, fileTempNameIng);
    	strcpy(ricette[*totRicette].prepaPos, fileTempNamePrep);
    	ricette[*totRicette].totIngredienti=0;
    	while(flag){
    		flag=1;
    		puts("Inserimento nuova ricetta\n");
    		fputs("Vuoi aggiungere un nuovo ingrediente alla ricetta? s/n\n"
    			">>> ", stdout);
    		scelta= getchar();
    		clearBuffer();
   			system("@cls||clear");
    		if (scelta=='s'){
    			addIngredientsGuided(ricette[*totRicette].ingredienti, &ricette[*totRicette].totIngredienti, elencoCattgorie, *&totCat, database, *&totDatabase);
    		}else if(scelta=='n'){
    			flag=0;
    		}else{
   				system("@cls||clear");
    			puts("<!> scelta errata\n");
    		}
    	}
    	fputs("Quanto ci vuole a preparare questa ricetta?\n"
        	">>> ", stdout);
        scanf("%d", &ricette[*totRicette].tempoPrep);
        clearBuffer(); 
    	createNewFile(ricette[*totRicette].ingrePos); //andiamo a creare il file contenente gli ingredienti per questa ricetta
    	createNewFile(ricette[*totRicette].prepaPos);

        int id_buffer[maxRicette];
        for (int i = 0; i < *totRicette; ++i){
            id_buffer[i]=ricette[i].id_ricetta;
        }
        ricette[*totRicette].id_ricetta=checkIdPresence(id_buffer, *totRicette, 0);
        ricette[*totRicette].nVolteUs=0;
        *totRicette=*totRicette+1;
        saveRecipes(repiceslocation, ricette, *totRicette);
        return 1;
    }else{
    	system("@cls||clear");
    	puts("<!> Ricetta già presente\n");
    	return 0;
    }
}

//inserimento ricette da approvare <-- Commento di Ale

/* La seguente funzione controlla se data in input una stringa esiste una ricetta con lo stesso nome,
* La funzione confronterà il nome della nuova ricetta con il nome delle ricette già presenti
*/

int searchRecipes(Ricetta ricette[], int totRicette, char elemento[]){
	for (int i = 0; i < totRicette; ++i) {
        if(0 == strcmp(elemento, ricette[i].nome)){
            return i;
        }
    }
    return -1;
}

/* La seguente funzione permette di visualizzare tutte le ricette presenti e 
* permette di eliminare una ricetta tra quelli presenti
*/

int rimrElem(Ricetta ricette[], int *totRicette){
	char ricTemp[25], scelta;
	int nElem, pos;
	_Bool flag;
	system("@cls||clear");
	while(1){
		showRecipes(ricette, *totRicette);
		fputs("\nQuale delle seguenti ricette vuoi rimuovere?\n"
			"Altrimenti per annullare l'operazione premi 0.\n"
			">>> ", stdout);
		scanf("%s", ricTemp);
		clearBuffer();
		if(strcmp(ricTemp, "0")==0){

			return 0;
		}
		pos = searchRecipes(ricette, *totRicette, ricTemp); 
		system("@cls||clear");
		if(pos >= 0){
			while(!flag){
				flag = 1;
				fputs("Sicuro di voler rimuovere questa ricetta?\n"
					"s/n\n"
					">>> ", stdout);
				scelta = getchar();
				clearBuffer();
				switch(scelta){
					case 's':
						scalarStruct(ricette, *totRicette, pos);
						*totRicette=*totRicette-1;
						saveRecipes(repiceslocation, ricette, *totRicette);
						return 2;
					break;
					case 'n':
						return 0;
					break;
					default:
						flag = 0;
						system("@cls||clear");
						puts("<!> Seleziona tra s/n\n\n");
					break;
				}
			}
		}else{
			puts("<!> Ricetta non esistente\n");
		}
	}
}

/* La seguente funzione (dovrebbe confrontare le ricette e quindi le posizione degli indici)
* "Non ho capito bene ancora cosa faccia" appena finisco tutto poi la rivedo
*/

void scalarStruct (Ricetta ricette[], int totRicette, int startPoint){
	for (int i = startPoint; i < totRicette-1; ++i){
		ricette[i] = ricette[i+1];
	}
}

/* La seguente funzione permette di calcolare la ricetta consigliata per l'utente
* considerando gli alimenti prossimi alla scadenza in base alla dispensa disponibile
* Questa funzione e' da rivedere pesantemente
*/

int calcolaRicettaConsigliata(Alimento dispensa[], int totAlimenti, Ricetta ricette[], int totRicette){
	int count=0;
	for (int i = 0; i < totAlimenti; ++i){
		if(isInScadenza(dispensa[i])){ //@Kri: Ale ma questa funzione dove la trovo ? //@Ale: si trova in dispensa.c
			for (int j = 0; j < totRicette; ++j){
				for (int k = 0; k < ricette[j].totIngredienti; ++k){
					if(strcmp(dispensa[i].nome, ricette[j].ingredienti[k].nome)==0){
						return j;
					}
				}
			}
		}
	}
	return -1;
}

int searchRecipesById(int id, Ricetta ricette[], int totRicette){
	for (int i = 0; i < totRicette; ++i) {
        if(ricette[i].id_ricetta==id){
            return i;
        }
    }
    return -1;
}

void showInstructions(Ricetta ricetta){
	char buffer[50];
	FILE *pf;
	int len;
	if(NULL==(pf=fopen(ricetta.prepaPos, "r"))){
        fclose(pf);
    }else{
        while(!feof(pf)){
            //stampa di username, password, admin, nome, cognome ed età     
            fscanf(pf, "%s", buffer);
            len=len+strlen(buffer);
            if(len>90){
            	puts("");
            	len=0;
            }
        	printf("%s ", buffer);
        }
        fclose(pf);
    }
}

int getPossibleRepice(Ricetta ricette[], int totRicette, Alimento dispensa[], int totAlimenti){
	//ciclo che gira sulle ricette scorrendo tutti gli ingredienti confrontandoli uno ad uno con tutti quelli presenti in dispensa.
	//se un ingrediente non è disponibile in quantità necessaria andrà alla ricetta successiva.
	//se non troverà una ricetta disponibile ritornerà -1 altrimenti l'id della ricetta che è possibile cucinare
	_Bool flagTrovato=0, flagRicetta=1;
	for (int i = 0; i < totRicette; ++i){ //giro le ricette
		for (int j = 0; j < ricette[i].totIngredienti && flagRicetta; ++j){ //giro gli angredienti della singola ricetta
			flagTrovato=0;
			for (int k = 0; k < totAlimenti && !flagTrovato; ++k){ //giro gli alimenti disponibili
				if (strcmp(ricette[i].ingredienti[j].nome, dispensa[k].nome)==0 && (dispensa[k].quantita - ricette[i].ingredienti[j].quantita)>0){
					flagTrovato=1;
				}
			}
			if (!flagTrovato){
				//vuol dire che non ho trovato quell'ingrediente
				//dobbiamo cambiare ricetta
				flagRicetta=0;
			}
		}
		if (flagRicetta){
			/*questa ricetta è valida, andiamo a comunicarla*/
			return ricette[i].id_ricetta;
		}
	}
	return -1;
}
