#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "account.h"
#include "file.h"
#include "various.h"


int createNewFile(const char nome[]){
    FILE *pf;

    pf=fopen(nome,"w");
    if(pf==NULL){
        fclose(pf);
        return 0;
    }else{
        fprintf(pf, "0\n");
        fclose(pf);
        return 1;
    }
}


int saveAccount(const char nome[], Utente utenti[], int totUtenti){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
        fprintf(pf, "%d\n", totUtenti);
        for (int i = 0; i < totUtenti; ++i){
            //stampa di username, password, admin, nome, cognome ed età     
            fprintf(pf, "%d %s %s %d %s %s %2d %2d %4d %s %d\n", utenti[i].id, utenti[i].user, utenti[i].password, utenti[i].isadmin, utenti[i].nome, utenti[i].cognome, utenti[i].eta.gg, utenti[i].eta.mm, utenti[i].eta.aaaa, utenti[i].intopos, utenti[i].totinto);
            saveInto(utenti[i].intopos, utenti[i].intolleranze, utenti[i].totinto);
        }
        fclose(pf);
        return 1;
    }
}


int saveStorage(const char nome[], Dispensa dispensa[], int totAlimenti){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
        fprintf(pf, "%d\n", totAlimenti);
        for (int i = 0; i < totAlimenti; ++i){
            //stampa di nome, caegoria, data di scadenza, data di apertura, giorni max util, quantità, kcal
            fprintf(pf, "%d %d %2d.%2d.%4d %d %d %d\n", dispensa[i].id, dispensa[i].id_alimento, dispensa[i].scadenza.gg, dispensa[i].scadenza.mm, dispensa[i].scadenza.aaaa, dispensa[i].giorniMaxUtil, dispensa[i].quantita, &dispensa[i].kcal);
        }
    }
    fclose(pf);
    return 1;
}

int saveList(const char nome[], Spesa spesa[], int totElem){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
        fprintf(pf, "%d\n", totElem);
        for (int i = 0; i < totElem; ++i){
            //stampa di nome, caegoria, data di scadenza, data di apertura, giorni max util, quantità, kcal
            fprintf(pf, "%d %d %d\n", spesa[i].id, spesa[i].id_alimento, spesa[i].quantita);
        }
    }
    fclose(pf);
    return 1;
}



int getDim(const char nome[]){
    int tot;
    FILE *pf;
    if(NULL==(pf=fopen(nome, "r"))){
        fclose(pf);
        return 0;
    }else{
        fscanf(pf, "%d", &tot);
    }
    fclose(pf);
    return tot;
}

int loadAccount(const char nome[], Utente utenti[], int *totUtenti){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "r"))){
        fclose(pf);
        return 0;
    }else{
        fscanf(pf, "%d", *&totUtenti);
        for (int i = 0; i < *totUtenti; ++i){

            fscanf(pf, "%d %s %s %d %s %s %2d %2d %4d %s %d\n", &utenti[i].id, utenti[i].user, utenti[i].password, &utenti[i].isadmin, utenti[i].nome, utenti[i].cognome, &utenti[i].eta.gg, &utenti[i].eta.mm, &utenti[i].eta.aaaa, utenti[i].intopos, &utenti[i].totinto);
            loadInto(utenti[i].intopos, utenti[i].intolleranze, utenti[i].totinto);
        }
    }
    return 1;
}

int loadStorage(const char nome[], Dispensa dispensa[], int *totAlimenti){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "r"))){
        fclose(pf);
        return 0;
    }else{
        fscanf(pf, "%d", *&totAlimenti);;
        for (int i = 0; i < *totAlimenti; ++i){
            fscanf(pf, "%d %d %2d.%2d.%4d %d %d %d\n", &dispensa[i].id, &dispensa[i].id_alimento, &dispensa[i].scadenza.gg, &dispensa[i].scadenza.mm, &dispensa[i].scadenza.aaaa, &dispensa[i].giorniMaxUtil, &dispensa[i].quantita, &dispensa[i].kcal);
        }
    }
    fclose(pf);
    return 1;
}

int loadList(const char nome[], Spesa spesa[], int *totElem){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "r"))){
        fclose(pf);
        return 0;
    }else{
        fscanf(pf, "%d", *&totElem);
        for (int i = 0; i < *totElem; ++i){
            fscanf(pf, "%d %d %d\n", &spesa[i].id, &spesa[i].id_alimento, &spesa[i].quantita);
        }
    }
    fclose(pf);
    return 1;
}

int loadRecipes(const char nome[], Ricetta ricette[], int *totRicette){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "r"))){
        fclose(pf);
        return 0;
    }else{
        fscanf(pf, "%d", *&totRicette);
        for (int i = 0; i < *totRicette; ++i){
            fscanf(pf, "%d %s %s %s %d %s %d\n", &ricette[i].id, ricette[i].nome, ricette[i].paese, ricette[i].ingrePos, &ricette[i].totIngredienti, ricette[i].prepaPos, &ricette[i].tempoPrep);
            loadIngredients(ricette[i].ingrePos, ricette[i].ingredienti, ricette[i].totIngredienti);
        }
    }
    fclose(pf);
    return 1;
}


int saveRecipes(const char nome[], Ricetta ricette[], int totRicette){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
        fprintf(pf, "%d\n", totRicette);
        for (int i = 0; i < totRicette; ++i){
            //stampa di nome, caegoria, data di scadenza, data di apertura, giorni max util, quantità, kcal
            fprintf(pf, "%s %s %s %d %s %d\n", ricette[i].nome, ricette[i].paese, ricette[i].ingrePos, ricette[i].totIngredienti, ricette[i].prepaPos, ricette[i].tempoPrep);
            saveIngredients(ricette[i].ingrePos, ricette[i].ingredienti, ricette[i].totIngredienti);
        }
    }
    fclose(pf);
    return 1;
}

