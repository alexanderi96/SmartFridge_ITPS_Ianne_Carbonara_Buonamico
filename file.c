//
// Created by aless on 21/04/2018.
//

#include <mem.h>
#include <stdio.h>

int createNewCsv(char nome[]){
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

//Ricerca su file (la ricerca verrà eseguita per qualunque parola inserita dall'utente)
int searchOnFile(char word[], char file[]){
    FILE *pf;
    pf=fopen(file,"r");
    char buffer[2048];

    if(pf==NULL){
        printf("Impossibile leggere il file\n");
        return 0;
    }else{
        printf("Ricerca della parola nel file\n");
        while((fgets(buffer,2048,pf))!=NULL){
            //Ricerca della parola digitata precedentemente
            for(int i=0;i<buffer[i]!='\0';i++){
                if(buffer[i]==word[0]){
                    if(ricerca(buffer,word,i)==1){
                        //Parola trovata e avvio della funzione ricerca
                    }
                }
            }
        }
    }
    fflush(stdin);
    getchar();
    return 0;
}

int ricerca(const char *buffer, const char *word, int i){
    for(;*word!='\0';buffer++,word++){
        if(*(word+buffer)!=*word){
            return 0;
        }
    }
    return 1;
}
