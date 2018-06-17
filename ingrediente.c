#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "various.h"
#include "ingrediente.h"
#include "spesa.h"
#include "file.h"
#include "prodotti.h"

int addIngredientsGuided(Ingredienti ingredienti[], int *totIngredienti, char elencoCategorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase){
    char categoriaTemp[maxCatLen], scelta, alimentsTemp[maxCatLen];
    int pos, num;
    _Bool flag=0;
    while(!flag){
    	flag=1;
    	fputs("Quale è il nome dell'alimento da aggiungere alla ricetta??\n"
       		">>> ", stdout);
		scanf("%s", alimentsTemp);
		clearBuffer(); 
		system("@cls||clear");
    	pos=checkPresenceOrAdd(elencoCategorie, *&totCat, database, *&totDatabase, alimentsTemp);
    	if(pos<0){
    		return 0;	
    	}else{
    		fputs("Quanti te ne servono per questa ricetta?\n"
    			">>> ", stdout);
     	   	scanf("%d", &ingredienti[*totIngredienti].quantita);
     	   	clearBuffer(); 
			system("@cls||clear");
     	   	ingredienti[*totIngredienti].kcal=database[pos].kcal*ingredienti[*totIngredienti].quantita;
     	   	strcpy(ingredienti[*totIngredienti].nome, database[pos].nome);
    		strcpy(ingredienti[*totIngredienti].categoria, database[pos].categoria);
    		*totIngredienti=*totIngredienti+1;
        	return 1;
    	}
    }
    return 0;
}

//inserimento guidato di ingredienti in attesa di approvazione


int searchIngredient(Ingredienti ingredienti[], int totIngredienti, char elemento[]){
	for (int i = 0; i < totIngredienti; ++i) {
        if(0 == strcmp(elemento, ingredienti[i].nome)){
            return i;
        }
    }
    return -1;
}

void showIngredients(Ingredienti ingredienti[], int totIngredienti){
    printf("\n|%-30s|%-30s|%-30s|%-30s|\n", "Nome", "Categoria", "quantita", "kcal per 100g");
    puts("|------------------------------|------------------------------|------------------------------|------------------------------|");
    for (int i = 0; i < totIngredienti; ++i){
        printf("|%-30s|%-30s|%-30d|%-30d|\n", ingredienti[i].nome, ingredienti[i].categoria, ingredienti[i].quantita, ingredienti[i].kcal);
    }
    printf("\n");
}