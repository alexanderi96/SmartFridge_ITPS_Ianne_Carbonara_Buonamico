#ifndef VARIOUS_H
#define VARIOUS_H

//contiene tutte le strutture del programma e varie costanti

#define maxUtenti 10
#define maxAlimenti 50
#define maxRicette 20
#define maxIngredienti 20
#define maxCatLen 25
#define totCategorie 50

//struttura creata per la gestione delle date
typedef struct{
	int gg;
	int mm;
	int aaaa;
}Data;

typedef struct{
    char nome[50];
	char categoria[50];
	Data scadenza;
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
    char intopos[50];
    int totinto;
    char intolleranze[maxCatLen][maxCatLen];
}Utente;

typedef struct{
	char nome[50];
	char categoria[50];
	int quantita;
}Spesa;

typedef struct{
    char nome[50];
	char categoria[50];
	//Intolleranze intolleranze[maxINtolleranze];
	int quantita;
	int kcal;
}Ingredienti;

typedef struct{
	char nome[50];
	char paese[50];
	char ingrePos[100]; //collegamento al file degli ingredienti
	Ingredienti ingredienti[maxIngredienti];
	int totIngredienti; 
	char prepaPos[100]; //collegamento al nome del file che contiene la preparazione
}Ricetta;

void clearBuffer();
void make_directory(const char* name);
void setCurrentDate(Data *data, int giorniSupp);

extern const char accountlocation[];
extern const char listlocation[];
extern const char dispensalocation[];
extern const char repiceslocation[];
extern const char databasedir[];
extern const char notificationsdir[];
extern const char ricettedir[];
extern const char ingreDir[];
extern const char intoDir[];
extern const char databaseAlimenti[];
extern const char catLocation[];
extern const char notCatLocation[];
extern const char notRicLocation[];
extern const char notAlimLocation[];
extern const char ricetteAppdir[];
extern const char databaseAlimApp[];
extern const char notlistlocation[];
extern const char menulocation[];
extern const char accountdir[];

#endif