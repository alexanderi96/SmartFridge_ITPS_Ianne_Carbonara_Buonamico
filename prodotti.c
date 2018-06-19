//mi serve una funzione per aggiungere prodotti
//ed una per cercare tra i prodotti disponibili
//una funzione per aggiungere categorie
//un'altra per cercare le categorie

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "spesa.h"
#include "various.h"
#include "file.h"

void showCategories(char elencoCategorie[][maxCatLen], int totCat){
	printf("|%-20s|\n", "Elenco categorie");
  puts("|--------------------|");
	for (int i = 0; i < totCat; ++i){
		printf("|%-20s|\n", elencoCategorie[i]);
	}
	puts("");
}

void showAliments(Alimento database[], int totDatabase, char categoria[]){
	puts("Elenco categorie\n");
	for (int i = 0; i < totDatabase; ++i){
		if (strcmp(database[i].categoria, categoria)==0){
			printf("%s %d %d\n", database[i].nome, database[i].kcal, database[i].giorniMaxUtil);
		}
	}
}

int searchCat(char categorie[][maxCatLen], int totCat, char elemento[]){
	for (int i = 0; i < totCat; ++i) {
        if(0 == strcmp(elemento, categorie[i])){
            return i;
        }
    }
    return -1;
}

int searchAlim(Alimento database[], int totAlim, char elemento[], char categoria[]){
	for (int i = 0; i < totAlim; ++i) {
        if(0 == strcmp(database[i].categoria, categoria)){
            if (0 == strcmp(database[i].nome, elemento))
            {
            	return i;
            } 
        }
    }
    return -1;
} 

int searchAlimNocat(Alimento database[], int totAlim, char elemento[]){
	for (int i = 0; i < totAlim; ++i) {
        if (0 == strcmp(database[i].nome, elemento)){
            return i;
        }
    }
    return -1;
}

//consente di aggiungere gli alimenti al database e ritorna 1 se ha aggiunto una nuova categoria
void addAliments(Alimento database[], int *totElencoAlim, char categoriaTemp[], char alimentsTemp[], int kcal, int giorniMaxUtil){
	strcpy(database[*totElencoAlim].categoria, categoriaTemp);
  strcpy(database[*totElencoAlim].nome, alimentsTemp);
  database[*totElencoAlim].kcal=kcal;
  database[*totElencoAlim].giorniMaxUtil=giorniMaxUtil;
  int id_buffer[maxAlimenti];
  for (int i = 0; i < *totElencoAlim; ++i){
    id_buffer[i]=database[i].id_alimento;
  }
  database[*totElencoAlim].id_alimento=checkIdPresence(id_buffer, *totElencoAlim, 0);
  *totElencoAlim=*totElencoAlim+1;
  saveAlim(databaseAlimenti, database, *totElencoAlim);
}

void addCat(char categoriaTemp[], char elencoCategorie[][maxCatLen], int *totCat){
	//da aggiungere i controlli per vedere se abbiamo riempito l'elenco categorie
	strcpy(elencoCategorie[*totCat], categoriaTemp);
	*totCat = *totCat+1;
	saveCategories(catLocation, elencoCategorie, *totCat);
}

int checkPresenceOrAdd(char elencoCategorie[][maxCatLen], int *totCat, Alimento databaseAlimenti[], int *totDatabaseAlimenti, char alimentsTemp[]){
	char scelta, categoriaTemp[maxCatLen];
	_Bool flag=1;
    	int kcal, giorni, pos=searchAlimNocat(databaseAlimenti, *totDatabaseAlimenti, alimentsTemp);
		if (pos<0){
	   		while(scelta!='s' || scelta!='n' && flag){
	    		flag=0;
	    		system("@cls||clear");
	   			fputs("<!> Elemento non esistente\n\n"
	    			"Vuoi aggiungere questo elemento al database? s/n\n"
	    			">>> ", stdout);
   	 				scelta = getchar();
				clearBuffer(); 
				system("@cls||clear");
    			switch(scelta){
   					case 's':
   						showCategories(elencoCategorie, *totCat);
   						fputs("Inserisci la categoria alla quale appartiene\n"
   							"se la categoria che stai cercando non e' pressente puoi inserirla nel campo sottostante\n"
   							">>> ", stdout);
   						scanf("%s", categoriaTemp);
   						clearBuffer(); 
						system("@cls||clear");
    					if(searchCat(elencoCategorie, *totCat, categoriaTemp)<0){
    						//questa categoria non esiste
    						while(scelta!='s' || scelta!='n' && !flag){
    							flag=1;
	   							system("@cls||clear");
				    			fputs("<!> Categoria non esistente\n\n"
			   						"Vuoi creare una nuova categoria? s/n\n"
    								">>> ", stdout);
  				 				scelta = getchar();
								clearBuffer(); 
								switch(scelta){
    								case 's':
    									addCat(categoriaTemp, elencoCategorie, *&totCat);
    								break;
    								case 'n':
    									puts("operazione annullata");
    									return -1;
    								break;
    								default:
    									flag=0;
    								break;
    							}
    						}
    						flag=0;
    					}		
    					fputs("Inserisci la quantità di kkal ogni 100 g/l del suddetto prodotto\n"
       						">>> ", stdout);
      					scanf("%d", &kcal);
       		 			clearBuffer(); 
						system("@cls||clear");	
       					fputs("Per quanti giorni può essere tenuto in frigo il prodotto prima di cestinarlo?\n"
       						">>> ", stdout);
     					scanf("%d", &giorni);
       					clearBuffer(); 
						system("@cls||clear");
    					addAliments(databaseAlimenti, *&totDatabaseAlimenti, categoriaTemp, alimentsTemp, kcal, giorni);
    					pos= *totDatabaseAlimenti;

    					return pos;
    				break;
    				case 'n':
    					puts("operazione annullata");
   						return -1;
  					break;
   					default:
    					flag=1;
    				break;
   				}
   			}
   		}
   		return pos;
}
