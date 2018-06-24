#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include "various.h"
#include <time.h>

// Questo file si occupa dell'organizzazione del programma in modo generale per non avere dei file sparsi nel programma


/* Definiamo globalmente la posizione dei vari file
*/

const char accountlocation[] = "./database/account/accountlist.txt";
const char listlocation[] = "./database/listaspesa.txt";
const char dispensalocation[] = "./database/dispensa.txt";
const char databaseAlimenti[] = "./database/databaseAlimenti.txt";
const char catLocation[] = "./database/categorie.txt";
const char repiceslocation[] = "./database/ricette/sommarioricette.txt";
const char menulocation[] = "./database/menusettimanale.txt";

/* Definiamo globalmente la posizione delle varie sottocartelle
*/

const char databasedir[] = "./database/";
const char accountdir[] = "./database/account/";
const char ricettedir[] = "./database/ricette/";

/* La seguente funzione permette di svuotare il buffer per le stringhe fornite in input
* con medesima funzione considereremo solo il primo carattere o numero inserito
*/

void clearBuffer(){
	while(getchar()!='\n');
}

/* Definiamo la funzione per la creazione di cartelle nella root del sorgente
*/

void make_directory(const char* name){
   #ifdef __linux__
       mkdir(name, 777); 
   #else
       _mkdir(name);
   #endif
}

/* La seguente funzione permette di determinare in maniera esatta la data corrente per poi visualizzarla all'interno del programma
* la data sarà visualizzata al momento del login e sarà utilizzata per le scadenze dei prodotti, quindi sarà utilizzata come un parametro
* per controllare le scadenze dei prodotti
*/

void setCurrentDate(Data *data, int giorniSupp){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int maxgiornimese, mesiAgg,anniAgg;
	
	if(tm.tm_mon+1==2){
		maxgiornimese=28;
	}else if(tm.tm_mon + 1  == 4 || tm.tm_mon + 1  == 6 || tm.tm_mon + 1 == 9 || tm.tm_mon + 1  == 11){
		maxgiornimese=30;
	}else{
		maxgiornimese=31;
	}


	data->hh=tm.tm_hour;
	data->min=tm.tm_min;
	data->mm=tm.tm_mon + 1 ;
	data->aaaa=tm.tm_year + 1900;
	data->gg=tm.tm_mday;

	data->gg=tm.tm_mday+giorniSupp;
	while(data->gg>maxgiornimese){
		data->mm++;
		data->gg=data->gg-maxgiornimese;
	}
	while(data->mm>12){
		data->aaaa++;
		data->mm=data->mm-12;
	}	
}


int checkIdPresence(int elencoid[], int totElem, int nextId){
	for (int i = 0; i < totElem; ++i){
		if (elencoid[i]==nextId){
			return checkIdPresence(elencoid, totElem, nextId+1);
		}
	}
	return nextId;
}

int compareToCurrentDate(Data data){ //ritorna 0 se la data non è passata, 1 se corrisponde -1 se è passata
	Data oggi;

	setCurrentDate(&oggi, 0);

	if(oggi.aaaa<data.aaaa){
		return 0; //la data non è ancora arrivata
	}else if(oggi.aaaa==data.aaaa){
		if(oggi.mm<data.mm){
			return 0; //la data non è ancora arrivata
		}else if(oggi.mm==data.mm){
			if(oggi.gg<data.gg){
				return 0;
			}else if(oggi.gg==data.gg){
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

int compareTwoDate(Data data1, Data data2){ //ritorna 0 se la data non è passata, 1 se corrisponde -1 se è passata
	if(data1.aaaa<data2.aaaa){
		return 0; //la data2 non è ancora arrivata
	}else if(data1.aaaa==data2.aaaa){
		if(data1.mm<data2.mm){
			return 0; //la data2 non è ancora arrivata
		}else if(data1.mm==data2.mm){
			if(data1.gg<data2.gg){
				return 0;
			}else if(data1.gg==data2.gg){
				return 1;
			}else{
				return -1;
			}
		}else{
			return -1; //la data2 è passata
		}
	}else{
		return -1; //la data2 è passata
	}
}

