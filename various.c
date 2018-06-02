#include <stdio.h>
#include <direct.h>
#include "various.h"

//definisco globalmente la posizione dei vari file
const char accountlocation[] = "./database/account.txt";
const char listlocation[] = "./database/listaspesa.txt";
const char dispensalocation[] = "./database/dispensa.txt";
const char repiceslocation[] = "./database/ricette/sommarioricette.txt";
//definisco globalmente la posizione delle varie sottocartelle
const char databasedir[] = "database";
const char notificationsdir[] = "notifications";
const char ricettedir[] = "./database/ricette";
const char ingreDir[] = "./database/ricette/ingredienti";
const char intoDir[] = "./database/ricette/intolleranze";


//pulisce il buffer imput, non avremo più problemi del tipo "inserisci un valore corretto" dopo aver messo qualcosa in input
void clearBuffer(){
	while(getchar()!='\n');
}

//finzione utilizzata per la creazione di cartelle nella root del sorgente (non volevo avere file testuali messi li a caso...)
void make_directory(const char* name){
   #ifdef __linux__
       mkdir(name, 777); 
   #else
       _mkdir(name);
   #endif
}