int saveIngredients(const char nome[], Ingredienti ingredienti[], int totIngredienti){
	FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
        for (int i = 0; i < totIngredienti; ++i){
            //stampa di nome, caegoria, data di scadenza, data di apertura, giorni max util, quantità, kcal
            fprintf(pf, "%d %d %d %d\n", ingredienti[i].id, ingredienti[i].id_alimento, ingredienti[i].quantita, ingredienti[i].kcal);
        }
    }
    fclose(pf);
    return 1;
}

int loadIngredients(const char nome[], Ingredienti ingredienti[], int totIngredienti){
	FILE *pf;
    if(NULL==(pf=fopen(nome, "r"))){
        fclose(pf);
        printf("%s\n", nome);
        return 0;
    }else{
        for (int i = 0; i < totIngredienti; ++i){
            fscanf(pf, "%d %d %d %d\n", &ingredienti[i].id, &ingredienti[i].id_alimento, &ingredienti[i].quantita, &ingredienti[i].kcal);
        }
    }
    fclose(pf);
    return 1;
}

int loadDatabaseAlimenti(const char nome[], Alimento database[], int *numeroAlimenti){
	FILE *pf;
    if(NULL==(pf=fopen(nome, "r"))){
        fclose(pf);
        return 0;
    }else{
    	fscanf(pf, "%d\n", *&numeroAlimenti);
        for (int i = 0; i < *numeroAlimenti; ++i){
            fscanf(pf, "%d %d %s %d %d\n", &database[i].id, &database[i].categoria, database[i].nome, &database[i].kcal, &database[i].giorniMaxUtil);
        }
    }
    fclose(pf);
    return 1;
}

int loadSingleDatabaseAlimenti(const char nome[], Alimento database, int id_alimento){
    FILE *pf;
    int totAlimenti;
    Alimento buffer;
    if(NULL==(pf=fopen(nome, "r"))){
        fclose(pf);
        return 0;
    }else{
        fscanf(pf, "%d\n", &totAlimenti);
        for (int i = 0; i < totAlimenti; ++i){
            fscanf(pf, "%d %d %s %d %d\n", &buffer.id, &buffer.categoria, buffer.nome, &buffer.kcal, &buffer.giorniMaxUtil);
            if(buffer.id==id_alimento){
                database=buffer;
                fclose(pf);
                return 1;
            }
        }
    }
    fclose(pf);
    return 0;
}

int loadCategories(const char nome[], Categorie categorie[], int *totCat){
	FILE *pf;
	if (NULL==(pf=fopen(nome, "r"))){
		puts("<!> Non è presente alcuna categoria");
        fclose(pf);
        return
	}else{
		fscanf(pf, "%d\n", *&totCat);
		for (int i = 0; i < *totCat; ++i){
			fscanf(pf, "%d %s\n", &categorie[i].id, categorie[i].categoria);
		}
	}
	fclose(pf);
	return 1;	
}

int loadSingleCategories(const char nome[], Categorie categoria, int categoria){
    FILE *pf;
    Categorie buffer;
    int totCat;
    if (NULL==(pf=fopen(nome, "r"))){
        puts("<!> Non è presente alcuna categoria");
        fclose(pf);
        return 0;
    }else{
        fscanf(pf, "%d\n", &totCat);
        for (int i = 0; i < totCat; ++i){
            fscanf(pf, "%d %s\n", &buffer.id, buffer.categoria);
            if (buffer.id==categoria){
                categoria=buffer;
                fclose(pf);
                return 1;
            }
        }
    }
    fclose(pf);
    return 0;   
}

int saveCategories(const char nome[], Categorie categorie[], int totCat){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
        fprintf(pf, "%d\n", totCat);
        for (int i = 0; i < totCat; ++i){
            fprintf(pf, "%d %s\n", categorie[i].id, categorie[i].categoria);
        }
        fclose(pf);
        return 1;
    }
}

int saveAlim(const char nome[], Alimento database[], int totDatabase){
	FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
    	fprintf(pf, "%d\n", totDatabase);
        for (int i = 0; i < totDatabase; ++i){
            fprintf(pf, "%d %d %s %d %d\n", database[i].id, database[i].categoria, database[i].nome, database[i].kcal, database[i].giorniMaxUtil);
        }
    }
    fclose(pf);
    return 1;
}

int saveInto(const char nome[], int intolleranze[], int totInto){
	FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
        for (int i = 0; i < totInto; ++i){
            fprintf(pf, "%d\n", intolleranze[i]);
        }
    }
    fclose(pf);
    return 1;
}

int loadInto(const char nome[], int intolleranze[], int totInto){
	FILE *pf;
	char buffer[maxCatLen];
	if (NULL==(pf=fopen(nome, "r"))){
		return 0;
	}else{
		for (int i = 0; i < totInto; ++i){
			fscanf(pf, "%d\n", &intolleranze[i]);
		}
	}
	fclose(pf);
	return 1;
}

int loadMenu(const char nome[], int menu[]){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "r"))){
        fclose(pf);
        return 0;
    }else{
        for (int i = 0; i < totPastiSett, i=i+2){
            fscanf(pf, "%d %d\n", &menu[i], &menu[i+1]);
        }
    }
    fclose(pf);
    return 1;
}

int saveMenu(const char nome[], int menu[]){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
        for (int i = 0; i < totPastiSett, i=i+2){
            fprintf(pf, "%d %d\n", menu[i], menu[i+1]);
        }
    }
    fclose(pf);
    return 1;
}
