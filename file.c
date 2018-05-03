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
        return 0;
    }else{
        fclose(pf);
        return 1;
    }

}

int searchOnFile(char word[]){

}