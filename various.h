#ifndef VARIOUS_H
#define VARIOUS_H

//contiene tutte le strutture del programma e varie costanti

#define maxUtenti 100
#define maxAlimenti 500
#define maxRicette 100
#define maxIngredienti 100
#define maxCatLen 50
#define totCategorie 50
#define totGiorniSett 7

//struttura creata per la gestione delle date
typedef struct{
	int gg;
	int mm;
	int aaaa;
}Data;

typedef struct{
	Data giorno;
	int mattina;
	int sera;
}Menu; //questa struttura definisce il menù relativo ad un singolo giorno con data di validità e id della ricetta.

typedef struct{
	int id_alimento;
    char nome[50];
	char categoria[50];
	Data scadenza;
	int giorniMaxUtil; //permette di capire quanti giorni può rimanere aperto un prodotto dopo l'apertura 
	int quantita;
	int kcal; //relative a 100 g/ml di prodotto
}Alimento;

typedef struct{
	int id_utente;
    char user[25];
    char nome[25];
    char cognome[25];
    char password[25];
    int eta;
    _Bool isadmin;
    char intopos[50];
    int totinto;
    char intolleranze[totCategorie][maxCatLen];
}Utente;

typedef struct{
	int id_acquisto;
	char nome[50];
	char categoria[50];
	int quantita;
}Spesa;

typedef struct{
	int id_ingredienti;
    char nome[50];
	char categoria[50];
	int quantita; //espressa in g/ml
	int kcal; //kcal per la quantità di prodotto necessaria
}Ingredienti;

typedef struct{
	int id_ricetta;
	char nome[50];
	char paese[50];
	char ingrePos[100]; //collegamento al file degli ingredienti
	Ingredienti ingredienti[maxIngredienti];
	int totIngredienti; 
	char prepaPos[100]; //collegamento al nome del file che contiene la preparazione
	int tempoPrep;
	int nVolteUs; //numero di volte che una ricetta è stata cucinata.
}Ricetta;

void clearBuffer();
void make_directory(const char* name);
void setCurrentDate(Data *data, int giorniSupp);
int checkIdPresence(int elencoid[], int totElem, int nextId);
int generaRandom(int seme);

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