#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "various.h"
#include "ingrediente.h"
#include "spesa.h"
#include "file.h"

int addIngredientsGuided(Ingredienti ingredienti[], int totIngredienti, char elencoCattgorie[][maxCatLen], int *totCat, Alimento database[], int *totDatabase){
    char categoriaTemp[maxCatLen], scelta, alimentsTemp[maxCatLen];
    int pos, num;
    _Bool flag=0;
    while(!flag){
    	flag=1;
    	showCategories(elencoCattgorie, *totCat);
	    puts("Che tipo di ingrediente vuoi aggiungere?");
    	scanf("%s", categoriaTemp);
		clearBuffer(); 
		system("@cls||clear");
	    //andiamo a mostrare solo gli alimenti possibili presenti nella categoria
	    pos=searchCat(elencoCattgorie, maxCatLen, categoriaTemp);
	    if (pos<0){
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

	    						

        						saveAlim(databaseAlimenti, database, *totDatabase);

        						*totDatabase= *totDatabase+1;
        						fputs("Quanti te ne servono per questa ricetta?\n"
    								">>> ", stdout);
     	   						scanf("%d", &ingredienti[totIngredienti].quantita);
     	   						ingredienti[totIngredienti].kcal=database[*totDatabase].kcal*ingredienti[totIngredienti].quantita;
     	   						strcpy(ingredienti[totIngredienti].nome, alimentsTemp);
    							strcpy(ingredienti[totIngredienti].categoria, categoriaTemp);
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
    		fputs("Quale dei seguenti alimenti vuoi aggiungere?\n"
        		">>> ", stdout);
    		scanf("%s", alimentsTemp);
    		pos=searchAlim(database, *totDatabase, alimentsTemp, categoriaTemp);
    		if (pos<0){
    			system("@cls||clear");
    			puts("<!> Alimento non presente\n");
    			return 0;
    		}else{
    			system("@cls||clear");
    			strcpy(ingredienti[totIngredienti].nome, alimentsTemp);
    			strcpy(ingredienti[totIngredienti].categoria, categoriaTemp);
    			fputs("Quanti te ne servono per questa ricetta?\n"
    				">>> ", stdout);
     			scanf("%d", &ingredienti[totIngredienti].quantita);
     			ingredienti[totIngredienti].kcal=database[pos].kcal*ingredienti[totIngredienti].quantita;
    	    	return 1;
    		}	
    	}
    }
    return 0;
}

//inserimento guidato di ingredienti in attesa di approvazione
int addIngredientsAppGuided(Ingredienti ingredienti[], int totIngredienti, char elencoCattgorie[][maxCatLen], int totCat, Alimento database[], int totDatabase, char elencoCatApp[][maxCatLen], int *totCatApp, Alimento alimApp[], int *totAlimApp){
    char categoriaTemp[maxCatLen], scelta, alimentsTemp[maxCatLen];
    int pos, num;
    _Bool flag=0;
    while(!flag){
    	flag=1;
    	showCategories(elencoCattgorie, totCat);
	    puts("Che tipo di ingrediente vuoi aggiungere?");
    	scanf("%s", categoriaTemp);
		clearBuffer(); 
		system("@cls||clear");
	    //andiamo a mostrare solo gli alimenti possibili presenti nella categoria
	    pos=searchCat(elencoCattgorie, maxCatLen, categoriaTemp);
	    if (pos<0){
	    	system("@cls||clear");
	    	fputs("<!> Categoria non presente\n\n"
	    		"Vuoi creare una nuova categoria? s/n\n"
	    		">>> ", stdout);
	    		while(scelta!='s' || scelta!='n' && flag){
   		 			scelta = getchar();
					clearBuffer(); 
    				switch(scelta){
    					case 's':
        					strcpy(alimApp[*totAlimApp].categoria, categoriaTemp);
        					fputs("Quale è il nome del nuovo alimento da aggiungere al database?\n"
        						">>> ", stdout);
        					scanf("%s", alimentsTemp);
							clearBuffer(); 
							system("@cls||clear");
							pos = searchAlimNocat(database, totDatabase, alimentsTemp);
							if (pos<0){
    							strcpy(alimApp[*totAlimApp].nome, alimentsTemp);
        						fputs("Inserisci la quantità di kcalorie del suddetto prodotto\n"
        							">>> ", stdout);
	        					scanf("%d", &alimApp[*totAlimApp].kcal);
    	    					clearBuffer(); 
								system("@cls||clear");
        						fputs("Per quanti giorni puo essere tenuto in frigo il prodotto prima che debba essere buttato?\n"
        							">>> ", stdout);
	        					scanf("%d", &alimApp[*totAlimApp].giorniMaxUtil);
    	    					clearBuffer(); 
								system("@cls||clear");
								strcpy(elencoCatApp[*totCatApp], categoriaTemp);
        						*totCatApp = *totCatApp+1;

        						saveCategories(notCatLocation, elencoCatApp, *totCatApp);
        						saveAlim(databaseAlimApp, alimApp, *totAlimApp);

        						*totAlimApp= *totAlimApp+1;
        						fputs("Quanti te ne servono per questa ricetta?\n"
    								">>> ", stdout);
     	   						scanf("%d", &ingredienti[totIngredienti].quantita);
     	   						ingredienti[totIngredienti].kcal=alimApp[*totAlimApp].kcal*ingredienti[totIngredienti].quantita;
     	   						strcpy(ingredienti[totIngredienti].nome, alimentsTemp);
    							strcpy(ingredienti[totIngredienti].categoria, categoriaTemp);
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
    		showAliments(database, totDatabase, categoriaTemp);
    		fputs("Quale dei seguenti alimenti vuoi aggiungere?\n"
        		">>> ", stdout);
    		scanf("%s", alimentsTemp);
    		pos=searchAlim(database, totDatabase, alimentsTemp, categoriaTemp);
    		if (pos<0){
    			system("@cls||clear");
    			puts("<!> Alimento non presente\n");
    			return 0;
    		}else{
    			system("@cls||clear");
    			strcpy(ingredienti[totIngredienti].nome, alimentsTemp);
    			strcpy(ingredienti[totIngredienti].categoria, categoriaTemp);
    			fputs("Quanti te ne servono per questa ricetta?\n"
    				">>> ", stdout);
     			scanf("%d", &ingredienti[totIngredienti].quantita);
     			ingredienti[totIngredienti].kcal=database[pos].kcal*ingredienti[totIngredienti].quantita;
    	    	return 1;
    		}	
    	}
    }
    return 0;
}

int searchIngredient(Ingredienti ingredienti[], int totIngredienti, char elemento[]){
	for (int i = 0; i < totIngredienti; ++i) {
        if(0 == strcmp(elemento, ingredienti[i].nome)){
            return i;
        }
    }
    return -1;
}