#include <stdio.h>
#include <direct.h>
#include "various.h"

//definisco globalmente la posizione dei vari file
const char accountlocation[] = "./database/account.txt";
const char listlocation[] = "./database/listaspesa.txt";
const char dispensalocation[] = "./database/dispensa.txt";
const char repiceslocation[] = "./database/ricette/sommarioricette.txt";
const char databasedir[] = "database";
const char notificationsdir[] = "notifications";
const char ricettedir[] = "./database/ricette";

void clearBuffer(){
	while(getchar()!='\n');
}

void make_directory(const char* name){
   #ifdef __linux__
       mkdir(name, 777); 
   #else
       _mkdir(name);
   #endif
}