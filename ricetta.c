#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "various.h"
#include "ricetta.h"
#include "ingrediente.h"
#include "prodotti.h"
#include "file.h"
#include "dispensa.h"

/* @Kri: La seguente funzione permette di visualizzare le ricette
* La funzione stampa il nome della ricetta e il paese di provenienza
* ....
*/

void showRecipes(Ricetta ricette[], int totRicette){
	printf("\n|%-25s|%-25s|\n", "Nome", "Paese");
	puts("|-------------------------|-------------------------|");
	for (int i = 0; i < totRicette; ++i){
		printf("|%-25s|%-25s|\n", ricette[i].nome, ricette[i].paese);
	}
	printf("\n");
}

/* @Kri: La seguente funzione permette di inserire una nuova ricetta
* La funzione controllerà se la ricetta esiste confrontando il nome della stesa
* permette di inserire il nome della ricetta, il paese di provenienza e gli ingredienti
* ....
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
    	createNewFile(ricette[*totRicette].ingrePos); //andiamo a creare il file contenente gli ingredienti per questa ricetta
    	createNewFile(ricette[*totRicette].prepaPos);
        *totRicette=*totRicette+1;
        saveRecipes(repiceslocation, ricette, *totRicette);
        return 1;
    }else{
    	system("@cls||clear");
    	puts("<!> Ricetta già presente\n");
    	return 0;
    }
}

//inserimento ricette da approvare


int searchRecipes(Ricetta ricette[], int totRicette, char elemento[]){
	for (int i = 0; i < totRicette; ++i) {
        if(0 == strcmp(elemento, ricette[i].nome)){
            return i;
        }
    }
    return -1;
}

int rimrElem(Ricetta ricette[], int *totRicette){
	char ricTemp[25], scelta;
	int nElem, pos;
	_Bool flag;
	system("@cls||clear");
	while(1){
		showRecipes(ricette, *totRicette);
		fputs("Quale delle seguenti ricette vuoi rimuovere?\n"
			">>> ", stdout);
		scanf("%s", ricTemp);
		clearBuffer();
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

void scalarStruct (Ricetta ricette[], int totRicette, int startPoint){
	for (int i = startPoint; i < totRicette-1; ++i){
		ricette[i] = ricette[i+1];
	}
}

int calcolaRicettaConsigliata(Alimento dispensa[], int totAlimenti, Ricetta ricette[], int totRicette){
	int count=0;
	for (int i = 0; i < totAlimenti; ++i){
		if(isInScadenza(dispensa[i])){
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
