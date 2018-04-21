//
// Created by aless on 21/04/2018.
//

#include <mem.h>
#include <stdio.h>

int createNewBin(char nome[9]){
    FILE *pf;
    //devo sistemare la concatenazione
    strcat(nome,".bin");
    printf("cioa");
    pf=fopen(nome,"w");
    if(pf==NULL){
        printf("Errore durante la creazione del file.\n");
    }else{
        fclose(pf);
    }
    return 1;
}