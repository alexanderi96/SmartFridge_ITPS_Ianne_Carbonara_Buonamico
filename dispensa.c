#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "various.h"
#include "prodotti.h"
#include "spesa.h"
#include "dispensa.h"
#include "file.h"


//ritorna 1 se le date di scadenza coincidono, altriment 0 se non coincidono. bisogna prendere in considerazione anche l'anno
int compareExpiry(Alimento alimento){
	Data confronto;
	setCurrentDate(&confronto, alimento.giorniMaxUtil);
	if(confronto.aaaa>alimento.scadenza.aaaa){
		return 0; //la alimento.scadenza non è ancora arrivata
	}else if(confronto.aaaa==alimento.scadenza.aaaa){
		if(confronto.mm>alimento.scadenza.mm){
			return 0; //la alimento.scadenza non è ancora arrivata
		}else if(confronto.mm==alimento.scadenza.mm){
			if(confronto.gg>alimento.scadenza.gg){
				return 0;
			}else if(confronto.gg==alimento.scadenza.gg){
				return 1;
			}else{
				return -1;
			}
		}else{
			return -1; //la data è passata
		}
	}else{
		return -1; //la data è passata
	}
}


int addToStorage(Alimento dispensa[], int *totAlimenti, char elencoCategorie[][maxCatLen], int *totCat, Alimento databaseAlimenti[], int *totDatabaseAlimenti){
	Spesa appoggio;
    char categoriaTemp[maxCatLen], scelta, alimentsTemp[maxCatLen];
    int pos, posDisp, num, kcal, giorni;
    _Bool flag=1, ifAdded=0;
    while(flag){
    	flag=1;
	fputs("Quale e' il nome dell'alimento da aggiungere alla dispensa?\n"
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
    						ifAdded=1;
    						system("@cls||clear");
    						puts("Quanti ne vuoi aggiungere?");
    						scanf("%d", &num);
    						clearBuffer();
                    
    						if(compareExpiry(dispensa[posDisp])){
    							dispensa[posDisp].quantita=dispensa[posDisp].quantita+num;
    						}else{
    							addNewAliment(dispensa, *&totAlimenti, alimentsTemp, num, databaseAlimenti, *totDatabaseAlimenti);
    						}
    						//ho aggiunto un alimento (presente o non presente) nella dispensa
    					break;
    					case 'n':
    						puts("<*> Alimento non inserito\n");
    					break;
    					default:
    						flag=1;
    					break;
    				}
   				}
   				flag=1;		
    		}else{
    			ifAdded=1;
    			system("@cls||clear");
 				fputs("Inserisi la quantita' in g/ml da aggiungere alla dispensa?\n"
    				">>> ", stdout);
       			scanf("%d", &num);
       			clearBuffer(); 
				system("@cls||clear");
				addNewAliment(dispensa, *&totAlimenti, alimentsTemp, num, databaseAlimenti, *totDatabaseAlimenti);
    		}
    	}
    	flag=0;
    	while(!flag){
    		fputs("Vuoi aggiungere altri alimenti alla dispensa?\n"
    			"s/n\n"
    			">>> ", stdout);
    		scelta=getchar();
    		clearBuffer();
    		switch(scelta){
    			case 's':
    				flag=1;
    			break;
    			case 'n':
    				if(ifAdded){
    					saveStorage(dispensalocation, dispensa, *totAlimenti);
    					return 1;
    				}
    				return 0;
    			break;
    			default:
    				flag=0;
    			break;
    		}	
	
    	}
    }
}


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
    				addNewAliment(dispensa, *&totAlimenti, listaSpesa[posList].nome, listaSpesa[posList].quantita, database, totDatabase);
					scalaStruct(listaSpesa, *&totElemLista, posList);
    			}
			}else{
				addNewAliment(dispensa, *&totAlimenti, listaSpesa[posList].nome, listaSpesa[posList].quantita, database, totDatabase);
				scalaStruct(listaSpesa, *&totElemLista, posList);
			}
		}
	}
	puts("<*> Tutti gli elementi sono stati inseriti nella dispensa\n");
	saveList(listlocation, listaSpesa, *totElemLista);
	saveStorage(dispensalocation, dispensa, *totAlimenti);
	return 1;
}

void addNewAliment(Alimento dispensa[], int *totAlimenti, char nome[], int quantita, Alimento database[], int totDatabase){
	int pos=*totAlimenti;
	int posdatabase=searchAlimNocat(database, totDatabase, nome);
	strcpy(dispensa[pos].nome, database[posdatabase].nome);
	strcpy(dispensa[pos].categoria, database[posdatabase].categoria);
	dispensa[pos].giorniMaxUtil = database[posdatabase].giorniMaxUtil;
	
	/*
	la scadenza verrà impostata aggiungendo i giorni max di utilizzo alla data odierna, con tutti gli incrementi del caso in base alla data corrente
	*/
	setCurrentDate(&dispensa[pos].scadenza, dispensa[pos].giorniMaxUtil);

			 
	dispensa[pos].quantita = quantita;
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
	int pos;
	for (int i = 0; i < *totElemLista; ++i){
		pos = searchAlimDisp(dispensa, *totAlimenti, listaSpesa[i].nome);
		if(pos>-1){
			setCurrentDate(&confronto, dispensa[pos].giorniMaxUtil);
			if (confronto.mm==dispensa[pos].scadenza.mm){
				if (confronto.gg==dispensa[pos].scadenza.gg){
					dispensa[pos].quantita=dispensa[pos].quantita+listaSpesa[i].quantita;
				}else{
					addNewAliment(dispensa, *&totAlimenti, listaSpesa[i].nome, listaSpesa[i].quantita, database, totDatabase);
				}
			}else{
				addNewAliment(dispensa, *&totAlimenti, listaSpesa[i].nome, listaSpesa[i].quantita, database, totDatabase);
			}
			
		}else{
			addNewAliment(dispensa, *&totAlimenti, listaSpesa[i].nome, listaSpesa[i].quantita, database, totDatabase);
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
		puts("<!> Non e' presente alcun alimento nella dispensa");
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
		if(compareToCurrentDate(dispensa[i].scadenza)==-1){
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

int getQuantityR(Alimento dispensa[], int totAlimenti, char alim[], int startPoint){
	int quantita=0; 
	for (int i = startPoint; i < totAlimenti; ++i){
		if(strcmp(dispensa[i].nome, alim) == 0){			
			quantita=dispensa[i].quantita+getQuantityR(dispensa, totAlimenti, alim, i+1);	
		}
	}
	return quantita;
}

void rimIng(Alimento dispensa[], int *totAlimenti, Ingredienti ingredienti[], int totIngredienti){
	int qIngTemp, disPos;
	for (int i = 0; i < totIngredienti; ++i){
		qIngTemp=ingredienti[i].quantita;
		while(qIngTemp>0){
			disPos=searchAlimDisp(dispensa, *totAlimenti, ingredienti[i].nome);
			if(dispensa[disPos].quantita>qIngTemp){
				dispensa[disPos].quantita=dispensa[disPos].quantita-qIngTemp;
			}else{
				qIngTemp=qIngTemp-dispensa[disPos].quantita;
				scalaStructA(dispensa, *&totAlimenti, disPos);
			}
		}
	}
	saveStorage(dispensalocation, dispensa, *totAlimenti);
}