#include <stdio.h>
#include <direct.h>
#include "various.h"

//definisco globalmente la posizione dei vari file
const char accountlocation[] = "./database/account.txt";
const char listlocation[] = "./database/listaspesa.txt";
const char dispensalocation[] = "./database/dispensa.txt";
const char databaseAlimenti[] = "./database/databaseAlimenti.txt";
const char catLocation[] = "./database/categorie.txt";
const char repiceslocation[] = "./database/ricette/sommarioricette.txt";

const char notCatLocation[] = "./notifications/notCat.txt";
const char notRicLocation[] = "./notifications/notRic.txt";
const char notAlimLocation[] = "./notifications/notAlim.txt";
const char databaseAlimApp[] = "./notifications/databaseAlimApp.txt";
const char notlistlocation[] = "./notifications/listaspesa.txt";

//definisco globalmente la posizione delle varie sottocartelle
const char databasedir[] = "database";
const char notificationsdir[] = "./notifications";
const char ricettedir[] = "./database/ricette/";

const char ricetteAppdir[] = "./notifications/ricette/";


//pulisce il buffer imput, non avremo più problemi del tipo "inserisci un valore corretto" dopo aver messo qualcosa in input
void clearBuffer(){
	while(getchar()!='\n');
}

//finzione utilizzata per la creazione di cartelle nella root del sorgente (non volevo avere file messi a caso nella root del programma)
void make_directory(const char* name){
   #ifdef __linux__
       mkdir(name, 777); 
   #else
       _mkdir(name);
   #endif
}