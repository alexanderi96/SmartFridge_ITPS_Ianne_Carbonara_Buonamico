/*
mi serve una funzione per generare un menù settimanale, che generi la lista prendendo prima di tutto in considerazione gli alimenti in scadenza

verrà generato un menù settimanale in comune per tutti, nel momento in cui si incapperà in un utente coin delle intolleranze si andrà a fare un menù personalizzato per lui.
*/
#include <stdio.h>
#include <stdlib.h>
#include "various.h"
#include "ricetta.h"
#include <time.h>
#include "prodotti.h"
#include "string.h"
#include "dispensa.h"
#include "spesa.h"
#include "menuSettimanale.h"
#include "file.h"


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

	for (int i = 0; i<totGiorniSett; ++i){
		
		if(i==0){

			//andiamo ad aggiungere senza problemi la prima ricetta per il pranzo, e cerchiamo di mettere una ricetta diversa a cena (possibilmente qualcosa di leggero)
			posRic=rand()%totricette;

			menuSett[i].mattina=ricette[posRic].id_ricetta;
			 //generata a caso
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
	}
	return 1;
}

int searchCurrentMenu(Menu menuSett[], Data oggi){

	for (int i = 0; i < totGiorniSett; i++){
		if (1==compareTwoDate(oggi, menuSett[i].giorno)){
			return i;
		}
	}
	return -1;
}

int checkListandStorage(Spesa spesa[], int *totLista, Alimento dispensa[], int totAlimenti, Menu menuSettimanale[], Ricetta ricette[], int totRicette){
	Alimento temp[maxAlimenti];
	Ricetta ricettatemp;
	Data data;
	int totProdTemp=0, pos, qNecess, flag=0;
	//mettiamo il totale degli ingredienti disponibili, da confrontare con quelli richiesti dalla ricetta

	

	for (int i = 0; i < 2; ++i){
		setCurrentDate(&data, i);
		ricettatemp=ricette[searchRecipesById(menuSettimanale[searchCurrentMenu(menuSettimanale, data)].mattina, ricette, totRicette)];
		 //copio i dati della ricetta della mattina del primo giorno
		for (int k = 0; k < ricettatemp.totIngredienti; ++k){
			pos=searchAlimNocat(temp, totProdTemp, ricettatemp.ingredienti[k].nome);
			if(pos>-1){
				temp[pos].quantita=temp[pos].quantita+ricettatemp.ingredienti[k].quantita;
			}else{
				strcpy(temp[totProdTemp].nome, ricettatemp.ingredienti[k].nome);
				strcpy(temp[totProdTemp].categoria, ricettatemp.ingredienti[k].categoria);
				temp[totProdTemp].quantita=ricettatemp.ingredienti[k].quantita;
				totProdTemp++;
			}
		}
		//facciamo lo stesso per la sera
		ricettatemp=ricette[searchRecipesById(menuSettimanale[searchCurrentMenu(menuSettimanale, data)].sera, ricette, totRicette)];
		for (int k = 0; k < ricettatemp.totIngredienti; ++k){
			pos=searchAlimNocat(temp, totProdTemp, ricettatemp.ingredienti[k].nome);
			if(pos>-1){
				temp[pos].quantita=temp[pos].quantita+ricettatemp.ingredienti[k].quantita;
			}else{
				strcpy(temp[totProdTemp].nome, ricettatemp.ingredienti[k].nome);
				strcpy(temp[totProdTemp].categoria, ricettatemp.ingredienti[k].categoria);
				temp[totProdTemp].quantita=ricettatemp.ingredienti[k].quantita;
				totProdTemp++;
			}
		}
	}
	
	/*
	ora dobbiamo confrontare ogni alimento presente in temp con quello della dispensa e le relative quantità.
	Nel momento in cui non fossero sufficienti quelli presenti in dispensa dobbiamo vedere se quelli che ci mancano sono presenti nella lista della spesa.
	se sono presenti sollecitiamo l'utente a fare l'acquisto, altrimenti aggiungiamoli alla lista della spesa.
	*/

	return ifIngredientsInStorage(temp, totProdTemp, dispensa, totAlimenti, spesa, *&totLista);
}

int ifIngredientsInStorage(Alimento aliTemp[], int totAlitemp, Alimento dispensa[], int totAlimenti, Spesa spesa[], int *totLista){
	_Bool flag=0;
	int qIngre, qTotDatabase, posList; //serve ad indicarci la quantità di un determinato ingrediente
	for (int i = 0; i < totAlitemp; ++i){
		qTotDatabase=getQuantityR(dispensa, totAlimenti, aliTemp[i].nome, 0);
		qIngre=aliTemp[i].quantita - qTotDatabase; 
		if (qIngre<=0){
			//ok, questo prodotto è sufficiente.
		}else{
			if (flag!=1 || flag!=2){
				flag=1;
			}
			 //da ricordare all'utente di fare la spesa
			//andiamo a controllare nella lista della spesa se sommando anche i prodotti che vogliamo acquistare la quantità di questo prodotto è sufficiente
			posList=searchElement(spesa, *totLista, aliTemp[i].nome);
			if(posList>-1){
				//l'alimento è presente nella lista della sppesa
				qIngre=qIngre-spesa[posList].quantita;
				if (qIngre>0){
					if(flag!=2){
						flag=2; //diciamogli che abbiamo aggiunto delle cose alla sua lista della spesa.
					}
					//dobbiamo inserire la quantità mancante nella lista della spesa
					spesa[posList].quantita=spesa[posList].quantita+qIngre;
				}
			}else{
				if(flag!=2){
						flag=2; //diciamogli che abbiamo aggiunto delle cose alla sua lista della spesa.
				}
				//l'alimento non è nella lista della spesa e va aggiunto
				copyToList(spesa, *&totLista, aliTemp[i]);
			}
		}
	}

    saveList(listlocation, spesa, *totLista);
	return flag;
}

