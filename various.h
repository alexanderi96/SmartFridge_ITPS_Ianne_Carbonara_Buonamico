#ifndef VARIOUS_H
#define VARIOUS_H

//contiene tutte le strutture del programma e varie costanti

#define maxUtenti 10
#define maxAlimenti 50
#define maxRicette 20

//struttura creata per la gestione delle date
typedef struct{
	int gg;
	int mm;
	int aaaa;
}Data;

typedef struct{
    char nome[25];
	char categoria[25];
	int scadenza; //per ora la data verrà considerata in questo formato intero ggmmaa es: 110796 -> 11 luglio 1996
	int apertura;
	int giorniMaxUtil; //permette di capire quanti giorni può rimanere aperto un prodotto dopo l'apertura 
	int quantita;
	int kcal;
}Alimento;

typedef struct{
    char user[25];
    char nome[25];
    char cognome[25];
    char password[25];
    int eta;
    _Bool isadmin;
}Utente;

typedef struct{
	char nome[25];
	char categoria[25];
	int quantita;
}Spesa;

typedef struct{
	char nome[25];
	char paese[25];
	char ingredienti[25]; //collegamento al file degli ingredienti
	char intolleranze[25]; //collegamento al file contenente le possibili intolleranze
	char preparazione[25]; //collegamento al nome del file che contiene la preparazione
}Ricetta;

void clearBuffer();
void make_directory(const char* name);

extern const char accountlocation[];
extern const char listlocation[];
extern const char dispensalocation[];
extern const char repiceslocation[];
extern const char databasedir[];
extern const char notificationsdir[];
extern const char ricettedir[];

#endif