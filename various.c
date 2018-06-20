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
	int maxgiornimese;
	
	if(tm.tm_mon+1==2){
		maxgiornimese=28;
	}else if(tm.tm_mon + 1  == 4 || tm.tm_mon + 1  == 6 || tm.tm_mon + 1 == 9 || tm.tm_mon + 1  == 11){
		maxgiornimese=30;
	}else{
		maxgiornimese=31;
	}

	if((tm.tm_mon + 1 + giorniSupp)>maxgiornimese){
		if(tm.tm_mon + 1 ==12){
			data->mm=1;
			data->aaaa=tm.tm_year + 1900 +1;	
		}else{
			data->aaaa=tm.tm_year + 1900;
				data->mm=tm.tm_mon + 1 + 1;
		}
		data->gg=giorniSupp+tm.tm_mday-maxgiornimese;
	}else{
		data->mm=tm.tm_mon + 1 ;
		data->aaaa=tm.tm_year + 1900;
		data->gg=giorniSupp+tm.tm_mday;
	}
}

// Ale cosa fai qui ?

int checkIdPresence(int elencoid[], int totElem, int nextId){
	for (int i = 0; i < totElem; ++i){
		if (elencoid[i]==nextId){
			return checkIdPresence(elencoid, totElem, nextId+1);
		}
	}
	return nextId;
}
