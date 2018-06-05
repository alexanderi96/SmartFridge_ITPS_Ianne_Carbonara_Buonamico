#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "spesa.h"
#include "various.h"
#include "file.h"

void showList(Spesa Elementlista[], int totElem){
	if (totElem>0){
		printf("Nome\tCategoria\tQuantità\n");
		for (int i = 0; i < totElem; ++i){
			printf("%s\t%s\t%d\n", Elementlista[i].nome, Elementlista[i].categoria, Elementlista[i].quantita);
		}
		printf("\n");
	}else{
		puts("<!> Non è presente alcun alimento nella lista della spesa");
	}
}

void showCategories(char elencoCategorie[][maxCatLen], int totCat){
	puts("Elenco categorie\n");
	for (int i = 0; i < totCat; ++i){
		printf("%s\n", elencoCategorie[i]);
	}
	puts("");
}

void showAliments(Alimento database[], int totDatabase, char categoria[]){
	puts("Elenco categorie\n");
	for (int i = 0; i < totDatabase; ++i){
		if (strcmp(database[i].categoria, categoria)==0){
			printf("%s %d %d\n", database[i].nome, database[i].kcal, database[i].giorniMaxUtil);
		}
	}
}

int addtoListGuided(Spesa Elementlista[], int totElem, char elencoCattgorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase){
    char categoriaTemp[maxCatLen], scelta, alimentsTemp[maxCatLen];
    int pos, num;
    _Bool flag=0;
    while(!flag){
    	flag=1;
    	printf("ciao\n");
    	showCategories(elencoCattgorie, *totCat);
	    printf("Che tipo di prodotto vuoi aggiungere?\n");
    	scanf("%s", categoriaTemp);
		clearBuffer(); 
		system("@cls||clear");
	    //andiamo a mostrare solo gli alimenti possibili presenti nella categoria 
	    if (searchCat(elencoCattgorie, maxCatLen, categoriaTemp)<0){
	    	system("@cls||clear");
	    	fputs("<!> Categoria non presente\n\n"
	    		"Vuoi creare una nuova categoria? s/n\n"
	    		">>> ", stdout);
	    		while(scelta!='s' || scelta!='n' && flag){
   		 			scelta = getchar();
					clearBuffer(); 
    				switch(scelta){
    					case 's':
        					strcpy(database[*totDatabase].categoria, categoriaTemp);
        					fputs("Quale è il nome del nuovo alimento da aggiungere al database?\n"
        						">>> ", stdout);
        					scanf("%s", alimentsTemp);
							clearBuffer(); 
							system("@cls||clear");
							pos = searchAlimNocat(database, *totDatabase, alimentsTemp);
							if (pos<0){
    							strcpy(database[*totDatabase].nome, alimentsTemp);
        						fputs("Inserisci la quantità di kcalorie del suddetto prodotto\n"
        							">>> ", stdout);
	        					scanf("%d", &database[*totDatabase].kcal);
    	    					clearBuffer(); 
								system("@cls||clear");
        						fputs("Per quanti giorni puo essere tenuto in frigo il prodotto prima che debba essere buttato?\n"
        							">>> ", stdout);
	        					scanf("%d", &database[*totDatabase].giorniMaxUtil);
    	    					clearBuffer(); 
								system("@cls||clear");
								strcpy(elencoCattgorie[*totCat], categoriaTemp);
        						*totCat = *totCat+1;
        						saveCategories(catLocation, elencoCattgorie, *totCat);
	    						strcpy(Elementlista[totElem].nome, alimentsTemp);
    							strcpy(Elementlista[totElem].categoria, categoriaTemp);
        						*totDatabase= *totDatabase+1;
        						saveAlim(databaseAlimenti, database, *totDatabase);
        						fputs("Quanti ne vuoi aggiungere alla lista della spesa?\n"
    								">>> ", stdout);
     	   						scanf("%d", &Elementlista[totElem].quantita);
        						clearBuffer(); 
								system("@cls||clear");
        						return 1;
    						}else{
    							system("@cls||clear");
    							printf("<!> Il seguete alimento e' gia' presente sotto la categoria %s\n\n", database[pos].categoria);
    							flag=0;
    						}
    					break;
    					case 'n':
    						return 0;
    					break;
    					default:
    					break;
    				}
    			}
   		}else{
    		system("@cls||clear");
    		showAliments(database, *totDatabase, categoriaTemp);
    		scanf("%s", alimentsTemp);
    		if (searchAlim(database, *totDatabase, alimentsTemp, categoriaTemp)<0){
    			system("@cls||clear");
    			puts("<!> Alimento non presente\n");
    			return 0;
    		}else{
    			system("@cls||clear");
    			strcpy(Elementlista[totElem].nome, alimentsTemp);
    			strcpy(Elementlista[totElem].categoria, categoriaTemp);
    			fputs("Quanti ne vuoi aggiungere alla lista della spesa?\n"
    				">>> ", stdout);
    	    	scanf("%d", &Elementlista[totElem].quantita);
    	    	return 1;
    		}	
    	}
    }
    return 0;
}

