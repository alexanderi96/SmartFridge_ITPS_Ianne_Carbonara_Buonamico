#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "various.h"
#include "prodotti.h"
#include "spesa.h"
#include "dispensa.h"
#include "file.h"


//ritorna 1 se le date di scadenza coincidono, altriment 0 se non coincidono
int compareExpiry(Alimento alimento){
	Data confronto;
	setCurrentDate(&confronto, alimento.giorniMaxUtil);
	if (confronto.mm==alimento.scadenza.mm){
		if (confronto.gg==alimento.scadenza.gg){
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

/*
int addToStorage(Alimento dispensa[], int *totAlimenti, char elencoCategorie[][maxCatLen], int *totCat, Alimento databaseAlimenti[], int *totDatabaseAlimenti){
	Alimento appoggio;
    char categoriaTemp[maxCatLen], scelta, alimentsTemp[maxCatLen];
    int pos, posDisp, num, kcal, giorni;
    _Bool flag=1;
    while(flag){
    	flag=1;
    	fputs("Quale e' il nome dell'alimento da aggiungere al database?\n"
       		">>> ", stdout);
		scanf("%s", alimentsTemp);
		clearBuffer(); 
		system("@cls||clear");
		pos=checkPresenceOrAdd(elencoCategorie, *&totCat, databaseAlimenti, *&totDatabaseAlimenti, alimentsTemp);
    	if(pos<0){
    		return 0;	
    	}else{
   			posDisp = searchAlimDisp(dispensa, *totAlimenti, alimentsTemp);
   			if (posDisp>=0){
   				flag=1;
   				while(flag){
   					flag=0;
   					system("@cls||clear");
    				fputs("<!> Alimento gia' presente in dispensa\n\n"
    					"vuoi aggiungerne altri? s/n\n"
    					">>> ", stdout);
    				scelta=getchar();
    				clearBuffer(); 
    				switch(scelta){
    					case 's':
    						puts("Quanti ne vuoi aggiungere?");
    						scanf("%d", &num);

    						if(compareExpiry(dispensa[posDisp])){
    							dispensa[posDisp].quantita=dispensa[posDisp].quantita+num;
    						}else{
    							addNewAliment(dispensa, *&totAlimenti, dispensa[posDisp], database, totDatabase);
								scalaStruct(listaSpesa, *&totElemLista, posList);
    						}

    						
    						
   							return 1;
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
    			strcat(dispensa[*totAlimenti].nome, databaseAlimenti[pos].nome);
   				strcat(dispensa[*totAlimenti].categoria, databaseAlimenti[pos].categoria);
 				fputs("Quanti ne vuoi aggiungere alla dispensa?\n"
    				">>> ", stdout);
       			scanf("%d", &dispensa[*totAlimenti].quantita);
       			clearBuffer(); 
				system("@cls||clear");

            	int id_buffer[maxAlimenti];
   				for (int i = 0; i < pos; ++i){
		   			id_buffer[i]=dispensa[i].id_alimento;
    			}
   				dispensa[pos].id_alimento=checkIdPresence(id_buffer, pos, 0);
				*totAlimenti=pos+1;
   				return 1;
    		}
    	}	
	}
}
*/

int addPartialToStorage(Alimento dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista, Alimento database[], int totDatabase){
	Data confronto;
	int pos, posList, maxgiornimese, totelem;
	char elemTemp[maxCatLen];
	totelem=*totElemLista;
	while(0<*totElemLista){
		showList(listaSpesa, *totElemLista);
		fputs("Questi sono gli elementi presenti nella lista della spesa.\n"
			"Quale hai acquistato? (puoi selezionare solo un elemento alla volta)\n"
			"Altrimenti premi 0 per tornare al menu' precedente\n"
			">>> ", stdout);
		scanf("%s", elemTemp);
		clearBuffer();
		system("@cls||clear");
		if(strcmp(elemTemp, "0")==0){
			saveList(listlocation, listaSpesa, *totElemLista);
			saveStorage(dispensalocation, dispensa, *totAlimenti);
			return 1;
		}
		posList=searchElement(listaSpesa, *totElemLista, elemTemp);
		if(posList>-1){
			pos = searchAlimDisp(dispensa, *totAlimenti, listaSpesa[posList].nome);
			if(pos>-1){

				if(compareExpiry(dispensa[pos])){
    				dispensa[pos].quantita=dispensa[pos].quantita+listaSpesa[posList].quantita;
					scalaStruct(listaSpesa, *&totElemLista, posList);
    			}else{
    				addNewAliment(dispensa, *&totAlimenti, listaSpesa[posList], database, totDatabase);
					scalaStruct(listaSpesa, *&totElemLista, posList);
    			}
			}else{
				addNewAliment(dispensa, *&totAlimenti, listaSpesa[posList], database, totDatabase);
				scalaStruct(listaSpesa, *&totElemLista, posList);
			}
		}
	}
	puts("<*> Tutti gli elementi sono stati inseriti nella dispensa\n");
	saveList(listlocation, listaSpesa, *totElemLista);
	saveStorage(dispensalocation, dispensa, *totAlimenti);
	return 1;
}

void addNewAliment(Alimento dispensa[], int *totAlimenti, Spesa listaSpesa, Alimento database[], int totDatabase){
	int pos=*totAlimenti;
	int posdatabase=searchAlimNocat(database, totDatabase, listaSpesa.nome);
	strcpy(dispensa[pos].nome, listaSpesa.nome);
	strcpy(dispensa[pos].categoria, listaSpesa.categoria);
	dispensa[pos].giorniMaxUtil = database[posdatabase].giorniMaxUtil;
	
	/*
	la scadenza verrà impostata aggiungendo i giorni max di utilizzo alla data odierna, con tutti gli incrementi del caso in base alla data corrente
	*/
	setCurrentDate(&dispensa[pos].scadenza, dispensa[pos].giorniMaxUtil);

			 
	dispensa[pos].quantita = listaSpesa.quantita;
	dispensa[pos].kcal = database[posdatabase].kcal;
	int id_buffer[maxAlimenti];
   	for (int i = 0; i < pos; ++i){
   		id_buffer[i]=dispensa[i].id_alimento;
    }
   	dispensa[pos].id_alimento=checkIdPresence(id_buffer, pos, 0);
	*totAlimenti=pos+1;
}


int addAllToStorage(Alimento dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista, Alimento database[], int totDatabase){
	Data confronto;
	int pos, maxgiornimese;
	for (int i = 0; i < *totElemLista; ++i){
		pos = searchAlimDisp(dispensa, *totAlimenti, listaSpesa[i].nome);
		if(pos>-1){
			setCurrentDate(&confronto, dispensa[pos].giorniMaxUtil);
			if (confronto.mm==dispensa[pos].scadenza.mm){
				if (confronto.gg==dispensa[pos].scadenza.gg){
					dispensa[pos].quantita=dispensa[pos].quantita+listaSpesa[i].quantita;
				}else{
					addNewAliment(dispensa, *&totAlimenti, listaSpesa[i], database, totDatabase);
				}
			}else{
				addNewAliment(dispensa, *&totAlimenti, listaSpesa[i], database, totDatabase);
			}
			
		}else{
			addNewAliment(dispensa, *&totAlimenti, listaSpesa[i], database, totDatabase);
		}
	}
	*totElemLista=0;
	saveList(listlocation, listaSpesa, *totElemLista);
	saveStorage(dispensalocation, dispensa, *totAlimenti);
	return 1;
}

int searchAlimDisp(Alimento dispensa[], int totAlimenti, char alim[]){
	for (int i = 0; i < totAlimenti; ++i){
		if(strcmp(dispensa[i].nome, alim) == 0){
			return i;
		}
	}
	return -1;
}

void showAlimDisp(Alimento dispensa[], int totAlimenti){
	if (totAlimenti>0){
		printf("|%-20s|%-30s|%-20s|%-20s|%-20s|\n","Nome","Categoria","Quantita'","Scadenza","kcal X 100g");
		puts("|--------------------|------------------------------|--------------------|--------------------|--------------------|");

		for (int i = 0; i < totAlimenti; ++i){
			printf("|%-20s|%-30s|%-20d|%-2d.%2d.%-14d|%-20d|\n", dispensa[i].nome, dispensa[i].categoria, dispensa[i].quantita, dispensa[i].scadenza.gg, dispensa[i].scadenza.mm, dispensa[i].scadenza.aaaa, dispensa[i].kcal);
		}
		printf("\n");
	}else{
		puts("<!> Non è presente alcun alimento nella dispensa");
	}
}

void contaProdScad(Alimento dispensa[], int totAlimenti, int *countScad, int *countInScad){
	int ris;
	for (int i = 0; i < totAlimenti; ++i){
		ris=isInScadenza(dispensa[i]);
		if(ris==2){
			*countScad = *countScad + 1;
		}else if(ris==1){
			*countInScad = *countInScad + 1;
		}
	}
}

int isInScadenza(Alimento alimento){
	Data data;
	setCurrentDate(&data, 0);
	if (alimento.scadenza.aaaa == data.aaaa){
		if(alimento.scadenza.mm == data.mm){
			if(alimento.scadenza.gg <= data.gg){
				return 2;
			}else if(alimento.scadenza.gg <= data.gg + 3){
				return 1;
			}
		}else if(alimento.scadenza.mm < data.mm){
			//da migliorare questo algoritmo... bisogna capire quando è passato solo qualche giorno dall'inizio del mese
			//per ora lo diamo per scadutp
			return 2;
		}
	}else if(alimento.scadenza.aaaa < data.aaaa){
		//alimento scaduto da un anno
		return 2;
	}
	//l'alimento scadrà l'anno prossimo
	return 0;
}

int rimScad(Alimento dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista){
	puts("I seguenti alimenti verranno eliminati dalla dispensa e aggiunti automaticamente alla lista della spesa:\n");
	printf("|%-20s|%-30s|%-20s|%-20s|%-20s|\n","Nome","Categoria","Quantita'","Scadenza","kcal X 100g");
	puts("|--------------------|------------------------------|--------------------|--------------------|--------------------|");

	for (int i = 0; i < *totAlimenti; ++i){
		if(isInScadenza(dispensa[i])==2){
			showSingleAlim(dispensa[i]);
			copyToList(listaSpesa, *&totElemLista, dispensa[i]); //lo aggiungo nuovamente alla lista della spesa
			scalaStructA(dispensa, *&totAlimenti, i);
			i=0;
		}
	}
	puts("");
	saveStorage(dispensalocation, dispensa, *totAlimenti);
	return 1;
}

void scalaStructA (Alimento alimento[], int *totAlim, int startPoint){
	for (int i = startPoint; i < *totAlim-1; ++i){
		alimento[i] = alimento[i+1];
	}
	*totAlim=*totAlim-1;
}

void showSingleAlim(Alimento alimento){
	printf("|%-20s|%-30s|%-20d|%-2d.%2d.%-14d|%-20d|\n", alimento.nome, alimento.categoria, alimento.quantita, alimento.scadenza.gg, alimento.scadenza.mm, alimento.scadenza.aaaa, alimento.kcal);
}
