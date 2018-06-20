/*
mi serve una funzione per generare un menù settimanale, che generi la lista prendendo prima di tutto in considerazione gli alimenti in scadenza

verrà generato un menù settimanale in comune per tutti, nel momento in cui si incapperà in un utente coin delle intolleranze si andrà a fare un menù personalizzato per lui.
*/
#include <stdio.h>
#include <stdlib.h>
#include "various.h"
#include "ricetta.h"
#include <time.h>


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
	srand(time(NULL));
	char tipoDieta;
	int posRic, kcalSera;
	_Bool flag=1;
	while(flag){
		fputs("Procedura di generazione menu' settimanale\n\n"
			"1. Genera una dieta ipocalorica (circa 1200 kcal al giorno)\n"
			"2. Genera un menu' senza particolari accorgimenti\n\n"
			">>> ", stdout);
		tipoDieta=getchar();
		clearBuffer();
		switch(tipoDieta){
			case '1':
				//generazione dieta ipocalorica
			break;
			case '2':
				//generazione menù normalissimo
				for (int i = 0; i<totGiorniSett; ++i){
					if(i==0){
						//andiamo ad aggiungere senza problemi la prima ricetta per il pranzo, e cerchiamo di mettere una ricetta diversa a cena (possibilmente qualcosa di leggero)
						posRic=rand()%totricette;
						menuSett[i].mattina=ricette[posRic].id_ricetta; //generata a caso
						do{
							posRic=rand()%totricette;
							kcalSera=calcTotKcal(ricette[posRic]);
							menuSett[i].sera=ricette[posRic].id_ricetta;
							//printf("mattina %d sera %d kcal sera: %d\n", menuSett[i].mattina, posRic, kcalSera);
						}while(menuSett[i].mattina==menuSett[i].sera && kcalSera>500); //ripeto a generare ricette finchè non ne trovo una diversa da quella della mattina e che non sia troppo pesante... sappiamo quanto faccia male mangiare pesante la sera
							
					}else if(i==1){
						do{
							posRic=rand()%totricette;
							menuSett[i].mattina=ricette[posRic].id_ricetta;
							printf("%d\n", menuSett[i].sera);
						}while(menuSett[i].mattina==menuSett[i-1].mattina && menuSett[i].mattina==menuSett[i-1].sera);
							
						do{
							posRic=rand()%totricette;
							kcalSera=calcTotKcal(ricette[posRic]);
							menuSett[i].sera=ricette[posRic].id_ricetta;
						}while(menuSett[i].sera==menuSett[i-1].sera && menuSett[i].sera==menuSett[i-1].mattina &&
							menuSett[i].mattina==menuSett[i].sera && kcalSera>500);						
					}else{
						do{
							posRic=rand()%totricette;
							menuSett[i].mattina=ricette[posRic].id_ricetta;
						}while(menuSett[i].mattina==menuSett[i-1].mattina && menuSett[i].mattina==menuSett[i-1].sera &&
							menuSett[i].mattina==menuSett[i-2].mattina && menuSett[i].mattina==menuSett[i-2].sera);
							
						do{
							posRic=rand()%totricette;
							kcalSera=calcTotKcal(ricette[posRic]);
							menuSett[i].sera=ricette[posRic].id_ricetta;
						}while(menuSett[i].sera==menuSett[i-1].sera && menuSett[i].sera==menuSett[i-1].mattina &&
							menuSett[i].sera==menuSett[i-2].sera && menuSett[i].sera==menuSett[i-2].mattina &&
							menuSett[i].mattina==menuSett[i].sera && kcalSera>500);	
					}
					setCurrentDate(&menuSett[i].giorno, i); //imposto la data di validità della ricetta appena generata
					printf("%d.%d.%d\n", menuSett[i].giorno.gg, menuSett[i].giorno.mm, menuSett[i].giorno.aaaa);
				}
				return 1;
			break;
			default:
			break;
		}
	}
	

}