int searchElement(Spesa Elementlista[], int totElem, char elemento[]){
	for (int i = 0; i < totElem; ++i) {
        if(0 == strcmp(elemento, Elementlista[i].nome)){
            return i;
        }
    }
    return -1;
}

int searchCat(char categorie[][maxCatLen], int totCat, char elemento[]){
	for (int i = 0; i < totCat; ++i) {
        if(0 == strcmp(elemento, categorie[i])){
            return i;
        }
    }
    return -1;
}

int searchAlim(Alimento database[], int totAlim, char elemento[], char categoria[]){
	for (int i = 0; i < totAlim; ++i) {
        if(0 == strcmp(database[i].categoria, categoria)){
            if (0 == strcmp(database[i].nome, elemento))
            {
            	return i;
            } 
        }
    }
    return -1;
} 

int searchAlimNocat(Alimento database[], int totAlim, char elemento[]){
	for (int i = 0; i < totAlim; ++i) {
        if (0 == strcmp(database[i].nome, elemento)){
            return i;
        }
    }
    return -1;
}

int rimElem(Spesa lista[], int totElem){
	char elementTemp[25], scelta;
	int nElem, pos;
	_Bool flag;
	system("@cls||clear");
	while(1){
		showList(lista, totElem);
		fputs("Quale dei seguenti alimenti vuoi rimuovere dalla lista della spesa?\n"
			">>> ", stdout);
		scanf("%s", elementTemp);
		pos = searchElement(lista, totElem, elementTemp);
		clearBuffer(); 
		system("@cls||clear");
		if(pos >= 0){
			while(!flag){
				flag = 1;
				fputs("Quanti alimenti vuoi che rimangano nella lista della spesa?\n"
					">>> ", stdout);
				scanf("%d", &nElem);
				clearBuffer();
				if(nElem == 0){
					scalaStruct(lista, totElem, pos);
					return 2;
				}
				system("@cls||clear");
				if (getQuantity(lista, totElem, elementTemp, pos) - nElem <= 0){
					fputs("Il numero di elementi che vuoi rimuovere e' maggiore/uguale del numero degli elementi presenti\n"
						"Vuoi rimuovere interamente il prodotto? s/n\n"
						"premi 0 per annullare l'operazione\n"
						">>> ", stdout);
					scelta = getchar();
					clearBuffer();
					switch(scelta){
						case 's':
							scalaStruct(lista, totElem, pos);
							return 2;
						break;
						case 'n':
							flag = 0;
							system("@cls||clear");
						break;
						case '0':
							return 0;
						break;
						default:
							flag = 0;
							system("@cls||clear");
							puts("<!> Seleziona tra s/n\n\n");
						break;
					}
				}else{
					lista[pos].quantita = lista[pos].quantita - nElem;
					getchar();
					return 1; 
				}
			}
		}else{
			puts("<!> Alimento non presente nella lista della spesa\n\n");
		}
	}
}

int getQuantity(Spesa Elementlista[], int totElem, char elemento[], int pos){
	if(pos>=0){
		return Elementlista[pos].quantita;
	}else{
		for (int i = 0; i < totElem; ++i) {
     	    if(0 == strcmp(elemento, Elementlista[i].nome)){
        	    return Elementlista[i].quantita;
        	}
    	}
	}
    return -1;
}

void scalaStruct (Spesa Elementlista[], int totElem, int startPoint){
	for (int i = startPoint; i < totElem-1; ++i){
		Elementlista[i] = Elementlista[i+1];
	}
}
