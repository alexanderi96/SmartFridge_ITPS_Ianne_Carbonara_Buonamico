#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "various.h"
#include "file.h"
#include "prodotti.h"

int addIntollerance(int intolleranze, Categorie elencoCategorie[], int *totCat){
	loadCategories(catLocation, elencoCategorie, *&totCat);
	
	_Bool flag=0;
	char scelta, tempCat[maxCatLen];
	system("@cls||clear");
	showCategories(elencoCategorie, *totCat);
	fputs("Seleziona la categoria di prodotti alla quale sei intollerante\n"
		">>> ", stdout);
	scanf("%s", tempCat);
	clearBuffer();
	intoId=searchCat(elencoCategorie, *totCat, tempCat);
	if(intoId<0){
    	//questa categoria non esiste
    	while(scelta!='s' || scelta!='n' && !flag){
    		flag=1;
	   		system("@cls||clear");
			fputs("<!> Intolleranza non esistente\n\n"
				"Vuoi crearne una nuova? s/n\n"
    			">>> ", stdout);
  			scelta = getchar();
			clearBuffer(); 
			switch(scelta){
    			case 's':
    				system("@cls||clear");
    				addCat(tempCat, elencoCategorie, *&totCat);
    				intolleranze=*totCat;
    				return 1;
    			break;
    			case 'n':
    				puts("operazione annullata");
    				return 0;
    			break;
    			default:
    				flag=0;
    			break;
    		}
    	}
    	flag=0;
    }else{
    	intolleranze=intoId;
    }
}

void showInto(char intolleranze[][maxCatLen], int totInto){
	for (int i = 0; i < totInto; ++i){
		printf("%s\n", intolleranze[i]);
	}
}