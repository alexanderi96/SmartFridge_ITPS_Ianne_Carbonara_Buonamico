#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "various.h"
#include "prodotti.h"
#include "spesa.h"
#include "dispensa.h"
#include "file.h"

#include <time.h>




int addAllToStorage(Alimento dispensa[], int *totAlimenti, Spesa listaSpesa[], int *totElemLista, Alimento database[], int totDatabase){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int pos, posdatabase, maxgiornimese;
	for (int i = *totElemLista; i > 0; --i){
		pos = searchAlimDisp(dispensa, *totAlimenti, listaSpesa[i].nome);
		if(pos>-1){
			dispensa[pos].quantita=dispensa[pos].quantita+listaSpesa[i].quantita;
		}else{
			posdatabase=searchAlimNocat(database, totDatabase, listaSpesa[i].nome);
			strcat(dispensa[*totAlimenti].nome, listaSpesa[i].nome);
			strcat(dispensa[*totAlimenti].categoria, listaSpesa[i].categoria);
			dispensa[*totAlimenti].giorniMaxUtil = database[posdatabase].giorniMaxUtil;
			
			/*
			la scadenza verrà impostata aggiungendo i giorni max di utilizzo alla data odierna, con tutti gli incrementi del caso in base alla data corrente
			*/

			if(tm.tm_mon==2){
				maxgiornimese=28;
			}else if(tm.tm_mon == 4 || tm.tm_mon == 6 || tm.tm_mon== 9 || tm.tm_mon == 11){
				maxgiornimese=30;
			}else{
				maxgiornimese=31;
			}

			if(tm.tm_mon+database[posdatabase].giorniMaxUtil>maxgiornimese){
				if(tm.tm_mon==12){
					dispensa[*totAlimenti].scadenza.mm=1;
					dispensa[*totAlimenti].scadenza.aaaa=tm.tm_year + 1900 +1;
				}else{
					dispensa[*totAlimenti].scadenza.mm=tm.tm_mon + 1 + 1;
				}
				dispensa[*totAlimenti].scadenza.gg=database[posdatabase].giorniMaxUtil+tm.tm_mday-maxgiornimese;
			}else{
				dispensa[*totAlimenti].scadenza.gg=database[posdatabase].giorniMaxUtil+tm.tm_mday;
			}
			
			 
			dispensa[*totAlimenti].quantita = listaSpesa[i].quantita;
			dispensa[*totAlimenti].kcal = database[posdatabase].kcal;
		}
		scalaStruct(listaSpesa, *&totElemLista, i);
		*totAlimenti=*totAlimenti+1;
	}
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
			printf("%s\t%s\t%2d.%2d.%4d\t%d\n", dispensa[i].nome, dispensa[i].categoria, dispensa[i].quantita, dispensa[i].scadenza.gg, dispensa[i].scadenza.mm, dispensa[i].scadenza.aaaa, dispensa[i].kcal);
		}
		printf("\n");
	}else{
		puts("<!> Non è presente alcun alimento nella dispensa");
	}
}