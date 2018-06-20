/*
mi serve una funzione per generare un menù settimanale, che generi la lista prendendo prima di tutto in considerazione gli alimenti in scadenza

verrà generato un menù settimanale in comune per tutti, nel momento in cui si incapperà in un utente coin delle intolleranze si andrà a fare un menù personalizzato per lui.
*/
#include <stdio.h>
#include "various.h"


int generaMenu(Menu menuSett[], Ricetta ricette[], int totricette){
	/*
	cosa ci serve ? creare un menù settimanale in maniera casuale adatto a tutti gli utenti
	nel momento in cui si riscontrano delle intolleranze andiamo a modificare il menù per quella singola persona
	andando a sostituire gli alimenti problematici con alimenti adatti 
		METODI DI SALVATAGGIO
		-su un nuovo file
		-non salviamo su file, ma nel momento in cui noi avremo bisogno di mostrare un altro alimento
		 comunicheremo semplcemente l'alimento adatto a quella persona in quella determinata occasione

	*/
	char tipoDieta;
	int i=0, posRic;
	_Bool flag=1;
	while(flag){
		fputs("Procedura di generazione menu' settimanale\n\n"
			"1. Genera una dieta ipocalorica (circa 1200 kcal al giorno)\n"
			"2. Genera un menu' senza particolari accorgimenti\n\n"
			">>> ", stdout);
		tipoDieta=getchar();
		switch(tipoDieta){
			case '1':
				//generazione dieta ipocalorica
			break;
			case '2':
				//generazione menù normalissimo
				while(i<totGiorniSett){
					posRic=generaRandom(totricette);//generata a caso
					if(i==0){
						//andiamo ad aggiungere senza problemi la prima ricetta per il pranzo, e cerchiamo di mettere una ricetta diversa a cena (possibilmente qualcosa di leggero)
						menuSett[i].mattina=ricette[posRic].id_ricetta;
						return 1;
					}
				}
			break;
			default:
			break;
		}
	}
	

}