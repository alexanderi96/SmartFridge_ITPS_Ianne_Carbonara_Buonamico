#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "various.h"
#include "ingrediente.h"

int addIngredients(Ingredienti ingredienti[], int totIngredienti){
	_Bool flag=1;
	char	nomeTemp[25];
	fputs("Aggiungi un ingrediente a questa ricetta!\n"
		"inserisci il nome dell'ingrediente\n"
		">>> ", stdout);
	scanf("%s", nomeTemp);
	if(searchIngredient(ingredienti, totIngredienti, nomeTemp)==-1){
		strcpy(ingredienti[totIngredienti].nome, nomeTemp);
		fputs("A che categoria appartiene?\n"
			">>> ", stdout);
		scanf("%s", ingredienti[totIngredienti].categoria);
		fputs("Quanto te ne serve?\n"
			">>> ", stdout);
		scanf("%d", &ingredienti[totIngredienti].quantita);
		fputs("Quante kcal possiede questo ingrediente?\n"
		">>> ", stdout);
		scanf("%d", &ingredienti[totIngredienti].kcal);
		//devo andare ad inserire questo ingrediente nel reegistro intolleranze di questa ricetta
		return 1;
	}
	return 0;
}

int searchIngredient(Ingredienti ingredienti[], int totIngredienti, char elemento[]){
	for (int i = 0; i < totIngredienti; ++i) {
        if(0 == strcmp(elemento, ingredienti[i].nome)){
            return i;
        }
    }
    return -1;
}