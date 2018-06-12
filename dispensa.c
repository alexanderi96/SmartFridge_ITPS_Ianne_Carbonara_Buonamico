#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "various.h"
#include "prodotti.h"
#include "spesa.h"
#include "dispensa.h"
#include "file.h"






int addAllToStorage(Alimento dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista, Alimento database[], int totDatabase){
	
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
		printf("Nome\tCategoria\tQuantita'\tScadenza\tkcal per singolo elemento\n");
		for (int i = 0; i < totAlimenti; ++i){
			printf("%s\t%s\t%d\t%2d.%2d.%4d\t%d\n", dispensa[i].nome, dispensa[i].categoria, dispensa[i].quantita, dispensa[i].scadenza.gg, dispensa[i].scadenza.mm, dispensa[i].scadenza.aaaa, dispensa[i].kcal);
		}
		printf("\n");
	}else{
		puts("<!> Non è presente alcun alimento nella dispensa");
	}
}

int contaProdScad(Alimento dispensa[], int totAlimenti){
	int count=0;
	for (int i = 0; i < totAlimenti; ++i){
		if(isInScadenza(dispensa[i])){
			count++;
		}
	}
	return count;
}

int isInScadenza(Alimento alimento){
	Data data;
	setCurrentDate(&data, 3);
	if (alimento.scadenza.aaaa <= data.aaaa){
		if(alimento.scadenza.mm <= data.mm){
			if(alimento.scadenza.gg <= data.gg){
				return 1;
			}
		}
	}
	return 0;
}