void checkTimeandcook(Ricetta ricette[], int totRicette, Menu menuSettimanale[], Alimento dispensa[], int totAlimenti, Spesa spesa[], int *totLista, Alimento database[], int *totDatabase, char elencoCategorie[][maxCatLen], int *totCat){
	Alimento aliTemp[maxAlimenti];
	Ricetta ricetta;
	Data oggi;
	setCurrentDate(&oggi, 0);
	char scelta;
	int posRic;
	_Bool flag=1;
	if(11<=oggi.hh && oggi.hh<15){
		ricetta=ricette[searchRecipesById(menuSettimanale[searchCurrentMenu(menuSettimanale, oggi)].mattina, ricette, totRicette)];
        printf("E' ora di pranzo!, il pasto consigliato in questo momento e': %s\n", ricetta.nome);
            
    }else if(19<=oggi.hh && oggi.hh<=22){
    	ricetta=ricette[searchRecipesById(menuSettimanale[searchCurrentMenu(menuSettimanale, oggi)].sera, ricette, totRicette)];
        printf("E' ora di cena!, il pasto consigliato in questo momento e': %s\n", ricetta.nome);
    }else{
    	return;
    }

    copyIngredienttoAliment(aliTemp, ricetta.ingredienti, ricetta.totIngredienti);

    while(0!=ifIngredientsInStorage(aliTemp, ricetta.totIngredienti, dispensa, totAlimenti, spesa, *&totLista)){
    	puts("Purtroppo non hai a disposizione tutti gli alimenti per cucinare questa ricetta e di conseguenza sono stati inseriti nella lista della spesa.\n");
    	if((12<=oggi.hh && oggi.hh<14) || (19<=oggi.hh && oggi.hh<21)){
    		while(flag){
    			fputs("Hai ancora a disposizione poco tempo per andare a comprare gli alimenti che ho inserito nella lista della spesa.\n"
    				"1. Comunica alimenti acquistati\n"
    				"2. Fai una ricetta alternativa\n"
    				"3. Visita justeat.it per ordinare qualcosa (e vai al menu' principale)\n\n"
    				"0. Vai al menu' principale\n"
    				">>> ", stdout);
 				scelta=getchar();

        		clearBuffer();	
        		system("@cls||clear");
        		switch(scelta){
        			case '1':
        				mainmenusel4(dispensa, &totAlimenti, spesa, *&totLista, database, *&totDatabase, elencoCategorie, *&totCat);
        			break;
        			case '2':
        				posRic=searchRecipesById(getPossibleRepice(ricette, totRicette, dispensa, totAlimenti), ricette, totRicette);
        				if(posRic>-1){
        					printf("mo, questaricetta è Purtroppo valida %s\n", ricette[posRic].nome);
        					getchar();

        				}else{
        					puts("Purtroppo non puoi preparare nessuna delle ricette presenti in memoria con gli alimenti presenti in dispensa\n"
        						"Premi invio per tornare al menu principale . . .\n");
        					getchar();
        					return;
        				}
        			break;
        			case '3':
        				return;
        			break;
        			case '0':
        				return;
        			break;
        			default:
        			break;

        		}
    		}
    		flag=1;
    	}
    	puts("E'anche troppo tardi per andare a fare la spesa.\n"
    		"Visita justeat.it per ordinare qualcosa\n\n"
    		"Premi invio per andare al menu principale . . .\n");
    	getchar();
    	return;
    }
   	while(flag){
   		fputs("Vuoi cominciare a cucinare? s/n\n"
   			">>> ", stdout);
   		scelta=getchar();

        clearBuffer();	
        system("@cls||clear");
   		switch(scelta){
   			case 's':
   				startCooking();
   			break;
   			case 'n':
   				return;
   			break;
   			default:
   			break;
   		}
   	}
}

void startCooking(){

}

//funzione usata per convertire alimenti in ingredienti
void copyIngredienttoAliment(Alimento alimenti[], Ingredienti ingredienti[], int dimensione){
	for (int i = 0; i < dimensione; ++i){
		strcpy(alimenti[i].nome, ingredienti[i].nome);
		strcpy(alimenti[i].categoria, ingredienti[i].categoria);
		alimenti[i].quantita=ingredienti[i].quantita;
	}
}