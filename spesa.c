#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "spesa.h"
#include "various.h"
#include "file.h"
#include "prodotti.h"

void showList(Spesa Elementlista[], int totElem){
	if (totElem>0){
		printf("|%-20s|%-30s|%-20s|\n", "Nome", "Categoria", "Quantità");
		puts("|--------------------|------------------------------|--------------------|");
		for (int i = 0; i < totElem; ++i){
			printf("|%-20s|%-30s|%-20d|\n", Elementlista[i].nome, Elementlista[i].categoria, Elementlista[i].quantita);
		}
		printf("\n");
	}else{
		puts("<!> Non e' presente alcun alimento nella lista della spesa");
	}
}


int addtoListGuided(Spesa listaSpesa[], int *totElemLista, char elencoCategorie[][maxCatLen], int *totCat, Alimento databaseAlimenti[], int *totDatabaseAlimenti){
    char categoriaTemp[maxCatLen], scelta, alimentsTemp[maxCatLen];
    int pos, posList, num, kcal, giorni;
    _Bool flag=1;
    while(flag){
    	flag=1;
    	fputs("Quale e' il nome dell'alimento da aggiungere alla lista della spesa?\n"
       		">>> ", stdout);
		scanf("%s", alimentsTemp);
		clearBuffer(); 
		system("@cls||clear");
		pos=checkPresenceOrAdd(elencoCategorie, *&totCat, databaseAlimenti, *&totDatabaseAlimenti, alimentsTemp);
    	if(pos<0){
    		return 0;	
    	}else{
   			posList = searchElement(listaSpesa, *totElemLista, alimentsTemp);
   			if (posList>=0){
   				flag=1;
   				while(flag){
   					flag=0;
   					system("@cls||clear");
    				fputs("<!> Alimento gia' presente nella lista della spesa\n\n"
    					"vuoi aggiungerne altri? s/n\n"
    					">>> ", stdout);
    				scelta=getchar();
    				clearBuffer(); 
    				switch(scelta){
    					case 's':
    						puts("Quanti ne vuoi aggiungere?");
    						scanf("%d", &num);
    						listaSpesa[posList].quantita=listaSpesa[posList].quantita + num;
    					break;
    					case 'n':
    						return 0;
    					break;
    					default:
    						flag=1;
    					break;
    				}
   				}		
    		}else{
    			system("@cls||clear");
    			strcat(listaSpesa[*totElemLista].nome, databaseAlimenti[pos].nome);
   				strcat(listaSpesa[*totElemLista].categoria, databaseAlimenti[pos].categoria);
 				fputs("Quanti ne vuoi aggiungere alla lista della spesa?\n"
    				">>> ", stdout);
       			scanf("%d", &listaSpesa[*totElemLista].quantita);
       			clearBuffer(); 
				system("@cls||clear");
    			*totElemLista=*totElemLista+1;
    			saveList(listlocation, listaSpesa, *totElemLista);
   				return 1;
    		}
    	}	
	}
}

int searchElement(Spesa Elementlista[], int totElem, char elemento[]){
	for (int i = 0; i < totElem; ++i) {
        if(0 == strcmp(elemento, Elementlista[i].nome)){
            return i;
        }
    }
    return -1;
}


int rimElem(Spesa lista[], int *totElem){
	char elementTemp[25], scelta;
	int nElem, pos;
	_Bool flag;
	system("@cls||clear");
	while(1){
		showList(lista, *totElem);
		fputs("Quale dei seguenti alimenti vuoi rimuovere dalla lista della spesa?\n"
			">>> ", stdout);
		scanf("%s", elementTemp);
		pos = searchElement(lista, *totElem, elementTemp);
		clearBuffer(); 
		system("@cls||clear");
		if(pos >= 0){
			while(!flag){
				flag = 1;
				fputs("Quanti alimenti vuoi che rimangano nella lista della spesa?\n"
					">>> ", stdout);
				scanf("%d", &nElem);
				clearBuffer();
				if(nElem == 0){
					scalaStruct(lista, *&totElem, pos);
					return 2;
				}
				system("@cls||clear");
				if (getQuantity(lista, *totElem, elementTemp, pos) - nElem <= 0){
					fputs("Il numero di elementi che vuoi rimuovere e' maggiore/uguale del numero degli elementi presenti\n"
						"Vuoi rimuovere interamente il prodotto? s/n\n"
						"premi 0 per annullare l'operazione\n"
						">>> ", stdout);
					scelta = getchar();
					clearBuffer();
					switch(scelta){
						case 's':
							scalaStruct(lista, *&totElem, pos);
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
				}else{
					lista[pos].quantita = lista[pos].quantita - nElem;
					getchar();
					return 1; 
				}
			}
		}else{
			puts("<!> Alimento non presente nella lista della spesa\n\n");
		}
	}
}

int getQuantity(Spesa Elementlista[], int totElem, char elemento[], int pos){
	if(pos>=0){
		return Elementlista[pos].quantita;
	}else{
		for (int i = 0; i < totElem; ++i) {
     	    if(0 == strcmp(elemento, Elementlista[i].nome)){
        	    return Elementlista[i].quantita;
        	}
    	}
	}
    return -1;
}

void scalaStruct (Spesa Elementlista[], int *totElem, int startPoint){
	for (int i = startPoint; i < *totElem-1; ++i){
		Elementlista[i] = Elementlista[i+1];
	}
	*totElem=*totElem-1;
}
