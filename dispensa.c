#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "various.h"
#include "prodotti.h"
#include "spesa.h"
#include "dispensa.h"
#include "file.h"






int addAllToStorage(Dispensa dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista, Alimento database[], int totDatabase){
	
	int pos, posdatabase, maxgiornimese;
	for (int i = 0; i < *totElemLista; ++i){
		pos = searchAlimDisp(dispensa, *totAlimenti, listaSpesa[i].nome);
		if(pos>-1){
			dispensa[pos].quantita=dispensa[pos].quantita+listaSpesa[i].quantita;
		}else{
			pos=*totAlimenti;
			posdatabase=searchAlimNocat(database, totDatabase, listaSpesa[i].nome);
			strcpy(dispensa[pos].nome, listaSpesa[i].nome);
			strcpy(dispensa[pos].categoria, listaSpesa[i].categoria);
			dispensa[pos].giorniMaxUtil = database[posdatabase].giorniMaxUtil;
			
			/*
			la scadenza verrà impostata aggiungendo i giorni max di utilizzo alla data odierna, con tutti gli incrementi del caso in base alla data corrente
			*/

			setCurrentDate(&dispensa[pos].scadenza, dispensa[pos].giorniMaxUtil);
			
			 
			dispensa[pos].quantita = listaSpesa[i].quantita;
			dispensa[pos].kcal = database[posdatabase].kcal;
			*totAlimenti=*totAlimenti+1;
		}
	}
	*totElemLista=0;
	saveList(listlocation, listaSpesa, *totElemLista);
	saveStorage(dispensalocation, dispensa, *totAlimenti);
	return 1;
}

int searchAlimDisp(Dispensa dispensa[], int totAlimenti, char alim[]){
	for (int i = 0; i < totAlimenti; ++i){
		if(strcmp(dispensa[i].nome, alim) == 0){
			return i;
		}
	}
	return -1;
}

void showAlimDisp(Dispensa dispensa[], int totAlimenti){
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

void contaProdScad(Dispensa dispensa[], int totAlimenti, int *countScad, int *countInScad){
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

int isInScadenza(Dispensa alimento){
	Data data;
	setCurrentDate(&data, 0);
	if (alimento.scadenza.aaaa <= data.aaaa){
		if(alimento.scadenza.mm <= data.mm){
			if(alimento.scadenza.gg <= data.gg){
				return 2;
			}else if(alimento.scadenza.gg <= data.gg + 3){
				return 1;
			}
		}
	}
	return 0;
}

int rimScad(Dispensa dispensa[], int *totAlimenti){
	puts("I seguenti alimenti verranno eliminati dalla dispensa:\n");
	printf("|%-20s|%-30s|%-20s|%-20s|%-20s|\n","Nome","Categoria","Quantita'","Scadenza","kcal X 100g");
	puts("|--------------------|------------------------------|--------------------|--------------------|--------------------|");
	for (int i = 0; i < *totAlimenti; ++i){
		if(isInScadenza(dispensa[i])==2){
			showSingleAlim(dispensa[i]);
			scalaStructA(dispensa, *&totAlimenti, i);
			i=0;
		}
	}
	puts("");
	saveStorage(dispensalocation, dispensa, *totAlimenti);
	return 1;
}

void scalaStructA (Dispensa alimento[], int *totAlim, int startPoint){
	for (int i = startPoint; i < *totAlim-1; ++i){
		alimento[i] = alimento[i+1];
	}
	*totAlim=*totAlim-1;
}

void showSingleAlim(Dispensa elmento){
	Alimento singAlim;
	Categorie categoria;
	loadSingleDatabaseAlimenti(databaseLocation, singAlim, elemento.id_alimento);
	loadSingleCat(catLocation, categoria);
	printf("|%-20s|%-30s|%-20d|%-2d.%2d.%-14d|%-20d|\n", singAlim.nome, categoria.categoria, elemento.quantita, elemento.scadenza.gg, elemento.scadenza.mm, elemento.scadenza.aaaa, database[i].kcal);
}