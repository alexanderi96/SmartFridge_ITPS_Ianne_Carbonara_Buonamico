#include <stdio.h>
#include "account.h"
#include "file.h"


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


int saveAccount(const char nome[], Utente utneti[], int totUtenti){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
        fprintf(pf, "%d\n", totUtenti);
        for (int i = 0; i < totUtenti; ++i){
            //stampa di username, password, admin, nome, cognome ed età
            fprintf(pf, "%s %s %d %s %s %d\n", utneti[i].user, utneti[i].password, utneti[i].isadmin, utneti[i].nome, utneti[i].cognome, utneti[i].eta);
        }
        fclose(pf);
        return 1;
    }
}


int saveStorage(const char nome[], Alimento dispensa[], int totAlimenti){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "w"))){
        fclose(pf);
        return 0;
    }else{
        fprintf(pf, "%d\n", totAlimenti);
        for (int i = 0; i < totAlimenti; ++i){
            //stampa di nome, caegoria, data di scadenza, data di apertura, giorni max util, quantità, kcal
            fprintf(pf, "%s %s %d %d %d %d %d\n", dispensa[i].nome, dispensa[i].categoria, dispensa[i].scadenza, dispensa[i].apertura, dispensa[i].giorniMaxUtil, dispensa[i].quantita, dispensa[i].kcal);
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
            fprintf(pf, "%s %s %d\n", spesa[i].nome, spesa[i].categoria, spesa[i].quantita);
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
            fscanf(pf, "%s %s %d %s %s %d\n", utenti[i].user, utenti[i].password, &utenti[i].isadmin, utenti[i].nome, utenti[i].cognome, &utenti[i].eta);
        }
    }
    return 1;
}

int loadStorage(const char nome[], Alimento dispensa[], int *totAlimenti){
    FILE *pf;
    if(NULL==(pf=fopen(nome, "r"))){
        fclose(pf);
        return 0;
    }else{
        fscanf(pf, "%d", *&totAlimenti);;
        for (int i = 0; i < *totAlimenti; ++i){
            fscanf(pf, "%s %s %6d %6d %d %d %d\n", dispensa[i].nome, dispensa[i].categoria, &dispensa[i].scadenza, &dispensa[i].apertura, &dispensa[i].giorniMaxUtil, &dispensa[i].quantita, &dispensa[i].kcal);
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
            fscanf(pf, "%s %s %d\n", spesa[i].nome, spesa[i].categoria, &spesa[i].quantita);
        }
    }
    fclose(pf);
    return 1;
}

int loadRecipes(const char nome[], Ricetta ricette[], int *totRicette){
    puts("it works");
    return 1;
}

int saveRecipes(const char nome[], Ricetta ricette[], int totRicette){
    puts("it works");
    return 1;
}
