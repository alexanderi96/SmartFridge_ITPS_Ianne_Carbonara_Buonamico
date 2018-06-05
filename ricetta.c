#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "various.h"
#include "ricetta.h"
#include "ingrediente.h"



void showRecipes(Ricetta ricette[], int totRicette){
	printf("\nNome\tPaese\n");
	for (int i = 0; i < totRicette; ++i){
		printf("%s\t%s\n", ricette[i].nome, ricette[i].paese);
	}
	printf("\n");
}

int addRecipes(Ricetta ricette[], int totRicette, char elencoCattgorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase){
    char ricTemp[25], scelta, fileTempName[100];
    int pos, num;
    _Bool flag=1;
    fputs("Inserisci il nome della ricetta che vuoi aggiungere\n"
    	">>> ", stdout);
    scanf("%s", ricTemp);
    clearBuffer();
    system("@cls||clear");
    pos = searchRecipes(ricette, totRicette, ricTemp); 
    if(pos==-1){
        strcpy(ricette[totRicette].nome, ricTemp);
        puts("Inserimento nuova ricetta\n");
        fputs("Da che paese proviene?\n"
        	">>> ", stdout);
        scanf("%s", ricette[totRicette].paese);
    	clearBuffer();
   		system("@cls||clear");
        //bisogna andare ad aggiungere la posizione dei file contenenti gli ingredienti ecc...
        //andiamo a creare il file degli ingredienti per questa ricetta
        strcpy(fileTempName, ricettedir);
    	strcat(fileTempName, ricTemp);
    	make_directory(fileTempName);
    	strcat(fileTempName, "/ingredienti.txt");
    	strcpy(ricette[totRicette].ingrePos, fileTempName);
    	ricette[totRicette].totIngredienti=0;
    	while(flag){
    		flag=1;
    		puts("Inserimento nuova ricetta\n");
    		fputs("Vuoi aggiungere un nuovo ingrediente alla ricetta? s/n\n"
    			">>> ", stdout);
    		scelta= getchar();
    		clearBuffer();
   			system("@cls||clear");
    		if (scelta=='s'){
    			addIngredientsGuided(ricette[totRicette].ingredienti, ricette[totRicette].totIngredienti, elencoCattgorie, *&totCat, database, *&totDatabase);
    			ricette[totRicette].totIngredienti++;
    		}else if(scelta=='n'){
    			flag=0;
    		}else{
   				system("@cls||clear");
    			puts("<!> scelta errata\n");
    		}
    	}
    	
        return 1;
    }else{
    	system("@cls||clear");
    	puts("<!> Ricetta già presente\n");
    	return 0;
    }
}

//inserimento ricette da approvare
int addReciApp(Ricetta ricette[], int totRicette, Ricetta riceApp[], int totRicApp, char elencoCategorie[][maxCatLen], int totCat, Alimento database[], int totDatabase, char elencoCatApp[][maxCatLen], int *totCatApp, Alimento alimApp[], int *totAlimApp){
	char ricTemp[25], scelta, fileTempName[100];
    int pos, num;
    _Bool flag=1;
    fputs("Inserisci il nome della ricetta che vuoi aggiungere\n"
    	">>> ", stdout);
    scanf("%s", ricTemp);
    clearBuffer();
    system("@cls||clear");
    pos = searchRecipes(ricette, totRicette, ricTemp); 
    if(pos==-1){
        strcpy(riceApp[totRicApp].nome, ricTemp);
        puts("Inserimento nuova ricetta\n");
        fputs("Da che paese proviene?\n"
        	">>> ", stdout);
        scanf("%s", riceApp[totRicApp].paese);
    	clearBuffer();
   		system("@cls||clear");
        //bisogna andare ad aggiungere la posizione dei file contenenti gli ingredienti ecc...
        //andiamo a creare il file degli ingredienti per questa ricetta
        strcpy(fileTempName, ricetteAppdir);
    	strcat(fileTempName, ricTemp);
    	make_directory(fileTempName);
    	strcat(fileTempName, "/ingredienti.txt");
    	strcpy(riceApp[totRicApp].ingrePos, fileTempName);
    	riceApp[totRicApp].totIngredienti=0;
    	while(flag){
    		flag=1;
    		puts("Inserimento nuova ricetta\n");
    		fputs("Vuoi aggiungere un nuovo ingrediente alla ricetta? s/n\n"
    			">>> ", stdout);
    		scelta= getchar();
    		clearBuffer();
   			system("@cls||clear");
    		if (scelta=='s'){
    			addIngredientsAppGuided(riceApp[totRicApp].ingredienti, riceApp[totRicApp].totIngredienti, elencoCategorie, totCat, database, totDatabase, elencoCatApp, *&totCatApp, alimApp, *&totAlimApp); 
    			riceApp[totRicApp].totIngredienti++;
    		}else if(scelta=='n'){
    			flag=0;
    		}else{
   				system("@cls||clear");
    			puts("<!> scelta errata\n");
    		}
    	}
    	
        return 1;
    }else{
    	system("@cls||clear");
    	puts("<!> Ricetta già presente\n");
    	return 0;
    }
}

int searchRecipes(Ricetta ricette[], int totRicette, char elemento[]){
	for (int i = 0; i < totRicette; ++i) {
        if(0 == strcmp(elemento, ricette[i].nome)){
            return i;
        }
    }
    return -1;
}

int rimrElem(Ricetta ricette[], int totRicette){
	char ricTemp[25], scelta;
	int nElem, pos;
	_Bool flag;
	system("@cls||clear");
	while(1){
		showRecipes(ricette, totRicette);
		fputs("Quale delle seguenti ricette vuoi rimuovere?\n"
			">>> ", stdout);
		scanf("%s", ricTemp);
		clearBuffer();
		pos = searchRecipes(ricette, totRicette, ricTemp); 
		system("@cls||clear");
		if(pos >= 0){
			while(!flag){
				flag = 1;
				fputs("Sicuro di voler rimuovere questa ricetta?\n"
					"s/n\n"
					"premi 0 per annullare l'operazione\n"
					">>> ", stdout);
				scelta = getchar();
				clearBuffer();
				switch(scelta){
					case 's':
						scalarStruct(ricette, totRicette, pos);
						return 2;
					break;
					case 'n':
						flag = 0;
						system("@cls||clear");
					break;
					case '0':
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
