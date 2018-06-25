#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "various.h"
#include "file.h"
#include "prodotti.h"
#include "intolleranze.h"



int addIntollerance(char intolleranze[maxCatLen], char elencoCategorie[][maxCatLen], int *totCat){
	loadCategories(catLocation, elencoCategorie, *&totCat);
	
	_Bool flag=0;
	char scelta, tempCat[maxCatLen];
	system("@cls||clear");
	showCategories(elencoCategorie, *totCat);
	fputs("Seleziona la categoria di prodotti alla quale sei intollerante\n"
		">>> ", stdout);
	scanf("%s", tempCat);
	clearBuffer();
	if(searchCat(elencoCategorie, *totCat, tempCat)<0){
    	//se siamo qui questa categoria non esiste
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
    				strcpy(intolleranze, tempCat);
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
    	strcpy(intolleranze, tempCat);
    }
}

int rmInto(char intolleranze[][maxCatLen], int intoDim){
    char into[maxCatLen];
    int catPos;
    showCategories(intolleranze, intoDim);
    
    do{
        fputs("Inserisci l'intolleranza che vuoi rimuovere."
            ">>> ", stdout);
        scanf("%s", into);
       catPos=searchCat(intolleranze, intoDim, into);
       if (catPos<0){
           puts("<!> Intolleranza non presente\n");
       }else{
            rimCat(intolleranze, &intoDim, catPos);
       }
    }while(0>catPos);
}

void showInto(char intolleranze[][maxCatLen], int totInto){
	for (int i = 0; i < totInto; ++i){
		printf("|%-92s|\n", intolleranze[i]);
	}
}