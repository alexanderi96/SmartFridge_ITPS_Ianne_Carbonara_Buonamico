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

int addRecipes(Ricetta ricette[], int totRicette){
    char ricTemp[25], scelta, fileTempName[100];
    int pos, num;
    _Bool flag=1;
    printf("Inserisci il nome della ricetta che vuoi aggiungere\n");
    scanf("%s", ricTemp);
    pos = searchRecipes(ricette, totRicette, ricTemp); 
    if(pos==-1){
        strcpy(ricette[totRicette].nome, ricTemp);
        printf("Da che paese proviene?\n");
        scanf("%s", ricette[totRicette].paese);
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
    		puts("Vuoi aggiungere un nuovo ingrediente alla ricetta?");
    		scelta= getchar();

    		if (scelta=='s'){
    			addIngredients(ricette[totRicette].ingredienti, ricette[totRicette].totIngredienti);
    			ricette[totRicette].totIngredienti++;
    		}else if(scelta=='n'){
    			flag=0;
    		}else{
    			puts("<!> scelta errata");
    		}
    	}
    	
        return 1;
    }else{
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
