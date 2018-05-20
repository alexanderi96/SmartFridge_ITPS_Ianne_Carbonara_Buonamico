//
// Created by aless on 21/04/2018.
//

#include <mem.h>
#include <stdio.h>

int createNewFile(char nome[]){
    FILE *pf;

    pf=fopen(nome,"w");
    if(pf==NULL){
        printf("Errore durante la creazione del file.\n");
        fclose(pf);
        return 0;
    }else{
        fclose(pf);
        return 1;
    }
}

//Ricerca su file (la ricerca verrà eseguita per qualunque parola inserita dall'utente)
int searchOnFile(char word[], char file[]){
    FILE *pf=fopen(file, "r");
    char buffer[1024], temp[1024];
    printf("sono in sof\n");
    while(!feof(pf)){
        printf("ciao");
        fscanf(pf,"%s", buffer);
        if(0 == strcmp(buffer, word)){
            fclose(pf);
            printf("trovato\n");
            return 1;
        }
    }
    fclose(pf);
    return 0;
}

int searchOnTxt(char word[], char file[]){
    FILE *pf;
    pf=fopen(file, "r");
    char buffer[1024];
    while(!feof(pf)){
        fscanf(pf,"%s", buffer);
        if(0 == strcmp(buffer, word)){
            fclose(pf);
            return 1;
        }
    }
    fclose(pf);
    return 0;
}